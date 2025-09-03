cmake_minimum_required(VERSION 3.31)
project(tb_math)

file(GLOB_RECURSE SRC src/*cpp)
set(SOURCES ${SRC})
add_executable(tb_math ${SOURCES})
