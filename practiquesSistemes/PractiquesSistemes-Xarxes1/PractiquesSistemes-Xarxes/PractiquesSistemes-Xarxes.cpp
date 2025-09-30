// PractiquesSistemes-Xarxes.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include<string>
#include<thread>

#include "TutorialThreads/ThreadTutorial.h"
#include "Utils/ConsoleControl.h"
#include "InputSystem/InputSystem.h"



int main()
{
	InputSystem* iS = new InputSystem();
	InputSystem::KeyBinding* kb = iS->AddListener(K_1, []() {
		CC::Lock();
		std::cout << "A key pressed" << std::endl;
		CC::Unlock();
		});
	InputSystem::KeyBinding* kb = iS->AddListener(K_2, []() {
		CC::Lock();
		std::cout << "A key pressed" << std::endl;
		CC::Unlock();
		});
	InputSystem::KeyBinding* kb = iS->AddListener(K_3, []() {
		CC::Lock();
		std::cout << "A key pressed" << std::endl;
		CC::Unlock();
		});
	
	iS->StartListen();




while(true){

}


