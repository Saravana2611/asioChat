#include <DropDown.hpp>

DropDown::DropDown(QWidget *parent)
    : QWidget(parent)
{
    dropDown = new QComboBox(this);
    dropDown->setFixedSize(100,30);
}

QStringList vectorToQStringList(const std::vector<std::string>& stringVec) {
    QStringList qtStrings;
    qtStrings.reserve(stringVec.size());
    std::transform(stringVec.begin(), stringVec.end(), std::back_inserter(qtStrings),
                   &QString::fromStdString);
    return qtStrings;
}

DropDown::DropDown(std::vector<std::string> dropDownList, QWidget *parent)
    : QWidget(parent)
{
    dropDown = new QComboBox(this);
    dropDown->setMinimumWidth(300);
    dropDown->addItems(vectorToQStringList(dropDownList));
}

std::string DropDown::getSelectedOption()
{
    return dropDown->currentText().toStdString();
}

QComboBox* DropDown::getDropDown()
{
    return dropDown;
}