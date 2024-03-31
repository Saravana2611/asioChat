#pragma once

#include <QWidget>
#include <QPushButton>

class Button : public QWidget
{

public:
    QPushButton *button;
    Button(QWidget *parent = nullptr);
    Button(std::string buttonLabel, QWidget *parent = nullptr);
};