set(common gestmemory.c dictionary.c metadata.c input.c buffer.c)

add_executable(Dictionary1 main1.c ${common} gestbib.c)
add_executable(Dictionary2 main2.c ${common} gestrech.c)
add_executable(Dictionary3 main3.c ${common} gestorth.c)
add_executable(Dictionary4 main4.c ${common} gestexpr.c)

