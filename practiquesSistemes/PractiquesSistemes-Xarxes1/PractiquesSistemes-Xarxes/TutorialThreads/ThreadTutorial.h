#pragma once
#include <iostream>
#include<string>
#include<thread>
#include<chrono>
#pragma region Functions Declaration Header
void PrintElapsedTime(
    std::chrono::system_clock::time_point start,
    std::chrono::system_clock::time_point end,
    std::string threadName);
void Count(unsigned long long maxCounter, std::string threadName);
void Exemple01();
void Exemple02();
void Exemple03();
void Exemple04();
void Exemple05();
void Exemple06();
void Exemple07();

#pragma endregion
#pragma region Global Variables
std::chrono::system_clock::time_point startDate;
#pragma endregion
void ThreadTutorialTest() {

    startDate = std::chrono::system_clock::now();


    int exampleUsed = 1;
    switch (exampleUsed) {
    case 1:
        Exemple01();
        break;


    case 2:
        Exemple02();
        break;
    case 3:
        Exemple03();
        break;
    case 4:
        Exemple04();
        break;
    case 5:
        Exemple05();
        break;
    case 6:
        Exemple06();
        break;
    case 7:
        Exemple07();
        break;
        
    default:
        break;
    }
    std::cout << "Example 0" << exampleUsed << "finished " << std::endl;
}

void PrintElapsedTime(
    std::chrono::system_clock::time_point start,
    std::chrono::system_clock::time_point end,
    std::string threadName){
    std::chrono::duration<double>elapsedTime = end - start;
    std::cout << "Thread:" << threadName << "-Elapsed time:"<<elapsedTime.count()<< " seconds " << std::endl;
}
void Count(unsigned long long maxCounter, std::string threadName) {
    for (unsigned long long i = 0; i<maxCounter; i++) {

    }
    std::chrono::system_clock::time_point endDate = std::chrono::system_clock::now();
    PrintElapsedTime(startDate, endDate, threadName);
}
void Exemple01() {
    unsigned long long totalCount = 100000000ull;


    std::thread* Couter1 = new std::thread(Count, totalCount, "1");
    std::thread* Couter2 = new std::thread(Count, totalCount, "2");
    std::thread* Couter3 = new std::thread(Count, totalCount, "3");

    Couter1->join();
    Couter2->join();
    Couter3->join();
    Count(totalCount, "0");
  
}
void Exemple02() {}
void Exemple03() {}
void Exemple04() {}
void Exemple05() {}
void Exemple06() {}
void Exemple07() {}
