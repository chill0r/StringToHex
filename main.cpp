#include "stringtohex.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StringToHex w;
    w.show();
    return a.exec();
}
