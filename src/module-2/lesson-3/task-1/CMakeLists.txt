cmake_minimum_required(VERSION 3.30)
project(eltex)

add_executable(eltex
  ./converter.c
  ./converter.h
  ./main.c
  ./main.h
  ./permissions_editor.c
  ./permissions_editor.h
  ./permissions_input.c
  ./permissions_input.h
  ./permissions_output.c
  ./permissions_output.h)

add_library(libutils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h)

target_link_libraries(eltex PRIVATE libutils)
