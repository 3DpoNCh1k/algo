#pragma once

#include <map>

namespace algo::strings::trie {
template <typename Letter>
struct TrieNode {
  TrieNode(int parent, Letter letter)
      : parent(parent),
        letter(letter) {
  }
  int parent;
  Letter letter;
  std::map<Letter, int> children;
  bool is_terminal = false;

  std::map<Letter, int> cache;
  int longest_suffix = -1;
  int longest_terminal_suffix = -1;

  bool HasChild(char c) {
    auto it = children.find(c);
    return it != children.end();
  }

  int GetChild(Letter c) {
    return children[c];
  }

  void AddChild(Letter c, int index) {
    children[c] = index;
  }
};
}  // namespace algo::strings::trie
