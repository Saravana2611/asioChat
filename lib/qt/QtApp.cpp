#include <QtApp.hpp>

#include <iostream>
#include <QVBoxLayout>

#include "../Messages.hpp"

QtApp::QtApp(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("AsioChat");

    resize(800, 600);
    stack = new QStackedWidget(this);

    mainPage = createMainPage();
    chatPage = createChatPage();

    stack->addWidget(mainPage);
    stack->addWidget(chatPage);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack);
}

//  TODO: Change to enum Class
const std::vector<std::string> connectionTypes{
    "tcp",
    "udp",
    "tcp with tls"};

QWidget *QtApp::createMainPage()
{
    QWidget *page = new QWidget();

    QVBoxLayout *VLayout = new QVBoxLayout(page);
    VLayout->addStretch();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(10);

    layout->addStretch();
    auto dropDown = new DropDown(connectionTypes);
    layout->addWidget(dropDown->getDropDown());

    auto simulateButton = new Button("Simulate");
    layout->addWidget(simulateButton->getButton());

    layout->addStretch();
    QObject::connect(simulateButton->getButton(), &QPushButton::clicked, [dropDown, this]()
                     {
        Message message(Message::PROTOCOL_SELECTED, dropDown->getSelectedOption());
        this->mediator_->Notify(this, message);
        std::cout << "Simulation started for " << dropDown->getSelectedOption() << std::endl;

        // TODO: Change page after receiving response from server/client that connection is established instead of changing page immediately after clicking the button
        stack->setCurrentWidget(chatPage); });

    VLayout->addLayout(layout);
    VLayout->addStretch();

    return page;
}

QWidget *QtApp::createChatPage()
{
    QWidget *page = new QWidget();

    QHBoxLayout *layout = new QHBoxLayout(page);

    QVBoxLayout *chatLayout = new QVBoxLayout();

    textArea = new TextArea();
    chatLayout->addWidget(textArea->getQTextEdit());

    QHBoxLayout *msgBox = new QHBoxLayout();

    textField = new TextField("Input Field:");
    submitButton = new Button("Submit");
    msgBox->addWidget(textField->getQLabel());
    msgBox->addWidget(textField->getQLineEdit());
    msgBox->addWidget(submitButton->getButton());

    chatLayout->addLayout(msgBox);

    QObject::connect(submitButton->getButton(), &QPushButton::clicked, [this]()
                     { 
                    Message message(Message::FROM_SERVER_UI_TO_SERVER, textField->getInputFieldInStr());
                    this->mediator_->Notify(this, message);
                    textArea->getQTextEdit()->append(textField->getInputFieldInQStr().prepend(QString("You: "))); });

    QVBoxLayout *chatLayout2 = new QVBoxLayout();

    textArea2 = new TextArea();
    chatLayout2->addWidget(textArea2->getQTextEdit());

    QHBoxLayout *msgBox2 = new QHBoxLayout();

    textField2 = new TextField("Input Field:");
    submitButton2 = new Button("Submit");
    msgBox2->addWidget(textField2->getQLabel());
    msgBox2->addWidget(textField2->getQLineEdit());
    msgBox2->addWidget(submitButton2->getButton());

    chatLayout2->addLayout(msgBox2);

    QObject::connect(submitButton2->getButton(), &QPushButton::clicked, [this]()
                     { 
                        Message message(Message::FROM_CLIENT_UI_TO_CLIENT, textField2->getInputFieldInStr());
                        this->mediator_->Notify(this, message);
                        textArea2->getQTextEdit()->append(textField2->getInputFieldInQStr().prepend(QString("You: "))); });

    layout->addLayout(chatLayout);
    layout->addLayout(chatLayout2);

    return page;
}

void QtApp::appendMsgToTextArea2(const std::string message)
{
    textArea2->getQTextEdit()->append(QString::fromStdString(message).prepend(QString("Server: ")));
}

void QtApp::appendMsgToTextArea(const std::string message)
{
    textArea->getQTextEdit()->append(QString::fromStdString(message).prepend(QString("Client: ")));
}

QtApp::~QtApp()
{
    delete textField;
    delete submitButton;
    delete textArea;
    delete textField2;
    delete submitButton2;
    delete textArea2;
}