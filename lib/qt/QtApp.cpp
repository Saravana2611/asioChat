#include <QtApp.hpp>

#include <iostream>

QtApp::QtApp(QWidget* parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);

    textField = new TextField("Input Field:");
    Button submitButton("Submit");

    grid->addWidget(textField->getQLabel(), 0, 0);
    grid->addWidget(textField->getQLineEdit(), 0, 1);

    grid->addWidget(submitButton.getButton(), 1, 1, Qt::AlignRight);

    QObject::connect(submitButton.getButton(), &QPushButton::clicked, [this]()
                     { std::cout << "HERE\n";
                        std::cout << textField->getInputFieldInStr() << "\n"; });
    resize(250, 150);
    setWindowTitle("Simple App");
}

QtApp::~QtApp()
{
    delete textField;
}