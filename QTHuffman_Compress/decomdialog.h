#ifndef DECOMDIALOG_H
#define DECOMDIALOG_H

#include <QDialog>

namespace Ui {
class DecomDialog;
}

class DecomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecomDialog(QWidget *parent = nullptr);
    ~DecomDialog();

private slots:

    void on_addFileNamesButton_2_clicked(); //点击“添加”按钮

    void on_delteFileNamesButton_2_clicked();   //点击“删除”按钮

    void on_choseFilePathButton_2_clicked();  //点击“浏览”按钮

    void on_CanelButton_2_clicked();  //点击“取消”按钮

    void on_StartButton_2_clicked();  //点击“开始”按钮

private:
    Ui::DecomDialog *ui;
};

#endif // DECOMDIALOG_H
