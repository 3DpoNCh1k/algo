#include <iostream>

#include <algo/strings/aho_corasick.hpp>

int main() {
  int n;
  std::cin >> n;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }
  std::string t;
  std::cin >> t;

  auto aho = algo::strings::AhoCorasick(2e6);
  aho.MakeTrie(s);
  aho.Solve(t);
}
