#pragma once

#include <string>
#include <vector>

#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/string.hpp>

using algo::utils::random::Maybe;
using algo::utils::random::RandomInt;
using algo::utils::random::Shuffle;

template <typename GeneratorFunction>
auto GeneratePatterns(int max_pattern_count, int max_pattern_length,
                      GeneratorFunction&& gf) {
  std::vector<std::string> patterns;
  int n = RandomInt(1, max_pattern_count);
  for (int i = 0; i < n; ++i) {
    int len = RandomInt(1, max_pattern_length);
    patterns.push_back(gf(len));
  }
  if (n < max_pattern_count && Maybe()) {
    int index = RandomInt(0, patterns.size() - 1);
    patterns.push_back(patterns[index]);
    Shuffle(patterns);
  }
  return patterns;
}

template <typename Tester>
void StressShort() {
  auto string_generator = algo::utils::generators::StringGenerator();
  for (int rep = 0; rep < 1000; ++rep) {
    auto patterns = GeneratePatterns(2, 3, [&string_generator](int len) {
      return string_generator.Lowercase(len);
    });
    auto tester = Tester(patterns);
    for (int q = 0; q < 1000; ++q) {
      int len = RandomInt(0, 10);
      auto s = string_generator.Lowercase(len);
      tester.Test(s);
    }
  }
}

template <typename Tester>
void StressLong() {
  {
    auto string_generator = algo::utils::generators::StringGenerator();
    for (int rep = 0; rep < 100; ++rep) {
      auto patterns = GeneratePatterns(5, 15, [&string_generator](int len) {
        return string_generator.Lowercase(len);
      });
      auto tester = Tester(patterns);
      for (int q = 0; q < 100; ++q) {
        int len = RandomInt(0, 100);
        auto s = string_generator.Lowercase(len);
        tester.Test(s);
      }
    }
  }

  {
    auto string_generator = algo::utils::generators::StringGenerator();
    for (int rep = 0; rep < 10; ++rep) {
      auto patterns = GeneratePatterns(5, 5, [&string_generator](int len) {
        return string_generator.Printable(len);
      });
      auto tester = Tester(patterns);
      for (int q = 0; q < 50; ++q) {
        int len = 10'000;
        auto s = string_generator.Printable(len);
        tester.Test(s);
      }
    }
  }
}
