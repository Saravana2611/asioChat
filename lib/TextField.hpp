#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class TextField : public QWidget
{

public:
    QLabel *label;
    QLineEdit *inputField;
    TextField(QWidget *parent = nullptr);
    TextField(std::string labelStr, QWidget *parent = nullptr);
};