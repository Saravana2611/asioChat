#pragma once

#include <QWidget>
#include <QGridLayout>

#include "DropDown.hpp"
#include "TextArea.hpp"
#include "TextField.hpp"
#include "PushButton.hpp"
#include "../BaseComponent.hpp"

class QtApp;

class QtApp : public QWidget, public BaseComponent
{
    QGridLayout* grid;
    TextField* textField;
    Button* submitButton;
    TextArea* textArea;
    std::vector<QWidget*> addedWidgetsList;
    std::vector<QMetaObject::Connection> connectionList;
public:
    QtApp(QWidget *parent = nullptr);
    void createPage(QGridLayout *grid);
    void createMainPage(QGridLayout *grid);
    void appendMsgToTextArea(const std::string message);
    ~QtApp();
};
