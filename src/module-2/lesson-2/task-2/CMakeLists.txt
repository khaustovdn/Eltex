cmake_minimum_required(VERSION 3.30)
project(eltex)

add_executable(eltex
  ./calculator.c
  ./calculator.h
  ./main.c
  ./main.h)

add_library(libutils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h)

target_link_libraries(eltex PRIVATE libutils)
