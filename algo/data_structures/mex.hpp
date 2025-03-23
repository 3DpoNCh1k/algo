#pragma once

#include <cassert>
#include <set>

namespace algo::data_structures {
struct MinimumExcluded {
  // multiset [0, n]
  explicit MinimumExcluded(int n) {
    for(int v = 0; v <= n + 1; ++v) {
        excluded_.insert(v);
    }
  }

  void Add(int v) {
    excluded_.erase(v);
    included_.insert(v);
  }

  void Remove(int v) {
    assert(Contains(v));
    included_.erase(included_.find(v));
    if (!Contains(v)) {
        excluded_.insert(v);
    }
  }

  int Count(int v) {
    return included_.count(v);
  }

  bool Contains(int v) {
    return included_.find(v) != included_.end();
  }

  int Mex() {
    assert(!excluded_.empty());
    return *excluded_.begin();
  }

  
 private:
  std::multiset<int> included_;
  std::multiset<int> excluded_;
};

using MEX = MinimumExcluded;

}  // namespace algo::data_structures
