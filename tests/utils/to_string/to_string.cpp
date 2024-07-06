#include <algo/utils/to_string/to_string.hpp>
#include <iostream>
#include <utility>

using algo::utils::ToString;
using std::cout;
using std::endl;

void TestPair() {
  auto p = std::make_pair(1, 2);
  cout << ToString(p) << endl;
}

int main() {
  TestPair();
}
