#include <algo/trees/fenwick/operations/add.hpp>
#include <algo/trees/fenwick/statistics/sum.hpp>
#include <algo/trees/fenwick/trees.hpp>
#include <algo/utils/generators/random.hpp>
#include <tests/testing/asserts.hpp>

using namespace algo::trees::fenwick;
using namespace operations;
using namespace statistics;

struct AddAndSumTester3D {
  using RandomGenerator = algo::utils::generators::RandomGenerator;
  int n;
  int m;
  int k;
  RandomGenerator random;

  using Fenwick = Fenwick3D<Operation<AddOp>, Statistics<Sum>>;
  Fenwick fenwick;
  std::vector<std::vector<std::vector<i64>>> rival;

  explicit AddAndSumTester3D(int n, int m, int k)
      : n(n),
        m(m),
        k(k),
        random(RandomGenerator(0)),
        fenwick(Fenwick(n, m, k)),
        rival(n, std::vector<std::vector<i64>>(m, std::vector<i64>(k))) {
  }

  i64 GetAtPointFenwick(int x, int y, int z) {
    auto res = fenwick.GetAtIndex<Sum>(x, y, z);
    return res.result;
  }
  i64 GetAtPointRival(int x, int y, int z) {
    return rival[x][y][z];
  }

  void AddAtPointFenwick(int x, int y, int z, i64 value) {
    auto add_operation = AddOp{value};
    fenwick.ApplyAtIndex(add_operation, x, y, z);
  }

  void AddAtPointRival(int x, int y, int z, i64 value) {
    rival[x][y][z] += value;
  }

  i64 GetFrom3DRectangleFenwick(int x0, int x1, int y0, int y1, int z0,
                                int z1) {
    auto res = fenwick.GetFromRange<Sum>(x0, x1, y0, y1, z0, z1);
    return res.result;
  }

  i64 GetFrom3DRectangleRival(int x0, int x1, int y0, int y1, int z0, int z1) {
    i64 rival_result = 0;
    for (int x = x0; x <= x1; ++x) {
      for (int y = y0; y <= y1; ++y) {
        for (int z = z0; z <= z1; ++z) {
          rival_result += rival[x][y][z];
        }
      }
    }
    return rival_result;
  }

  void Test(int queries, i64 min_add_value, i64 max_add_value) {
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        for (int z = 0; z < k; ++z) {
          auto f = GetAtPointFenwick(x, y, z);
          auto r = GetAtPointRival(x, y, z);
          ASSERT_EQ(f, 0);
          ASSERT_EQ(r, 0);
        }
      }
    }

    for (int q = 0; q < queries; ++q) {
      if (random.GetBool()) {
        QueryAddAtPoint(min_add_value, max_add_value);
        continue;
      }
      if (random.GetBool()) {
        QueryGetAtPoint();
        continue;
      }
      QueryGetFrom3DRectangle();
    }
  }

  void QueryGetAtPoint() {
    auto x = random.GetInt(0, n - 1);
    auto y = random.GetInt(0, m - 1);
    auto z = random.GetInt(0, k - 1);

    auto result = GetAtPointFenwick(x, y, z);
    auto rival_result = GetAtPointRival(x, y, z);
    ASSERT_EQ(result, rival_result)
  }

  void QueryAddAtPoint(i64 min_add_value, i64 max_add_value) {
    auto x = random.GetInt(0, n - 1);
    auto y = random.GetInt(0, m - 1);
    auto z = random.GetInt(0, k - 1);

    auto value = random.GetInt(min_add_value, max_add_value);
    AddAtPointFenwick(x, y, z, value);
    AddAtPointRival(x, y, z, value);
  }

  void QueryGetFrom3DRectangle() {
    auto x0 = random.GetInt(0, n - 1);
    auto x1 = random.GetInt(x0, n - 1);

    auto y0 = random.GetInt(0, m - 1);
    auto y1 = random.GetInt(y0, m - 1);

    auto z0 = random.GetInt(0, k - 1);
    auto z1 = random.GetInt(z0, k - 1);

    auto result = GetFrom3DRectangleFenwick(x0, x1, y0, y1, z0, z1);
    i64 rival_result = GetFrom3DRectangleRival(x0, x1, y0, y1, z0, z1);
    ASSERT_EQ(result, rival_result);
  }
};

void TestAddAndSum() {
  { AddAndSumTester3D(3, 3, 3).Test(10, -10, 10); }
  { AddAndSumTester3D(9, 9, 9).Test(1000, -1000, 1000); }
  { AddAndSumTester3D(55, 55, 55).Test(100, -1e9, 1e9); }
}

int main() {
  TestAddAndSum();
}
