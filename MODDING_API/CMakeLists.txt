cmake_minimum_required(VERSION 2.8.9)
project(MODDING_API)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(../GAME/include)

include_directories(F:/Projects/C++/C++_LIBS/SFML-2.4.2/include)

if(WIN32)
	link_directories(link_win32)
endif(WIN32)

file(GLOB SOURCES "src/*.cpp" "include/*.hpp" "../GAME/include/*.hpp")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../GAME/link)

add_library(MODDING_API SHARED ${SOURCES})

if(WIN32)
	target_link_libraries(MODDING_API sfml-window-2 sfml-graphics-2 sfml-system-2)
	ADD_CUSTOM_COMMAND(TARGET MODDING_API POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy libMODDING_API.dll ../../GAME/link/)
    ADD_CUSTOM_COMMAND(TARGET MODDING_API POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ../../GAME/link/libMODDING_API.dll ../../GAME/run/)
elseif(UNIX)
	target_link_libraries(MODDING_API sfml-window sfml-graphics sfml-system)
	ADD_CUSTOM_COMMAND(TARGET MODDING_API POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy libMODDING_API.so ../../GAME/link/)
    ADD_CUSTOM_COMMAND(TARGET MODDING_API POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ../../GAME/link/libMODDING_API.so ../../GAME/run/)
endif(WIN32)


