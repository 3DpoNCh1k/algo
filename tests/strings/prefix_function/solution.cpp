#include <iostream>
#include <string>

#include <algo/strings/prefix_function.hpp>

int main() {
  std::string s;
  std::cin >> s;

  auto length = algo::strings::PrefixFunction(s);
  for (int i = 0; i < length.size(); ++i) {
    std::cout << length[i] << (i + 1 == length.size() ? "" : " ");
  }
  std::cout << "\n";
}
