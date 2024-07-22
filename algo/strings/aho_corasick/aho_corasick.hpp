#pragma once

#include <deque>
#include <map>
#include <string>
#include <vector>

#include <algo/strings/aho_corasick/details/node.hpp>

namespace algo::strings::aho_corasick {

template <typename StatisticsTuple>
struct AhoCorasick {
  // TODO: speedup building & links creation
  using Patterns = std::vector<std::string>;
  struct TreeNode {
    TreeNode(int parent, char letter)
        : parent(parent),
          letter(letter) {
    }
    // build
    std::map<char, int> children;
    bool is_terminal = false;
    // create links
    int parent;
    char letter;
    int longest_suffix = -1;
    std::map<char, int> cache;
    // scan
    int pattern_node_index = -1;
    int longest_terminal_suffix = -1;

    bool HasChild(char c) {
      auto it = children.find(c);
      return it != children.end();
    }

    int GetChild(char c) {
      return children[c];
    }

    void AddChild(char c, int index) {
      children[c] = index;
    }
  };

  int root;
  std::vector<TreeNode> nodes;
  std::vector<details::Node<StatisticsTuple>> unique_pattern_nodes;
  std::vector<int> pattern_index_to_unique_pattern_node_index;
  std::vector<int> unique_patterns_ordered_by_length;
  std::vector<int> pattern_index_to_tree_node_index;

  explicit AhoCorasick(const Patterns& patterns) {
    AllocateMemory(patterns);
    BuildTrie(patterns);
    CreateLinks();
  }

  void AllocateMemory(const Patterns& patterns) {
    pattern_index_to_unique_pattern_node_index.resize(patterns.size());
    unique_pattern_nodes.reserve(patterns.size());
    unique_patterns_ordered_by_length.reserve(patterns.size());
    pattern_index_to_tree_node_index.reserve(patterns.size());
    int max_trie_size = 1;
    for (const auto& pattern : patterns) {
      max_trie_size += pattern.size();
    }
    nodes.reserve(max_trie_size);
  }

  void BuildTrie(const Patterns& patterns) {
    root = 0;
    AddNode(root, 0);
    for (int i = 0; i < patterns.size(); ++i) {
      const std::string& pattern = patterns[i];
      int current_index = root;
      for (char c : patterns[i]) {
        if (!nodes[current_index].HasChild(c)) {
          nodes[current_index].AddChild(c, AddNode(current_index, c));
        }
        current_index = nodes[current_index].GetChild(c);
      }
      if (!nodes[current_index].is_terminal) {
        nodes[current_index].is_terminal = true;
        nodes[current_index].pattern_node_index = AddPatternNode(pattern);
      }
      pattern_index_to_unique_pattern_node_index[i] =
          nodes[current_index].pattern_node_index;

      pattern_index_to_tree_node_index[nodes[current_index]
                                           .pattern_node_index] = current_index;
    }
  };

  int AddNode(int parent, char letter) {
    nodes.emplace_back(parent, letter);
    return nodes.size() - 1;
  }

  int AddPatternNode(const std::string& pattern) {
    unique_pattern_nodes.emplace_back(pattern);
    return unique_pattern_nodes.size() - 1;
  }

  void CreateLinks() {
    std::deque<int> q;
    q.push_back(root);
    while (!q.empty()) {
      int node_index = q.front();
      q.pop_front();
      for (auto [letter, child_index] : nodes[node_index].children) {
        nodes[child_index].longest_suffix = FindSuffixIndex(node_index, letter);
        if (nodes[nodes[child_index].longest_suffix].is_terminal) {
          nodes[child_index].longest_terminal_suffix =
              nodes[child_index].longest_suffix;
        } else {
          nodes[child_index].longest_terminal_suffix =
              nodes[nodes[child_index].longest_suffix].longest_terminal_suffix;
        }

        if (nodes[child_index].is_terminal) {
          unique_patterns_ordered_by_length.push_back(
              nodes[child_index].pattern_node_index);
        }
        q.push_back(child_index);
      }
    }
  }

  int FindSuffixIndex(int parent_index, char letter) {
    if (parent_index == root) {
      return root;
    }

    if (nodes[parent_index].cache.find(letter) ==
        nodes[parent_index].cache.end()) {
      if (nodes[nodes[parent_index].longest_suffix].HasChild(letter)) {
        nodes[parent_index].cache[letter] =
            nodes[nodes[parent_index].longest_suffix].GetChild(letter);
      } else {
        nodes[parent_index].cache[letter] =
            FindSuffixIndex(nodes[parent_index].longest_suffix, letter);
      }
    }
    return nodes[parent_index].cache[letter];
  }

  void Scan(const std::string& t) {
    // PrintTree();
    int current_index = root;
    for (int i = 0; i < t.size(); ++i) {
      auto letter = t[i];
      current_index = Go(current_index, letter);
      if (nodes[current_index].pattern_node_index != -1) {
        unique_pattern_nodes[nodes[current_index].pattern_node_index]
            .UpdateAsLongest(i);
      } else if (nodes[current_index].longest_terminal_suffix != -1) {
        auto index = nodes[current_index].longest_terminal_suffix;
        unique_pattern_nodes[nodes[index].pattern_node_index].UpdateAsLongest(
            i);
      }
    }
    CalculateStatistics();
  }

  void PrintTree() {
    for (int i = 0; i < nodes.size(); ++i) {
      auto parent = nodes[i].parent;
      auto letter = nodes[i].letter;
      auto suffix = nodes[i].longest_suffix;
      auto terminal_suffix = nodes[i].longest_terminal_suffix;
      auto pattern = nodes[i].pattern_node_index;
    }
  }

  void CalculateStatistics() {
    int n = unique_patterns_ordered_by_length.size();
    for (int i = n - 1; i >= 0; --i) {
      int pattern_index = unique_patterns_ordered_by_length[i];
      int tree_index = pattern_index_to_tree_node_index[pattern_index];
      int next_pattern_tree_index = nodes[tree_index].longest_terminal_suffix;
      if (next_pattern_tree_index != -1) {
        int next_pattern_index =
            nodes[next_pattern_tree_index].pattern_node_index;
        unique_pattern_nodes[next_pattern_index].UpdateAsSuffix(
            unique_pattern_nodes[pattern_index]);
      }
    }
  }

  int Go(int index, char letter) {
    if (nodes[index].HasChild(letter)) {
      return nodes[index].GetChild(letter);
    }
    if (index == root) {
      return root;
    }
    return Go(nodes[index].longest_suffix, letter);
  }

  void ResetAllStatistics() {
    for (auto& pattern_node : unique_pattern_nodes) {
      pattern_node.ResetAll();
    }
  }

  template <typename Statistics>
  Statistics Get(int pattern_index) const {
    int unique_index =
        pattern_index_to_unique_pattern_node_index[pattern_index];
    auto stat = unique_pattern_nodes[unique_index].template Get<Statistics>();
    return stat;
  }
};

template <typename... Stats>
using Statistics = std::tuple<Stats...>;

}  // namespace algo::strings::aho_corasick
