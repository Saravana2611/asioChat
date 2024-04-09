#pragma once

#include <QWidget>
#include <QGridLayout>

#include "TextField.hpp"
#include "PushButton.hpp"
#include "../BaseComponent.hpp"

class QtApp;

class QtApp : public QWidget, BaseComponent
{
    QGridLayout* grid;
    TextField* textField;
public:
    QtApp(QWidget *parent = nullptr);
    ~QtApp();
};
