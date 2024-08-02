cmake_minimum_required(VERSION 3.28)
project(eltex)

add_executable(eltex ./main.c)

add_library(utils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h)

target_link_libraries(eltex PRIVATE utils)
