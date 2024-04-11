find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

add_library(mylib STATIC AppManager.cpp)

add_subdirectory(qt)
add_subdirectory(asio)

target_link_libraries(mylib PRIVATE Qt5::Widgets Qt5::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC myQt myAsio)
target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/lib)