#include "BiGraph.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <exception>

//#define DEBUG_GRAPH_GENERATION

std::random_device rd;
std::mt19937 generator(rd());


BiGraph::BiGraph(const int numberOfVertices, const int kindOfGraph)
{
  switch (kindOfGraph) {
  case 0: { // рандомный граф с равномерым распределение кол-ва вершин в долях
    // определяем рандомно размер первой и второй доли и для первой доли берем меньшее количество вершин
    std::uniform_int_distribution<int> uni_distribution;
    uni_distribution.param(std::uniform_int_distribution<int>::param_type(0, numberOfVertices));
    int partition = uni_distribution(generator);
    n1 = std::min(partition, numberOfVertices - partition);
    n2 = numberOfVertices - n1;
    break;
  }
  case 1: { // рандомный граф с биномиальным распределение кол-ва вершин в долях
    // определяем рандомно размер первой и второй доли и для первой доли берем меньшее количество вершин
    std::binomial_distribution<int> bin_distribution;
    bin_distribution.param(std::binomial_distribution<int>::param_type(numberOfVertices));
    int partition = bin_distribution(generator);
    n1 = std::min(partition, numberOfVertices - partition);
    n2 = numberOfVertices - n1;
    break;
  }
  case 2: { // плотный граф с одинаковым кол-вом вершин в долях
    n1 = numberOfVertices / 2;
    n2 = numberOfVertices - n1;
    break;
  }
  }

#ifdef DEBUG_GRAPH_GENERATION
  std::cout << "n1: " << n1 << ' ' << "n2: " << n2 << '\n';
#endif // DEBUG_GRAPH_GENERATION

  graph.resize(n1);

  // временный массив вершин второй доли
  std::vector<int> verticesOfSecondPart;
  verticesOfSecondPart.reserve(n2);
  for (size_t i = 0;i < n2;++i) {
    verticesOfSecondPart.push_back(i);
  }

  // заполняем рандомным количеством ребер между вершинами первой и второй доли
  std::uniform_int_distribution<int> uni_distribution;
  uni_distribution.param(std::uniform_int_distribution<int>::param_type(0, n2));
  for (size_t i = 0;i < n1; ++i) {
    int numOfEdges = uni_distribution(generator);
    graph[i].reserve(numOfEdges);
    std::shuffle(verticesOfSecondPart.begin(), verticesOfSecondPart.end(), generator);

#ifdef DEBUG_GRAPH_GENERATION
    std::cout << "numOfEdges: " << numOfEdges << '\n';
#endif // DEBUG_GRAPH_GENERATION

    for (size_t j = 0;j < numOfEdges;++j) {
      graph[i].push_back(verticesOfSecondPart[j]);
    }
  }
}

int BiGraph::get_n1() const
{
  return n1;
}

int BiGraph::get_n2() const
{
  return n2;
}