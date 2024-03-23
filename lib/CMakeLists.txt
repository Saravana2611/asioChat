add_library(mylib STATIC mylib.cpp)

target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/lib)