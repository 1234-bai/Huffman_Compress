#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comdialog.h"
#include "decomdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_deButton_clicked()  //点击“文件压缩”按钮
{
    ComDialog* a = new ComDialog(); //打开“压缩文件界面”类
    a->show();
}

void MainWindow::on_pushButton_2_clicked()  //点击“文件解压”按钮
{
    DecomDialog *a = new DecomDialog(); //打开“解压文件界面类”
    a->show();
}
