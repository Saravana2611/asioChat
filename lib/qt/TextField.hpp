#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class TextField : public QWidget
{
    QLabel *label;
    QLineEdit *inputField;
public:
    TextField(QWidget *parent = nullptr);
    TextField(std::string labelStr, QWidget *parent = nullptr);
    QLineEdit* getQLineEdit();
    QLabel* getQLabel();
    std::string getInputFieldInStr();
};