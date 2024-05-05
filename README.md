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
    │   ├── asio
    │   │   ├── Client.cpp
    │   │   ├── Client.hpp
    │   │   ├── Server.cpp
    │   │   └── Server.hpp
    │   └── qt
    │       ├── PushButton.cpp
    │       ├── PushButton.hpp
    │       ├── QtApp.cpp
    │       ├── QtApp.hpp
    │       ├── TextArea.cpp
    │       └── TextArea.hpp
    └── src
        └── main.cpp

## Library Components

### AppManager
  The AppManager class serves as a mediator between the Qt user interface (QtApp) and the server (Server) or client (Client) components. It receives notifications from these components and triggers appropriate actions based on the received events.
### Boost.Asio Networking

  - **Server**: Manages TCP server functionality, handles incoming connections, and processes client requests.
  - **Client**: Establishes connections to the server and sends/receives data.

### Qt User Interface

  - **QtApp**: Main application window.
  - **PushButton**: Custom button widget.
  - **TextField**: Custom text field widget.
  - **TextArea**: Custom text area widget.

## Build Process

    ./configure.sh
    ./make.sh
    ./run.sh (Run another instance to create client)

## User Interface Screenshots
![Screenshot from 2024-05-05 14-01-49](https://github.com/Saravana2611/asioChat/assets/76907286/5164801f-0645-4eb5-8e86-20cc1dfe8e25)

## Dependencies

  - **CMake**: https://cmake.org/download/
  - **Boost.Asio**: https://www.boost.org/users/download/
  - **Qt**: https://www.qt.io/download
## Note

This project is a personal endeavor aimed at learning CMake, Boost.Asio, and Qt. It serves to deepen understanding and proficiency in these technologies by building a practical application that combines them seamlessly. The primary goals include gaining hands-on experience with CMake for efficient project building, understanding Boost.Asio's networking capabilities, and exploring Qt's GUI framework. 
