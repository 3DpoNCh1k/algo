#include <algo/trees/fenwick/operations/operation.hpp>
#include <algo/trees/fenwick/statistics/base.hpp>
#include "algo/trees/fenwick/details/fenwick_tree.hpp"
#include "algo/trees/fenwick/operations/add.hpp"
#include "algo/trees/fenwick/statistics/statistics.hpp"
#include "algo/trees/fenwick/statistics/sum.hpp"
#include "algo/utils/debug.hpp"
#include "algo/utils/generators/random_generator.hpp"
#include "tests/testing/asserts.hpp"

#include "algo/trees/fenwick/trees.hpp"

using namespace algo::trees::fenwick;

using std::cout;
using std::endl;

void TestOperation() {
  // auto x = operations::At(1);
  // auto x = operations::At(1, 2, 3);
  // dbg(x.v);

  // auto res = x.Apply(1);

  // cout << typeid(decltype(x)::RT<char>).name() << endl;

  auto a = operations::Apply(0.5).At(1);
  auto b = operations::Apply(0.5).At(1, 2);

  // auto b = operations::details::F(0.5, 1, 2);
  // auto b = operations::At(1, 2).Apply(0.5);
  // auto c = operations::At(1, 2, 3).Apply(0.5);
  cout << typeid(a).name() << endl;
  cout << typeid(b).name() << endl;

  double op = 0;
  int i = 1;
  int j = 2;
  {
    auto c = operations::Apply(op).At(i, j);
    cout << c.index << " " << c.operation.index << endl;
    ASSERT_EQ(c.index, i);
    ASSERT_EQ(c.operation.index, j);
  }
  {
    // auto c = operations::Apply(op).AtX(i, j);
    // cout << c.index << " " << c.operation.index << endl;
  }
  {
    auto c = statistics::Get<double>().From(i, j);
    ASSERT_EQ(c.l, i);
    ASSERT_EQ(c.r, j);
  }
};

void TestFen() {
  using namespace operations;
  using namespace statistics;
  using IndexOp = OperationAtIndex<AddOp>;
  using RangeStat = StatisticsFromRange<Sum>;
  using FT = details::FenwickTreeImpl<IndexOp, std::tuple<Sum>>;

  auto tree = FT(4);
  {
    auto add = AddOp{1};
    tree.Apply(IndexOp(0, add));
  }
  {
    auto add = AddOp{1};
    tree.Apply(IndexOp(2, add));
  }
  {
    auto range = RangeStat(0, 3);
    auto res = tree.GetFromRange(range);
    cout << "res.result = " << res.result << endl;
  }
}

using namespace algo::trees::fenwick;
using namespace operations;
using namespace statistics;

// void StressTest() {
//   dbg("StressTest");
//   auto random = algo::utils::generators::RandomGenerator(0);

//   const int REP = 50;
//   for (int n = 1; n <= 10; ++n) {
//     auto fenwick = FenwickTree<Operation<AddOp>, Statistics<Sum>>(n);
//     dbg(n);
//     for (int i = 0; i < n; ++i) {
//       auto res = fenwick.GetAtIndex<Sum>(i);
//       assert(res.result == 0);
//     }

//     for (int rep = 0; rep < REP; ++rep) {
//       auto value = random.GetBool() ? 1 : 0;
//       auto idx = random.GetInt(0, n - 1);
//       // fenwick.SetValue(k, value);
//       auto add = AddOp{value};
//       dbg(rep, idx, value);
//       fenwick.ApplyAtIndex(add, idx);
//       for (int i = 0; i < n; ++i) {
//         dbg("GetAtIndex", i);
//         auto res = fenwick.GetAtIndex<Sum>(i);
//         assert(res.result >= 0);
//       }
//     }
//   }
// }

int main() {
  TestOperation();
  TestFen();
}
