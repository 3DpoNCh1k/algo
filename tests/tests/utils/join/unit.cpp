#include <map>
#include <set>

#include <algo/utils/join.hpp>
#include <tests/framework/stubs/move_only.hpp>
#include <tests/framework/stubs/dummies.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(One) {
  auto dummy_string = DummyWithToString().ToString();
  std::vector<DummyWithToString> dummies = {DummyWithToString()};
  {
    auto s = algo::utils::JoinToString(dummies);
    ASSERT_EQ(s, dummy_string);
  }

  auto move_only_string = MoveOnlyWithToString().ToString();
  std::vector<MoveOnlyWithToString> move_onlies;
  move_onlies.emplace_back();
  {
    auto s = algo::utils::JoinToString(move_onlies);
    ASSERT_EQ(s, move_only_string);
  }
}

TEST(Many) {
  {
    std::vector<int> v = {1, 2, 3};
    auto result = algo::utils::JoinToString(v, ", ");
    std::string expected = "1, 2, 3";
    ASSERT_EQ(result, expected)
  }
  {
    std::map<int, bool> m = {{1, true}, {2, false}};
    auto result = algo::utils::JoinToString(m, "; ");
    std::string expected = "(1, true); (2, false)";
    ASSERT_EQ(result, expected)
  }
}

TEST(ManyWithTransform) {
  {
    std::vector<int> v = {1, 2, 3};
    auto result = algo::utils::JoinToString(
        v,
        [](int i) {
          return algo::utils::ToString(-i);
        },
        " ");
    std::string expected = "-1 -2 -3";
    ASSERT_EQ(result, expected)
  }

  {
    std::vector<MoveOnly> move_onlies;
    move_onlies.emplace_back();
    move_onlies.emplace_back();
    move_onlies.emplace_back();

    int counter = 0;
    auto transformer = [&counter](auto& move_only) {
      return algo::utils::ToString(++counter);
    };

    auto result = algo::utils::JoinToString(move_onlies, transformer, ", ");
    std::string expected = "1, 2, 3";
    ASSERT_EQ(result, expected)
  }
}

RUN_ALL_TESTS()
