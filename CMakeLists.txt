cmake_minimum_required(VERSION 3.14.4)

set(SRC_PATH "./src")

project(MAIN)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_PATH}/main.cpp)
add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE mylib)
