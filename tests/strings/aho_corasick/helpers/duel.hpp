#pragma once

#include <string>
#include <vector>

#include <tests/testing/asserts.hpp>

template <typename BruteForce, typename AhoCorasick, typename Statistics>
struct Duel {
  using Patterns = std::vector<std::string>;
  const Patterns& patterns;
  BruteForce& brute_force;
  AhoCorasick& aho_corasick;
  explicit Duel(const Patterns& patterns, BruteForce& brute_force,
                AhoCorasick& aho_corasick)
      : patterns(patterns),
        brute_force(brute_force),
        aho_corasick(aho_corasick) {
  }

  void Combat(const std::string& s) {
    for (int pattern_index = 0; pattern_index < patterns.size();
         ++pattern_index) {
      auto stat = aho_corasick.template Get<Statistics>(pattern_index);
      auto correct_stat = brute_force.Get(pattern_index);
      ASSERT_EQ(stat, correct_stat);
    }
  };
};
