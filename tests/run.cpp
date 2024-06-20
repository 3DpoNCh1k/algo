#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <iostream>

#include <algo/utils/debug.hpp>

// NOLINTBEGIN
using namespace std;
// NOLINTEND

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << "Hello" << endl;

  dbg(123);
}
