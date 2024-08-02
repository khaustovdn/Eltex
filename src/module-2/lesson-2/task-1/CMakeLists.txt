cmake_minimum_required(VERSION 3.28)
project(eltex)

add_executable(eltex
  ./main.c
  ./main.h
  ./contact.c
  ./contact.h
  ./phonebook.c
  ./phonebook.h)

add_library(utils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h)

target_link_libraries(eltex PRIVATE utils)
