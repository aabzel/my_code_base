cmake_minimum_required(VERSION 3.19)

set(BIT_UTILS ON)

set(PATH_SRC C:/1_lessons/C_programming_language/trainings/training/)

set(LIST_SRC ${PATH_SRC}main.c ${PATH_SRC}uTests.c ${PATH_SRC}utils.c ${PATH_SRC}float_utils.c  ${PATH_SRC}convert.c)
set(OPT -Wall -fexceptions -g  )
list(APPEND OPT "-DHAS_UTESTS" )

if(${BIT_UTILS})
  message("  BIT_UTILS ${BIT_UTILS}")
  list(APPEND OPT "-DBIT_UTILS" )
  list(APPEND LIST_SRC ${PATH_SRC}bit_utils.c )
  list(APPEND LIST_SRC ${PATH_SRC}test_bit_utils.c )
endif()


set(CMAKE_GENERATOR "MinGW Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")
message("PATH_SRC=${PATH_SRC}")
message("LIST_SRC=${LIST_SRC}")
message("OPT=${OPT}")

set(PROJECT_NAME c_trainings)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES C)
add_compile_options( ${OPT} )
 
add_executable(${PROJECT_NAME}  ${LIST_SRC})



