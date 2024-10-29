#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>

#include <algo/utils/to_string/to_string.hpp>
#include <tests/framework/stubs/dummies.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

using algo::utils::ToString;

#define CHECK_TO_STRING(object, expected) \
  { ASSERT_EQ(ToString(object), expected); }

TEST(Pair) {
  {
    auto p = std::make_pair(1, 2);
    CHECK_TO_STRING(p, "(1, 2)");
  }
  {
    auto p = std::make_pair("Hello!", 2);
    CHECK_TO_STRING(p, "(Hello!, 2)");
  }
}

TEST(Array) {
  {
    auto a = std::array<int, 0>();
    CHECK_TO_STRING(a, "[]");
  }
  {
    auto a = std::array<int, 3>({1, 2, 3});
    CHECK_TO_STRING(a, "[i=0: 1, i=1: 2, i=2: 3]");
  }
  {
    using Element = std::array<int, 3>;
    Element e0 = {1, 2, 3};
    Element e1 = {4, 5, 6};
    auto a = std::array<Element, 2>({e0, e1});
    std::string expected =
        "["
        "\n"
        "i=0: [i=0: 1, i=1: 2, i=2: 3]"
        ", "
        "\n"
        "i=1: [i=0: 4, i=1: 5, i=2: 6]"
        "]";
    CHECK_TO_STRING(a, expected);
  }
}

TEST(Vector) {
  {
    auto v = std::vector<int>();
    CHECK_TO_STRING(v, "[]");
  }
  {
    auto v = std::vector<int>({1, 2, 3});
    CHECK_TO_STRING(v, "[i=0: 1, i=1: 2, i=2: 3]");
  }
  {
    using Element = std::vector<int>;
    Element e0 = {1, 2, 3};
    Element e1 = {4, 5, 6};
    auto v = std::vector<Element>({e0, e1});
    std::string expected =
        "["
        "\n"
        "i=0: [i=0: 1, i=1: 2, i=2: 3]"
        ", "
        "\n"
        "i=1: [i=0: 4, i=1: 5, i=2: 6]"
        "]";
    CHECK_TO_STRING(v, expected);
  }
}

TEST(Bitset) {
  std::string bit_string = "00110010";
  auto b = std::bitset<8>(bit_string);
  CHECK_TO_STRING(b, bit_string);
}

TEST(String) {
  std::string s = "Hello, world!";
  CHECK_TO_STRING(s, s);
}

TEST(VectorBool) {
  {
    auto v = std::vector<bool>({false, true, false});
    CHECK_TO_STRING(v, "010");
  }
}

TEST(HasToString) {
  CHECK_TO_STRING(DummyWithToString(), "I'm DummyWithToString!");
}

TEST(ToStringable) {
  CHECK_TO_STRING(123, "123");
  CHECK_TO_STRING(123L, "123");
}

TEST(Iterable) {
  {
    auto s = std::set<int>({1, 2, 3});
    std::string expected = "{1, 2, 3}";
    CHECK_TO_STRING(s, expected);
  }
  {
    auto ms = std::multiset<int>({1, 1, 2});
    std::string expected = "{1, 1, 2}";
    CHECK_TO_STRING(ms, expected);
  }
  {
    auto hs = std::unordered_set<int>({1, 2});
    std::string expected1 = "{1, 2}";
    std::string expected2 = "{2, 1}";
    auto result = ToString(hs);
    ASSERT_TRUE(result == expected1 || result == expected2);
  }
  {
    auto m = std::map<std::string, int>({{"key1", 1}, {"key2", 2}});
    std::string expected = "{(key1, 1), (key2, 2)}";
    CHECK_TO_STRING(m, expected);
  }
  {
    auto mm = std::multimap<std::string, int>({{"key1", 1}, {"key1", 2}});
    std::string expected1 = "{(key1, 1), (key1, 2)}";
    std::string expected2 = "{(key1, 2), (key1, 1)}";
    auto result = ToString(mm);
    ASSERT_TRUE(result == expected1 || result == expected2);
  }
  {
    auto hm = std::unordered_map<std::string, int>({{"key1", 1}, {"key2", 2}});
    std::string expected1 = "{(key1, 1), (key2, 2)}";
    std::string expected2 = "{(key2, 2), (key1, 1)}";
    auto result = ToString(hm);
    ASSERT_TRUE(result == expected1 || result == expected2);
  }
  {
    auto q = std::deque<int>({1, 2, 3});
    std::string expected = "{1, 2, 3}";
    CHECK_TO_STRING(q, expected);
  }
}

TEST(Fundamentals) {
  CHECK_TO_STRING(false, "false");
  CHECK_TO_STRING(true, "true");
  CHECK_TO_STRING("Hi", "Hi");
  CHECK_TO_STRING('a', "a");
}

RUN_ALL_TESTS()
