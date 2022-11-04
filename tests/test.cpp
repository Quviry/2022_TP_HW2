#include <gtest/gtest.h>

#include "matrix.hpp"

TEST(TestMatrix, Creation_arrays) {
    EXPECT_NO_THROW(nvec::Matrix({{1, 2}, {3, 4}}));
}

TEST(TestMatrix, Creation_void){
    EXPECT_NO_THROW({ nvec::Matrix<int>(); });
}

TEST(TestMatrix, Creation_void_height) {
    // EXPECT_NO_THROW({ nvec::Matrix<int><2>(); });
}

TEST(TestMatrix, Creation_void_height_width) {
    // nvec::Matrix<int><2, 3>();
}

TEST(TestMatrix, Creation_bool) {
#if __cplusplus >= 202002L
    EXPECT_THROW_ANY({ nvec::Matrix({true}); });
#else
    EXPECT_NO_THROW({ nvec::Matrix({true}); });
#endif
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
