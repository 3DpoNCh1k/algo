#include <iostream>
#include <string>

#include <algo/strings/prefix_function.hpp>
#include "algo/utils/join.hpp"

int main() {
  std::string s;
  std::cin >> s;

  auto length = algo::strings::PrefixFunction(s);
  std::cout << algo::utils::JoinToString(length, {.separator = " "}) << "\n";
}
