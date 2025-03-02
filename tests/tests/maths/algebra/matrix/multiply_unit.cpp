#include <algo/utils/types/modular.hpp>
#include <algo/maths/algebra/matrix/matrix.hpp>
#include <tests/framework/asserts.hpp>

#include <tests/framework/test.hpp>

namespace matrix = algo::maths::algebra::matrix;

TEST(1x1) {
  auto a = matrix::Matrix<int>(1,1);
  a[0][0] = 2;

  auto b = matrix::Matrix<int>(1,1);
  b[0][0] = 3;

  auto c= a * b;
  ASSERT_EQ(c.k_row, 1);
  ASSERT_EQ(c.k_column, 1);
  ASSERT_EQ(c[0][0], 6);
}

TEST(2x2) {
    auto a = matrix::Matrix<int>(2,2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
  
    auto b = matrix::Matrix<int>(2,2);
    b[0][0] = 8;
    b[0][1] = 7;
    b[1][0] = 6;
    b[1][1] = 5;
  
    auto c= a * b;
    ASSERT_EQ(c.k_row, 2);
    ASSERT_EQ(c.k_column, 2);
    
    ASSERT_EQ(c[0][0], 20);
    ASSERT_EQ(c[0][1], 17);
    ASSERT_EQ(c[1][0], 48);
    ASSERT_EQ(c[1][1], 41);
}

TEST(1x2x2x1) {
    auto a = matrix::Matrix<int>(1,2);
    a[0][0] = 1;
    a[0][1] = 2;
    
    auto b = matrix::Matrix<int>(2,1);
    b[0][0] = 4;
    b[1][0] = 3;
  
    auto c= a * b;
    ASSERT_EQ(c.k_row, 1);
    ASSERT_EQ(c.k_column, 1);
    
    ASSERT_EQ(c[0][0], 10);
}

TEST(Modular) {
  using Modular = algo::utils::Modular<i64, 5>;
  auto a = matrix::Matrix<Modular>(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  
  auto b = matrix::Matrix<Modular>(2);
  b[0][0] = 8;
  b[0][1] = 7;
  b[1][0] = 6;
  b[1][1] = 5;

  auto expected = matrix::Matrix<Modular>(2);
  expected[0][0] = 0;
  expected[0][1] = 2;
  expected[1][0] = 3;
  expected[1][1] = 1;
  
  auto c= a * b;

  ASSERT_EQ(c, expected);
}

RUN_ALL_TESTS()