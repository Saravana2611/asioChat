# Project Documentation
## Overview

This project implements a TCP server-client communication system with a Qt-based user interface. The server and client functionality are integrated into the same binary, allowing seamless communication between multiple instances of the application.

## Directory Structure

    ├── CMakeLists.txt
    ├── configure.sh
    ├── make.sh
    ├── run.sh
    ├── lib
    │   ├── AppManager.cpp
    │   ├── AppManager.hpp
    │   ├── BaseComponent.hpp
    │   ├── Messages.hpp
    │   ├── mediator.hpp
    │   ├── asio
    │   │   ├── IConnection.hpp
    │   │   ├── NetworkManager.cpp
    │   │   ├── NetworkManager.hpp
    │   │   ├── TcpConnection.cpp
    │   │   ├── TcpConnection.hpp
    │   │   ├── TlsConnection.cpp
    │   │   ├── TlsConnection.hpp
    │   │   ├── UdpConnection.cpp
    │   │   ├── UdpConnection.hpp
    │   │   ├── utils.cpp
    │   │   └── utils.hpp
    │   └── qt
    │       ├── DropDown.cpp
    │       ├── DropDown.hpp
    │       ├── PushButton.cpp
    │       ├── PushButton.hpp
    │       ├── QtApp.cpp
    │       ├── QtApp.hpp
    │       ├── TextArea.cpp
    │       ├── TextArea.hpp
    │       ├── TextField.cpp
    │       └── TextField.hpp
    └── src
        └── main.cpp

## Library Components

### AppManager
  The AppManager class serves as a mediator between the Qt user interface (QtApp) and the networking components (NetworkManager). It receives notifications from these components and triggers appropriate actions based on the received events.
### Boost.Asio Networking

  - **NetworkManager**: Manages network operations, handles connections, and processes data transmission.
  - **IConnection**: Interface defining the contract for different connection types.
  - **TcpConnection**: Implements TCP connection functionality for reliable data transmission.
  - **TlsConnection**: Implements TLS/SSL connection for secure communication.
  - **UdpConnection**: Implements UDP connection for connectionless communication.

### Qt User Interface

  - **QtApp**: Main application window.
  - **PushButton**: Custom button widget.
  - **TextField**: Custom text field widget.
  - **TextArea**: Custom text area widget.
  - **DropDown**: Custom dropdown menu widget.

## Build Process

    ./configure.sh
    ./make.sh
    ./run.sh (Run another instance to create client)

## User Interface Screenshots
<img width="792" height="632" alt="image" src="https://github.com/user-attachments/assets/12710e9c-f4b7-4f10-a48f-09fbf3b960a7" />

<img width="794" height="631" alt="image" src="https://github.com/user-attachments/assets/54769f33-b31e-4014-a260-da237a4c6531" />

## Dependencies

  - **CMake**: https://cmake.org/download/
  - **Boost.Asio**: https://www.boost.org/users/download/
  - **Qt**: https://www.qt.io/download
## Note

This project is a personal endeavor aimed at learning CMake, Boost.Asio, and Qt. It serves to deepen understanding and proficiency in these technologies by building a practical application that combines them seamlessly. The primary goals include gaining hands-on experience with CMake for efficient project building, understanding Boost.Asio's networking capabilities, and exploring Qt's GUI framework. 
