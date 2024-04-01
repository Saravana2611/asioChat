#include <PushButton.hpp>

Button::Button(QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton("DEFAULT", this);
    button->setFixedSize(100,30);
}

Button::Button(std::string buttonLabel, QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton(QString::fromStdString(buttonLabel), this);
    button->setFixedSize(100,30);
}

QPushButton* Button::getButton()
{
    return button;
}