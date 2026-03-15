#include <PushButton.hpp>

Button::Button(QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton("DEFAULT", this);
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

Button::Button(std::string buttonLabel, QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton(QString::fromStdString(buttonLabel), this);
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QPushButton* Button::getButton()
{
    return button;
}