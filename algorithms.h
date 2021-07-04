#pragma once
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "BiGraph.h"



// O(|E| * |V|)
// не хранит граф, хранит только паросочетание
class Kuhn
{
public:
  std::vector<int> matching;
private:
  std::vector<char> used;
  std::vector<char> usedHeuristic;
public:
  Kuhn(const BiGraph& bigraph);
  void maxMatching(const BiGraph& bigraph);
private:
  bool tryKuhn(const int v, const BiGraph& bigraph);
};

// O(|E| * sqrt(|V|))
// хранит измененный граф и паросочетание
class HopkroftKarp
{
public:
  std::vector<int> matching;
private:
  int n1, n2, m, edges;
  std::vector<int> last;
  std::vector<int> prev;
  std::vector<int> head;
  std::vector<int> dist;
  std::vector<int>  Q;
  std::vector<bool> used;
  std::vector<bool> vis;
public:
  HopkroftKarp(const BiGraph& bigraph);
  int maxMatching();
  void clearState();
private:
  void addEdge(const int u, const int v);
  void bfs();
  bool dfs(const int u1);
};

#endif // ALGORITHMS_H
