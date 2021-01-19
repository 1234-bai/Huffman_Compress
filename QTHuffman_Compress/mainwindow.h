#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_deButton_clicked();     //点击“文件压缩”按钮

    void on_pushButton_2_clicked();     //点击“文件解压”

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
