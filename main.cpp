#include "dialog.h"
#include <QApplication>
//#include <QTextCodec>
//#include <QDebug>

int main(int argc, char *argv[])
{
    //qDebug()<<QTextCodec::codecForLocale()->name();
    QCoreApplication::addLibraryPath("./plugins");
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
