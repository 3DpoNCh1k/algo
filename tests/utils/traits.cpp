#include <string>
#include <vector>
#include <array>
#include <set>

#include "../../utils/traits/traits.hpp"

#define SINGLE_ARG(...) __VA_ARGS__

#define CHECK(func, type)        \
  {                              \
    static_assert(func<type>);   \
    static_assert(func<type&>);  \
    static_assert(func<type&&>); \
  }

#define CHECK_WITH_CONST(func, type) \
  { CHECK(func, SINGLE_ARG(const type)); }

#define CHECK_ALL(func, type)                 \
  {                                           \
    CHECK(func, SINGLE_ARG(type));            \
    CHECK_WITH_CONST(func, SINGLE_ARG(type)); \
  }

#define CHECK_HAS_TO_STRING(type) \
  { CHECK_ALL(has_ToString_v, SINGLE_ARG(type)); }

#define CHECK_IS_TO_STRINGABLE(type) \
  { CHECK_ALL(is_to_stringable_v, SINGLE_ARG(type)); }

#define CHECK_IS_ITERBALE(type) \
  { CHECK_ALL(is_iterable_v, SINGLE_ARG(type)); }

#define CHECK_IS_STD_VECTOR(type) \
  { CHECK_ALL(is_std_vector_v, SINGLE_ARG(type)); }

#define CHECK_IS_STD_ARRAY(type) \
  { CHECK_ALL(is_std_array_v, SINGLE_ARG(type)); }

struct Dummy {
  std::string ToString() const {
    return "I have ToString!";
  }
};

void RunHasToStringTests() {
  CHECK_HAS_TO_STRING(Dummy);
}

void RunIsToStringableTests() {
  CHECK_IS_TO_STRINGABLE(int);
}

void RunIterbaleTests() {
  CHECK_IS_ITERBALE(std::set<int>);
}

void RunVectorTests() {
  CHECK_IS_STD_VECTOR(std::vector<int>);
  CHECK_IS_STD_VECTOR(std::vector<std::vector<int>>);
}

void RunArrayTests() {
  CHECK_IS_STD_ARRAY(SINGLE_ARG(std::array<int, 0>));
  CHECK_IS_STD_ARRAY(SINGLE_ARG(std::array<std::array<int, 0>, 1>));
}

void RunTests() {
  RunHasToStringTests();
  RunIsToStringableTests();
  RunIterbaleTests();
  RunVectorTests();
  RunArrayTests();
}

int main() {
  RunTests();
}