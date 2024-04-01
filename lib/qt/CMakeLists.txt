find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

add_library(myQt STATIC TextField.cpp PushButton.cpp)

target_link_libraries(myQt PRIVATE Qt5::Widgets Qt5::Core)
target_include_directories(myQt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})