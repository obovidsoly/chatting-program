cmake_minimum_required(VERSION 3.0.0)
project(ChatServer)

set(TARGET server_main)
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_libraries(pthread)

add_compile_options(-Wall -O2)

add_executable(${TARGET} ${SRCS})