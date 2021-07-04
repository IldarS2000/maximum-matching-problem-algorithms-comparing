#pragma once
#ifndef BI_GRAPH_H
#define BI_GRAPH_H

#include <vector>

class BiGraph
{
private:
  int n1;
  int n2;
public:
  std::vector<std::vector<int>> graph;
public:
  BiGraph(const int numberOfVertices, const int kindOfGraph);
  int get_n1() const;
  int get_n2() const;
};

//void generate_graph(const int numberOfVertices, int& n1, int& n2, std::vector<std::vector<int>>& graph);

#endif // !BI_GRAPH_H

