#include <TextField.hpp>

TextField::TextField(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("Default: ", this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    inputField = new QLineEdit(this);
}

TextField::TextField(std::string labelStr, QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel(QString::fromStdString(labelStr), this);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    inputField = new QLineEdit(this);
}

QLineEdit* TextField::getQLineEdit()
{
    return inputField;
}

QLabel* TextField::getQLabel()
{
    return label;
}

std::string TextField::getInputFieldInStr()
{
    return inputField->displayText().toStdString();
}