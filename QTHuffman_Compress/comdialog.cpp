#include "comdialog.h"
#include "ui_comdialog.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "../FileRW.h"

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
    ui->delteFileNamesButton->setEnabled(false);
    ui->tw->setColumnCount(5);
    ui->tw->verticalHeader()->setVisible(true);   //隐藏列表头
    ui->tw->horizontalHeader()->setVisible(false); //隐藏行表头
    QStringList header;
    header<<"名称"<<"大小"<<"创建时间"<<"最后修改时间"<<"文件路径";
    ui->tw->setHorizontalHeaderLabels(header);
//    ui->tw->setColumnWidth(2,200);
//    ui->tw->setColumnWidth(3,200);
//    ui->tw->setColumnWidth(4,400);
    ui->tw->show();
}

ComDialog::~ComDialog()
{
    delete ui;
}

void ComDialog::on_addFileNamesButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "chose files", ".../", "( *.txt);;(*.bmp)");
    if(fileName.isNull()){
        QMessageBox::warning(this,tr("warning"),tr("the file is not exist"));
        return;
     }
    QFileInfo info(fileName);
    int row = ui->tw->rowCount();
        ui->tw->verticalHeader()->setVisible(true);   //隐藏列表头
        ui->tw->horizontalHeader()->setVisible(true); //隐藏行表头
        QStringList header;
        header<<"名称"<<"大小"<<"创建时间"<<"最后修改时间"<<"文件路径";
        ui->tw->setHorizontalHeaderLabels(header);
    ui->tw->setRowCount(row+1);
    ui->tw->setItem(row,0,new QTableWidgetItem(info.fileName()));
    ui->tw->setItem(row,1,new QTableWidgetItem(tr("%1").arg(info.size())));
    ui->tw->setItem(row,2,new QTableWidgetItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss")));
    ui->tw->setItem(row,3,new QTableWidgetItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss")));
    ui->tw->setItem(row,4,new QTableWidgetItem(info.path()));
    ui->tw->resizeColumnsToContents();
    ui->tw->show();
    ui->delteFileNamesButton->setEnabled(true);
}

void ComDialog::on_delteFileNamesButton_clicked()
{
    int rows = ui->tw->rowCount();
    int currentrow = ui->tw->currentRow();
    if(currentrow <= 0){
        ui->tw->removeRow(rows - 1);
    }
    else{
        ui->tw->removeRow(currentrow);
    }
    rows--;
    if(rows <= 1){
        ui->delteFileNamesButton->setEnabled(false);
    }
}

void ComDialog::on_choseFilePathButton_clicked()
{
    QString filesPath = QFileDialog::getExistingDirectory(this, "chose path","../");
    if(filesPath.isNull()){
        QMessageBox::warning(this,"警告","文件路径为空");
        return;
    }
    ui->textEdit->setText(filesPath);
}

void ComDialog::on_CanelButton_clicked()
{
    this->close();
}
//写文件不全，不知道是哪的问题：是qt的问题，还是核心代码的问题。
void ComDialog::on_StartButton_clicked()
{
    int currentrow = ui->tw->rowCount();
    //QMessageBox::information(this,tr("Gragulations"),QString::number(currentrow));
    if(currentrow < 1){
        QMessageBox::warning(this,tr("warning"),tr("no file"));
        return;
    }
    QString savepath = ui->textEdit->toPlainText();
    for(int i = 1; i <= currentrow; ++i){
        QString path = ui->tw->item(i-1,4)->text();
        //QMessageBox::warning(this,tr("warning"),path);

        QString filename = ui->tw->item(i-1,0)->text();
        QString tofile = savepath + QString(QLatin1Char('/')) +
                         filename.left( filename.lastIndexOf(".")+1 ) + ui->choseFileTypeButton->text();
        QString fromfile = path + QString(QLatin1Char('/')) + filename;
        FileRW fi;
        if(!fi.initFileRW( fromfile.toStdString().c_str() )){
            QMessageBox::warning(this,tr("warning"),tr("can't open %1").arg(filename));
            return;
        }
        if( !fi.codeF2comF( tofile.toStdString().c_str() ) ){
            QMessageBox::warning(this,tr("Pity"),filename + tr("save fail"));
            return;
        }
        //ui->tw->removeRow(i);
        //加进度条
    }
    QMessageBox::information(this,tr("Gragulations"),tr("all files save sucessfully"));
}
