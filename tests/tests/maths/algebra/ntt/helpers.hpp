#pragma once

#include <vector>

#include "algo/utils/types/modular.hpp"

template <i64 Mod>
using Modular = algo::utils::Modular<i64, Mod>;

template <typename Modular>
std::vector<int> AsInts(const std::vector<Modular>& a) {
  std::vector<int> b(a.size());
  for (int i = 0; i < a.size(); ++i) {
    b[i] = a[i].GetValue();
  }
  return b;
};

template <typename Modular>
std::vector<Modular> AsModulars(const std::vector<int>& a) {
  std::vector<Modular> b(a.size());
  for (int i = 0; i < a.size(); ++i) {
    b[i] = a[i];
  }
  return b;
};
