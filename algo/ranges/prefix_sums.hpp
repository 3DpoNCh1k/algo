#include <vector>
#include "algo/utils/types/fundamentals.hpp"
namespace algo::ranges {
struct PrefixSums {
  template <typename T>
  explicit PrefixSums(const std::vector<T>& a) {
    s.resize(a.size() + 1);
    for (int i = 1; i < s.size(); ++i) {
      s[i] = s[i - 1] + a[i - 1];
    }
  }

  i64 GetFromPrefix(int i) const {
    return s[i + 1];
  }

  i64 GetFromSuffix(int i) const {
    int n = s.size() - 1;
    return GetFromRange(i, n - 1);
  }

  i64 GetFromRange(int l, int r) const {
    return s[r + 1] - s[l];
  }

  std::vector<i64> s;
};
}  // namespace algo::ranges
