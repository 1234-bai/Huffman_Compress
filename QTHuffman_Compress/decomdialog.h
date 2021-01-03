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

    void on_addFileNamesButton_2_clicked();

    void on_delteFileNamesButton_2_clicked();

    void on_choseFilePathButton_2_clicked();

    void on_CanelButton_2_clicked();

    void on_StartButton_2_clicked();

private:
    Ui::DecomDialog *ui;
};

#endif // DECOMDIALOG_H
