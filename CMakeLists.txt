cmake_minimum_required(VERSION 2.8)

# Obtain parent directory name as project id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

# Setup testing
enable_testing()

# Include gtest library and directory
find_package(gtest REQUIRED gtest>=1.8.0)
include_directories(${gtest_INCLUDE_DIRS})

# Add executable
add_executable(runUnitTest FizzBuzz.cpp)

# Link test executable against gtest & gtest_main
# target_link_libraries(runUnitTest ${GTEST_LIBRARY_DEBUG} ${GTEST_MAIN_LIBRARY_DEBUG})
target_link_libraries(runUnitTest ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

add_test(
    NAME runUnitTest
    COMMAND runUnitTest
)