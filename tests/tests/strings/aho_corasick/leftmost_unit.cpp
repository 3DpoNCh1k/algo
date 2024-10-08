#include <string>

#include <algo/strings/aho_corasick/aho_corasick.hpp>
#include <algo/strings/aho_corasick/statistics/leftmost.hpp>
#include <algo/utils/debug.hpp>
#include <tests/framework/asserts.hpp>

using namespace algo::strings::aho_corasick;

using String = std::string;
using Leftmost = algo::strings::aho_corasick::statistics::Leftmost<String>;

void Test() {
  {
    std::vector<std::string> patterns = {"b", "abc"};
    AhoCorasick<Statistics<Leftmost>, String> aho_corasick(patterns);
    std::string s = "abde";
    aho_corasick.Scan(s);
    {
      auto stat = aho_corasick.Get<Leftmost>(0);
      dbg(stat.result);
      ASSERT_EQ(stat.result, 1);
    }
    {
      auto stat = aho_corasick.Get<Leftmost>(1);
      dbg(stat.result);
      ASSERT_EQ(stat.result, -1);
    }
  }
}

int main() {
  Test();
}
