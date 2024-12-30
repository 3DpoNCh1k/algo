#include "sum_unit.hpp"
#include <tests/framework/test.hpp>

TEST(EagerPropagationStaticSegmentTree) {
  std::vector<int> values(3);
  auto segment_tree =
      algo::ranges::segment_tree::EagerPropagationStaticSegmentTree<IntAdd,
                                                                    IntSum>(
          values);
  unit::sum::OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTree) {
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationStaticSegmentTree<IntAdd,
                                                                   IntSum>(3,
                                                                           0);
  unit::sum::OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTree) {
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationDynamicSegmentTree<IntAdd,
                                                                    IntSum>(
          0, 2, [](int, int) {
            return 0;
          });
  unit::sum::OnlyApplyAtIndex(segment_tree);
}

TEST(LazyPropagationStaticSegmentTreeWithRange) {
  std::vector<int> values(3);
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationStaticSegmentTree<IntAdd,
                                                                   IntSum>(
          values);
  unit::sum::WithApplyOnRange(segment_tree);
}

TEST(LazyPropagationDynamicSegmentTreeWithRange) {
  auto segment_tree =
      algo::ranges::segment_tree::LazyPropagationDynamicSegmentTree<IntAdd,
                                                                    IntSum>(
          0, 2, 0);
  unit::sum::WithApplyOnRange(segment_tree);
}

RUN_ALL_TESTS()
