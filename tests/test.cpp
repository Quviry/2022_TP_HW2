#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "matrix.hpp"

TEST(TestMatrix, Creation_arrays) {
    EXPECT_NO_THROW(nvec::Matrix({{1, 2}, {3, 4}}));
}

TEST(TestMatrix, Creation_void){
    EXPECT_NO_THROW({ nvec::Matrix<int>(); });
}

TEST(TestMatrix, Creation_bool) {
#if __cplusplus >= 202002L
    EXPECT_THROW_ANY({ nvec::Matrix({true}); });
#else
    EXPECT_NO_THROW({ nvec::Matrix({true}); });
#endif
}

TEST(TestMatrix, Get_value){
    EXPECT_EQ(nvec::Matrix({{1, 2}, {3, 4}})(1, 1) , 4);
}

TEST(TestMatrix, Get_brackets_value){
    EXPECT_EQ(nvec::Matrix({{1, 2}, {3, 4}})[1][1] , 4);
}

TEST(TestMatrix, Get_value_mutable){
    auto matrix = nvec::Matrix({{1, 2}, {3, 4}});
    auto& elem = matrix(1, 1);
    elem = 10;
    EXPECT_EQ(matrix[1][1], 10);
}

TEST(TestMatrix, Get_brackets_value_immutable){
    auto matrix = nvec::Matrix({{1, 2}, {3, 4}});
    auto elem = matrix[1][1];
    elem = 10;
    EXPECT_EQ(matrix[1][1], 4);
}

TEST(TestMatrix, Get_brackets_value_immutable){
    auto matrix = nvec::Matrix({{1, 2}, {3, 4}});
    EXPECT_THAT(matrix.to_string(), ::testing::StartsWith("1 2 \n3 4\n"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
