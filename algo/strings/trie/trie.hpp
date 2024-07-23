#pragma once

#include <algo/strings/trie/node.hpp>
#include <deque>
#include <string>
#include <vector>

namespace algo::strings::trie {
struct Trie {
  int root;
  std::vector<TrieNode> nodes;

  Trie() {
    root = 0;
    AddNode(root, 0);
  }

  void Reserve(int size) {
    nodes.reserve(size);
  }

  int AddString(const std::string& s) {
    int current_index = root;
    for (char c : s) {
      if (!nodes[current_index].HasChild(c)) {
        int new_node_index = AddNode(current_index, c);
        nodes[current_index].AddChild(c, new_node_index);
      }
      current_index = nodes[current_index].GetChild(c);
    }
    nodes[current_index].is_terminal = true;
    return current_index;
  }

  void CreateLinks() {
    std::deque<int> q;
    q.push_back(root);
    while (!q.empty()) {
      int node_index = q.front();
      q.pop_front();
      const auto& node = nodes[node_index];
      for (auto [letter, child_index] : node.children) {
        auto& child = nodes[child_index];
        child.longest_suffix = FindSuffixIndex(node_index, letter);
        auto& longest_sufix_node = nodes[child.longest_suffix];
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
    if (nodes[index].HasChild(letter)) {
      return nodes[index].GetChild(letter);
    }
    if (index == root) {
      return root;
    }
    return Go(nodes[index].longest_suffix, letter);
  }

  int GetRoot() {
    return root;
  }

  bool IsTerminal(int index) {
    return nodes[index].is_terminal;
  }

  int GetLongestTerminalSuffix(int index) {
    return nodes[index].longest_terminal_suffix;
  }

 private:
  int AddNode(int parent, char letter) {
    nodes.emplace_back(parent, letter);
    return nodes.size() - 1;
  }

  int FindSuffixIndex(int parent_index, char letter) {
    if (parent_index == root) {
      return root;
    }
    auto& parent = nodes[parent_index];
    if (parent.cache.find(letter) == parent.cache.end()) {
      if (nodes[parent.longest_suffix].HasChild(letter)) {
        parent.cache[letter] = nodes[parent.longest_suffix].GetChild(letter);
      } else {
        parent.cache[letter] = FindSuffixIndex(parent.longest_suffix, letter);
      }
    }
    return parent.cache[letter];
  }
};

};  // namespace algo::strings::trie
