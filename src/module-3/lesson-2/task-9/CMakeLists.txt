cmake_minimum_required(VERSION 3.30)
project(eltex)

add_executable(server ./server.c)
add_executable(client ./client.c)

add_library(libutils STATIC
  ../../../utils/utils.c
  ../../../utils/utils.h)

target_link_libraries(server PRIVATE libutils)
