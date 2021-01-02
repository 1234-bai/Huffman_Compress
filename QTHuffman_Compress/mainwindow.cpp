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


void MainWindow::on_deButton_clicked()
{
    ComDialog* a = new ComDialog(this);
    a->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    DecomDialog *a = new DecomDialog(this);
    a->show();
}
