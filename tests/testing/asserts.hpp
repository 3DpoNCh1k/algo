#pragma once

#include <cassert>

#define ASSERT_TRUE(condition) \
  { assert(condition); }

#define ASSERT_FALSE(condition) \
  { assert(!(condition)); }

#define ASSERT_EQ(a, b) ASSERT_TRUE((a) == (b))
#define ASSERT_NE(a, b) ASSERT_TRUE((a) != (b))
#define ASSERT_GT(a, b) ASSERT_TRUE((a) > (b))
#define ASSERT_GE(a, b) ASSERT_TRUE((a) >= (b))
#define ASSERT_LT(a, b) ASSERT_TRUE((a) < (b))
#define ASSERT_LE(a, b) ASSERT_TRUE((a) <= (b))

#define STATIC_ASSERT_TRUE(condition) \
  { static_assert(condition); }

#define STATIC_ASSERT_FALSE(condition) \
  { static_assert(!(condition)); }

#define STATIC_ASSERT_EQ(a, b) STATIC_ASSERT_TRUE((a) == (b))
#define STATIC_ASSERT_NE(a, b) STATIC_ASSERT_TRUE((a) != (b))
#define STATIC_ASSERT_GT(a, b) STATIC_ASSERT_TRUE((a) > (b))
#define STATIC_ASSERT_GE(a, b) STATIC_ASSERT_TRUE((a) >= (b))
#define STATIC_ASSERT_LT(a, b) STATIC_ASSERT_TRUE((a) < (b))
#define STATIC_ASSERT_LE(a, b) STATIC_ASSERT_TRUE((a) <= (b))
