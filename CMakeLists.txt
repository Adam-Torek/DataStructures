cmake_minimum_required(VERSION 3.14)

project(DataStructures VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    GoogleTest 
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG b514bdc
)

FetchContent_MakeAvailable(GoogleTest)

enable_testing()

add_subdirectory(data_structures)

add_executable(DataStructure_UnitTests unit_tests/linear/dynamic_array_tests.cpp)
target_include_directories(DataStructure_UnitTests PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(DataStructure_UnitTests PRIVATE DataStructures GTest::gtest_main GTest::gtest)

include(GoogleTest)

gtest_discover_tests(DataStructure_UnitTests)

