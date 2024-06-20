#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include <algo/utils/random.hpp>

void SubsetGenerator() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto rng = RandomGenerator();

  int from = 1, to = 5;
  int n = rng.RandomInt(from, to);
  std::cout << n << "\n";
  std::set<int> used;
  for (int i = 0; i < n; ++i) {
    int x;
    do {
      x = rng.RandomInt(from, to);
    } while (used.count(x) != 0);
    std::cout << x << " ";
    used.insert(x);
  }
  std::cout << "\n";
}

void TreeGenerator() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto rng = RandomGenerator();

  int from = 2, to = 10;
  int n = rng.RandomInt(from, to);
  std::cout << n << "\n";
  std::vector<std::pair<int, int>> edges;
  for (int i = 1; i < n; ++i) {
    edges.emplace_back(rng.RandomInt(0, i - 1), i);
  }

  // rename vertices
  std::vector<int> perm(n + 1);
  for (int i = 1; i <= n; ++i) {
    perm[i] = i;
  }
  std::shuffle(perm.begin() + 1, perm.end(), rng.GetRng());

  // shuffle edges
  std::shuffle(edges.begin(), edges.end(), rng.GetRng());

  for (std::pair<int, int> edge : edges) {
    int a = edge.first, b = edge.second;
    if (rng.RandomBool()) {
      // random order of two vertices
      std::swap(a, b);
    }
    std::cout << perm[a] << perm[b] << "\n";
  }
}
