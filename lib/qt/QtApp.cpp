#include <QtApp.hpp>

#include <iostream>

QtApp::QtApp(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);
    createMainPage(grid);
    resize(500, 500);
    setWindowTitle("AsioChat");
}

const std::vector<std::string> connectionTypes
{
    "tcp",
    "udp",
    "tcp with tls"
};

void QtApp::createMainPage(QGridLayout *grid)
{
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(4, 1);

    grid->setRowStretch(0, 1);
    grid->setRowStretch(3, 1);

    auto dropDown = new DropDown(connectionTypes);
    grid->addWidget(dropDown->getDropDown(), 1, 1, 1, 2, Qt::AlignCenter);

    auto simulateButton = new Button("Simulate");
    grid->addWidget(simulateButton->getButton(), 1, 3, Qt::AlignCenter);

    QObject::connect(simulateButton->getButton(), &QPushButton::clicked, [dropDown](){
        std::cout << "Simulation started for " << dropDown->getSelectedOption() << std::endl;
    });
}

void QtApp::createPage(QGridLayout *grid)
{
    textField = new TextField("Input Field:");
    submitButton = new Button("Submit");
    textArea = new TextArea();

    grid->addWidget(textArea->getQTextEdit(), 0, 0, 1, 2);
    addedWidgetsList.push_back(textArea->getQTextEdit());

    grid->addWidget(textField->getQLabel(), 1, 0);
    addedWidgetsList.push_back(textField->getQLabel());

    grid->addWidget(textField->getQLineEdit(), 1, 1);
    addedWidgetsList.push_back(textField->getQLineEdit());

    grid->addWidget(submitButton->getButton(), 2, 1, Qt::AlignRight);
    addedWidgetsList.push_back(submitButton->getButton());

    QMetaObject::Connection conn = QObject::connect(submitButton->getButton(), &QPushButton::clicked, [this, grid]()
                                                    { 
                        this->mediator_->Notify(this, "SEND_TO_HOST", textField->getInputFieldInStr());
                        textArea->getQTextEdit()->append(textField->getInputFieldInQStr().prepend(QString("You: "))); });
    connectionList.push_back(conn);
}

void QtApp::appendMsgToTextArea(const std::string message)
{
    textArea->getQTextEdit()->append(QString::fromStdString(message).prepend(QString("Other Person: ")));
}

QtApp::~QtApp()
{
    delete textField;
    delete submitButton;
}