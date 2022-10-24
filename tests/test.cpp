#include <gtest/gtest.h>
#include "Matrix.hpp"


TEST(Test, Subtest_2) {
  ASSERT_TRUE(nvec::Matrix({{1, 2}, {3, 4}})(0, 0) == 1);
}

TEST(Test, Subtest_3) {
  ASSERT_TRUE(nvec::Matrix({true})(0, 0));
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}