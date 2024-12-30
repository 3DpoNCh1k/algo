#include <algo/debug/debug.hpp>
#include <tests/framework/test.hpp>

#include <algo/maths/algebra/group_theory/monoids/int_plus.hpp>
#include <algo/maths/algebra/group_theory/monoids/int_min.hpp>

namespace gt = algo::maths::algebra::group_theory;

TEST(Simple) {
  {
    auto e = gt::monoid::IntPlus::Identity();
    debug(e);

    auto a = 1;
    auto b = 2;
    auto c = gt::monoid::IntPlus::Combine(a, b);
    debug(c);
  }

  {
    auto e = gt::monoid::IntMin::Identity();
    debug(e);

    auto a = 1;
    auto b = 2;
    auto c = gt::monoid::IntMin::Combine(a, b);
    debug(c);
  }
}

RUN_ALL_TESTS()
