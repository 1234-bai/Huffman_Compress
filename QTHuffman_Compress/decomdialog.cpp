#include "decomdialog.h"
#include "ui_decomdialog.h"
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include "../FileRW.h"

DecomDialog::DecomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecomDialog)
{
    ui->setupUi(this);
    QMenu *pMenu = new QMenu;
    pMenu->addAction(tr("txt"));
    pMenu->addAction(tr("cpr"));
    ui->choseFileTypeButton_2->setMenu(pMenu);
    ui->choseFileTypeButton_2->setText(tr("txt"));
}

DecomDialog::~DecomDialog()
{
    delete ui;
}

void DecomDialog::on_choseFileTypeButton_2_triggered(QAction *arg1)
{

}

void DecomDialog::on_addFileNamesButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "chose files", ".../", "( *.cpr)");
    if(fileName.isNull()){
        QMessageBox::warning(this,tr("warning"),tr("the file is not exist"));
        return;
     }
    QFileInfo info(fileName);
    int row = ui->tw_2->rowCount();
    ui->tw_2->setRowCount(row+1);
    ui->tw_2->setItem(row,0,new QTableWidgetItem(info.fileName()));
    ui->tw_2->setItem(row,1,new QTableWidgetItem(tr("%1").arg(info.size())));
    ui->tw_2->setItem(row,2,new QTableWidgetItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss")));
    ui->tw_2->setItem(row,3,new QTableWidgetItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss")));
    ui->tw_2->setItem(row,4,new QTableWidgetItem(info.path()));
    ui->tw_2->resizeColumnsToContents();
    ui->tw_2->show();
}

void DecomDialog::on_delteFileNamesButton_2_clicked()
{
    int row = ui->tw_2->currentRow();
    ui->tw_2->removeRow(row);
}


void DecomDialog::on_choseFilePathButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "chose path",".../","(*.txt);;(*.bmp)");
    ui->textEdit_2->setText(filename);
}

void DecomDialog::on_CanelButton_2_clicked()
{
    this->close();
}

void DecomDialog::on_StartButton_2_clicked()
{
    int row = ui->tw_2->currentRow();
    if(row <= 0){
        QMessageBox::warning(this,tr("warning"),tr("no file"));
        return;
    }
    QString tofile = ui->textEdit_2->toPlainText();
    QString path = ui->tw_2->item(row,4)->text();
    QString filename = ui->tw_2->item(row,0)->text();
    FileRW fi( (filename + path).toStdString().c_str() );
    if( fi.comF2codF( tofile.toStdString().c_str() ) ){
        QMessageBox::information(this,tr("Gragulations"),tr("save sucessfully"));
    }
    else {
        QMessageBox::warning(this,tr("Pity"),tr("save fail"));
    }
}
