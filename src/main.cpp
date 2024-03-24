#include <iostream>
#include "mylib.hpp"

#include <QApplication>
#include <QPushButton>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create the Qt application object

    QPushButton button("Click me!"); // Create a QPushButton widget
    button.resize(100, 30); // Set the size of the button
    button.show(); // Display the button

    cout << mylib::add(10, 2) << endl;

    cout << mylib::add(10, 2) << endl;
    cout << mylib::sub(10, 2) << endl;
    cout << mylib::mul(10, 2) << endl;
    cout << mylib::div(10, 2) << endl;

    cout << mylib::add(1.0, 2.5) << endl;
    cout << mylib::sub(1.0, 2.5) << endl;
    cout << mylib::mul(1.0, 2.5) << endl;
    cout << mylib::div(1.0, 2.5) << endl;
    
    return app.exec(); // Enter the Qt event loop
}
