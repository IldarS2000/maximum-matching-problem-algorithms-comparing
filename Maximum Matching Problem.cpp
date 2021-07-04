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
    std::cout << " ��������� ������:\n";
    int numOfGraphs = getPositiveInt("1. ���������� ����������� ������ ��� ������ ���������� ������: ");
    int numOfTestsInGraph = getPositiveInt("2. ���������� ������ �� ������ ����: ");
    int InitialNumOfVertices = getPositiveInt("3. ��������� ���������� ������: ");
    int stepOfIncreasingVertices = getPositiveInt("4. ��� ���������� ���������� ������: ");
    int maxNumOfVertices = getPositiveInt("5. ������������ ���������� ������: ");
    std::cout << '\n';

    // ���������� ������ � ����� �����������
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



