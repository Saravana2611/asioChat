#pragma once

#include <QWidget>
#include <QComboBox>

class DropDown : public QWidget
{
    QComboBox *dropDown;
public:
    DropDown(QWidget *parent = nullptr);
    DropDown(std::vector<std::string> dropDownList, QWidget *parent = nullptr);
    QComboBox* getDropDown();
    std::string getSelectedOption();
};