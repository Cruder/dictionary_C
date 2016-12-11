cmake_minimum_required(VERSION 3.0)

#target_include_directory(. PUBLIC)

add_subdirectory(AccelLib)

if(INCLUDES)
    set(INCLUDES ${INCLUDES} PARENT_SCOPE)
endif()

if(LINKS)
    set(LINKS ${LINKS} PARENT_SCOPE)
endif()

