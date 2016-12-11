cmake_minimum_required(VERSION 3.0)

project(libAccelLib)

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

if(WIN32)
    if(MSYS OR MINGW)
        set(LINKS ${CMAKE_CURRENT_SOURCE_DIR}/lib/mingw PARENT_SCOPE)
    elseif()
        message(SEND_ERROR "AccelLib not already avaible for this environnement.")
        #link_directories(lib/win32)
    endif()
else() #unix system
    set(LINKS ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix PARENT_SCOPE)
endif()

#environnement cible
if(WIN32)
    add_definitions(-DWIN32)
elseif(APPLE)
    add_definitions(-DAPPLE)
elseif(UNIX AND NOT APPLE)
    add_definitions(-DLINUX)
elseif(UNIX)
    add_definitions(-DUNIX)
endif()

#compilateur utilisé
if(BORLAND)
    add_definitions(-DBORLAND)
elseif(MSYS)
    add_definitions(-DMSYS)
elseif(MINGW)
    add_definitions(-DMINGW)
elseif(CYGWIN)
    add_definitions(-DCYGWIN)
elseif(WATCOM)
    add_definitions(-DWATCOM)
elseif(MSVC OR MSVC_IDE OR MSVC60 OR MSVC70 OR MSVC71 OR MSVC80 OR CMAKE_COMPILER_2005 OR MSVC90 OR MSVC10 OR "MSVC10 (Visual Studio 2010)")
    add_definitions(-DMSVC)
endif()

