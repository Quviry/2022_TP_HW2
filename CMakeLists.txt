cmake_minimum_required(VERSION 3.12)
project(MatrixCalculator CXX)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
include_directories(include)

# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
		include/matrix.hpp
		include/vector.hpp
		include/RealContainer.hpp
		include/tools.hpp
)

# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs )

add_subdirectory(tests)
