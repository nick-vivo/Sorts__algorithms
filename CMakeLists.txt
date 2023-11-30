cmake_minimum_required(VERSION 3.27.1)

project(Sort_Algoritms CXX)

include_directories(include)
include_directories(modules/STL/include)

#string
set(SORT_LIB "include/sort.hh" "src/sort.cc")
add_library(sort SHARED ${SORT_LIB})
# target_include_directories(sort PRIVATE "include")
target_link_libraries(sort)

add_subdirectory(modules/STL)

add_executable(main "main.cpp")
target_include_directories(main PRIVATE "include")
target_link_libraries(main memory exception)