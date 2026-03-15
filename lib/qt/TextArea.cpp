#include <TextArea.hpp>

TextArea::TextArea(QWidget *parent)
{
    textArea = new QTextEdit(this);
    textArea->setReadOnly(true);
    textArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QTextEdit *TextArea::getQTextEdit()
{
    return textArea;
}