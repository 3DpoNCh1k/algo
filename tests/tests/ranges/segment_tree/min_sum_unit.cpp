#include "sum_unit.hpp"
#include "min_unit.hpp"

#include "tests/framework/test.hpp"

TEST(EagerPropagationStaticSegmentTree) {
  std::vector<int> values(3);
  {
    auto segment_tree =
        EagerPropagationStaticSegmentTree<IntSetAdd, IntSum, IntMinimum>(
            values);
    unit::sum::OnlyApplyAtIndex(segment_tree);
  }
  {
    auto segment_tree =
        EagerPropagationStaticSegmentTree<IntSetAdd, IntSum, IntMinimum>(
            values);
    unit::min::OnlyApplyAtIndex(segment_tree);
  }
}

TEST(LazyPropagationStaticSegmentTree) {
  {
    auto segment_tree =
        LazyPropagationStaticSegmentTree<IntSetAdd, IntSum, IntMinimum>(3, 0);
    unit::sum::OnlyApplyAtIndex(segment_tree);
  }
  {
    auto segment_tree =
        LazyPropagationStaticSegmentTree<IntSetAdd, IntSum, IntMinimum>(3, 0);
    unit::min::OnlyApplyAtIndex(segment_tree);
  }
}

TEST(LazyPropagationStaticSegmentTreeWithRange) {
  std::vector<int> values(3);
  {
    auto segment_tree =
        LazyPropagationStaticSegmentTree<IntSetAdd, IntSum, IntMinimum>(values);
    unit::sum::WithApplyOnRange(segment_tree);
  }
  {
    auto segment_tree =
        LazyPropagationStaticSegmentTree<IntSetAdd, IntSum, IntMinimum>(values);
    unit::min::WithApplyOnRange(segment_tree);
  }
}

RUN_ALL_TESTS()