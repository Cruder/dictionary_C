if(INCLUDES)
    MESSAGE( STATUS "INCLUDES : " ${INCLUDES} )
    include_directories(${INCLUDES})
endif()

if(LINKS)
    MESSAGE( STATUS "LINKS : " ${LINKS} )
    link_directories(${LINKS})
endif()

set(common dictionary.c metadata.c gestmemory.c input.c utils.c)

add_executable(Dictionary1 main1.c gestbib.c ${common})
add_executable(Dictionary2 main2.c gestrech.c ${common} linked_words.c menu.c)
add_executable(Dictionary3 main3.c gestrech.c gestorth.c linked_words.c menu.c ${common})
add_executable(Dictionary4 main4.c gestexpr.c ${common})

target_link_libraries(Dictionary1 AccelLib)
target_link_libraries(Dictionary2 AccelLib)
target_link_libraries(Dictionary3 AccelLib)

