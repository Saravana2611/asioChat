#pragma once

#include <QWidget>
#include <QPushButton>

class Button : public QWidget
{
    QPushButton *button;
public:
    Button(QWidget *parent = nullptr);
    Button(std::string buttonLabel, QWidget *parent = nullptr);
    QPushButton* getButton();
};