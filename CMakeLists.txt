cmake_minimum_required(VERSION 3.12)
project(MatrixCalculator CXX)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
include_directories(include)

# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
		include/Matrix.hpp
		include/Column.hpp
		include/Row.hpp
		include/RealContainer.hpp
		include/tools.hpp
)

# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs )

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
    tests/test.cpp
)

target_link_libraries(${PROJECT_NAME}_unittest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_unittest)


# Benchmarks
# not yet added

# Functional Tests
# not yet added

if(DEFINED ENV{PREFIX})
	message(STATUS "Set install prefix: $ENV{PREFIX}")
	file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
	set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif()


install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})