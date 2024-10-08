#include <string>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/count.hpp>
#include <algo/utils/debug.hpp>
#include <tests/testing/asserts.hpp>

using namespace algo::strings::aho_corasick;

using String = std::string;
using Count = algo::strings::aho_corasick::statistics::Count<String>;

void Test() {
  {
    std::string pattern = "a";
    AhoCorasick<Statistics<Count>, String> aho_corasick({pattern});
    std::string s = "aba";
    aho_corasick.Scan(s);
    auto stat = aho_corasick.Get<Count>(0);
    dbg(stat.result);
    ASSERT_EQ(stat.result, 2);
  }
  {
    std::vector<std::string> patterns = {"a", "aba"};
    AhoCorasick<Statistics<Count>, String> aho_corasick(patterns);
    std::string s = "abac";
    aho_corasick.Scan(s);
    {
      auto stat = aho_corasick.Get<Count>(0);
      dbg(stat.result);
      ASSERT_EQ(stat.result, 2);
    }
    {
      auto stat = aho_corasick.Get<Count>(1);
      dbg(stat.result);
      ASSERT_EQ(stat.result, 1);
    }
  }
}

int main() {
  Test();
}
