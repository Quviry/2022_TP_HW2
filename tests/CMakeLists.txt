cmake_minimum_required(VERSION 3.12)
project(MatrixCalculator CXX)

include(GNUInstallDirs)
include_directories(../include)

set(GCC_COVERAGE_LINK_FLAGS " -coverage -lgcov")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(CMAKE_CXX_STANDARD 17)

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


enable_testing()

add_executable(${PROJECT_NAME}_unittest
    test.cpp
)

target_link_libraries(${PROJECT_NAME}_unittest
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_unittest)
