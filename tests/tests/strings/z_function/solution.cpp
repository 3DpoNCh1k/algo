#include <algo/strings/z_function.hpp>
#include <iostream>
#include "algo/utils/join.hpp"

int main() {
  std::string s;
  std::cin >> s;
  auto length = algo::strings::ZFunction(s);
  std::cout << algo::utils::JoinToString(length, {.separator = " "}) << "\n";
}
