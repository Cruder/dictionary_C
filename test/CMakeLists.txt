include_directories(${CMAKE_BINARY_DIR}/src)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Dictionnary_test check_addition.c ${CMAKE_BINARY_DIR}/src/addition.c)

if(APPLE)
  target_link_libraries(Dictionnary_test check m ${CMAKE_THREAD_LIBS_INIT})
elseif(WIN32)
elseif(UNIX)
  target_link_libraries(Dictionnary_test check subunit check_pic rt m ${CMAKE_THREAD_LIBS_INIT})
endif()
