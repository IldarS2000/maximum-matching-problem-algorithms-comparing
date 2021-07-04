#include "algorithms.h"


// алгоритм Куна
Kuhn::Kuhn(const BiGraph& bigraph)
{
  matching.reserve(bigraph.get_n1() * bigraph.get_n2());
  usedHeuristic.resize(bigraph.get_n1());
  used.reserve(bigraph.get_n2());
}

bool Kuhn::tryKuhn(const int v, const BiGraph& bigraph) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (size_t i = 0; i < bigraph.graph[v].size(); ++i) {
		int to = bigraph.graph[v][i];
		if (matching[to] == -1 || tryKuhn(matching[to], bigraph)) {
			matching[to] = v;
			return true;
		}
	}
	return false;
}

void Kuhn::maxMatching(const BiGraph& bigraph)
{
	matching.assign(bigraph.get_n2(), -1);
  for (size_t i = 0; i < bigraph.get_n1(); ++i) {
    for (size_t j = 0; j < bigraph.graph[i].size(); ++j) {
      if (matching[bigraph.graph[i][j]] == -1) {
        matching[bigraph.graph[i][j]] = i;
        usedHeuristic[i] = true;
        break;
      }
    }
  }
	for (size_t i = 0; i < bigraph.get_n1(); ++i) {
		if (usedHeuristic[i]) {
			continue;
		}
		used.assign(bigraph.get_n1(), false);
		tryKuhn(i, bigraph);
	}
}


// алгоритм Хопкрофта - Карпа
HopkroftKarp::HopkroftKarp(const BiGraph& bigraph)
{
  this->n1 = bigraph.get_n1();
  this->n2 = bigraph.get_n2();
  m = bigraph.get_n1() * bigraph.get_n2();
  edges = 0;
  last.resize(n1);
  prev.resize(m);
  head.resize(m);
  matching.resize(n2);
  dist.resize(n1);
  Q.resize(n1);
  used.resize(n1);
  vis.resize(n1);

  last.assign(n1, -1);

  // копируем граф в новый формат
  for (size_t i = 0;i < bigraph.graph.size();++i) {
    for (size_t j = 0;j < bigraph.graph[i].size();++j) {
      addEdge(i, bigraph.graph[i][j]);
    }
  }
}

void HopkroftKarp::addEdge(const int u, const int v)
{
  head[edges] = v;
  prev[edges] = last[u];
  last[u] = edges;
  ++edges;
}

void HopkroftKarp::bfs()
{
  dist.assign(n1, -1);
  int sizeQ = 0;
  for (int u = 0; u < n1; ++u) {
    if (!used[u]) {
      Q[sizeQ++] = u;
      dist[u] = 0;
    }
  }
  for (int i = 0; i < sizeQ; i++) {
    int u1 = Q[i];
    for (int e = last[u1]; e >= 0; e = prev[e]) {
      int u2 = matching[head[e]];
      if (u2 >= 0 && dist[u2] < 0) {
        dist[u2] = dist[u1] + 1;
        Q[sizeQ++] = u2;
      }
    }
  }
}

bool HopkroftKarp::dfs(const int u1)
{
  vis[u1] = true;
  for (int e = last[u1]; e >= 0; e = prev[e]) {
    int v = head[e];
    int u2 = matching[v];
    if (u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)) {
      matching[v] = u1;
      used[u1] = true;
      return true;
    }
  }
  return false;
}

int HopkroftKarp::maxMatching()
{
  used.assign(n1, false);
  matching.assign(n2, -1);
  for (int res = 0;;) {
    bfs();
    vis.assign(n1, false);
    int f = 0;
    for (int u = 0; u < n1; ++u) {
      if (!used[u] && dfs(u)) {
        ++f;
      }
    }
    if (!f) {
      return res;
    }
    res += f;
  }
}

void HopkroftKarp::clearState()
{
  edges = 0;
  last.clear();
  prev.clear();
  head.clear();
  dist.clear();
  Q.clear();
  vis.clear();

  last.assign(n1, -1);
}
