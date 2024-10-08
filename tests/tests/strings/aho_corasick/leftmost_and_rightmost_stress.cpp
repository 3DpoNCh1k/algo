#include <string>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/leftmost.hpp>
#include <algo/strings/aho_corasick/statistics/rightmost.hpp>

#include "helpers/brute_force.hpp"
#include "helpers/tester.hpp"
#include "helpers/stress.hpp"
#include "helpers/duel.hpp"

using namespace algo::strings::aho_corasick;
using String = std::string;
using Leftmost = algo::strings::aho_corasick::statistics::Leftmost<String>;
using Rightmost = algo::strings::aho_corasick::statistics::Rightmost<String>;

struct LeftmostBruteForce : BruteForce {
  explicit LeftmostBruteForce(const Patterns& patterns)
      : BruteForce(patterns){};

  Leftmost Get(int pattern_index) {
    const auto& pattern = patterns[pattern_index];
    auto stat = Leftmost();
    for (int i = 0; i < s.size(); ++i) {
      if (s.substr(i, pattern.size()) == pattern) {
        stat.result = i;
        break;
      }
    }
    return stat;
  };
};

struct RightmostBruteForce : BruteForce {
  explicit RightmostBruteForce(const Patterns& patterns)
      : BruteForce(patterns){};

  Rightmost Get(int pattern_index) {
    const auto& pattern = patterns[pattern_index];
    auto stat = Rightmost();
    for (int i = int(s.size()) - 1; i >= 0; --i) {
      if (s.substr(i, pattern.size()) == pattern) {
        stat.result = i;
        break;
      }
    }
    return stat;
  };
};

struct LeftmostAndRightmostTester : Tester {
  using AhoCorasickType = AhoCorasick<Statistics<Leftmost, Rightmost>, String>;
  LeftmostBruteForce leftmost_brute_force;
  RightmostBruteForce rightmost_brute_force;
  AhoCorasickType aho_corasick;
  Duel<LeftmostBruteForce, AhoCorasickType, Leftmost> leftmost_duel;
  Duel<RightmostBruteForce, AhoCorasickType, Rightmost> rightmost_duel;

  explicit LeftmostAndRightmostTester(const Patterns& patterns)
      : Tester(patterns),
        leftmost_brute_force(patterns),
        rightmost_brute_force(patterns),
        aho_corasick(patterns),
        leftmost_duel(patterns, leftmost_brute_force, aho_corasick),
        rightmost_duel(patterns, rightmost_brute_force, aho_corasick) {
  }

  void Test(const std::string& s) {
    aho_corasick.Scan(s);
    leftmost_brute_force.Scan(s);
    rightmost_brute_force.Scan(s);
    leftmost_duel.Combat(s);
    rightmost_duel.Combat(s);
    aho_corasick.ResetAllStatistics();
  }
};

int main() {
  StressShort<LeftmostAndRightmostTester>();
  StressLong<LeftmostAndRightmostTester>();
}
