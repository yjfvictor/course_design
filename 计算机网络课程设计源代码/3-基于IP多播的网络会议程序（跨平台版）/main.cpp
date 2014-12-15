#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);

    Dialog w;
    w.show();

    return a.exec();
}
