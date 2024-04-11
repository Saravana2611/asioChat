#pragma once

#include <QWidget>
#include <QGridLayout>

#include "TextField.hpp"
#include "PushButton.hpp"
#include "../BaseComponent.hpp"

class QtApp;

class QtApp : public QWidget, public BaseComponent
{
    QGridLayout* grid;
    TextField* textField;
    Button* submitButton;
    std::vector<QWidget*> addedWidgetsList;
    std::vector<QMetaObject::Connection> connectionList;
public:
    QtApp(QWidget *parent = nullptr);
    void createPage(QGridLayout *grid);
    void createPage2(QGridLayout *grid);
    void clearPage(QGridLayout *grid);
    ~QtApp();
};
