cmake_minimum_required (VERSION 2.6)
project (learn_leptjson C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(learn_leptjson learn_leptjson.c)
add_executable(leptjson_test learn_test.c)
target_link_libraries(leptjson_test learn_leptjson)
