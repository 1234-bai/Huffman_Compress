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
    ui->delteFileNamesButton_2->setEnabled(false);
}

DecomDialog::~DecomDialog()
{
    delete ui;
}

void DecomDialog::on_addFileNamesButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "chose files", ".../", "( *.cpr);;(*.dee)");
    if(fileName.isNull()){
        QMessageBox::warning(this,tr("warning"),tr("the file is not exist"));
        return;
     }
    QFileInfo info(fileName);
    ui->tw_2->verticalHeader()->setVisible(false);   //隐藏列表头
    ui->tw_2->horizontalHeader()->setVisible(true); //隐藏行表头
    QStringList header;
    header<<"名称"<<"大小"<<"创建时间"<<"最后修改时间"<<"文件路径";
    ui->tw_2->setHorizontalHeaderLabels(header);
    int row = ui->tw_2->rowCount();
    ui->tw_2->setRowCount(row+1);
    ui->tw_2->setItem(row,0,new QTableWidgetItem(info.fileName()));
    ui->tw_2->setItem(row,1,new QTableWidgetItem(tr("%1").arg(info.size())));
    ui->tw_2->setItem(row,2,new QTableWidgetItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss")));
    ui->tw_2->setItem(row,3,new QTableWidgetItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss")));
    ui->tw_2->setItem(row,4,new QTableWidgetItem(info.path()));
    ui->tw_2->resizeColumnsToContents();
    ui->tw_2->show();
    ui->delteFileNamesButton_2->setEnabled(true);
}

void DecomDialog::on_delteFileNamesButton_2_clicked()
{
    int rows = ui->tw_2->rowCount();
    int currentrow = ui->tw_2->currentRow();
    if(currentrow <= 0){
        ui->tw_2->removeRow(rows - 1);
    }
    else{
        ui->tw_2->removeRow(currentrow);
    }
    rows--;
    if(rows <= 1){
        ui->delteFileNamesButton_2->setEnabled(false);
    }
}

void DecomDialog::on_choseFilePathButton_2_clicked()
{
    QString filesPath = QFileDialog::getExistingDirectory(this, "chose path","../");
    if(filesPath.isNull()){
        QMessageBox::warning(this,"警告","文件路径为空");
        return;
    }
    ui->lineEdit->setText(filesPath);
}

void DecomDialog::on_CanelButton_2_clicked()
{
    this->close();
}

void DecomDialog::on_StartButton_2_clicked()
{
    int currentrow = ui->tw_2->rowCount();
    if(currentrow < 1){
        QMessageBox::warning(this,tr("warning"),tr("no file"));
        return;
    }

    QString savepath = ui->lineEdit->text();

    for(int i = 1; i <= currentrow; ++i){

        QString path = ui->tw_2->item(i-1,4)->text();
        QString filename = ui->tw_2->item(i-1,0)->text();

        QString tofile = savepath + QString(QLatin1Char('/')) +
                         filename.left( filename.lastIndexOf(".")+1 ) + ui->comboBox->currentText();

        QString fromfile = path + QString(QLatin1Char('/')) + filename;
        QString filetype = filename.right( filename.lastIndexOf(".") );

        FileRW fi;
        if(!fi.initFileRW( fromfile.toStdString().c_str()  )){
            QMessageBox::warning(this,tr("warning"),tr("can't open %1").arg(filename));
            return;
        }

        bool warn = false;
        if(filetype == ".cpr"){
            warn = !fi.comF2codF( tofile.toStdString().c_str() );
        }
        else if(filetype == ".dee"){
            warn = !fi.decodF2codeF( tofile.toStdString().c_str() );
        }
        else{
            QMessageBox::warning(this,tr("warning"),filetype + tr(" 目标文件格式错误"));
            return;
        }

        if(warn){
            QMessageBox::warning(this,tr("Pity"),filename + tr(" save fail"));
            return;
        }
//        ui->tw->removeRow(0);
//        ui->tw->show();
    }
    QMessageBox::information(this,tr("Gragulations"),tr("all files save sucessfully"));
}
