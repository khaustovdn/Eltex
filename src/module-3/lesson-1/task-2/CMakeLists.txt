cmake_minimum_required(VERSION 3.28)
project(eltex)

add_executable(eltex
  ./main.c
  ./main.h)

add_executable(max_line_finder
  ./max_line_finder.c
  ./max_line_finder.h)

add_executable(max_number_finder
  ./max_number_finder.c
  ./max_number_finder.h)

add_executable(string_joiner
  ./string_joiner.c
  ./string_joiner.h)

add_executable(summator
  ./summator.c
  ./summator.h)

add_library(utils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h)

target_link_libraries(eltex PRIVATE utils)
target_link_libraries(max_line_finder PRIVATE utils)
target_link_libraries(max_number_finder PRIVATE utils)
target_link_libraries(string_joiner PRIVATE utils)
target_link_libraries(summator PRIVATE utils)
