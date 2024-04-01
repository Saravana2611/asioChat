
add_library(mylib STATIC mylib.cpp)

add_subdirectory(qt)
add_subdirectory(asio)

target_link_libraries(${PROJECT_NAME} PRIVATE myQt myAsio)
target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/lib)