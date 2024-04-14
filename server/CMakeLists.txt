cmake_minimum_required(VERSION 3.0.0)
project(ChatServer)

set(TARGET_BIN server_main)
set(TARGET_LIB server)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-Wall -O2)

add_library(${TARGET_LIB} SHARED ${SRCS})
target_link_libraries(${TARGET_LIB} PUBLIC pthread)
set_target_properties(${TARGET_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH})

add_executable(${TARGET_BIN} ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
target_link_libraries(${TARGET_BIN} ${TARGET_LIB})
set_target_properties(${TARGET_BIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})