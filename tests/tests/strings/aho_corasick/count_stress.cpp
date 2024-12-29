#include <string>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/count.hpp>

#include "helpers/brute_force.hpp"
#include "helpers/tester.hpp"
#include "helpers/stress.hpp"
#include "helpers/duel.hpp"
#include <tests/framework/test.hpp>

using namespace algo::strings::aho_corasick;

using String = std::string;
using Count = algo::strings::aho_corasick::statistics::Count<String>;

struct CountBruteForce : BruteForce {
  explicit CountBruteForce(const Patterns& patterns)
      : BruteForce(patterns) {};

  Count Get(int pattern_index) {
    const auto& pattern = patterns[pattern_index];
    auto stat = Count();
    for (int i = 0; i < s.size(); ++i) {
      if (s.substr(i, pattern.size()) == pattern) {
        stat.result++;
      }
    }
    return stat;
  };
};

struct CountTester : Tester {
  using BruteForceType = CountBruteForce;
  using AhoCorasickType = AhoCorasick<Statistics<Count>, String>;
  BruteForceType brute_force;
  AhoCorasickType aho_corasick;
  Duel<BruteForceType, AhoCorasickType, Count> duel;

  explicit CountTester(const Patterns& patterns)
      : Tester(patterns),
        brute_force(patterns),
        aho_corasick(patterns),
        duel(patterns, brute_force, aho_corasick) {
  }

  void Test(const std::string& s) {
    aho_corasick.Scan(s);
    brute_force.Scan(s);
    duel.Combat(s);
    aho_corasick.ResetAllStatistics();
  }
};

TEST(StressShort) {
  StressShort<CountTester>();
}

TEST(StressLong) {
  StressLong<CountTester>();
}

RUN_ALL_TESTS()
