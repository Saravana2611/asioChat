#include <iostream>

#include "mylib.hpp"
#include "qt/TextField.hpp"
#include "qt/PushButton.hpp"

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
                     { std::cout << textField.getInputFieldInStr();});
                     
    mainWindow.resize(250, 150);
    mainWindow.setWindowTitle("Simple App");
    mainWindow.show();

    return app.exec(); // Enter the Qt event loop
}
