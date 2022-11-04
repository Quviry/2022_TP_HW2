cmake_minimum_required(VERSION 3.12)
project(MatrixCalculator CXX)

include(GNUInstallDirs)
include_directories(../include)

# Tests include sector
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Unit Tests

enable_testing()

add_executable(${PROJECT_NAME}_unittest
    test.cpp
)

target_link_libraries(${PROJECT_NAME}_unittest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_unittest)
