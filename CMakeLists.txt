cmake_minimum_required(VERSION 3.17)
project(graphBlas)
set (CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include)
find_library(PATH_TO_GRAPHBLAS graphblas)
find_library(PATH_TO_GOOGLETEST gtest)
add_compile_options(-fPIC)

add_executable(graphBlas main.cpp)
add_executable(graphBlasTest test_main.cpp dfs.cpp dfs.h)

target_link_libraries (graphBlas ${PATH_TO_GRAPHBLAS})
target_link_libraries (graphBlasTest ${PATH_TO_GOOGLETEST} ${PATH_TO_GRAPHBLAS})
