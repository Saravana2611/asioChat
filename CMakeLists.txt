cmake_minimum_required(VERSION 3.14.4)

set(SRC_PATH "./src")

project(MAIN)

add_executable(${PROJECT_NAME} ${SRC_PATH}/main.cpp)
add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE mylib)
