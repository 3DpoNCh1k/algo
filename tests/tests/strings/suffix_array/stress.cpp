#include <string>

#include <algo/strings/suffix_array.hpp>
#include <algo/utils/random/random.hpp>
#include <algo/utils/generators/string.hpp>

#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

struct Tester {
  int max_len;
  explicit Tester(int n)
      : max_len(n) {
  }

  void Test(int k_rep) {
    auto string_generator = algo::utils::generators::StringGenerator();
    for (int rep = 0; rep < k_rep; ++rep) {
      int len = algo::utils::random::RandomInt(0, max_len);
      Check(string_generator.Printable(len));
    }
  };

  void Check(const std::string& s) {
    auto suffix_array = algo::strings::SuffixArray(s);
    auto correct_suffix_array = CalculateSuffixArray(s);
    ASSERT_EQ(suffix_array.size(), correct_suffix_array.size());
    for (int i = 0; i < suffix_array.size(); ++i) {
      ASSERT_EQ(suffix_array[i], correct_suffix_array[i]);
    }
  }

  std::vector<int> CalculateSuffixArray(const std::string& s) {
    int n = s.size();
    std::vector<std::string> suffixes;
    for (int i = 0; i < n; ++i) {
      suffixes.emplace_back(s.substr(i));
    }
    std::sort(suffixes.begin(), suffixes.end());
    std::vector<int> order;
    for (const auto& suffix : suffixes) {
      int i = n - suffix.size();
      order.push_back(i);
    }
    return order;
  };
};

TEST(StressSmall) {
  Tester(10).Test(10'000);
}

TEST(StressMedium) {
  Tester(100).Test(1000);
}

TEST(StressBig) {
  Tester(1000).Test(1000);
}

RUN_ALL_TESTS()
