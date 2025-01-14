if(CMAKE_BUILD_TYPE STREQUAL "Debug")

    if(NOT DEFINED UNIT_TESTS_SOURCE_FILES)
        set(UNIT_TESTS_SOURCE_FILES 
            unit_tests/linear/dynamic_array_tests.cpp
            PARENT_SCOPE)
    endif()

else()
    message("Skipping Test Executable")
endif()

