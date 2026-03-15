#include <iostream>
#include <thread>

#include <QApplication>

#include "AppManager.hpp"
#include "qt/QtApp.hpp"
#include "asio/NetworkManager.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Qt UI
    QtApp qtApp;

    // Asio context
    boost::asio::io_context io_context;

    // Keep io_context alive
    boost::asio::executor_work_guard<
        boost::asio::io_context::executor_type> work =
        boost::asio::make_work_guard(io_context);

    // Networking layer
    NetworkManager networkManager(io_context);

    // Mediator
    AppManager mediator(&qtApp, &networkManager);

    // Run Asio in separate thread
    std::thread io_thread([&]()
    {
        io_context.run();
    });

    qtApp.show();

    int result = app.exec();   // Qt event loop

    // Shutdown
    io_context.stop();
    io_thread.join();

    return result;
}