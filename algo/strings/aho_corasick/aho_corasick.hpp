#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include <algo/strings/aho_corasick/details/node.hpp>
#include <algo/strings/trie/trie.hpp>

namespace algo::strings::aho_corasick {

template <typename StatisticsTuple, typename String>
struct AhoCorasick {
  using Pattern = String;
  using PatternNode = details::Node<StatisticsTuple, String>;

  explicit AhoCorasick(const std::vector<Pattern>& patterns) {
    AllocateMemory(patterns);
    BuildTrie(patterns);
  }

  void Scan(const String& s) {
    int trie_node_index = trie_.GetRoot();
    for (int i = 0; i < s.size(); ++i) {
      auto letter = s[i];
      trie_node_index = trie_.Go(trie_node_index, letter);
      int pattern_node_index = -1;
      if (trie_.IsTerminal(trie_node_index)) {
        pattern_node_index = trie_to_pattern_[trie_node_index];
      } else {
        int longest_trie_node_index =
            trie_.GetLongestTerminalSuffix(trie_node_index);
        if (longest_trie_node_index != -1) {
          pattern_node_index = trie_to_pattern_[longest_trie_node_index];
        }
      }
      if (pattern_node_index != -1) {
        pattern_nodes_[pattern_node_index].UpdateAsLongest(i);
      }
    }
    CalculateStatistics();
  }

  void ResetAllStatistics() {
    for (auto& pattern_node : pattern_nodes_) {
      pattern_node.ResetAll();
    }
  }

  template <typename Statistics>
  Statistics Get(int input_pattern_index) const {
    int pattern_node_index = input_pattern_to_pattern_[input_pattern_index];
    return pattern_nodes_[pattern_node_index].template Get<Statistics>();
  }

 private:
  void AllocateMemory(const std::vector<Pattern>& patterns) {
    input_pattern_to_pattern_.reserve(patterns.size());
    pattern_nodes_.reserve(patterns.size());
    pattern_lengths_.reserve(patterns.size());

    int max_trie_size = 1;
    for (const auto& pattern : patterns) {
      max_trie_size += pattern.size();
    }
    trie_.Reserve(max_trie_size);
  }

  void BuildTrie(const std::vector<Pattern>& patterns) {
    for (const auto& pattern : patterns) {
      int trie_node_index = trie_.AddString(pattern);
      if (IsNewPattern(trie_node_index)) {
        AddPattern(trie_node_index, pattern);
      }
      int pattern_node_index = trie_to_pattern_[trie_node_index];
      input_pattern_to_pattern_.push_back(pattern_node_index);
    }
    trie_.CreateLinks();
  }
  bool IsNewPattern(int trie_node_index) {
    return trie_to_pattern_.find(trie_node_index) == trie_to_pattern_.end();
  }

  void AddPattern(int trie_node_index, const String& pattern) {
    int pattern_node_index = AddPatternNode(pattern);
    trie_to_pattern_[trie_node_index] = pattern_node_index;
    pattern_to_trie_[pattern_node_index] = trie_node_index;
    pattern_lengths_.emplace_back(pattern.size(), pattern_node_index);
  }

  int AddPatternNode(const String& pattern) {
    pattern_nodes_.emplace_back(pattern);
    return pattern_nodes_.size() - 1;
  }

  void CalculateStatistics() {
    std::sort(pattern_lengths_.begin(), pattern_lengths_.end(),
              std::greater<>());
    for (auto [_, pattern_node_index] : pattern_lengths_) {
      int trie_node_index = pattern_to_trie_[pattern_node_index];
      int next_trie_node_index =
          trie_.GetLongestTerminalSuffix(trie_node_index);
      if (next_trie_node_index != -1) {
        int next_pattern_node_index = trie_to_pattern_[next_trie_node_index];
        auto& pattern_node = pattern_nodes_[pattern_node_index];
        auto& next_pattern_node = pattern_nodes_[next_pattern_node_index];
        next_pattern_node.UpdateAsSuffix(pattern_node);
      }
    }
  }

  trie::Trie<String> trie_;

  std::vector<PatternNode> pattern_nodes_;
  std::vector<std::pair<int, int>> pattern_lengths_;

  std::vector<int> input_pattern_to_pattern_;
  std::map<int, int> trie_to_pattern_;
  std::map<int, int> pattern_to_trie_;
};

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::strings::aho_corasick
