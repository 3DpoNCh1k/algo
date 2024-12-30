#include <string>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/leftmost.hpp>
#include <algo/debug/debug.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using String = std::string;
using Leftmost = algo::strings::aho_corasick::statistics::Leftmost<String>;

TEST(Simple) {
  std::vector<std::string> patterns = {"b", "abc"};
  algo::strings::aho_corasick::AhoCorasick<
      algo::strings::aho_corasick::Statistics<Leftmost>, String>
      aho_corasick(patterns);
  std::string s = "abde";
  aho_corasick.Scan(s);
  {
    auto stat = aho_corasick.Get<Leftmost>(0);
    debug(stat.result);
    ASSERT_EQ(stat.result, 1);
  }
  {
    auto stat = aho_corasick.Get<Leftmost>(1);
    debug(stat.result);
    ASSERT_EQ(stat.result, -1);
  }
}

RUN_ALL_TESTS()
