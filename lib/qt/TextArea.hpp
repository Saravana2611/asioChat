#pragma once

#include <QWidget>
#include <QTextEdit>

class TextArea : public QWidget
{
    QTextEdit *textArea;
public:
    TextArea(QWidget *parent = nullptr);
    QTextEdit *getQTextEdit();
};