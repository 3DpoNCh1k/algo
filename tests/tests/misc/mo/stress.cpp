#include <algo/misc/mo.hpp>
#include <algo/maths/geometry/point.hpp>
#include <algo/maths/geometry/vector.hpp>
#include <algo/utils/random/random.hpp>
#include <tests/framework/asserts.hpp>
#include <tests/framework/test.hpp>

void Test(int from, int to, int k_points, int k_rep, bool as_segment = false) {
  using Point = algo::maths::geometry::Point<int>;

  for (int rep = 0; rep < k_rep; ++rep) {
    std::vector<Point> points;

    for (int i = 0; i < k_points; ++i) {
      int x = algo::utils::random::RandomInt(from, to);
      int y = algo::utils::random::RandomInt(from, to);
      if (as_segment) {
        auto l = std::min(x,y);
        auto r = std::max(x,y);
        x = l;
        y = r;
      }
      points.push_back({x, y});
    }
    
    auto order = algo::misc::Mo(points);
    // check permutation
    ASSERT_EQ(order.size(), k_points);
    for (int i = 0; i < k_points; ++i) {
      ASSERT_CONTAINS(order, i);
    }
    // check dist
    int dist_x = 0;
    int dist_y = 0;
    for (int i = 1; i < order.size(); ++i) {
      auto next = order[i];
      auto prev = order[i - 1];
      auto diff = points[next] - points[prev];
      
      dist_x += abs(diff.x);
      dist_y += abs(diff.y);
    }

    const auto bound = to - from + 1;
    const auto chunk_size = std::sqrt(bound + 1) + 1;
    const auto chunk_count = chunk_size;
    const auto x_diff = chunk_size * (k_points);
    const auto y_diff_in_chunk = chunk_count * (bound + 1);
    const auto y_diff_between_chunks = chunk_count * (bound + 1);

    ASSERT_LE(dist_x, x_diff);
    ASSERT_LE(dist_y, y_diff_in_chunk + y_diff_between_chunks);
  }
}

TEST(Small) {
  Test(0, 5, 5, 500);
}

TEST(SmallSegments) {
  Test(0, 5, 5, 500, true);
}


TEST(Medium) {
  Test(-10, 10, 10, 5000);
}

TEST(MediumSegments) {
  Test(-10, 10, 10, 5000, true);
}

TEST(Large) {
  Test(-1000, 1000, 1000, 500);
}

TEST(LargeSegments) {
  Test(-1000, 1000, 1000, 500, true);
}

RUN_ALL_TESTS()
