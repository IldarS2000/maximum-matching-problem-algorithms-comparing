// Maximum Matching Problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>
#include "tests.h"

#include <exception>

int getPositiveInt(const std::string message)
{
  while (true) {
    int number = 0;
    std::cout << message;
    std::cin >> number;
    if (std::cin.fail() || number < 0) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "invalid value, positive number was expected\n";
    }
    else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return number;
    }
  }
}

int main()
{
  setlocale(LC_ALL, "Russian");
  try {
    std::cout << " Параметры тестов:\n";
    int numOfGraphs = getPositiveInt("1. количество тестируемых графов под каждое количество вершин: ");
    int numOfTestsInGraph = getPositiveInt("2. количество тестов на каждый граф: ");
    int InitialNumOfVertices = getPositiveInt("3. начальное количество вершин: ");
    int stepOfIncreasingVertices = getPositiveInt("4. шаг увеличения количества вершин: ");
    int maxNumOfVertices = getPositiveInt("5. максимальное количество вершин: ");
    std::cout << '\n';

    // исполнение тестов и вывод результатов
    test(numOfGraphs, numOfTestsInGraph, InitialNumOfVertices, stepOfIncreasingVertices, maxNumOfVertices);
  }
  catch (const std::exception &e) {
    std::cout << e.what() << '\n';
  }
  catch (...) {
    std::cout << "unknown error...\n";
  }
  return 0; 
}



