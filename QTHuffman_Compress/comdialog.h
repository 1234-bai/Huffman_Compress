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
    void on_addFileNamesButton_clicked();

    void on_delteFileNamesButton_clicked();

    void on_choseFilePathButton_clicked();

    void on_CanelButton_clicked();

    void on_StartButton_clicked();

private:
    Ui::ComDialog *ui;
};

#endif // COMDIALOG_H
