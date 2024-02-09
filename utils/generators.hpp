#include "../header.hpp"
#include "random.hpp"

void SubsetGenerator() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  auto rng = RandomGenerator();

  int from = 1, to = 5;
  int n = rng.RandomInt(from, to);
  cout << n << "\n";
  set<int> used;
  for (int i = 0; i < n; ++i) {
    int x;
    do {
      x = rng.RandomInt(from, to);
    } while (used.count(x) != 0);
    cout << x << " ";
    used.insert(x);
  }
  cout << "\n";
}

void TreeGenerator() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  auto rng = RandomGenerator();

  int from = 2, to = 10;
  int n = rng.RandomInt(from, to);
  cout << n << "\n";
  vector<pair<int, int>> edges;
  for (int i = 1; i < n; ++i) {
    edges.emplace_back(rng.RandomInt(0, i - 1), i);
  }

  // rename vertices
  vector<int> perm(n + 1);
  for (int i = 1; i <= n; ++i) {
    perm[i] = i;
  }
  shuffle(perm.begin() + 1, perm.end(), rng.GetRng());

  // shuffle edges
  shuffle(edges.begin(), edges.end(), rng.GetRng());

  for (pair<int, int> edge : edges) {
    int a = edge.first, b = edge.second;
    if (rng.RandomBool()) {
      // random order of two vertices
      swap(a, b);
    }
    cout << perm[a] << perm[b] << "\n";
  }
}
