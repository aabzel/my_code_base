cmake_minimum_required(VERSION 3.19)

message("current dirrectory  ${CMAKE_CURRENT_SOURCE_DIR}")


set(insert_interval ON)
set(intervals OFF)
set(brick_wall OFF)
set(algorithms_oop OFF)
set(number_of_atoms OFF)
set(FINDREPEATEDDNASEQUENCES OFF)
 
set(PATH_SRC   ${CMAKE_CURRENT_SOURCE_DIR})

set(INCL_PATH_TESTS  ${PATH_SRC}/../tests)
set(INCL_PATH_UTILS  ${PATH_SRC}/../utils)


set(LIST_SRC ${PATH_SRC}/../main_cpp.cpp 
             ${PATH_SRC}/../tests/u_tests.cpp 
             ${PATH_SRC}/../utils/utils_cpp.cpp)
set(OPT -Wall -fexceptions -g -Weffc++ -std=c++14  -I${INCL_PATH_TESTS}  -I${INCL_PATH_UTILS})

if(${FINDREPEATEDDNASEQUENCES})
  message("  FINDREPEATEDDNASEQUENCES ${FINDREPEATEDDNASEQUENCES}")
  list(APPEND OPT "-DFINDREPEATEDDNASEQUENCES" )
  list(APPEND LIST_SRC ${PATH_SRC}repeated_dna_secuenses.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_repeated_dna_secuenses.cpp )
endif()


if(${insert_interval})
  message("  insert_interval ${insert_interval}")
  list(APPEND OPT "-DINSERT_INTERVAL" )
  list(APPEND OPT "-DDEBUG_INSERT_INTERVAL" )
  set(INCL_PATH_UTILS  ${PATH_SRC}/../leet_code)
  list(APPEND OPT -I${INCL_PATH_UTILS})
  list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/insert_interval.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}/..//tests/test_insert_interval.cpp )
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

set(PROJECT_NAME cpp_training)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
add_compile_options( ${OPT} )
 
add_executable(${PROJECT_NAME}  ${LIST_SRC})



