#include <iostream>

#include <QApplication>

#include "AppManager.hpp"
#include "qt/QtApp.hpp"
#include "asio/utils.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create the Qt application object

    QtApp qtApp;

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345);

    Server *server = nullptr;
    Client *client = nullptr;

    if (!isServerRunning(io_context, endpoint))
    {
        std::cout << "Starting as Server" << std::endl;
        server = new Server(io_context, endpoint);
        server->start_accept();
        AppManager *mediator = new AppManager(&qtApp, server);
    }
    else
    {
        std::cout << "Starting as Client" << std::endl;
        client = new Client(io_context, endpoint);
        client->start_client();
        AppManager *mediator = new AppManager(&qtApp, client);
    }

    // io_context.run();

    boost::asio::io_context::work work(io_context);

    std::thread io_thread([&io_context]()
                          { io_context.run(); });
    qtApp.show();
    int result = app.exec(); // Enter the Qt event loop

    // Clean up
    io_context.stop();
    io_thread.join();

    delete server;
    delete client;

    return result;
}
