#include <algo/maths/algebra/matrix/matrix.hpp>
#include <tests/framework/test.hpp>
#include "algo/ranges/range.hpp"
#include "algo/ranges/segment_tree/trees.hpp"
#include "algo/ranges/updates/set.hpp"
#include "algo/ranges/statistics/multiplication.hpp"
#include "tests/framework/asserts.hpp"

using algo::maths::algebra::matrix::IntMatrix;

TEST(EagerPropagationStaticSegmentTree) {
  auto a = IntMatrix(2, 3);
  a[0][0] = -1;
  a[0][1] = 1;
  a[0][2] = -3;
  a[1][0] = 2;
  a[1][1] = 3;
  a[1][2] = 1;
  
  auto b = IntMatrix(3, 2);
  b[0][0] = 1;
  b[0][1] = 2;
  b[1][0] = 4;
  b[1][1] = 3;
  b[2][0] = -5;
  b[2][1] = 6;

  auto c = IntMatrix(2, 1);
  c[0][0] = 7;
  c[1][0] = 2;

  using Update = algo::ranges::updates::IntMatrixSet;
  using Stat = algo::ranges::statistics::IntMatrixMultiplication;

  auto segment_tree =
      algo::ranges::segment_tree::EagerPropagationStaticSegmentTree<Update,
                                                                    Stat>(
          3, IntMatrix::Identity());

  segment_tree.ApplyAtIndex(Update(0, a));
  segment_tree.ApplyAtIndex(Update(1, b));
  segment_tree.ApplyAtIndex(Update(2, c));

  auto ab = segment_tree.GetFromRange<Stat>(algo::ranges::Range(0,1));
  
  auto expected_ab = IntMatrix(2, 2);
  expected_ab[0][0] = 18;
  expected_ab[0][1] = -17;
  expected_ab[1][0] = 9;
  expected_ab[1][1] = 19;
  
  ASSERT_EQ(ab, expected_ab)

  auto bc = segment_tree.GetFromRange<Stat>(algo::ranges::Range(1,2));
  
  auto expected_bc = IntMatrix(3, 1);
  expected_bc[0][0] = 11;
  expected_bc[1][0] = 34;
  expected_bc[2][0] = -23;
  
  ASSERT_EQ(bc, expected_bc)

  auto abc = segment_tree.GetFromRange<Stat>(algo::ranges::Range(0,2));
  
  auto expected_abc = IntMatrix(2, 1);
  expected_abc[0][0] = 92;
  expected_abc[1][0] = 101;
  
  ASSERT_EQ(abc, expected_abc)
}

RUN_ALL_TESTS()
