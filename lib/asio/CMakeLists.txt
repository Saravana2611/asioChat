add_library(myAsio STATIC Server.cpp)

target_include_directories(myAsio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})