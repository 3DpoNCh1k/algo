#include <algo/binary_search/binary_search.hpp>
#include "tests/testing/asserts.hpp"

using namespace algo::binary_search;

void TestFindFirstTrue() {
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

void TestFindLastTrue() {
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

void TestFindFirstFalse() {
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

void TestFindLastFalse() {
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

int main() {
  TestFindFirstTrue();
  TestFindLastTrue();
  TestFindFirstFalse();
  TestFindLastFalse();
}
