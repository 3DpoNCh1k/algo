#include <iostream>
#include <vector>

const int MODULO = 998244353;

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  // TODO: rewrite lazy segment tree and use it here
  // auto lazy = algo::trees::LazySegmentTree();

  for (int i = 0; i < q; ++i) {
    int command;
    std::cin >> command;
    switch (command) {
      case 0: {
        int l, r, b, c;
        std::cin >> l >> r >> b >> c;
        break;
      }
      case 1: {
        int index;
        std::cin >> index;
        break;
      }
    }
  }
}
