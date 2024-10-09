#include <algo/utils/random/random.hpp>
#include "algo/maths/algebra/power.hpp"
#include "algo/utils/types/modular.hpp"
#include "tests/framework/asserts.hpp"

#include <algo/maths/algebra/ntt/roots.hpp>
#include <algo/maths/algebra/ntt/ntt.hpp>

#include <algo/utils/debug.hpp>

#include "helpers.hpp"
#include "tests/framework/test.hpp"

using namespace algo::maths::algebra::ntt;
using namespace algo::utils::random;

template <typename Modular>
struct MultiplyTester {
  std::vector<Modular> roots;
  NTT<Modular> ntt;

  explicit MultiplyTester(const std::vector<Modular>& roots)
      : roots(roots),
        ntt(roots) {
  }
  void Test(int k_rep) {
    int max_n = roots.size();
    for (int rep = 0; rep < k_rep; ++rep) {
      int len_a = RandomInt(1, max_n);
      auto a = GenerateCoefs(len_a);
      auto b = GenerateCoefs(RandomInt(1, max_n - len_a + 1));
      auto expected = Multiply(a, b);
      auto result = MultiplyViaNTT(a, b);
      int n = std::max(expected.size(), result.size());
      expected.resize(n);
      result.resize(n);
      ASSERT_EQ(result, expected);
    }
  }

  std::vector<Modular> GenerateCoefs(int n) {
    std::vector<Modular> coefs(n);
    for (int i = 0; i < n; ++i) {
      coefs[i] = RandomInt(0, Modular::MOD - 1);
    }
    return coefs;
  }

  std::vector<Modular> Multiply(const std::vector<Modular>& a,
                                const std::vector<Modular>& b) {
    std::vector<Modular> result(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
      for (int j = 0; j < b.size(); ++j) {
        result[i + j] += a[i] * b[j];
      }
    }
    return result;
  };

  std::vector<Modular> MultiplyViaNTT(const std::vector<Modular>& a,
                                      const std::vector<Modular>& b) {
    assert(std::max(a.size(), b.size()) <= roots.size());
    std::vector<Modular> coef_a(roots.size());
    std::vector<Modular> coef_b(roots.size());
    for (int i = 0; i < a.size(); ++i) {
      coef_a[i] = a[i];
    }
    for (int i = 0; i < b.size(); ++i) {
      coef_b[i] = b[i];
    }
    return ntt.Multiply(coef_a, coef_b);
  };
};

template <typename Modular>
struct ScalarProductsTester {
  std::vector<Modular> roots;
  NTT<Modular> ntt;

  explicit ScalarProductsTester(const std::vector<Modular>& roots)
      : roots(roots),
        ntt(roots) {
  }
  void Test(int k_rep) {
    int max_n = roots.size();
    for (int rep = 0; rep < k_rep; ++rep) {
      int text_length = RandomInt(1, max_n);
      auto text = GenerateCoefs(text_length);
      auto pattern = GenerateCoefs(
          RandomInt(1, std::min(text_length, max_n - text_length + 1)));
      auto expected = ScalarProducts(text, pattern);
      auto result = ntt.ScalarProducts(text, pattern);
      ASSERT_EQ(result, expected);
    }
  }

  std::vector<Modular> GenerateCoefs(int n) {
    std::vector<Modular> coefs(n);
    for (int i = 0; i < n; ++i) {
      coefs[i] = RandomInt(0, Modular::MOD - 1);
    }
    return coefs;
  }

  std::vector<Modular> ScalarProducts(const std::vector<Modular>& text,
                                      const std::vector<Modular>& pattern) {
    if (pattern.size() == 0) {
      return {};
    }
    std::vector<Modular> result(text.size() - pattern.size() + 1);
    for (int i = 0; i < result.size(); ++i) {
      for (int j = 0; j < pattern.size(); ++j) {
        result[i] += text[i + j] * pattern[j];
      }
    }
    return result;
  };
};

template <typename Modular>
struct TransformTester {
  std::vector<Modular> roots;
  NTT<Modular> ntt;

  explicit TransformTester(const std::vector<Modular>& roots)
      : roots(roots),
        ntt(roots) {
  }

  void Test(int k_rep) {
    for (int rep = 0; rep < k_rep; ++rep) {
      auto a = GenerateCoefs(RandomInt(1, roots.size()));
      auto expected = Calculate(a);
      auto result = CalculateViaNTT(a);
      ASSERT_EQ(result, expected);
    }
  }

  std::vector<Modular> GenerateCoefs(int n) {
    std::vector<Modular> coefs(n);
    for (int i = 0; i < n; ++i) {
      coefs[i] = RandomInt(0, Modular::MOD - 1);
    }
    return coefs;
  }

  std::vector<Modular> Calculate(const std::vector<Modular>& a) {
    std::vector<Modular> result(roots.size());
    for (int r = 0; r < roots.size(); ++r) {
      auto root = roots[r];
      Modular current = 1;
      result[r] = 0;
      for (int i = 0; i < a.size(); ++i) {
        result[r] += a[i] * current;
        current *= root;
      }
    }
    return result;
  };

  std::vector<Modular> CalculateViaNTT(const std::vector<Modular>& a) {
    std::vector<Modular> coef_a(roots.size());
    for (int i = 0; i < a.size(); ++i) {
      coef_a[i] = a[i];
    }
    return ntt.Transform(coef_a);
  };
};

void TestTransform() {
  {
    // 17
    constexpr auto C = 1;
    constexpr auto K = 4;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 17);
    Modular<P> primitive_root = 3;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = TransformTester<Modular<P>>(roots);
    tester.Test(100);
  }

  {
    // 97
    constexpr auto C = 3;
    constexpr auto K = 5;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 97);
    Modular<P> primitive_root = 23;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = TransformTester<Modular<P>>(roots);
    tester.Test(100);
  }

  {
    // 193
    constexpr auto C = 3;
    constexpr auto K = 6;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 193);
    Modular<P> primitive_root = 5;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = TransformTester<Modular<P>>(roots);
    tester.Test(100);
  }
}

// clang-format off
void TestMultiply() {
  {
    // 257
    constexpr auto C = 1;
    constexpr auto K = 8;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 257);
    Modular<P> primitive_root = 3;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = MultiplyTester<Modular<P>>(roots);
    tester.Test(1000);
  }

  {
    // 7681
    constexpr auto C = 15;
    constexpr auto K = 9;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 7681);
    Modular<P> primitive_root = 123;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = MultiplyTester<Modular<P>>(roots);
    tester.Test(100);
  }
};

// clang-format off
void TestScalarProducts() {
  {
    // 257
    constexpr auto C = 1;
    constexpr auto K = 8;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 257);
    Modular<P> primitive_root = 3;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = ScalarProductsTester<Modular<P>>(roots);
    tester.Test(1000);
  }

  {
    // 7681
    constexpr auto C = 15;
    constexpr auto K = 9;
    constexpr auto P = C * (1 << K) + 1;
    static_assert(P == 7681);
    Modular<P> primitive_root = 123;
    int degree = 1 << K;
    auto g = algo::maths::algebra::Power(primitive_root, C);
    auto roots = UnityRoots(g, degree);
    auto tester = ScalarProductsTester<Modular<P>>(roots);
    tester.Test(100);
  }
};


TEST(StressTransform) {
  TestTransform();
}

TEST(StressMultiply) {
  TestMultiply();
}

TEST(StressScalarProducts) {
  TestScalarProducts();
}

RUN_ALL_TESTS()
