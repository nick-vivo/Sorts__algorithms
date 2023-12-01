cmake_minimum_required(VERSION 3.27.1)

project(Sort_Algoritms CXX)

include_directories(include)
include_directories(modules/STL/include)


add_subdirectory(modules/STL)

# #sorts
set(SORTS_2_LIB "include/sorts_2.hh" "src/sorts_2.cc")
add_library(sorts_2 SHARED ${SORTS_2_LIB})
target_link_libraries(sorts_2 exception )

add_executable(main "main.cpp")
target_include_directories(main PRIVATE "include")
target_link_libraries(main list sorts)