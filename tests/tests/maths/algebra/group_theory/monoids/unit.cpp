#include "algo/utils/debug.hpp"
#include "tests/framework/test.hpp"

#include <algo/maths/algebra/group_theory/monoids/int_plus.hpp>
#include <algo/maths/algebra/group_theory/monoids/int_min.hpp>

using namespace algo::maths::algebra::group_theory::monoid;

TEST(Simple) {
  {
    using M = IntPlus;
    auto e = M::Identity();
    dbg(e);

    auto a = 1;
    auto b = 2;
    auto c = M::Combine(a, b);
    dbg(c);
  }

  {
    using M = IntMin;
    auto e = M::Identity();
    dbg(e);

    auto a = 1;
    auto b = 2;
    auto c = M::Combine(a, b);
    dbg(c);
  }
}

RUN_ALL_TESTS()
