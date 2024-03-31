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