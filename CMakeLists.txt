cmake_minimum_required(VERSION 3.12)
project(MatrixCalculator CXX)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
include_directories(include)

set(GCC_COVERAGE_LINK_FLAGS " -coverage -lgcov")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# Sources
add_library(${PROJECT_NAME}_objs OBJECT
		include/matrix.hpp
		include/vector.hpp
		include/RealContainer.hpp
		include/tools.hpp
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs )

# Tests
add_subdirectory(tests)
