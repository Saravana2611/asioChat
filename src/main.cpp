#include <iostream>

#include "mylib.hpp"
#include "qt/TextField.hpp"
#include "qt/PushButton.hpp"
#include "asio/Server.hpp"
#include "asio/Client.hpp"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create the Qt application object
    QWidget mainWindow;

    auto *grid = new QGridLayout(&mainWindow);

    TextField textField("Input Field:");
    Button submitButton("Submit");

    grid->addWidget(textField.getQLabel(), 0, 0);
    grid->addWidget(textField.getQLineEdit(), 0, 1);

    grid->addWidget(submitButton.getButton(), 1, 1, Qt::AlignRight);

    QObject::connect(submitButton.getButton(), &QPushButton::clicked, [&textField]()
                     { std::cout << textField.getInputFieldInStr() << "\n"; });

    mainWindow.resize(250, 150);
    mainWindow.setWindowTitle("Simple App");
    mainWindow.show();

    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 12345);
        Server server(io_context, endpoint);
        Client client(io_context, endpoint);
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
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
