add_subdirectory(src/map)
add_subdirectory(src/linear)

if(NOT DEFINED DATA_STRUCTURES_SRC) 
    set(DATA_STRUCTURES_SRC 
    ${DATA_STRUCTURES_MAP_SRC}
    ${DATA_STRUCTURES_LINEAR_SRC}
    PARENT_SCOPE)
endif()
