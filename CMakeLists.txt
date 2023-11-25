cmake_minimum_required(VERSION 3.27.1)

project(Sort_Algoritms CXX)

include_directories(include)

#string
set(STRING_LIB "include/string.hpp" "src/string.cc")
add_library(string SHARED ${STRING_LIB})
target_include_directories(string  "include")
target_link_libraries(string tools)