#include <algo/strings/z_function.hpp>
#include <iostream>

int main() {
  std::string s;
  std::cin >> s;
  auto lcps = algo::strings::ZFunction(s);
  for (int i = 0; i < lcps.size(); ++i) {
    std::cout << lcps[i] << (i + 1 == lcps.size() ? "" : " ");
  }
  std::cout << std::endl;
}
