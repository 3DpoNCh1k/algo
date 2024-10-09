#include <map>
#include <set>

#include <algo/utils/join.hpp>
#include <tests/framework/stubs/move_only.hpp>
#include <tests/framework/stubs/dummies.hpp>
#include "tests/framework/asserts.hpp"
#include <tests/framework/test.hpp>

using namespace algo::utils;

TEST(One) {
  auto dummy_string = DummyWithToString().ToString();
  std::vector<DummyWithToString> dummies = {DummyWithToString()};
  {
    auto s = JoinToString(dummies);
    ASSERT_EQ(s, dummy_string);
  }
  {
    std::string prefix = "with prefix";
    auto s = JoinToString(dummies, {.prefix = prefix});
    ASSERT_EQ(s, prefix + dummy_string);
  }
  {
    std::string suffix = "with suffix";
    auto s = JoinToString(dummies, {.suffix = suffix});
    ASSERT_EQ(s, dummy_string + suffix);
  }

  auto move_only_string = MoveOnlyWithToString().ToString();
  std::vector<MoveOnlyWithToString> move_onlies;
  move_onlies.emplace_back();
  {
    auto s = JoinToString(move_onlies);
    ASSERT_EQ(s, move_only_string);
  }
  {
    std::string prefix = "with prefix";
    auto s = JoinToString(move_onlies, {.prefix = prefix});
    ASSERT_EQ(s, prefix + move_only_string);
  }
  {
    std::string suffix = "with suffix";
    auto s = JoinToString(move_onlies, {.suffix = suffix});
    ASSERT_EQ(s, move_only_string + suffix);
  }
}

TEST(Many) {
  {
    std::vector<int> v = {1, 2, 3};
    auto result = JoinToString(v);
    std::string expected = "1, 2, 3";
    ASSERT_EQ(result, expected)
  }
  {
    std::set<int> s = {1, 2, 3};
    auto result = JoinToString(s, {.prefix = "{", .suffix = "}"});
    std::string expected = "{1, 2, 3}";
    ASSERT_EQ(result, expected)
  }
  {
    std::map<int, bool> m = {{1, true}, {2, false}};
    auto result = JoinToString(m, {.separator = "; "});
    std::string expected = "(1, true); (2, false)";
    ASSERT_EQ(result, expected)
  }
}

TEST(ManyWithTransform) {
  {
    std::vector<int> v = {1, 2, 3};
    auto result = JoinToString(v, [](int i) {
      return ToString(-i);
    });
    std::string expected = "-1, -2, -3";
    ASSERT_EQ(result, expected)
  }

  {
    std::vector<MoveOnly> move_onlies;
    move_onlies.emplace_back();
    move_onlies.emplace_back();
    move_onlies.emplace_back();

    int counter = 0;
    auto transformer = [&counter](auto& move_only) {
      return ToString(++counter);
    };

    auto result = JoinToString(move_onlies, transformer);
    std::string expected = "1, 2, 3";
    ASSERT_EQ(result, expected)
  }
}

RUN_ALL_TESTS()