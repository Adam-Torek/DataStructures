cmake_minimum_required(VERSION 3.14)



if(NOT DEFINED DATA_STRUCTURES_LINEAR_SRC)
    SET(DATA_STRUCTURES_LINEAR_SRC 
    data_structures/src/linear/dynamic_array.hpp
    data_structures/src/linear/static_array.hpp
    PARENT_SCOPE)
endif()

