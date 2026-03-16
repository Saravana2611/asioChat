add_library(myAsio STATIC NetworkManager.cpp TcpConnection.cpp UdpConnection.cpp)

target_include_directories(myAsio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})