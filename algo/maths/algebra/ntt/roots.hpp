#pragma once

#include <cassert>
#include <utility>
#include <vector>
#include <algo/utils/types/fundamentals.hpp>
#include <algo/maths/algebra/power.hpp>
#include <algo/utils/bits.hpp>
#include <algo/utils/random/random.hpp>

namespace algo::maths::algebra::ntt {
std::pair<int, int> FindCK(int p) {
  // c*2^k + 1 = p
  int k = 0;
  int value = p - 1;
  while (value > 0 && value % 2 == 0) {
    value /= 2;
    k++;
  }
  return {value, k};
};

template <typename Modular>
std::vector<Modular> GenerateGroup(Modular g) {
  // assert Modular::Mod is prime
  assert(g != 0);
  std::vector<Modular> group = {1};
  Modular current = g;
  while (true) {
    if (current == 1) {
      break;
    }
    group.push_back(current);
    current *= g;
  }
  return group;
};

template <typename Modular>
Modular FindRoot(int degree) {
  assert(utils::bits::IsPowerOfTwo(u64(degree)));
  if (degree == 1) {
    return 1;
  }

  while (true) {
    auto g = Modular(utils::random::RandomInt(1, Modular::MOD - 1));
    if (Power(g, degree / 2) == -1) {
      return g;
    }
  }
};

template <typename Modular>
bool CheckRoot(Modular g, int degree) {
  auto group = GenerateGroup(g);
  return group.size() == degree;
};

template <typename Modular>
std::vector<Modular> UnityRoots(Modular g, int degree) {
  assert(CheckRoot(g, degree));
  return GenerateGroup(g);
};
}  // namespace algo::maths::algebra::ntt
