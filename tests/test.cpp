#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "matrix.hpp"
#include "rationalcontainer.hpp"

TEST(TestMatrix, Creation_arrays) {
    EXPECT_NO_THROW(nvec::Matrix<int>({{1, 2}, {3, 4}}));
}

TEST(TestMatrix, Creation_from_vector) {
    EXPECT_NO_THROW(nvec::Matrix<int>(
        {nvec::Vector<int>({1, 2}), nvec::Vector<int>({3, 4})}));
    EXPECT_EQ(nvec::Matrix<int>(
                  {nvec::Vector<int>({1, 2}), nvec::Vector<int>({3, 4})}),
              nvec::Matrix<int>({{1, 2}, {3, 4}}));
}

TEST(TestMatrix, Creation_void) {
    EXPECT_NO_THROW({ nvec::Matrix<int>(); });
}

TEST(TestMatrix, Creation_bool) {
#if __cplusplus >= 202002L
    EXPECT_THROW_ANY({ nvec::Matrix<bool>({true}); });
#else
    EXPECT_NO_THROW({ nvec::Matrix<bool>({true}); });
#endif
}

TEST(TestMatrix, Get_value) {
    EXPECT_EQ(nvec::Matrix<int>({{1, 2}, {3, 4}})(1, 1), 4);
}

TEST(TestMatrix, Get_brackets_value) {
    EXPECT_EQ(nvec::Matrix<int>({{1, 2}, {3, 4}})[1][1], 4);
}

TEST(TestMatrix, Get_value_mutable) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto& elem = matrix(1, 1);
    elem = 10;
    EXPECT_EQ(matrix[1][1], 10);
}

TEST(TestMatrix, Get_brackets_value_immutable) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto elem = matrix[1][1];
    elem = 10;
    EXPECT_EQ(matrix[1][1], 4);
}

TEST(TestMatrix, Get_diagonal) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix.get_diagonal(), nvec::Vector<int>({1, 4}));
}

TEST(TestMatrix, Get_diagonal_big_hor) {
    auto matrix =
        nvec::Matrix<int>({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});
    EXPECT_EQ(matrix.get_diagonal(), nvec::Vector<int>({1, 6, 11}));
}

TEST(TestMatrix, Get_diagonal_big_ver) {
    auto matrix =
        nvec::Matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
    EXPECT_EQ(matrix.get_diagonal(), nvec::Vector<int>({1, 5, 9}));
}

TEST(TestMatrix, Get_row) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix.get_row(0), nvec::Vector<int>({1, 2}));
    EXPECT_EQ(matrix.get_row(1), nvec::Vector<int>({3, 4}));
}

TEST(TestMatrix, Get_row_brackets) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix[0], nvec::Vector<int>({1, 2}));
    EXPECT_EQ(matrix[1], nvec::Vector<int>({3, 4}));
}

TEST(TestMatrix, Get_column) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix.get_column(0), nvec::Vector<int>({1, 3}));
    EXPECT_EQ(matrix.get_column(1), nvec::Vector<int>({2, 4}));
}

TEST(TestMatrix, Get_diagonal_immutable) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto diagonal = matrix.get_diagonal();
    diagonal[0] += 1;
    EXPECT_NE(diagonal[0], matrix[0][0]);
}

TEST(TestMatrix, Get_row_immutable) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto row = matrix[0];
    row[0] += 1;
    EXPECT_NE(row[0], matrix[0][0]);
}

TEST(TestMatrix, Get_column_immutable) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto column = matrix.get_column(0);
    column[0] += 1;
    EXPECT_NE(column[0], matrix[0][0]);
}

TEST(TestMatrix, Matrix_addition) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix1 + matrix2, nvec::Matrix<int>({{2, 4}, {6, 8}}));
}

TEST(TestMatrix, Matrix_subtraction) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix1 - matrix2, nvec::Matrix<int>({{0, 0}, {0, 0}}));
}

TEST(TestMatrix, Matrix_multiplication) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix1 * matrix2, nvec::Matrix<int>({{1, 4}, {9, 16}}));
}

TEST(TestMatrix, Number_multiplication) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix * 3, nvec::Matrix<int>({{3, 6}, {9, 12}}));
}

TEST(TestMatrix, Vector_multiplication) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto vector = nvec::Vector<int>({1, 2});
    EXPECT_EQ(matrix.matrix_multiply(vector), nvec::Vector<int>({5, 11}));
}

TEST(TestMatrix, Matrix_cross_multiplication) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_EQ(matrix1.matrix_multiply(matrix2),
              nvec::Matrix<int>({{7, 10}, {15, 22}}));
}

TEST(TestMatrix, Matrix_cross_multiplication_nr) {
    auto matrix1 = nvec::Matrix<int>({{0, 4, -2}, {-4, -3, 0}});
    auto matrix2 = nvec::Matrix<int>({{0, 1}, {1, -1}, {2, 3}});
    EXPECT_EQ(matrix1.matrix_multiply(matrix2),
              nvec::Matrix<int>({{0, -10}, {-3, -1}}));
}

TEST(TestMatrix, Matrix_sum_number) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{4, 5}, {6, 7}});
    EXPECT_EQ(matrix1 + 3, matrix2);
}

TEST(TestMatrix, Matrix_dec_number) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{-2, -1}, {0, 1}});
    EXPECT_EQ(matrix1 - 3, matrix2);
}

TEST(TestMatrix, Add_vector) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto vector = nvec::Vector<int>({1, 2});
    EXPECT_EQ(matrix.add_vector(vector), nvec::Matrix<int>({{2, 4}, {4, 6}}));
}

TEST(TestMatrix, Add_vector_vertical) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto vector = nvec::Vector<int>({1, 2});
    EXPECT_EQ(matrix.add_vector(vector, nvec::Position::Vertical),
              nvec::Matrix<int>({{2, 3}, {5, 6}}));
}

TEST(TestMatrix, Dec_vector) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto vector = nvec::Vector<int>({1, 2});
    EXPECT_EQ(matrix.dec_vector(vector), nvec::Matrix<int>({{0, 0}, {2, 2}}));
}

TEST(TestMatrix, Dec_vector_vertical) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto vector = nvec::Vector<int>({1, 2});
    EXPECT_EQ(matrix.dec_vector(vector, nvec::Position::Vertical),
              nvec::Matrix<int>({{0, 1}, {1, 2}}));
}

TEST(TestMatrix, Get_transposed) {
    auto matrix1 = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto matrix2 = nvec::Matrix<int>({{1, 3}, {2, 4}});
    EXPECT_EQ(matrix1.get_transposed(), matrix2);
}

TEST(TestMatrix, Get_minor_matrix) {
    auto matrix1 = nvec::Matrix<int>({{1, 4, 5}, {7, 8, 9}, {2, 7, 5}});
    auto matrix2 = nvec::Matrix<int>({{8, 9}, {7, 5}});
    EXPECT_EQ(matrix1.get_minor_matrix(0, 0), matrix2);
}

TEST(TestMatrix, Get_reversed) {
    auto matrix1 = nvec::Matrix<int>({{0, 1}, {1, 1}});
    auto matrix2 = nvec::Matrix<int>({{-1, 1}, {1, 0}});
    EXPECT_EQ(matrix1.get_reversed(), matrix2);
}

TEST(TestMatrix, Get_determinant) {
    auto matrix = nvec::Matrix<int>({{1, 4}, {7, 8}});
    EXPECT_EQ(matrix.get_determinant(), -20);
}

TEST(TestMatrix, Get_string_value) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_THAT(matrix.to_string(), ::testing::StartsWith("1 2 \n3 4"));
}

TEST(TestVector, Vector_reference_creation) {
    EXPECT_NO_THROW({
        auto vector1 = nvec::Vector<int>({1, 2, 3, 4});
        auto vector2 = nvec::Vector<int>(vector1);
    });
}

TEST(TestVector, Vector_addition) {
    auto vector1 = nvec::Vector<int>({1, 2, 3, 4});
    auto vector2 = nvec::Vector<int>({1, 2, 3, 4});
    EXPECT_EQ(vector1 + vector2, nvec::Vector<int>({2, 4, 6, 8}));
}

TEST(TestVector, Vector_subtraction) {
    auto vector1 = nvec::Vector<int>({1, 2, 3, 4});
    auto vector2 = nvec::Vector<int>({1, 2, 3, 4});
    EXPECT_EQ(vector1 - vector2, nvec::Vector<int>({0, 0, 0, 0}));
}

TEST(TestVector, Vector_multiplication) {
    auto vector1 = nvec::Vector<int>({1, 2, 3, 4});
    auto vector2 = nvec::Vector<int>({1, 2, 3, 4});
    EXPECT_EQ(vector1 * vector2, nvec::Vector<int>({1, 4, 9, 16}));
}

TEST(TestVector, Matrix_multiplication) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    auto vector = nvec::Vector<int>({1, 2});
    EXPECT_EQ(vector.matrix_multiply(matrix), nvec::Vector<int>({7, 10}));
}

TEST(TestVector, Add_number) {
    auto vector1 = nvec::Vector<int>({1, 2, 3, 4});
    auto vector2 = nvec::Vector<int>({2, 3, 4, 5});
    EXPECT_EQ(vector1 + 1, vector2);
}

TEST(TestVector, Dec_number) {
    auto vector1 = nvec::Vector<int>({1, 2, 3, 4});
    auto vector2 = nvec::Vector<int>({-9, -8, -7, -6});
    EXPECT_EQ(vector1 - 10, vector2);
}

TEST(TestVector, Get_string_value) {
    auto vector = nvec::Vector<int>({{1, 2, 3, 4}});
    EXPECT_THAT(vector.to_string(), ::testing::StartsWith("1 2 3 4"));
}

TEST(TestRational, FullTest) {
    using _ = nvec::RationalContainer;
    auto matrix1 = nvec::Matrix<_>({{_(3), _(1)}, {_(1), _(1)}});
    auto matrix2 = nvec::Matrix<_>({{_(0.5), _(-0.5)}, {_(-0.5), _(1.5)}});
    EXPECT_EQ(matrix1.get_reversed(), matrix2);
}

TEST(TestRational, Creation) {
    using _ = nvec::RationalContainer;
    auto type1 = _(0);
    auto type2 = _();
    EXPECT_EQ(type1, type2);
}

TEST(TestRational, Getting) {
    using _ = nvec::RationalContainer;
    auto value = _(1);
    EXPECT_EQ(value.get_value(), 1);
}

TEST(TestRational, Root) {
    using _ = nvec::RationalContainer;
    auto value = _(4);
    EXPECT_EQ(value.get_root().get_value(), 2);
}

TEST(TestRational, Operators) {
    using _ = nvec::RationalContainer;
    auto value1 = _(4);
    auto value2 = _(2);
    EXPECT_EQ(value1 + value2, _(6));
    EXPECT_EQ(value1 - value2, _(2));
    EXPECT_EQ(value1 * value2, _(8));
    EXPECT_EQ(value1 / value2, _(2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
