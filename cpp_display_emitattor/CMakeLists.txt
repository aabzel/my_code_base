cmake_minimum_required(VERSION 3.19)

set(PATH_SRC C:/1_lessons/C_programming_language/trainings/training/)

set(LIST_SRC main.cpp ${PATH_SRC}u_tests.cpp ${PATH_SRC}utils_cpp.cpp)
set(OPT -Wall -fexceptions -g -Weffc++ -std=c++14 )

set(CMAKE_GENERATOR "MinGW Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")
message("PATH_SRC=${PATH_SRC}")
message("LIST_SRC=${LIST_SRC}")
message("OPT=${OPT}")

include(${CMAKE_SOURCE_DIR}/cmake/Config.cmake)

set(PROJECT_NAME emulate_lcd)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
add_compile_options( ${OPT} )
 
add_executable(${PROJECT_NAME}  ${LIST_SRC})



