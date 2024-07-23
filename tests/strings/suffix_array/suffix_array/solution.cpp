#include <iostream>

#include <algo/strings/suffix_array.hpp>

int main() {
  std::string s;
  std::cin >> s;
  auto suffix_array = algo::strings::SuffixArray(s);

  for (int i = 0; i < suffix_array.size(); ++i) {
    std::cout << suffix_array[i] << (i + 1 == suffix_array.size() ? "" : " ");
  }
  std::cout << std::endl;
}
