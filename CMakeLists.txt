cmake_minimum_required(VERSION 3.2)

project(Dictionary VERSION 0.0.1)

add_compile_options(-std=gnu11) # Add c11
add_compile_options(-Wall)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
