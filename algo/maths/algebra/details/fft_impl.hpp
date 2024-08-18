#pragma once

#include <algorithm>
#include <cassert>
#include <vector>
#include <algo/utils/types/fundamentals.hpp>
#include <algo/maths/algebra/power.hpp>
#include <algo/utils/bits.hpp>

namespace algo::maths::algebra::details {
template <typename T>
struct FastFourierTransformImpl {
  using Coefficient = T;
  using Value = T;
  int n;
  int log_n;
  std::vector<T> roots;
  std::vector<int> position;

  explicit FastFourierTransformImpl(const std::vector<T>& roots0)
      : roots(roots0) {
    n = roots.size();
    assert(utils::bits::IsPowerOfTwo(u64(n)));
    log_n = utils::bits::IndexOfMostSignificantBit(u64(n));
    position.resize(n);
    roots.resize(n);

    position[0] = 0;
    int power_of_2 = 0;
    for (int i = 1; i < n; ++i) {
      if (i == (1 << (power_of_2 + 1))) {
        power_of_2++;
      }
      position[i] =
          position[i ^ (1 << power_of_2)] | (1 << (log_n - 1 - power_of_2));
    }
  }

  void TransformTo(std::vector<Value>& result,
                   const std::vector<Coefficient>& coefs) {
    assert(n == result.size());
    assert(n == coefs.size());
    for (int i = 0; i < n; ++i) {
      result[position[i]] = coefs[i];
    }
    for (int level = 0; level < log_n; ++level) {
      int block_size = 1 << level;
      int root_shift = (1 << (log_n - level - 1));
      for (int start = 0; start < n; start += (block_size << 1)) {
        for (int j = 0; j < block_size; ++j) {
          auto x = roots[j * root_shift];
          auto a = result[start + j] + x * result[start + block_size + j];
          auto b = result[start + j] - x * result[start + block_size + j];
          result[start + j] = a;
          result[start + block_size + j] = b;
        }
      }
    }
  }

  std::vector<Value> Transform(const std::vector<Coefficient>& coefs) {
    std::vector<Value> values(coefs.size());
    TransformTo(values, coefs);
    return values;
  }

  void InverseTo(std::vector<Coefficient>& result,
                 const std::vector<Value>& values) {
    TransformTo(result, values);
    std::reverse(result.begin() + 1, result.end());
    int n = result.size();
    for (int i = 0; i < n; ++i) {
      result[i] /= n;
    }
  }

  std::vector<Coefficient> Inverse(const std::vector<Value>& values) {
    std::vector<Coefficient> coefs(values.size());
    InverseTo(coefs, values);
    return coefs;
  }

  std::vector<Coefficient> Multiply(const std::vector<Coefficient>& a,
                                    const std::vector<Coefficient>& b) {
    assert(a.size() == b.size());
    assert(a.size() == n);
    std::vector<Value> values_a(a.size());
    std::vector<Value> values_b(b.size());
    TransformTo(values_a, a);
    TransformTo(values_b, b);
    for (int i = 0; i < n; ++i) {
      values_a[i] *= values_b[i];
    }
    return Inverse(values_a);
  }

  std::vector<Coefficient> ScalarProducts(std::vector<Coefficient> text,
                                          std::vector<Coefficient> pattern) {
    int text_length = text.size();
    int pattern_length = pattern.size();
    assert(pattern_length > 0);
    assert(text_length + pattern_length - 1 <= n);
    if (pattern_length > text_length) {
      return {};
    }
    std::reverse(text.begin(), text.end());
    text.resize(n);
    pattern.resize(n);
    auto product = Multiply(text, pattern);
    // dbg(product);
    std::vector<Coefficient> result(text_length - pattern_length + 1);
    for (int i = 0; i < result.size(); ++i) {
      result[i] = product[text_length - 1 - i];
    }
    return result;
  }
};
}  // namespace algo::maths::algebra::details
