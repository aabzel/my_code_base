cmake_minimum_required(VERSION 3.19)

message("current dirrectory  ${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 14)

set(add_c_src ON)

set(generate_parentheses OFF)
set(interval_list_intersections OFF)
set(merge_interval OFF)
set(insert_interval OFF)
set(intervals OFF)
set(brick_wall OFF)
set(algorithms_oop OFF)
set(number_of_atoms OFF)
set(FINDREPEATEDDNASEQUENCES OFF)
 
 
 
 
set(PATH_SRC   ${CMAKE_CURRENT_SOURCE_DIR})

set(INCL_PATH_TESTS  ${PATH_SRC}/../tests)
set(INCL_PATH_ADT  ${PATH_SRC}/../ADT)
set(INCL_PATH_UTILS  ${PATH_SRC}/../utils)
set(INCL_PATH_LEET_CODE  ${PATH_SRC}/../leet_code)


set(LIST_SRC ${PATH_SRC}/../main_cpp.cpp 
             ${PATH_SRC}/../tests/u_tests.cpp 
             ${PATH_SRC}/../utils/utils_cpp.cpp
			 )
set(OPT -Wall -fexceptions -g -Weffc++ -std=c++14  -I${INCL_PATH_TESTS}  
                                                   -I${INCL_PATH_UTILS}
                                                   -I${INCL_PATH_ADT})

  
  
list(APPEND OPT -I${INCL_PATH_LEET_CODE})
list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/majority_element.cpp)
list(APPEND LIST_SRC ${PATH_SRC}/..//tests/test_majority_element.cpp )
 
list(APPEND OPT "-DBULLS_AND_COWS" )
list(APPEND OPT "-DDEBUG_BULLS_COWS" )
list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/bulls_and_cows.cpp)
list(APPEND LIST_SRC ${PATH_SRC}/..//tests/test_bulls_and_cows.cpp )
  
if(${FINDREPEATEDDNASEQUENCES})
  message("  FINDREPEATEDDNASEQUENCES ${FINDREPEATEDDNASEQUENCES}")
  list(APPEND OPT "-DFINDREPEATEDDNASEQUENCES" )
  list(APPEND LIST_SRC ${PATH_SRC}repeated_dna_secuenses.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}test_repeated_dna_secuenses.cpp )
endif()

if(${merge_interval} OR ${insert_interval} OR ${interval_list_intersections} )
    list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/interval_api.cpp )
endif()

if(${generate_parentheses})
  message("  generate_parentheses ${generate_parentheses}")
  list(APPEND OPT "-DGENERATE_PARENTHESES" )
  list(APPEND OPT "-DDEBUG_GENERATE_PARENTHESES" )
  set(INCL_PATH_UTILS  ${PATH_SRC}/../leet_code)
  list(APPEND OPT -I${INCL_PATH_UTILS})

 
  list(APPEND LIST_SRC ${PATH_SRC}/..//ADT/lifo_char.c )
  list(APPEND LIST_SRC ${PATH_SRC}/..//utils/str_ops.c )
  list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/generate_parentheses.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}/..//tests/test_generate_parentheses.cpp )
endif()


if(${interval_list_intersections})
  message("  interval_list_intersections ${interval_list_intersections}")
  list(APPEND OPT "-DINTERVAL_INTERSECTIONS" )
  list(APPEND OPT "-DDEBUG_INTERSEPT_INTERVAL" )
  set(INCL_PATH_UTILS  ${PATH_SRC}/../leet_code)
  list(APPEND OPT -I${INCL_PATH_UTILS})
  list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/interval_list_intersections.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}/..//tests/test_interval_list_intersections.cpp )
endif()

if(${merge_interval})
  message("  merge_interval ${merge_interval}")
  list(APPEND OPT "-DMERGE_INTERVAL" )
  #list(APPEND OPT "-DDEBUG_MERGE_INTERVAL" )
  set(INCL_PATH_UTILS  ${PATH_SRC}/../leet_code)
  list(APPEND OPT -I${INCL_PATH_UTILS})
  list(APPEND LIST_SRC ${PATH_SRC}/..//leet_code/merge_interval.cpp )
  list(APPEND LIST_SRC ${PATH_SRC}/..//tests/test_merge_interval.cpp )
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
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX C)
add_compile_options( ${OPT} )
 
add_executable(${PROJECT_NAME}  ${LIST_SRC})



