cmake_minimum_required(VERSION 3.14)

project(DataStructures VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT DEFINED DATA_STRUCTURE_UTILS)
    set(DATA_STRUCTURE_UTILS ${CMAKE_CURRENT_SOURCE_DIR}/cmake_include)
endif()

list(INSERT CMAKE_MODULE_PATH 0 "${DATA_STRUCTURE_UTILS}")

include(FetchContent)

FetchContent_Declare(
    GoogleTest 
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG b514bdc
)

FetchContent_MakeAvailable(GoogleTest)


include(SourceFileFunctions)
add_subdirectory(data_structures)
add_subdirectory(unit_tests)

enable_testing()

message("Building Test Executable for '${PROJECT_NAME}'")

add_library(DataStructures SHARED ${DATA_STRUCTURES_SRC})
set_target_properties(DataStructures PROPERTIES LINKER_LANGUAGE CXX)

add_executable(DataStructure_UnitTests ${UNIT_TESTS_SOURCE_FILES})
target_link_libraries(DataStructure_UnitTests PRIVATE DataStructures GTest::gtest_main GTest::gtest)
target_include_directories(DataStructure_UnitTests PRIVATE ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(DataStructure_UnitTests)


