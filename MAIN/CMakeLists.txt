cmake_minimum_required(VERSION 2.8.9)
project(MAIN)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
link_directories(../GAME/link)

include_directories(../MODDING_API/include)
include_directories(../GAME/include)

include_directories(F:/Projects/C++/C++_LIBS/SFML-2.4.2/include)

if(WIN32)
	include_directories(include_win32)
	link_directories(link_win32)
endif(WIN32)

file(GLOB SOURCES "src/*.cpp" "include/*.h" "include/*.hpp" "../../MODDING_API/include/*.hpp" "../../GAME/include/*.hpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../GAME/run/Mods)

add_library(MAIN SHARED ${SOURCES})

if(WIN32)
	target_link_libraries(MAIN sfml-window-2 sfml-graphics-2 sfml-system-2 MODDING_API)
elseif(UNIX)
	target_link_libraries(MAIN sfml-window sfml-graphics sfml-system MODDING_API)
endif(WIN32)
