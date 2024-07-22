#pragma once

#include <tuple>
#include <string>

#include <algo/utils/meta.hpp>

namespace algo::strings::aho_corasick::details {

template <typename StatisticsTuple>
struct Node {
  StatisticsTuple statistics;

  explicit Node(const std::string& pattern) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat.SetPattern(pattern);
        });
  }

  void UpdateAsSuffix(const Node& pattern_node) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          const auto& pattern_stat =
              std::get<index_number.Value>(pattern_node.statistics);
          stat.FoundAsSuffixOfLongerPattern(pattern_stat);
        });
  };

  void UpdateAsLongest(int index) {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat.FoundAsLongestPatternEndingAt(index);
        });
  };

  template <typename Statistics>
  Statistics Get() const {
    return std::get<Statistics>(statistics);
  }

  void ResetAll() {
    utils::meta::ForLoop<0, std::tuple_size_v<StatisticsTuple> - 1>(
        [&](auto index_number) {
          auto& stat = std::get<index_number.Value>(statistics);
          stat.Reset();
        });
  }
};
}  // namespace algo::strings::aho_corasick::details
