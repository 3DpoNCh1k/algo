#include <utility>

#include <algo/graphs/grid.hpp>
#include <tests/testing/asserts.hpp>

using namespace algo::graphs;

void TestNeighbors4() {
  {
    auto neighbors = Grid(1, 1).Neighbors4(0, 0);
    ASSERT_TRUE(neighbors.empty());
  }
  {
    auto neighbors = Grid(1, 3).Neighbors4(0, 0);
    ASSERT_EQ(neighbors.size(), 1);
    auto neighbor = std::make_pair(0, 1);
    ASSERT_CONTAINS(neighbors, neighbor);
  }
  {
    auto neighbors = Grid(1, 3).Neighbors4(0, 1);
    ASSERT_EQ(neighbors.size(), 2);
    {
      auto neighbor = std::make_pair(0, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(0, 2);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
  {
    auto neighbors = Grid(3, 2).Neighbors4(1, 0);
    ASSERT_EQ(neighbors.size(), 3);
    {
      auto neighbor = std::make_pair(0, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(1, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(2, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
  {
    auto neighbors = Grid(3, 3).Neighbors4(1, 1);
    ASSERT_EQ(neighbors.size(), 4);
    {
      auto neighbor = std::make_pair(0, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(1, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(1, 2);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(2, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
}

void TestNeighbors8() {
  {
    auto neighbors = Grid(1, 1).Neighbors8(0, 0);
    ASSERT_TRUE(neighbors.empty());
  }
  {
    auto neighbors = Grid(3, 1).Neighbors8(0, 0);
    ASSERT_EQ(neighbors.size(), 1);
    {
      auto neighbor = std::make_pair(1, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
  {
    auto neighbors = Grid(3, 1).Neighbors8(1, 0);
    ASSERT_EQ(neighbors.size(), 2);
    {
      auto neighbor = std::make_pair(0, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(2, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
  {
    auto neighbors = Grid(2, 2).Neighbors8(0, 0);
    ASSERT_EQ(neighbors.size(), 3);
    {
      auto neighbor = std::make_pair(0, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(1, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(1, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
  {
    auto neighbors = Grid(3, 2).Neighbors8(1, 1);
    ASSERT_EQ(neighbors.size(), 5);
    {
      auto neighbor = std::make_pair(0, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(0, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(1, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(2, 0);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
    {
      auto neighbor = std::make_pair(2, 1);
      ASSERT_CONTAINS(neighbors, neighbor);
    }
  }
  {
    auto neighbors = Grid(3, 3).Neighbors8(1, 1);
    ASSERT_EQ(neighbors.size(), 8);
    for (int row = 0; row < 3; ++row) {
      for (int col = 0; col < 3; ++col) {
        if (row == 1 && col == 1) {
          continue;
        }
        auto neighbor = std::make_pair(row, col);
        ASSERT_CONTAINS(neighbors, neighbor);
      }
    }
  }
}

int main() {
  TestNeighbors4();
  TestNeighbors8();
}
