#include <iostream>
#include <string>

#include <algo/strings/prefix_function.hpp>

int main() {
  std::string s;
  std::cin >> s;

  auto values = algo::strings::PrefixFunction(s);
  for(int v: values) {
    std::cout << v << " ";
  }
  std::cout << "\n";
}