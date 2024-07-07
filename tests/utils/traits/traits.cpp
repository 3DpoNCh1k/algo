#include <map>
#include <vector>
#include <array>
#include <set>

#include <algo/utils/traits/traits.hpp>
#include <algo/utils/preprocessor.hpp>
#include <tests/testing/stubs/dummies.hpp>
#include <tests/testing/asserts.hpp>

// NOLINTNEXTLINE
using namespace algo::utils::traits;

#define CHECK(template_value, type)             \
  {                                             \
    STATIC_ASSERT_TRUE(template_value<type>);   \
    STATIC_ASSERT_TRUE(template_value<type&>);  \
    STATIC_ASSERT_TRUE(template_value<type&&>); \
  }

#define CHECK_WITH_CONST(template_value, type) \
  { CHECK(template_value, const type); }

#define CHECK_ALL(template_value, type)     \
  {                                         \
    CHECK(template_value, type);            \
    CHECK_WITH_CONST(template_value, type); \
  }

#define CHECK_HAS_TO_STRING(type)     \
  {                                   \
    using T = type;                   \
    { CHECK_ALL(has_ToString_v, T); } \
  }

#define CHECK_IS_TO_STRINGABLE(type)      \
  {                                       \
    using T = type;                       \
    { CHECK_ALL(is_to_stringable_v, T); } \
  }

#define CHECK_IS_ITERBALE(type)      \
  {                                  \
    using T = type;                  \
    { CHECK_ALL(is_iterable_v, T); } \
  }

#define CHECK_IS_STD_VECTOR(type)      \
  {                                    \
    using T = type;                    \
    { CHECK_ALL(is_std_vector_v, T); } \
  }

#define CHECK_IS_STD_ARRAY(type)  \
  {                               \
    using T = type;               \
    CHECK_ALL(is_std_array_v, T); \
  }

void RunHasToStringTests() {
  CHECK_HAS_TO_STRING(DummyWithToString);
}

void RunIsToStringableTests() {
  CHECK_IS_TO_STRINGABLE(int);
}

void RunIterbaleTests() {
  CHECK_IS_ITERBALE(std::vector<Dummy>);
  CHECK_IS_ITERBALE(std::set<int>);
  CHECK_IS_ITERBALE(AS_SINGLE_ARGUMENT(std::map<std::string, int>));
}

void RunVectorTests() {
  CHECK_IS_STD_VECTOR(std::vector<int>);
  CHECK_IS_STD_VECTOR(std::vector<std::vector<int>>);
}

void RunArrayTests() {
  CHECK_IS_STD_ARRAY(AS_SINGLE_ARGUMENT(std::array<int, 0>));
  CHECK_IS_STD_ARRAY(AS_SINGLE_ARGUMENT(std::array<std::array<int, 0>, 1>));
}

void RunDimensionTest() {
  STATIC_ASSERT_EQ(dimension_v<int>, 0);
  STATIC_ASSERT_EQ(dimension_v<std::string>, 0);
  STATIC_ASSERT_EQ(dimension_v<std::set<int>>, 0);
  STATIC_ASSERT_EQ(dimension_v<std::vector<int>>, 1);
  STATIC_ASSERT_EQ(AS_SINGLE_ARGUMENT(dimension_v<std::array<int, 0>>), 1);
  STATIC_ASSERT_EQ(dimension_v<std::vector<std::vector<int>>>, 2);
  STATIC_ASSERT_EQ(
      AS_SINGLE_ARGUMENT(dimension_v<std::array<std::array<int, 0>, 0>>), 2);
  STATIC_ASSERT_EQ(
      AS_SINGLE_ARGUMENT(dimension_v<std::array<std::vector<int>, 0>>), 2);
};

void RunTests() {
  RunHasToStringTests();
  RunIsToStringableTests();
  RunIterbaleTests();
  RunVectorTests();
  RunArrayTests();
  RunDimensionTest();
}

int main() {
  RunTests();
}
