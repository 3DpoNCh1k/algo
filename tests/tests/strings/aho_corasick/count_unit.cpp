#include <string>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/count.hpp>
#include <algo/debug/debug.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using String = std::string;
using Count = algo::strings::aho_corasick::statistics::Count<String>;

TEST(Simple1) {
  std::string pattern = "a";
  algo::strings::aho_corasick::AhoCorasick<
      algo::strings::aho_corasick::Statistics<Count>, String>
      aho_corasick({pattern});
  std::string s = "aba";
  aho_corasick.Scan(s);
  auto stat = aho_corasick.Get<Count>(0);
  debug(stat.result);
  ASSERT_EQ(stat.result, 2);
}

TEST(Simple2) {
  std::vector<std::string> patterns = {"a", "aba"};
  algo::strings::aho_corasick::AhoCorasick<
      algo::strings::aho_corasick::Statistics<Count>, String>
      aho_corasick(patterns);
  std::string s = "abac";
  aho_corasick.Scan(s);
  {
    auto stat = aho_corasick.Get<Count>(0);
    debug(stat.result);
    ASSERT_EQ(stat.result, 2);
  }
  {
    auto stat = aho_corasick.Get<Count>(1);
    debug(stat.result);
    ASSERT_EQ(stat.result, 1);
  }
}

RUN_ALL_TESTS()
