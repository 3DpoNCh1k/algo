#include <iostream>
#include <string>

#include <algo/strings/prefix_function.hpp>

int main() {
  std::string s;
  std::cin >> s;

  auto values = algo::strings::PrefixFunction(s);
  for (int i = 0; i < values.size(); ++i) {
    std::cout << values[i] << (i + 1 == values.size() ? "" : " ");
  }
  std::cout << "\n";
}
