add_library(myAsio STATIC 
    NetworkManager.cpp
    TcpConnection.cpp
    UdpConnection.cpp
    TlsConnection.cpp
)

target_link_libraries(myAsio PUBLIC OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(myAsio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})