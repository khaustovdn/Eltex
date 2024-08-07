cmake_minimum_required(VERSION 3.28)
project(eltex)

add_executable(server ./server.c)
add_executable(client ./client.c)

add_library(utils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h
  ../../../module-2/lesson-2/task-2/calculator.c
  ../../../module-2/lesson-2/task-2/calculator.h)

target_link_libraries(server PRIVATE utils)
target_link_libraries(client PRIVATE utils)
