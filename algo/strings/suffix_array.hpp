#pragma once

#include <algorithm>
#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include "algo/utils/bits.hpp"

namespace algo::strings {
namespace details {
struct SuffixArrayImpl {
  explicit SuffixArrayImpl(const std::string& s) {
    auto [min_it, max_it] = std::minmax_element(s.begin(), s.end());
    int min = *min_it;
    int max = *max_it;
    int shift = -min + 1;
    for (unsigned char ch : s) {
      auto value = ch + shift;
      str_.push_back(value);
    }
    str_.push_back(0);
    n_ = str_.size();
  };

  std::vector<int> Calculate() {
    std::vector<int> suffix_array(n_);
    std::vector<int> equivalence_class(n_);
    for (int i = 0; i < n_; ++i) {
      suffix_array[i] = i;
      equivalence_class[i] = str_[i];
    }

    std::vector<int> suffixes_ordered_by_lowest_part(n_);
    int max_length = utils::bits::PowerOfTwoThatAtLeast(u64(n_));

    for (int length = 1; length <= max_length; length *= 2) {
      int part_length = length / 2;
      for (int pos = 0; pos < n_; ++pos) {
        suffixes_ordered_by_lowest_part[pos] =
            IndexOfHighestPart(suffix_array[pos], part_length);
      }

      StableCountingSort(suffixes_ordered_by_lowest_part, equivalence_class,
                         suffix_array);

      equivalence_class =
          CalculateEquivalenceClasses(suffix_array, [&](int suffix_index) {
            return std::make_pair(equivalence_class[suffix_index],
                                  equivalence_class[IndexOfLowestPart(
                                      suffix_index, part_length)]);
          });
    }

    return std::vector(suffix_array.begin() + 1, suffix_array.end());
  }

 private:
  int IndexOfHighestPart(int lowest_part_index, int part_length) {
    return (lowest_part_index - part_length + n_) % n_;
  }

  int IndexOfLowestPart(int highest_part_index, int part_length) {
    return (highest_part_index + part_length) % n_;
  }

  void StableCountingSort(const std::vector<int>& values,
                          const std::vector<int>& keys,
                          std::vector<int>& sorted_values) {
    int n = values.size();
    int key_count = (*std::max_element(keys.begin(), keys.end())) + 1;
    std::vector<int> counter(key_count, 0);
    for (int value : values) {
      counter[keys[value]]++;
    }
    for (int key = 1; key < key_count; ++key) {
      counter[key] += counter[key - 1];
    }
    for (int pos = n - 1; pos >= 0; --pos) {
      int value = values[pos];
      int new_pos = --counter[keys[value]];
      sorted_values[new_pos] = value;
    }
  }

  template <typename F>
  std::vector<int> CalculateEquivalenceClasses(const std::vector<int>& values,
                                               F&& key_function) {
    int n = values.size();
    std::vector<int> equivalence_class(n);
    equivalence_class[values[0]] = 0;
    int k_equivalence_class = 1;
    auto previous_key = key_function(values[0]);

    for (int pos = 1; pos < n; ++pos) {
      auto current_key = key_function(values[pos]);
      if (current_key != previous_key) {
        k_equivalence_class++;
      }

      equivalence_class[values[pos]] = k_equivalence_class - 1;
      previous_key = current_key;
    }

    return std::move(equivalence_class);
  }

  int n_;
  std::vector<int> str_;
};
}  // namespace details

std::vector<int> SuffixArray(const std::string& s) {
  return details::SuffixArrayImpl(s).Calculate();
}

}  // namespace algo::strings
