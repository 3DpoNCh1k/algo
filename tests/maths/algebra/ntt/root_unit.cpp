#include "algo/utils/types/modular.hpp"
#include "tests/testing/asserts.hpp"

#include <algo/maths/algebra/ntt/roots.hpp>
#include "helpers.hpp"

using namespace algo::maths::algebra::ntt;

// clang-format off
void TestGenerateGroup() {
  {
    auto g = Modular<2>(1);
    auto group = GenerateGroup(g);
    std::vector<int> expected = {1};
    ASSERT_EQ(AsInts(group), expected);
  }
  {
    auto g = Modular<3>(2);
    auto group = GenerateGroup(g);
    std::vector<int> expected = {1, 2};
    ASSERT_EQ(AsInts(group), expected);
  }
  {
    auto g = Modular<5>(2);
    auto group = GenerateGroup(g);
    std::vector<int> expected = {1, 2, 4, 3};
    ASSERT_EQ(AsInts(group), expected);
  }
  {
    auto g = Modular<5>(3);
    auto group = GenerateGroup(g);
    std::vector<int> expected = {1, 3, 4, 2};
    ASSERT_EQ(AsInts(group), expected);
  }
  {
    auto g = Modular<5>(4);
    auto group = GenerateGroup(g);
    std::vector<int> expected = {1, 4};
    ASSERT_EQ(AsInts(group), expected);
  }
};

void TestFindCK() {
  {
    auto [c, k] = FindCK(1);
    ASSERT_EQ(c, 0);
    ASSERT_EQ(k, 0);
  }
  {
    auto [c, k] = FindCK(1 * 256 + 1);
    ASSERT_EQ(c, 1);
    ASSERT_EQ(k, 8);
  }
  {
    auto [c, k] = FindCK(7 * (1 << 20) + 1);
    ASSERT_EQ(c, 7);
    ASSERT_EQ(k, 20);
  }
}

void TestCheckRoot() {
  {
    auto ok = CheckRoot(Modular<2>(1), 1);
    ASSERT_TRUE(ok);
  }
  {
    auto ok = CheckRoot(Modular<2>(1), 2);
    ASSERT_FALSE(ok);
  }
  {
    auto ok = CheckRoot(Modular<3>(2), 2);
    ASSERT_TRUE(ok);
  }
  {
    auto ok = CheckRoot(Modular<5>(4), 2);
    ASSERT_TRUE(ok);
  }
  {
    auto ok = CheckRoot(Modular<11>(6), 10);
    ASSERT_TRUE(ok);
  }
  {
    auto ok = CheckRoot(Modular<11>(7), 10);
    ASSERT_TRUE(ok);
  }
  {
    auto ok = CheckRoot(Modular<11>(8), 10);
    ASSERT_TRUE(ok);
  }
  {
    auto ok = CheckRoot(Modular<11>(9), 10);
    ASSERT_FALSE(ok);
  }

  {
    // 7340033
    auto constexpr P = 7 * (1 << 20) + 1;
    auto g = Modular<P>(3);
    auto ok = CheckRoot(g, P - 1);
    ASSERT_TRUE(ok);
  }
  {
    auto constexpr P = 7 * (1 << 20) + 1;
    auto g = algo::maths::algebra::Power(Modular<P>(3), 7);
    auto ok = CheckRoot(g, (1 << 20));
    ASSERT_TRUE(ok);
  }

  {
    // 998244353
    auto constexpr P = 119 * (1 << 23) + 1;
    auto g = algo::maths::algebra::Power(Modular<P>(3), 119);
    auto ok = CheckRoot(g, (1 << 23));
    ASSERT_TRUE(ok);
  }

  {
    // 998244353
    auto constexpr P = 119 * (1 << 23) + 1;
    auto g = algo::maths::algebra::Power(Modular<P>(5), 119);
    auto ok = CheckRoot(g, (1 << 23));
    ASSERT_TRUE(ok);
  }
}


void TestFindRoot() {
  {
    auto constexpr P = 2;
    int degree = 1;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }

  {
    auto constexpr P = 3;
    int degree = 2;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }

  {
    // 7340033
    auto constexpr P = 7 * (1 << 20) + 1;
    int degree = 1 << 20;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }
  {
    auto constexpr P = 7 * (1 << 20) + 1;
    int degree = 1 << 19;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }

  {
    // 998244353
    auto constexpr P = 119 * (1 << 23) + 1;
    int degree = 1 << 23;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }
  {
    auto constexpr P = 119 * (1 << 23) + 1;
    int degree = 1 << 22;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }
  {
    auto constexpr P = 119 * (1 << 23) + 1;
    int degree = 1 << 10;
    auto g = FindRoot<Modular<P>>(degree);
    auto ok = CheckRoot(g, degree);
    ASSERT_TRUE(ok);
  }
};

int main() {
  TestGenerateGroup();
  TestFindCK();
  TestCheckRoot();
  TestFindRoot();
}
