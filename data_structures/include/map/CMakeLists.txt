cmake_minimum_required(VERSION 3.14)

add_library(Map STATIC map.hpp multi_map.hpp)
set_target_properties(Map PROPERTIES LINKER_LANGUAGE CXX)