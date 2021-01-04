#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

//未解决的问题：进度条。计算时间。

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
