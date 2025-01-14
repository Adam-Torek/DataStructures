cmake_minimum_required(VERSION 3.14)

add_subdirectory(linear)
add_subdirectory(map)

add_library(Include INTERFACE)
target_link_libraries(Include INTERFACE Linear Map)
set_target_properties(Include PROPERTIES LINKER_LANGUAGE CXX)