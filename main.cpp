#include "mainwindow.h"
#include "mywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("KOI-8R"));
    QApplication a(argc, argv);
    MyWindow *window = new MyWindow;
    Interface *inter = new Interface;
    window->show();

    QObject::connect(window, SIGNAL(Sig(QString)), inter, SLOT(Message(QString)));
    return a.exec();
}
