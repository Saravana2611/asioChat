find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

add_library(mylib STATIC mylib.cpp TextField.cpp PushButton.cpp)

target_link_libraries(mylib PRIVATE Qt5::Widgets Qt5::Core)
target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/lib)