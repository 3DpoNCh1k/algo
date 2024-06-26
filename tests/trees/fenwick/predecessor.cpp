#include <iostream>
#include <algo/trees/fenwick.hpp>

int main() {
  int n, q;
  std::cin >> n >> q;
  std::string t;
  std::cin >> t;

  auto fenwick = algo::trees::Fenwick(n);
  for(int k = 0; k < n; ++k) {
    auto value = t[k] == '1'? 1: 0;
    fenwick.SetValue(k, value);
  }

  for (int query = 0; query < q; ++query) {
    int c, k;
    std::cin >> c >> k;
    switch (c) {
      case 0:
        fenwick.SetValue(k, 1);
        break;
      case 1:
        fenwick.SetValue(k, 0);
        break;
      case 2:
        std::cout << fenwick.GetValue(k) << std::endl;
        break;
      case 3: {
        int smallest = -1;
        int l = k, r = n - 1;
        int count = fenwick.GetSum(k, n-1);
        while(l < r) {
          int m = (l + r + 1) / 2;
          if (fenwick.GetSum(m, n-1) < count) {
            r = m - 1;
            smallest = r;
          } else {
            l = m;
          }
        }
        if (smallest == - 1 && fenwick.GetValue(n-1) == 1) {
          smallest = n - 1;
        }
        std::cout << smallest << std::endl;
        break;
      }
      case 4: {
        int largest = -1;
        int l = 0, r = k;
        int count = fenwick.GetSum(0, k);
        while(l < r) {
          int m = (l + r) / 2;
          if (fenwick.GetSum(0, m) < count) {
            l = m + 1;
            largest = l;
          } else {
            r = m;
          }
        }
        if (largest == - 1 && fenwick.GetValue(0) == 1) {
          largest = 0;
        }
        std::cout << largest << std::endl;
        break;
      }
    }
  }
}
