set(common dictionary.c metadata.c gestmemory.c input.c utils.c)

add_executable(Dictionary1 main1.c gestbib.c ${common})
add_executable(Dictionary2 main2.c gestrech.c ${common})
add_executable(Dictionary3 main3.c gestorth.c ${common})
add_executable(Dictionary4 main4.c gestexpr.c ${common})

#target_link_libraries(DictionaryX AccelLib)
