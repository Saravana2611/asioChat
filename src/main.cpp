#include <iostream>

#include <QApplication>

#include "AppManager.hpp"
#include "qt/QtApp.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create the Qt application object
    
    QtApp qtApp;
    qtApp.show();
    

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
    Server server(io_context, endpoint);
    Client client(io_context, endpoint);
    AppManager *mediator = new AppManager(&qtApp, &server);
    // io_context.run();

    boost::asio::io_context::work work(io_context);

    std::thread io_thread([&io_context]()
                          { io_context.run(); });

    int result = app.exec(); // Enter the Qt event loop

    // Clean up
    io_context.stop();
    io_thread.join();

    return result;
}
