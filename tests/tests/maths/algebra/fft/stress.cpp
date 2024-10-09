#include <algo/utils/random/random.hpp>
#include <algo/maths/algebra/fft/fft.hpp>

#include "algo/utils/debug.hpp"
#include "helpers.hpp"
#include "tests/framework/asserts.hpp"
#include "tests/framework/test.hpp"

using namespace algo::utils::random;

struct MultiplyTester {
  int from, to;
  i64 A;
  MultiplyTester(int from, int to)
      : from(from),
        to(to) {
    A = std::max(abs(from), abs(to));
  }
  void Test(int k_rep, int max_n) {
    assert(A * A * max_n <= 1e9);
    for (int rep = 0; rep < k_rep; ++rep) {
      auto a = GenerateCoefs(RandomInt(1, max_n));
      auto b = GenerateCoefs(RandomInt(1, max_n));
      auto expected = Multiply(a, b);
      auto result = MultiplyViaFFT(a, b);
      int n = std::max(expected.size(), result.size());
      expected.resize(n);
      result.resize(n);
      ASSERT_EQ(result, expected);
    }
  }

  std::vector<int> GenerateCoefs(int n) {
    std::vector<int> coefs(n);
    for (int i = 0; i < n; ++i) {
      coefs[i] = RandomInt(from, to);
    }
    return coefs;
  }

  std::vector<int> Multiply(const std::vector<int>& a,
                            const std::vector<int>& b) {
    std::vector<int> result(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
      for (int j = 0; j < b.size(); ++j) {
        result[i + j] += a[i] * b[j];
      }
    }
    return result;
  };

  std::vector<int> MultiplyViaFFT(const std::vector<int>& a,
                                  const std::vector<int>& b) {
    int n = algo::utils::bits::PowerOfTwoThatAtLeast(a.size() + b.size());
    std::vector<Complex> ca(n);
    std::vector<Complex> cb(n);
    for (int i = 0; i < a.size(); ++i) {
      ca[i] = a[i];
    }
    for (int i = 0; i < b.size(); ++i) {
      cb[i] = b[i];
    }
    auto coefs = FFT(n).Multiply(ca, cb);
    return AsInts(coefs);
  };
};

struct ScalarProductTester {
  int from, to;
  i64 A;

  ScalarProductTester(int from, int to)
      : from(from),
        to(to) {
    A = std::max(abs(from), abs(to));
  }
  void Test(int k_rep, int max_n) {
    assert(A * A * max_n <= 1e9);
    for (int rep = 0; rep < k_rep; ++rep) {
      int text_length = RandomInt(1, max_n);
      auto text = GenerateCoefs(text_length);
      auto pattern = GenerateCoefs(
          RandomInt(1, std::min(text_length, max_n - text_length + 1)));
      auto expected = ScalarProducts(text, pattern);
      auto result = ScalarProductsViaFFT(text, pattern);
      ASSERT_EQ(result, expected);
    }
  }

  std::vector<int> GenerateCoefs(int n) {
    std::vector<int> coefs(n);
    for (int i = 0; i < n; ++i) {
      coefs[i] = RandomInt(from, to);
    }
    return coefs;
  }

  std::vector<int> ScalarProducts(const std::vector<int>& text,
                                  const std::vector<int>& pattern) {
    if (pattern.size() == 0) {
      return {};
    }
    std::vector<int> result(text.size() - pattern.size() + 1);
    for (int i = 0; i < result.size(); ++i) {
      for (int j = 0; j < pattern.size(); ++j) {
        result[i] += text[i + j] * pattern[j];
      }
    }
    return result;
  };

  std::vector<int> ScalarProductsViaFFT(const std::vector<int>& text,
                                        const std::vector<int>& pattern) {
    int n = algo::utils::bits::PowerOfTwoThatAtLeast(text.size() +
                                                     pattern.size() - 1);
    auto text_complex = AsComplexes(text);
    auto pattern_complex = AsComplexes(pattern);
    auto coefs = FFT(n).ScalarProducts(text_complex, pattern_complex);
    return AsInts(coefs);
  };
};

TEST(MultiplySmall) {
  auto tester = MultiplyTester(-10, 10);
  tester.Test(1000, 10);
}

TEST(MultiplyMedium) {
  auto tester = MultiplyTester(-1e3, 1e3);
  tester.Test(100, 100);
}

TEST(MultiplyBig) {
  auto tester = MultiplyTester(-1e3, 1e3);
  tester.Test(10, 1000);
}

TEST(ScalarProductsSmall) {
  auto tester = ScalarProductTester(-10, 10);
  tester.Test(1000, 10);
}

TEST(ScalarProductsMedium) {
  auto tester = ScalarProductTester(-1e3, 1e3);
  tester.Test(100, 100);
}

TEST(ScalarProductsBig) {
  auto tester = ScalarProductTester(-1e3, 1e3);
  tester.Test(10, 1000);
}

RUN_ALL_TESTS()
