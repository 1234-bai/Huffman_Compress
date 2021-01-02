#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

//未解决的问题：进度条。计算时间。toolbutton。核心代码的那个小bug。表头消失问题

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
