cmake_minimum_required(VERSION 3.27.1)

project(Sort_Algoritms CXX)

include_directories(include)
include_directories(modules/STL/include)


add_subdirectory(modules/STL)

# #sorts
set(SORTS_2_LIB "include/sorts_2.hh" "src/sorts_2.cc")
add_library(sorts_2 SHARED ${SORTS_2_LIB})
target_link_libraries(sorts_2 exception )

add_executable(test "test.cpp")
target_include_directories(test PRIVATE "include")
target_link_libraries(test list sorts sorts_2)

add_executable(work "work.cpp")
target_include_directories(work PRIVATE "include")
target_link_libraries(work list sorts sorts_2)