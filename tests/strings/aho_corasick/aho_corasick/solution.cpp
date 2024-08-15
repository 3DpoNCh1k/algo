#include <iostream>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/leftmost.hpp>
#include <algo/strings/aho_corasick/statistics/rightmost.hpp>

using namespace algo::strings::aho_corasick;
using String = std::u32string;
using Leftmost = algo::strings::aho_corasick::statistics::Leftmost<String>;
using Rightmost = algo::strings::aho_corasick::statistics::Rightmost<String>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::vector<String> patterns(n);
  for (int p = 0; p < n; ++p) {
    std::cin >> s;
    patterns[p].resize(s.size());
    for (int i = 0; i < s.size(); ++i) {
      patterns[p][i] = s[i];
    }
  }

  String t;
  std::cin >> s;
  t.resize(s.size());
  for (int i = 0; i < s.size(); ++i) {
    t[i] = s[i];
  }

  auto aho_corasick =
      AhoCorasick<Statistics<Leftmost, Rightmost>, String>(patterns);
  aho_corasick.Scan(t);

  for (int i = 0; i < n; ++i) {
    std::cout << aho_corasick.Get<Leftmost>(i).result << " "
              << aho_corasick.Get<Rightmost>(i).result << "\n";
  }
}
