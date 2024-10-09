#include <algo/trees/fenwick/operations/add.hpp>
#include <algo/trees/fenwick/statistics/sum.hpp>
#include <algo/trees/fenwick/trees.hpp>
#include <algo/utils/random/random.hpp>
#include <tests/framework/asserts.hpp>
#include "tests/framework/test.hpp"

using namespace algo::trees::fenwick;
using namespace algo::utils::random;
using namespace operations;
using namespace statistics;

struct AddAndSumTester2D {
  int n;
  int m;

  using Fenwick = Fenwick2D<Operation<AddOp>, Statistics<Sum>>;
  Fenwick fenwick;
  std::vector<std::vector<i64>> rival;

  explicit AddAndSumTester2D(int n, int m)
      : n(n),
        m(m),
        fenwick(Fenwick(n, m)),
        rival(n, std::vector<i64>(m)) {
  }

  i64 GetAtPointFenwick(int i, int j) {
    auto res = fenwick.GetAtIndex<Sum>(i, j);
    return res.result;
  }
  i64 GetAtPointRival(int i, int j) {
    return rival[i][j];
  }

  void AddAtPointFenwick(int i, int j, i64 value) {
    auto add_operation = AddOp{value};
    fenwick.ApplyAtIndex(add_operation, i, j);
  }

  void AddAtPointRival(int i, int j, i64 value) {
    rival[i][j] += value;
  }

  i64 GetFromRectangleFenwick(int row0, int row1, int col0, int col1) {
    auto res = fenwick.GetFromRange<Sum>(row0, row1, col0, col1);
    return res.result;
  }

  i64 GetFromRectangleRival(int row0, int row1, int col0, int col1) {
    i64 rival_result = 0;
    for (int r = row0; r <= row1; ++r) {
      for (int c = col0; c <= col1; ++c) {
        rival_result += rival[r][c];
      }
    }
    return rival_result;
  }

  void Test(int queries, i64 min_add_value, i64 max_add_value) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        auto f = GetAtPointFenwick(i, j);
        auto r = GetAtPointRival(i, j);
        ASSERT_EQ(f, 0);
        ASSERT_EQ(r, 0);
      }
    }

    for (int q = 0; q < queries; ++q) {
      if (Maybe()) {
        QueryAddAtPoint(min_add_value, max_add_value);
        continue;
      }
      if (Maybe()) {
        QueryGetAtPoint();
        continue;
      }
      QueryGetFromRectangle();
    }
  }

  void QueryGetAtPoint() {
    auto row = RandomInt(0, n - 1);
    auto col = RandomInt(0, m - 1);

    auto result = GetAtPointFenwick(row, col);
    auto rival_result = GetAtPointRival(row, col);
    ASSERT_EQ(result, rival_result)
  }

  void QueryAddAtPoint(i64 min_add_value, i64 max_add_value) {
    auto row = RandomInt(0, n - 1);
    auto col = RandomInt(0, m - 1);
    auto value = RandomInt(min_add_value, max_add_value);
    AddAtPointFenwick(row, col, value);
    AddAtPointRival(row, col, value);
  }

  void QueryGetFromRectangle() {
    auto row0 = RandomInt(0, n - 1);
    auto row1 = RandomInt(row0, n - 1);

    auto col0 = RandomInt(0, m - 1);
    auto col1 = RandomInt(col0, m - 1);

    auto result = GetFromRectangleFenwick(row0, row1, col0, col1);
    i64 rival_result = GetFromRectangleRival(row0, row1, col0, col1);
    ASSERT_EQ(result, rival_result);
  }
};

TEST(StressSmall) {
  AddAndSumTester2D(5, 5).Test(10, -10, 10);
}

TEST(StressMedium) {
  AddAndSumTester2D(33, 33).Test(100, -1000, 1000);
}

TEST(StressBig) {
  AddAndSumTester2D(111, 111).Test(1000, -1e9, 1e9);
}

RUN_ALL_TESTS()