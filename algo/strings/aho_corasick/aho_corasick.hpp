#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <algo/strings/aho_corasick/details/node.hpp>
#include <algo/strings/trie/trie.hpp>

namespace algo::strings::aho_corasick {

template <typename StatisticsTuple>
struct AhoCorasick {
  using Patterns = std::vector<std::string>;
  using PatternNode = details::Node<StatisticsTuple>;
  trie::Trie trie;

  std::vector<PatternNode> pattern_nodes;
  std::vector<std::pair<int, int>> pattern_lengths;

  std::vector<int> input_pattern_to_pattern;
  std::map<int, int> trie_to_pattern;
  std::map<int, int> pattern_to_trie;

  explicit AhoCorasick(const Patterns& patterns) {
    AllocateMemory(patterns);
    BuildTrie(patterns);
  }

  void Scan(const std::string& s) {
    int trie_node_index = trie.GetRoot();
    for (int i = 0; i < s.size(); ++i) {
      auto letter = s[i];
      trie_node_index = trie.Go(trie_node_index, letter);
      int pattern_node_index = -1;
      if (trie.IsTerminal(trie_node_index)) {
        pattern_node_index = trie_to_pattern[trie_node_index];
      } else {
        pattern_node_index = trie.GetLongestTerminalSuffix(trie_node_index);
      }
      if (pattern_node_index != -1) {
        pattern_nodes[pattern_node_index].UpdateAsLongest(i);
      }
    }
    CalculateStatistics();
  }

  void ResetAllStatistics() {
    for (auto& pattern_node : pattern_nodes) {
      pattern_node.ResetAll();
    }
  }

  template <typename Statistics>
  Statistics Get(int input_pattern_index) const {
    int pattern_node_index = input_pattern_to_pattern[input_pattern_index];
    return pattern_nodes[pattern_node_index].template Get<Statistics>();
  }

 private:
  void AllocateMemory(const Patterns& patterns) {
    input_pattern_to_pattern.reserve(patterns.size());
    pattern_nodes.reserve(patterns.size());
    pattern_lengths.reserve(patterns.size());

    int max_trie_size = 1;
    for (const auto& pattern : patterns) {
      max_trie_size += pattern.size();
    }
    trie.Reserve(max_trie_size);
  }

  void BuildTrie(const Patterns& patterns) {
    for (const auto& pattern : patterns) {
      int trie_node_index = trie.AddString(pattern);
      if (IsNewPattern(trie_node_index)) {
        AddPattern(trie_node_index, pattern);
      }
      int pattern_node_index = trie_to_pattern[trie_node_index];
      input_pattern_to_pattern.push_back(pattern_node_index);
    }
    trie.CreateLinks();
  }
  bool IsNewPattern(int trie_node_index) {
    return trie_to_pattern.find(trie_node_index) == trie_to_pattern.end();
  }

  void AddPattern(int trie_node_index, const std::string& pattern) {
    int pattern_node_index = AddPatternNode(pattern);
    trie_to_pattern[trie_node_index] = pattern_node_index;
    pattern_to_trie[pattern_node_index] = trie_node_index;
    pattern_lengths.emplace_back(pattern.size(), pattern_node_index);
  }

  int AddPatternNode(const std::string& pattern) {
    pattern_nodes.emplace_back(pattern);
    return pattern_nodes.size() - 1;
  }

  void CalculateStatistics() {
    std::sort(pattern_lengths.begin(), pattern_lengths.end(), std::greater<>());
    for (auto [_, pattern_node_index] : pattern_lengths) {
      int trie_node_index = pattern_to_trie[pattern_node_index];
      int next_trie_node_index = trie.GetLongestTerminalSuffix(trie_node_index);
      if (next_trie_node_index != -1) {
        int next_pattern_node_index = trie_to_pattern[next_trie_node_index];
        auto& pattern_node = pattern_nodes[pattern_node_index];
        auto& next_pattern_node = pattern_nodes[next_pattern_node_index];
        next_pattern_node.UpdateAsSuffix(pattern_node);
      }
    }
  }
};

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::strings::aho_corasick
