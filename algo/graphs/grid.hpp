#pragma once

#include <array>
#include <utility>
#include <vector>

namespace algo::graphs {
struct Grid {
  Grid(int k_row, int k_column)
      : k_row_(k_row),
        k_col_(k_column){};

  using Neighbor = std::pair<int, int>;

  auto Neighbors8(int row, int col) {
    return Neighbors(row, col, DeltaRow8, DeltaColumn8);
  }

  auto Neighbors4(int row, int col) {
    return Neighbors(row, col, DeltaRow4, DeltaColumn4);
  }

 private:
  template <typename T>
  std::vector<Neighbor> Neighbors(int row, int col, const T& delta_row,
                                  const T& delta_column) {
    std::vector<Neighbor> neighbors;
    for (int i = 0; i < delta_row.size(); ++i) {
      int next_row = row + delta_row[i];
      int next_col = col + delta_column[i];
      if (IsValidRow(next_row) && IsValidColumn(next_col)) {
        neighbors.emplace_back(next_row, next_col);
      }
    }
    return neighbors;
  }

  inline bool IsValidRow(int row) {
    return row >= 0 && row < k_row_;
  }

  inline bool IsValidColumn(int col) {
    return col >= 0 && col < k_col_;
  }

  constexpr static std::array<int, 8> DeltaRow8 = {-1, -1, 0, 1, 1, 1, 0, -1};
  constexpr static std::array<int, 8> DeltaColumn8 = {0, 1,  1,  1,
                                                      0, -1, -1, -1};

  constexpr static std::array<int, 4> DeltaRow4 = {-1, 0, 1, 0};
  constexpr static std::array<int, 4> DeltaColumn4 = {0, 1, 0, -1};
  const int k_row_, k_col_;
};
}  // namespace algo::graphs
