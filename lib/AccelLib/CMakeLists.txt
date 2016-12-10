cmake_minimum_required(VERSION 3.0)

project(libAccelLib)

include_directories(include)

if(WIN32)
    if(MSYS OR MINGW)
        link_directories(lib/mingw)
    elseif()
        message(SEND_ERROR "AccelLib not already avaible for this environnement.")
        #link_directories(lib/win32)
    endif()
else() #unix system
    link_directories(lib/unix)
endif()

#environnement cible
if(WIN32)
    add_definitions(-DWIN32)
elseif(APPLE)
    add_definitions(-DAPPLE)
elseif(UNIX and not APPLE)
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
elseif(MSVC OR MSVC_IDE OR MSVC60 OR MSVC70 OR MSVC71 OR MSVC80 OR CMAKE_COMPILER_2005 OR MSVC90 OR MSVC10 (Visual Studio 2010))
    add_definitions(-DMSVC)
endif()
