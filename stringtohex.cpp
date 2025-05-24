#include "stringtohex.h"

StringToHex::StringToHex(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StringToHexClass())
{
    setupUi();
    setupSignalSlot();
}

StringToHex::~StringToHex()
{
    delete ui;
}

inline void StringToHex::setupSignalSlot()
{
    connect(ui->cbEncoding, &QComboBox::currentIndexChanged, this, &StringToHex::cbIndexChanged);
    connect(ui->teHex, &QPlainTextEdit::textChanged, this, &StringToHex::textEditChanged);
    connect(ui->teString, &QPlainTextEdit::textChanged, this, &StringToHex::textEditChanged);
    
}

inline void StringToHex::setupUi()
{
    ui->setupUi(this);
    ui->cbEncoding->addItem("ASCII/LATIN1", StringToHex::ASCII);
    ui->cbEncoding->addItem("UTF-8", StringToHex::UTF8);
    ui->cbEncoding->addItem("UTF-16", StringToHex::UTF16);
}

void StringToHex::convertToString(const QByteArray& data)
{
    QStringDecoder decoder;
  
    switch (m_encoding)
    {
    case StringToHex::ASCII:
        decoder = QStringDecoder(QStringDecoder::Latin1);
        break;
    case StringToHex::UTF8:
        decoder = QStringDecoder(QStringDecoder::Utf8);
        break;
    case StringToHex::UTF16:
        decoder = QStringDecoder(QStringDecoder::Utf16);
        break;
    default:
        return;
    }

    ui->teString->setPlainText(decoder(QByteArray::fromHex(data)));
}

void StringToHex::cbIndexChanged(int index)
{
    qDebug() << "Index:" << index;
    m_encoding = static_cast<StringToHex::Encoding>(ui->cbEncoding->itemData(index).toInt());
}

void StringToHex::textEditChanged()
{
    QPlainTextEdit* e = static_cast<QPlainTextEdit*>(sender());
    if (e == nullptr)
        return;
    if ((e == ui->teHex) && (ui->teHex->hasFocus()))
        convertToString(ui->teHex->toPlainText().toLocal8Bit());
    else if ((e == ui->teString) && (ui->teString->hasFocus()))
        convertToHex(ui->teString->toPlainText());
}

void StringToHex::convertToHex(const QString& text)
{
    QStringEncoder encoder;
    
    switch (m_encoding)
    {
    case StringToHex::ASCII:
        encoder = QStringEncoder(QStringEncoder::Latin1);
        break;
    case StringToHex::UTF8:
        encoder = QStringEncoder(QStringEncoder::Utf8);
        break;
    case StringToHex::UTF16:
        encoder = QStringEncoder(QStringEncoder::Utf16);
        break;
    default:
        return;
    }
    const QByteArray& temp = encoder(text);
    ui->teHex->setPlainText(temp.toHex(' '));
}
