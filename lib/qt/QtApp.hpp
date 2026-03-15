#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>

#include "DropDown.hpp"
#include "TextArea.hpp"
#include "TextField.hpp"
#include "PushButton.hpp"
#include "../BaseComponent.hpp"

class QtApp;

class QtApp : public QWidget, public BaseComponent
{
    QStackedWidget* stack;

    QGridLayout* grid;
    TextField* textField;
    Button* submitButton;
    TextArea* textArea;

    TextField* textField2;
    Button* submitButton2;
    TextArea* textArea2;

    QWidget* mainPage;
    QWidget* chatPage;
public:
    QtApp(QWidget *parent = nullptr);
    QWidget* createChatPage();
    QWidget* createMainPage();
    void appendMsgToTextArea(const std::string message);
    void appendMsgToTextArea2(const std::string message);
    ~QtApp();
};
