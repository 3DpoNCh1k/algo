#include <algo/data_structures/mex.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

TEST(Simple) {
  auto mex = algo::data_structures::MEX(5);
  ASSERT_EQ(mex.Mex(), 0);
  mex.Add(1);
  ASSERT_EQ(mex.Mex(), 0);
  mex.Add(0);
  ASSERT_EQ(mex.Mex(), 2);
  mex.Remove(1);
  ASSERT_EQ(mex.Mex(), 1);
}

TEST(Duplicates) {
  auto mex = algo::data_structures::MEX(5);
  ASSERT_EQ(mex.Mex(), 0);
  mex.Add(0);
  ASSERT_EQ(mex.Mex(), 1);
  mex.Add(0);
  ASSERT_EQ(mex.Mex(), 1);
  mex.Remove(0);
  ASSERT_EQ(mex.Mex(), 1);
  mex.Remove(0);
  ASSERT_EQ(mex.Mex(), 0);
}

RUN_ALL_TESTS()
