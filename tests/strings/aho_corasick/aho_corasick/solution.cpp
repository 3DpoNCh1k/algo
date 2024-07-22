#include <iostream>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/leftmost.hpp>
#include <algo/strings/aho_corasick/statistics/rightmost.hpp>

using namespace algo::strings::aho_corasick;
using namespace algo::strings::aho_corasick::statistics;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::string> patterns(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> patterns[i];
  }
  std::string t;
  std::cin >> t;

  auto aho_corasick = AhoCorasick<Statistics<Leftmost, Rightmost>>(patterns);
  aho_corasick.Scan(t);
  for (int i = 0; i < n; ++i) {
    std::cout << aho_corasick.Get<Leftmost>(i).result << " "
              << aho_corasick.Get<Rightmost>(i).result << "\n";
  }
}
