#include <QtApp.hpp>

#include <iostream>

QtApp::QtApp(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);
    createPage(grid);
    resize(500, 500);
    setWindowTitle("AsioChat");
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
                        this->mediator_->Notify(this, "A", textField->getInputFieldInStr());
                        textArea->getQTextEdit()->append(textField->getInputFieldInQStr().prepend(QString("Person 1: ")));
                    });
    connectionList.push_back(conn);
}

void QtApp::createPage2(QGridLayout *grid)
{
    textField = new TextField("Input Field:");
    submitButton = new Button("Submit");

    grid->addWidget(textField->getQLabel(), 0, 0);
    addedWidgetsList.push_back(textField->getQLabel());

    grid->addWidget(textField->getQLineEdit(), 0, 1);
    addedWidgetsList.push_back(textField->getQLineEdit());

    grid->addWidget(submitButton->getButton(), 1, 1, Qt::AlignRight);
    addedWidgetsList.push_back(submitButton->getButton());

    QMetaObject::Connection conn = QObject::connect(submitButton->getButton(), &QPushButton::clicked, [this, grid]()
                     {  std::cout <<"HERE\n"; });

    connectionList.push_back(conn);
}

void QtApp::clearPage(QGridLayout *grid)
{
    for_each(this->addedWidgetsList.begin(), this->addedWidgetsList.end(), [grid](auto widget){
        grid->removeWidget(widget);
        widget->setVisible(false);
    });
    for_each(this->connectionList.begin(), this->connectionList.end(), [](auto conn){
        QObject::disconnect(conn);
    });
}

void QtApp::appendMsgToTextArea(const std::string message)
{
    textArea->getQTextEdit()->append(QString::fromStdString(message));
}

QtApp::~QtApp()
{
    delete textField;
    delete submitButton;
}