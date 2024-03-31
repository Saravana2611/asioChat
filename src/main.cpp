#include <iostream>
#include "mylib.hpp"
#include "TextField.hpp"
#include "PushButton.hpp"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create the Qt application object
    QWidget mainWindow;

    auto *grid = new QGridLayout(&mainWindow);

    TextField window("Input Field:");
    Button submitButton("Submit");

    grid->addWidget(window.label, 0, 0);
    grid->addWidget(window.inputField, 0, 1);

    QObject::connect(submitButton.button, &QPushButton::clicked, [](){std::cout<<"HELLO";});
    grid->addWidget(submitButton.button, 1, 1, Qt::AlignRight);

    mainWindow.resize(250, 150);
    mainWindow.setWindowTitle("Simple App");
    mainWindow.show();

    return app.exec(); // Enter the Qt event loop
}
