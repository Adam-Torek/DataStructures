function(add_data_structure_source_files SOURCE_FILES)
    set(flags)
    set(args)
    set(listArgs SOURCE_FILES)
    cmake_parse_arguments(arg "${args}" "${flags}" "${listArgs}" ${ARGN})
    if(NOT DEFINED SOURCE_FILES) 
        message(FATAL_ERROR "[add_data_structure_source_files]: SOURCE_FILES is a required argument")
    endif()
    if(SOURCE_FILES IN_LIST arg_KEYWORDS_MISSING_VALUES)
        message(FATAL_ERROR "[add_data_structure_source_files]: SOURCE_FILES requires at least one value")
    endif()
    if(NOT DEFINED DATA_STRUCTURES_SOURCE_FILES)
        set(DATA_STRUCTURES_SOURCE_FILES 
        ${SOURCE_FILES} 
        PARENT_SCOPE)
    else()
        set(${DATA_STRUCTURES_SOURCE_FILES} 
        ${${DATA_STRUCTURES_SOURCE_FILES}} 
        ${SOURCE_FILES} 
        PARENT_SCOPE)
    endif()
    
   

endfunction()