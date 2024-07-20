#include <iostream>

#include <algo/strings/suffix_array.hpp>

int main() {
  std::string s;
  std::cin >> s;
  auto suffix_array = algo::strings::SuffixArray(s);
  auto result = suffix_array.GetSuffixArray();

  for (int i = 0; i < result.size(); ++i) {
    std::cout << result[i] << (i + 1 == result.size() ? "" : " ");
  }
  std::cout << std::endl;
}
