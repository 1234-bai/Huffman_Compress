#ifndef COMDIALOG_H
#define COMDIALOG_H

#include <QDialog>

namespace Ui {
class ComDialog;
}

class ComDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComDialog(QWidget *parent = nullptr);
    ~ComDialog();

private slots:
    void on_addFileNamesButton_clicked();   //点击“添加”按钮

    void on_delteFileNamesButton_clicked(); //点击“删除”按钮

    void on_choseFilePathButton_clicked();  //点击“浏览”按钮

    void on_CanelButton_clicked();  //点击“取消”按钮

    void on_StartButton_clicked();  //点击“开始”按钮

private:
    Ui::ComDialog *ui;
};

#endif // COMDIALOG_H
