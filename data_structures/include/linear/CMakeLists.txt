cmake_minimum_required(VERSION 3.14)

file(GLOB Linear_SRC "*.hpp")

add_library(Linear STATIC static_array.hpp dynamic_array.hpp)
set_target_properties(Linear PROPERTIES LINKER_LANGUAGE CXX)