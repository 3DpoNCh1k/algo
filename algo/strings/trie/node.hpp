#pragma once

#include <map>

namespace algo::strings::trie {
struct TrieNode {
  TrieNode(int parent, char letter)
      : parent(parent),
        letter(letter) {
  }
  int parent;
  char letter;
  std::map<char, int> children;
  bool is_terminal = false;

  std::map<char, int> cache;
  int longest_suffix = -1;
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
}  // namespace algo::strings::trie
