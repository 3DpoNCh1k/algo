#include <algo/strings/z_function.hpp>
#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  auto length = algo::strings::ZFunction(s);
  for (int i = 0; i < length.size(); ++i) {
    std::cout << length[i] << (i + 1 == length.size() ? "" : " ");
  }
  std::cout << std::endl;
}
