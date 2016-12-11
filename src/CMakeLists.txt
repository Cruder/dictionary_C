set(common dictionary.c metadata.c gestmemory.c input.c utils.c)

add_executable(Dictionary1 main1.c gestbib.c ${common})
add_executable(Dictionary2 main2.c gestrech.c linked_words.c ${common} menu.c)
add_executable(Dictionary3 main3.c gestrech.c gestorth.c linked_words.c ${common})
add_executable(Dictionary4 main4.c gestexpr.c ${common})

target_link_libraries(Dictionary2 AccelLib)
