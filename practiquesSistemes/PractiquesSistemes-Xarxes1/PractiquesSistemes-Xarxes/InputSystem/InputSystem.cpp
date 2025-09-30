#include "InputSystem.h"
#include "../Utils/ConsoleControl.h"

InputSystem::KeyBinding::KeyBinding(int key, OnKeyPress onKeyPress)
{
	_key = key;
	_onKeyPress = onKeyPress;
}

InputSystem::KeyBinding::~KeyBinding() {

}
InputSystem::InputSystem()

{

}
InputSystem::~InputSystem()
{
	for (std::pair<int, KeyBindingsList> pair : _keyBindingMap) //for each key in the map
	{
		KeyBindingsList bindinsList = pair.second;

		for (KeyBinding* keyBinding : bindinsList)
		{
			delete keyBinding;
		}
		bindinsList.clear();
	}
}

InputSystem:: KeyBinding* InputSystem::AddListener(int key, KeyBinding::OnKeyPress onKeyPress)
{
	_classMutex.lock(); //lock the
	if (_keyBindingMap.find(key) == _keyBindingMap.end()) //if the key does not exist
	{
		_keyBindingMap[key] = KeyBindingsList(); //create a new list for that key
	}
	KeyBinding* keyBinding = new KeyBinding(key, onKeyPress); //create the key binding
	_keyBindingMap[key].push_back(keyBinding); //add the key binding to the list
	_classMutex.unlock(); //unlock the

	return keyBinding;
}

void InputSystem::RemoveAndDeleteListener(KeyBinding* keyBinding)
{
	int key = keyBinding->_key;
	_classMutex.lock(); //lock the

	if(_keyBindingMap.find(key) != _keyBindingMap.end()) //if the key exists
	{
		KeyBindingsList list = _keyBindingMap[key];
		list.remove(keyBinding); //remove the key binding from the list

		delete keyBinding; //delete the key binding

		if (list.size() == 0) {
			_keyBindingMap.erase(key); //if the list is empty, remove the key from the map

		}

		
	}
	_classMutex.unlock(); //unlock the
}

void InputSystem::StartListen()
{
	_classMutex.lock(); //lock the
	if (_state != Stopped) //if the state isn't stopped
	{
		_classMutex.unlock(); //unlock the
		return; //early exit 
	
	
	}
	_state = Starting; //set the state to starting
	std::thread* listenLoopThread = new std::thread(&InputSystem::ListenLoop, this); //create a new thread to listen for key presses
	listenLoopThread->detach(); //detach the thread
	_classMutex.unlock(); //unlock the
}
void InputSystem::StopListen()
{
	_classMutex.lock(); //lock the
	if (_state != Listening) //if the state isn't listening
	{
		_classMutex.unlock(); //unlock the
		return; //early exit 
	
	
	}
	_state = Stopping; //set the state to stopping
	
	_classMutex.unlock(); //unlock the
}

void InputSystem::ListenLoop()
{
	_classMutex.lock(); //lock the

	_state = Listening; //set the state to listening
	State currentState = _state; //get the current state
	CC::ClearKeyBuffer(); //clear the key buffer

	_classMutex.unlock(); //unlock the

	while (currentState) {

		int key = CC::ReadNextKey(); //wait for a key press

		if (key != 0) {

			_classMutex.lock(); //lock the
			if (_keyBindingMap.find(key) != _keyBindingMap.end()) //if the key exists
			{
				KeyBindingsList list = _keyBindingMap[key]; //get the list of key bindings for that key
				for (KeyBinding* binding: list) //for each key binding in the list
				{
					//execute 
					std::thread* onKeyPressThread = new std::thread(binding->_onKeyPress); //create a new thread to execute the onKeyPress function
					onKeyPressThread->detach(); //detach the thread
				}
			}
			_classMutex.unlock(); //unlock the
		}

		_classMutex.lock(); //lock the
		currentState = _state; //get the current state
		_classMutex.unlock(); //Thread safe

	}

	_classMutex.lock(); //lock the
	if(_state == Stopping) //if the state is stopping
	{
		_state = Stopped; //set the state to stopped
	}
	_classMutex.unlock(); //unlock the
}
