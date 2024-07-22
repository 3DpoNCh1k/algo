#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <algo/utils/generators/random.hpp>
#include <algo/utils/generators/string.hpp>

using RandomGenerator = algo::utils::generators::RandomGenerator;
using StringGenerator = algo::utils::generators::StringGenerator;

auto GeneratePatterns(int max_pattern_count, int max_pattern_length,
                      RandomGenerator& random) {
  StringGenerator string_generator(random);
  std::vector<std::string> patterns;
  int n = random.GetInt(1, max_pattern_count);
  for (int i = 0; i < n; ++i) {
    int len = random.GetInt(1, max_pattern_length);
    patterns.push_back(string_generator.Get(len));
  }
  if (n < max_pattern_count && random.GetBool()) {
    int index = random.GetInt(0, patterns.size() - 1);
    patterns.push_back(patterns[index]);
    std::shuffle(patterns.begin(), patterns.end(), random.GetEngine());
  }
  return patterns;
}

template <typename Tester>
void StressShort() {
  RandomGenerator random(0);
  StringGenerator string_generator(random);
  for (int rep = 0; rep < 100; ++rep) {
    auto patterns = GeneratePatterns(10, 5, random);
    auto tester = Tester(patterns);
    for (int q = 0; q < 100; ++q) {
      int len = random.GetInt(0, 50);
      auto s = string_generator.Get(len);
      tester.Test(s);
    }
  }
}

template <typename Tester>
void StressLong() {
  RandomGenerator random(123);
  StringGenerator string_generator(random);
  for (int rep = 0; rep < 100; ++rep) {
    auto patterns = GeneratePatterns(5, 15, random);
    auto tester = Tester(patterns);
    for (int q = 0; q < 100; ++q) {
      int len = random.GetInt(0, 100);
      auto s = string_generator.Get(len);
      tester.Test(s);
    }
  }
}
