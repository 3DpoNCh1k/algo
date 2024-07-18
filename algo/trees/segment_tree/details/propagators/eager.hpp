#pragma once

namespace algo::trees::segment_tree::details {

template <typename Tree>
struct EagerPropagator {
  using Node = typename Tree::DataNode;
  using Operation = typename Node::Operation;

  Tree& tree;
  explicit EagerPropagator(Tree& tree)
      : tree(tree) {
  }

  void ApplyAtIndex(int idx, const Operation& op) {
    Node* current_node = &tree.GetNodeAt(idx);
    current_node->ApplyOperation(op);
    while (tree.HasParent(*current_node)) {
      current_node = &tree.GetParent(*current_node);
      current_node->Pull(tree.GetLeft(*current_node),
                         tree.GetRight(*current_node));
    }
  }

  template <typename Statistics>
  Statistics GetAtIndex(int idx) {
    return tree.GetNodeAt(idx).template Get<Statistics>();
  }

  template <typename Statistics>
  Statistics GetFromRange(int l, int r) {
    return GetFromRangeTopDown<Statistics>(l, r);
  }

  template <typename Statistics>
  Statistics GetFromRangeTopDown(int l, int r) {
    return GetFromRangeTopDownImpl<Statistics>(tree.GetRoot(), l, r);
  }

  template <typename Statistics>
  Statistics GetFromRangeTopDownImpl(Node& node, int l, int r) {
    if (node.IsOutside(l, r)) {
      return Statistics{};
    }
    if (node.IsInside(l, r)) {
      return node.template Get<Statistics>();
    }
    auto left = GetFromRangeTopDownImpl<Statistics>(tree.GetLeft(node), l, r);
    auto right = GetFromRangeTopDownImpl<Statistics>(tree.GetRight(node), l, r);
    return left.Merge(right);
  }
};

}  // namespace algo::trees::segment_tree::details
