#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_stringtohex.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StringToHexClass; };
QT_END_NAMESPACE

class StringToHex : public QMainWindow
{
    Q_OBJECT

public:
    StringToHex(QWidget *parent = nullptr);
    ~StringToHex();

private:
    Ui::StringToHexClass *ui;

    enum Encoding
    {
        ASCII = 0,
        UTF8 = 1,
        UTF16 = 2
    };

    Encoding m_encoding = ASCII;

    inline void setupSignalSlot();
    inline void setupUi();

private slots:
    void convertToHex(const QString& text);
    void convertToString(const QByteArray& data);
    
    void cbIndexChanged(int index);
    void textEditChanged();

};
