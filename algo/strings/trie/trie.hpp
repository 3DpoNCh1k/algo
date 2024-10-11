#pragma once

#include <algo/strings/trie/node.hpp>
#include <deque>
#include <string>
#include <vector>

namespace algo::strings::trie {
template <typename String>
struct Trie {
  using Letter = typename String::value_type;
  Trie() {
    root_ = 0;
    AddNode(root_, 0);
  }

  void Reserve(int size) {
    nodes_.reserve(size);
  }

  int AddString(const String& s) {
    int current_index = root_;
    for (char c : s) {
      if (!nodes_[current_index].HasChild(c)) {
        int new_node_index = AddNode(current_index, c);
        nodes_[current_index].AddChild(c, new_node_index);
      }
      current_index = nodes_[current_index].GetChild(c);
    }
    nodes_[current_index].is_terminal = true;
    return current_index;
  }

  void CreateLinks() {
    std::deque<int> q;
    q.push_back(root_);
    while (!q.empty()) {
      int node_index = q.front();
      q.pop_front();
      const auto& node = nodes_[node_index];
      for (auto [letter, child_index] : node.children) {
        auto& child = nodes_[child_index];
        child.longest_suffix = FindSuffixIndex(node_index, letter);
        auto& longest_sufix_node = nodes_[child.longest_suffix];
        if (longest_sufix_node.is_terminal) {
          child.longest_terminal_suffix = child.longest_suffix;
        } else {
          child.longest_terminal_suffix =
              longest_sufix_node.longest_terminal_suffix;
        }

        q.push_back(child_index);
      }
    }
  }

  int Go(int index, char letter) {
    if (nodes_[index].HasChild(letter)) {
      return nodes_[index].GetChild(letter);
    }
    if (index == root_) {
      return root_;
    }
    return Go(nodes_[index].longest_suffix, letter);
  }

  int GetRoot() {
    return root_;
  }

  bool IsTerminal(int index) {
    return nodes_[index].is_terminal;
  }

  int GetLongestTerminalSuffix(int index) {
    return nodes_[index].longest_terminal_suffix;
  }

 private:
  int AddNode(int parent, char letter) {
    nodes_.emplace_back(parent, letter);
    return nodes_.size() - 1;
  }

  int FindSuffixIndex(int parent_index, char letter) {
    if (parent_index == root_) {
      return root_;
    }
    auto& parent = nodes_[parent_index];

    if (nodes_[parent.longest_suffix].HasChild(letter)) {
      return nodes_[parent.longest_suffix].GetChild(letter);
    }
    return FindSuffixIndex(parent.longest_suffix, letter);
  }

  int root_;
  std::vector<TrieNode<Letter>> nodes_;
};

};  // namespace algo::strings::trie
