cmake_minimum_required(VERSION 3.0)

project(libmd5)

file(GLOB_RECURSE SRCS src/*.c)

file(GLOB_RECURSE HEADERS include/*.h)

include_directories(include)
add_library(md5 ${SRCS} ${HEADERS})

#Use of OpenSSL if available (more optimized)
find_package(OpenSSL)
if(OPENSSL_FOUND)
  target_include_directories(md5 PUBLIC ${OPENSSL_INCLUDE_DIR})
  target_link_libraries(md5 ${OPENSSL_LIBRARIES})
  add_definitions(-DHAVE_OPENSSL)
  #message("OpenSSL found : use ...")
endif()
