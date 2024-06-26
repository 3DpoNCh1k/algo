#include <algo/utils/types/128_t.hpp>
#include <algo/utils/types/types.hpp>
#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for(int t = 0; t < T; ++t) {
    using algo::utils::i128;
    i128 a, b;
    std::cin >> a >> b;
    // auto c = a + b;
    // std::cout << c << std::endl;
    std::cout << (a + b) << std::endl;
    // operator<<(std::cout, c);
    // algo::utils::operators::operator<<(std::cout, c);
    // algo::utils::operators::operator<<(std::cout, a + b);
  }
}