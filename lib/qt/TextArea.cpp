#include <TextArea.hpp>

TextArea::TextArea(QWidget *parent)
{
    textArea = new QTextEdit(this);
    textArea->setReadOnly(true);
}

QTextEdit *TextArea::getQTextEdit()
{
    return textArea;
}