cmake_minimum_required(VERSION 3.19)

set(intervals OFF)
set(brick_wall OFF)
set(algorithms_oop ON)
set(number_of_atoms OFF)
set(FINDREPEATEDDNASEQUENCES OFF)
 

set(PATH_SRC C:/1_lessons/C_programming_language/trainings/training/)

set(LIST_SRC ${PATH_SRC}main_cpp.cpp ${PATH_SRC}u_tests.cpp ${PATH_SRC}utils_cpp.cpp)
set(OPT -Wall -fexceptions -g -Weffc++ -std=c++14 )

if(${FINDREPEATEDDNASEQUENCES})
  message("  FINDREPEATEDDNASEQUENCES ${FINDREPEATEDDNASEQUENCES}")
  list(APPEND OPT "-DFINDREPEATEDDNASEQUENCES" )
  list(APPEND LIST_SRC ${PATH_SRC}repeated_dna_secuenses.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_repeated_dna_secuenses.cpp )
endif()


if(${algorithms_oop})
  message("  algorithms_oop ${algorithms}")
  list(APPEND OPT "-DALGORITHMS_OOP" )
  list(APPEND LIST_SRC ${PATH_SRC}algorithms_oop.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_algorithms_oop.cpp )
endif()


if(${number_of_atoms})
  message("  number_of_atoms ${number_of_atoms}")
  list(APPEND OPT "-DNUMBER_OF_ATOMS" )
  list(APPEND LIST_SRC ${PATH_SRC}number_of_atoms.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_number_of_atoms.cpp )
endif()
	
if(${intervals})
  message("  intervals ${intervals}")
  list(APPEND OPT "-DINTERVALS" )
  list(APPEND LIST_SRC ${PATH_SRC}intervals.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_intervals.cpp )
endif()
	
if(${brick_wall})
  message("  brick_wall ${brick_wall}")
  list(APPEND OPT "-DBRICK_WALL" )
  list(APPEND LIST_SRC ${PATH_SRC}brick_wall.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_brick_wall.cpp )
endif()

set(CMAKE_GENERATOR "MinGW Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")
message("PATH_SRC=${PATH_SRC}")
message("LIST_SRC=${LIST_SRC}")
message("OPT=${OPT}")

set(PROJECT_NAME cpp_trainings)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
add_compile_options( ${OPT} )
 
add_executable(${PROJECT_NAME}  ${LIST_SRC})



