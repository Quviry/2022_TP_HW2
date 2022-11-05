#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "matrix.hpp"

TEST(TestMatrix, Creation_arrays) {
    EXPECT_NO_THROW(nvec::Matrix<int>({{1, 2}, {3, 4}}));
}

TEST(TestMatrix, Creation_from_vector) {
    EXPECT_NO_THROW(nvec::Matrix<int>({nvec::Vector<int>({1, 2}), nvec::Vector<int>({3, 4})}));
    std::cout << nvec::Matrix<int>({nvec::Vector<int>({1, 2}), nvec::Vector<int>({3, 4})}).to_string() << std::endl;
    std::cout << nvec::Matrix<int>({{1, 2}, {3, 4}}).to_string() << std::endl;
    EXPECT_EQ(nvec::Matrix<int>({nvec::Vector<int>({1, 2}), nvec::Vector<int>({3, 4})}), nvec::Matrix<int>({{1, 2}, {3, 4}}));
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
    auto matrix = nvec::Matrix<int>({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});
    EXPECT_EQ(matrix.get_diagonal(), nvec::Vector<int>({1, 6, 11}));
}

TEST(TestMatrix, Get_diagonal_big_ver) {
    auto matrix = nvec::Matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
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


TEST(TestMatrix, Get_string_value) {
    auto matrix = nvec::Matrix<int>({{1, 2}, {3, 4}});
    EXPECT_THAT(matrix.to_string(), ::testing::StartsWith("1 2 \n3 4"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
