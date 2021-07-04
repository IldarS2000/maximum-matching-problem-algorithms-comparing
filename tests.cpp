#include "tests.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

//#define DEBUG_TEST

int getKindOfGraph()
{
  std::cout << "�������� ��������� �����:\n";
  std::cout << " ���� 0: ��������� ���� � ����������� ������������� ���-�� ������ � �����\n";
  std::cout << " ���� 1: ��������� ���� � ������������ ������������� ���-�� ������ � �����\n";
  std::cout << " ���� 2: ������� ���� � ���������� ���-��� ������ � �����\n";
  std::cout << " ��� �����: ";
  int kindOfGraph;
  while (true) {
    std::cin >> kindOfGraph;
    if (std::cin.fail() || (kindOfGraph != 0 && kindOfGraph != 1 && kindOfGraph != 2)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "invalid value\n";
    }
    else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "\n";
      return kindOfGraph;
    }
  }
}

void printDataOfTests(const int numOfVertices, const double avgTimeOfKuhn,
  const double avgTimeOfHopkroftKarp, std::ostream& out = std::cout)
{
  out << "���������� ������: " << numOfVertices << '\n';
  out << "runtime Kuhn: " << avgTimeOfKuhn << " msecs\n";
  out << "runtime Hopkroft - Karp: " << avgTimeOfHopkroftKarp << " msecs\n";
  out << "-----------------------\n";
}

void uploadDataToFile(const int numVertices, const double avgTimeOfKuhn, const double avgTimeOfHopkroftKarp,
  std::ofstream& numVertices_f, std::ofstream& kuhn_f, std::ofstream& karp_f)
{
  numVertices_f << numVertices << '\n';
  kuhn_f << avgTimeOfKuhn << '\n';
  karp_f << avgTimeOfHopkroftKarp << '\n';
}

void test(const int numOfGraphs, const int numOfTestsInGraph, const int InitialNumOfVertices,
  const int stepOfIncreasingVertices, const int maxNumOfVertices)
{
  // ���������� ���������� � �����
  std::ofstream numVertices_f("numVertices.txt");
  std::ofstream kuhn_f("kuhn.txt");
  std::ofstream karp_f("karp.txt");

  // �������� ����� ����� ���������
  int kindOfGraph = getKindOfGraph();

  // ��������� � ������� ���������
  clock_t startTime = std::clock();
  for (int numOfVertices = InitialNumOfVertices;numOfVertices <= maxNumOfVertices;numOfVertices += stepOfIncreasingVertices) {
    double avgTimeOfKuhn = 0;
    double avgTimeOfHopkroftKarp = 0;
    for (int g = 0;g < numOfGraphs;++g) {  // � ������ ����������� ����� ��������� numOfGraphs ��������� ������
      BiGraph bigraph(numOfVertices, kindOfGraph); // ��������� ����������� ����� � ������������
#ifdef DEBUG_TEST
      // ������� ��������������� ����
      std::cout << "graph:\n";
      for (int i = 0;i < bigraph.graph.size();++i) {
        std::cout << i << " -- ";
        for (int j = 0;j < bigraph.graph[i].size();++j) {
          std::cout << bigraph.graph[i][j] << ' ';
        }
        std::cout << '\n';
      }
#endif
// ��������� �������� ����
      Kuhn algorithm1(bigraph);
      clock_t avgTimeInThisGraph1 = 0;
      for (int i = 0;i < numOfTestsInGraph;++i) { // ������ ���� ��������� numOfTestsInGraph ���
        clock_t startTime = std::clock();
        algorithm1.maxMatching(bigraph);
        avgTimeInThisGraph1 += std::clock() - startTime;
      }
      avgTimeOfKuhn += static_cast<long double>(avgTimeInThisGraph1) / numOfTestsInGraph;
// ��������� �������� ��������� - ����� � ��������� ���������� � ������
      HopkroftKarp algorithm2(bigraph); // ��������� ���� � ������ ��� ��� ���������
      clock_t avgTimeInThisGraph2 = 0;
      for (int i = 0;i < numOfTestsInGraph;++i) { // ������ ���� ��������� numOfTestsInGraph ���
        clock_t startTime = std::clock();
        algorithm2.maxMatching();
        avgTimeInThisGraph2 += std::clock() - startTime;
        algorithm2.clearState();
      }
      avgTimeOfHopkroftKarp += static_cast<double>(avgTimeInThisGraph2) / numOfTestsInGraph;
#ifdef DEBUG_TEST
      // ������� �������������
      std::cout << "Kuhn matching:\n";
      for (int i = 0;i < algorithm1.matching.size();++i) {
        std::cout << algorithm1.matching[i] << " -- " << i << '\n';
      }
      std::cout << "Hopkroft - Karp matching:\n";
      for (int i = 0;i < algorithm2.matching.size();++i) {
        std::cout << algorithm2.matching[i] << " -- " << i << '\n';
      }
      std::cout << "---------------------------\n";
#endif
    }
    avgTimeOfKuhn /= numOfGraphs;
    avgTimeOfHopkroftKarp /= numOfGraphs;
    std::cout << numOfVertices << "/" << maxNumOfVertices << " is ready\n";
    //printDataOfTests(numOfVertices, avgTimeOfKuhn, avgTimeOfHopkroftKarp);
    uploadDataToFile(numOfVertices, avgTimeOfKuhn, avgTimeOfHopkroftKarp, numVertices_f, kuhn_f, karp_f);
  }
  double runtime = (static_cast<double>(std::clock()) - startTime) / CLOCKS_PER_SEC;
  std::cout << "general runtime: " << runtime << "secs\n";

  // ���������� ������ � ������ � ������� �������
  numVertices_f.close();
  kuhn_f.close();
  karp_f.close();
  system("python moveDataToExcelScript.py");
}

