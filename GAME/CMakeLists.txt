cmake_minimum_required(VERSION 2.8.9)
project(GAME)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(../MODDING_API/include)

link_directories(link)

if(WIN32)
	include_directories(include_win32)
endif(WIN32)

include_directories(F:/Projects/C++/C++_LIBS/SFML-2.4.2/include)

if(WIN32)
	include_directories(include_win32)
	link_directories(link_win32)
endif(WIN32)

file(GLOB SOURCES "src/*.cpp" "include/*.hpp" "../MODDING_API/include/*.hpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../run)

add_executable(GAME ${SOURCES})

if(WIN32)
	target_link_libraries(GAME sfml-window-2 sfml-graphics-2 sfml-system-2 dl MODDING_API)
elseif(UNIX)
	target_link_libraries(GAME sfml-window sfml-graphics sfml-system dl MODDING_API)
endif(WIN32)
