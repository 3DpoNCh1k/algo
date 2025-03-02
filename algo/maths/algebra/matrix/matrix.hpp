#pragma once

#include <algo/utils/types/fundamentals.hpp>
#include <cassert>
#include <vector>

namespace algo::maths::algebra::matrix {

template <typename E>
struct Matrix {
  using Element = E;
  Matrix(int k_row, int k_column)
      : k_row(k_row),
        k_column(k_column) {
    matrix.assign(k_row, std::vector<Element>(k_column));
  };

  explicit Matrix(int n): Matrix(n, n) {}

  static Matrix Identity(int n) {
    auto result = Matrix(n);
    for(int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }
    return result;
  }

  static Matrix Zero(int n) {
    return Matrix(n);
  }

  Matrix(const Matrix&) = default;
  Matrix(Matrix&&) = default;
  Matrix& operator=(const Matrix&) = default;
  Matrix& operator=(Matrix&&) = default;

  auto & operator[](int row) {
    return matrix[row];
  }

  const auto & operator[](int row) const {
    return matrix[row];
  }

  // +
  Matrix operator+(const Matrix& that) const {
    assert(k_row == that.k_row);
    assert(k_column == that.k_column);
    Matrix result = *this;
    for (int row = 0; row < k_row; ++row) {
      for (int col = 0; col < k_column; ++col) {
        result[row][col] += that[row][col];
      }
    }
    return result;
  }
  Matrix& operator+=(const Matrix& that) {
    *this = *this + that;
    return *this;
  }
  // +

  // Unary -
  Matrix operator-() const {
    Matrix result = *this;
    for (int row = 0; row < k_row; ++row) {
      for (int col = 0; col < k_column; ++col) {
        result[row][col] = -result[row][col];
      }
    }
    return result;
  }
  // Unary -

  // -
  Matrix operator-(const Matrix& that) const {
    return *this + (-that);
  }
  Matrix& operator-=(const Matrix& that) {
    *this = *this - that;
    return *this;
  }
  // -

  // *
  Matrix operator*(const Matrix& that) const {
    assert(k_column == that.k_row);
    auto result = Matrix(k_row, that.k_column);
    for (int row = 0; row < result.k_row; ++row) {
      for (int col = 0; col < result.k_column; ++col) {
        for (int i = 0; i < k_column; ++i) {
          result[row][col] += matrix[row][i] * that[i][col];
        }
      }
    }
    return result;
  }

  Matrix& operator*=(const Matrix& that) {
    *this = *this * that;
    return *this;
  }
  // *

  bool operator==(const Matrix& that) const {
    return k_row == that.k_row && k_column == that.k_column &&
           matrix == that.matrix;
  }

  bool operator!=(const Matrix& that) const {
    return !(*this == that);
  }

  bool IsSquare() const {
    return k_row == k_column;
  }

  std::vector<std::vector<Element>> matrix;
  int k_row, k_column;
};
}  // namespace algo::maths::algebra::matrix
