#include <string>

#include <algo/strings/suffix_array.hpp>
#include "algo/utils/generators/random.hpp"
#include "tests/testing/asserts.hpp"

struct Tester {
  algo::utils::generators::RandomGenerator random;
  int max_n;
  explicit Tester(int n)
      : max_n(n) {
  }

  void Test(int k_rep) {
    for (int rep = 0; rep < k_rep; ++rep) {
      int n = random.GetInt(1, max_n);
      std::string s;
      for (int i = 0; i < n; ++i) {
        char ch = random.GetInt(0, 255);
        s.push_back(ch);
      }
      Check(s);
    }
  };

  void Check(const std::string& s) {
    auto suffix_array = algo::strings::SuffixArray(s);

    auto order = suffix_array.GetSuffixArray();
    auto correct_order = CalculateSuffixArray(s);
    ASSERT_EQ(order.size(), correct_order.size());
    for (int i = 0; i < order.size(); ++i) {
      ASSERT_EQ(order[i], correct_order[i]);
    }

    auto lcp = suffix_array.GetLcpArray();
    auto correct_lcp = CalculateLcpArray(order, s);
    ASSERT_EQ(lcp.size(), correct_lcp.size());
    for (int i = 0; i < lcp.size(); ++i) {
      ASSERT_EQ(lcp[i], correct_lcp[i]);
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

  std::vector<int> CalculateLcpArray(const std::vector<int>& suffix_array,
                                     const std::string& s) {
    int n = s.size();
    std::vector<int> lcp;
    for (int i = 0; i < n - 1; ++i) {
      int cur_suffix = suffix_array[i];
      int next_suffix = suffix_array[i + 1];
      int l = 0;
      while (cur_suffix + l < n && next_suffix + l < n &&
             s[cur_suffix + l] == s[next_suffix + l]) {
        ++l;
      }
      lcp.push_back(l);
    }
    return lcp;
  };
};

int main() {
  Tester(10).Test(1000);
  Tester(100).Test(100);
}
