#include <algo/binary_search/binary_search.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(FindFirstTrue) {
  {
    std::vector<bool> value = {false, false, false};
    auto result = algo::binary_search::FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 3);
  }
  {
    std::vector<bool> value = {false, false, true};
    auto result = algo::binary_search::FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
  {
    std::vector<bool> value = {false, true, true};
    auto result = algo::binary_search::FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {true, true, true};
    auto result = algo::binary_search::FindFirstTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
}

TEST(FindLastTrue) {
  {
    std::vector<bool> value = {false, false, false};
    auto result = algo::binary_search::FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, -1);
  }
  {
    std::vector<bool> value = {true, false, false};
    auto result = algo::binary_search::FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
  {
    std::vector<bool> value = {true, true, false};
    auto result = algo::binary_search::FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {true, true, true};
    auto result = algo::binary_search::FindLastTrue(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
}

TEST(FindFirstFalse) {
  {
    std::vector<bool> value = {true, true, true};
    auto result = algo::binary_search::FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 3);
  }
  {
    std::vector<bool> value = {true, true, false};
    auto result = algo::binary_search::FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
  {
    std::vector<bool> value = {true, false, false};
    auto result = algo::binary_search::FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {false, false, false};
    auto result = algo::binary_search::FindFirstFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
}

TEST(FindLastFalse) {
  {
    std::vector<bool> value = {false, false, false};
    auto result = algo::binary_search::FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 2);
  }
  {
    std::vector<bool> value = {false, false, true};
    auto result = algo::binary_search::FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 1);
  }
  {
    std::vector<bool> value = {false, true, true};
    auto result = algo::binary_search::FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, 0);
  }
  {
    std::vector<bool> value = {true, true, true};
    auto result = algo::binary_search::FindLastFalse(0, 2, [&value](int i) {
      return value[i];
    });
    ASSERT_EQ(result, -1);
  }
}

RUN_ALL_TESTS()
