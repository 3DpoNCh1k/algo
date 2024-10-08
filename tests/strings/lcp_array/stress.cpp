#include <string>

#include <algo/strings/suffix_array.hpp>
#include <algo/strings/lcp_array.hpp>
#include <algo/utils/generators/random.hpp>
#include <algo/utils/generators/string.hpp>

#include <tests/framework/asserts.hpp>

struct Tester {
  algo::utils::generators::RandomGenerator random;
  int max_len;
  explicit Tester(int n)
      : max_len(n),
        random(0) {
  }

  void Test(int k_rep) {
    algo::utils::generators::AsciiStringGenerator string_generator(random);
    for (int rep = 0; rep < k_rep; ++rep) {
      int len = random.GetInt(0, max_len);
      Check(string_generator.Get(len));
    }
  };

  void Check(const std::string& s) {
    auto suffix_array = algo::strings::SuffixArray(s);
    auto lcp_array = algo::strings::LcpArray(suffix_array, s);
    auto correct_lcp_array = CalculateLcpArray(suffix_array, s);
    ASSERT_EQ(lcp_array.size(), correct_lcp_array.size());
    for (int i = 0; i < lcp_array.size(); ++i) {
      ASSERT_EQ(lcp_array[i], correct_lcp_array[i]);
    }
  }

  std::vector<int> CalculateLcpArray(const std::vector<int>& suffix_array,
                                     const std::string& s) {
    int n = s.size();
    std::vector<int> lcp_array;
    for (int i = 0; i < n - 1; ++i) {
      int cur_suffix = suffix_array[i];
      int next_suffix = suffix_array[i + 1];
      int l = 0;
      while (cur_suffix + l < n && next_suffix + l < n &&
             s[cur_suffix + l] == s[next_suffix + l]) {
        ++l;
      }
      lcp_array.push_back(l);
    }
    return lcp_array;
  };
};

int main() {
  Tester(10).Test(10'000);
  Tester(100).Test(1000);
  Tester(1000).Test(1000);
}
