#include <algo/binary_search/binary_search.hpp>
#include "tests/framework/asserts.hpp"
#include <tests/framework/test.hpp>

using namespace algo::binary_search;

TEST(FindFirstTrue) {
  {
    std::vector<bool> value = {false, false, false};
    auto result = FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 3);
  }
  {
    std::vector<bool> value = {false, false, true};
    auto result = FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
  {
    std::vector<bool> value = {false, true, true};
    auto result = FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {true, true, true};
    auto result = FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
}

TEST(FindLastTrue) {
  {
    std::vector<bool> value = {false, false, false};
    auto result = FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, -1);
  }
  {
    std::vector<bool> value = {true, false, false};
    auto result = FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
  {
    std::vector<bool> value = {true, true, false};
    auto result = FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {true, true, true};
    auto result = FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
}

TEST(FindFirstFalse) {
  {
    std::vector<bool> value = {true, true, true};
    auto result = FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 3);
  }
  {
    std::vector<bool> value = {true, true, false};
    auto result = FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
  {
    std::vector<bool> value = {true, false, false};
    auto result = FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {false, false, false};
    auto result = FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
}

TEST(FindLastFalse) {
  {
    std::vector<bool> value = {false, false, false};
    auto result = FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
  {
    std::vector<bool> value = {false, false, true};
    auto result = FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {false, true, true};
    auto result = FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
  {
    std::vector<bool> value = {true, true, true};
    auto result = FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, -1);
  }
}

RUN_ALL_TESTS()
