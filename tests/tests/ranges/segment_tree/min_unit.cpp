
#include "min_unit.hpp"
#include <tests/framework/test.hpp>

using algo::ranges::updates::IntSetAdd;

TEST(EagerPropagationStaticSegmentTree) {
  std::vector<int> values(3);
  auto segment_tree =
      algo::ranges::segment_tree::EagerPropagationStaticSegmentTree<IntSetAdd,
                                                                    IntMinimum>(
          values);
  unit::min::OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTree) {
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationStaticSegmentTree<IntSetAdd,
                                                                   IntMinimum>(
          3, 0);
  unit::min::OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTree) {
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationDynamicSegmentTree<IntSetAdd,
                                                                    IntMinimum>(
          0, 2, [](int, int) {
            return 0;
          });
  unit::min::OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTreeWithRange) {
  std::vector<int> values(3);
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationStaticSegmentTree<IntSetAdd,
                                                                   IntMinimum>(
          values);
  unit::min::WithApplyOnRange(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTreeWithRange) {
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationDynamicSegmentTree<IntSetAdd,
                                                                    IntMinimum>(
          0, 2, 0);
  unit::min::WithApplyOnRange(segment_tree);
}

RUN_ALL_TESTS()
