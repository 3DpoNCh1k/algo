#pragma once

#include <cassert>

#include <algo/ranges/statistics/value_of.hpp>
#include <algo/ranges/range.hpp>

namespace algo::ranges::updates {

struct Nop {
  Nop Compose(Nop update) const {
    return Nop();
  };

  template<typename Range>
  Nop OnSubrange(Range subrange) const {
    return Nop();
  }

  template<typename Stat>
  auto Apply(statistics::ValueOf<Stat> value) const {
    return value.value;
  }
};

}  // namespace algo::ranges::updates
