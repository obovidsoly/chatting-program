cmake_minimum_required(VERSION 3.0.0)
project(Chat)

# install(DIRECTORY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install)
# install(DIRECTORY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install/lib)
# install(DIRECTORY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install/bin)

set(INSTALL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/install)
set(LIB_PATH ${INSTALL_PATH}/lib)
set(BIN_PATH ${INSTALL_PATH}/bin)

add_compile_options(-std=c11)
add_compile_definitions(_POSIX_C_SOURCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/client)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/server)