#pragma once

#include <tuple>
#include <string>

#include <algo/utils/meta.hpp>

namespace algo::strings::aho_corasick::details {

template <typename StatisticsTuple, typename String>
struct Node {
  explicit Node(const String& pattern) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics_);
          stat.SetPattern(pattern);
        });
  }

  void UpdateAsSuffix(const Node& pattern_node) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics_);
          const auto& pattern_stat =
              std::get<index_number.Value>(pattern_node.statistics_);
          stat.FoundAsSuffixOfLongerPattern(pattern_stat);
        });
  };

  void UpdateAsLongest(int index) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics_);
          stat.FoundAsLongestPatternEndingAt(index);
        });
  };

  template <typename Statistics>
  Statistics Get() const {
    return std::get<Statistics>(statistics_);
  }

  void ResetAll() {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics_);
          stat.Reset();
        });
  }

 private:
  StatisticsTuple statistics_;
};
}  // namespace algo::strings::aho_corasick::details
