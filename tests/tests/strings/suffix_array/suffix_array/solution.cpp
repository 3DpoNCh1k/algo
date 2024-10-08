#include <iostream>

#include <algo/strings/suffix_array.hpp>
#include "algo/utils/join.hpp"

int main() {
  std::string s;
  std::cin >> s;
  auto suffix_array = algo::strings::SuffixArray(s);
  std::cout << algo::utils::JoinToString(suffix_array, {.separator = " "})
            << "\n";
}
