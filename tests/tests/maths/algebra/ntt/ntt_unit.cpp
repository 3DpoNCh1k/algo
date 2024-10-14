#include "algo/debug/debug.hpp"
#include "tests/framework/asserts.hpp"

#include <algo/maths/algebra/ntt/roots.hpp>
#include <algo/maths/algebra/ntt/ntt.hpp>

#include "helpers.hpp"
#include "tests/framework/test.hpp"

using namespace algo::maths::algebra::ntt;

template <typename Modular>
void TestMultiply(std::vector<Modular> a, std::vector<Modular> b,
                  std::vector<Modular> expected) {
  int n = algo::utils::bits::PowerOfTwoThatAtLeast(a.size() + b.size());
  auto constexpr P = Modular::MOD;
  auto [c, k] = FindCK(P);
  assert((1 << k) >= n);

  a.resize(n);
  b.resize(n);
  expected.resize(n);
  int degree = n;
  auto g = FindRoot<Modular>(degree);
  auto roots = UnityRoots(g, degree);
  auto ntt = NTT<Modular>(roots);

  auto result = ntt.Multiply(a, b);
  ASSERT_EQ(result, expected);
};

template <typename Modular>
void TestScalarProducts(std::vector<Modular> text, std::vector<Modular> pattern,
                        std::vector<Modular> expected) {
  int n =
      algo::utils::bits::PowerOfTwoThatAtLeast(text.size() + pattern.size());
  auto constexpr P = Modular::MOD;
  auto [c, k] = FindCK(P);
  assert((1 << k) >= n);

  int degree = n;
  auto g = FindRoot<Modular>(degree);
  auto roots = UnityRoots(g, degree);
  auto ntt = NTT<Modular>(roots);

  debug(n);
  debug(text);
  debug(pattern);
  auto result = ntt.ScalarProducts(text, pattern);
  debug(result);
  ASSERT_EQ(result, expected);
};

TEST(Multiply1) {
  constexpr auto P = 3;
  auto a = AsModulars<Modular<P>>({1});
  auto b = AsModulars<Modular<P>>({2});
  auto result = AsModulars<Modular<P>>({2});
  TestMultiply(a, b, result);
}

TEST(Multiply2) {
  constexpr auto P = 17;
  auto a = AsModulars<Modular<P>>({1, 2, 3});
  auto b = AsModulars<Modular<P>>({4, 5, 6});
  auto result = AsModulars<Modular<P>>({4, 13, 11, 10, 1});
  TestMultiply(a, b, result);
}

TEST(Multiply3) {
  constexpr auto P = 17;
  auto a = AsModulars<Modular<P>>({1, 2, 3, 4, 5, 6});
  auto b = AsModulars<Modular<P>>({7, 8, 9});
  auto result = AsModulars<Modular<P>>({7, 5, 12, 2, 9, 16, 8, 3});
  TestMultiply(a, b, result);
}

TEST(ScalarProducts1) {
  constexpr auto P = 3;
  auto text = AsModulars<Modular<P>>({1});
  auto pattern = AsModulars<Modular<P>>({2});
  auto result = AsModulars<Modular<P>>({2});
  TestScalarProducts(text, pattern, result);
}

TEST(ScalarProducts2) {
  constexpr auto P = 3;
  auto text = AsModulars<Modular<P>>({});
  auto pattern = AsModulars<Modular<P>>({1});
  auto result = AsModulars<Modular<P>>({});
  TestScalarProducts(text, pattern, result);
}

TEST(ScalarProducts3) {
  constexpr auto P = 17;
  auto text = AsModulars<Modular<P>>({1, 3, 2, 5, 4});
  auto pattern = AsModulars<Modular<P>>({1, 2, 3});
  auto result = AsModulars<Modular<P>>({13, 5, 7});
  TestScalarProducts(text, pattern, result);
}

RUN_ALL_TESTS()
