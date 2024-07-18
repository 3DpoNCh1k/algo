#include <algo/strings/suffix_array.hpp>
#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  auto suffix_array = algo::strings::SuffixArray(s);
  auto result = suffix_array.Solve();

  for (int i = 0; i < result.size(); ++i) {
    std::cout << result[i] << (i + 1 == result.size() ? "" : " ");
  }
  std::cout << std::endl;
}
