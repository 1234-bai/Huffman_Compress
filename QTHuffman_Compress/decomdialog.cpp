#include "decomdialog.h"
#include "ui_decomdialog.h"
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include "../FileRW.h"
#include <QProgressDialog>

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
        //QMessageBox::warning(this,tr("warning"),tr("the file is not exist"));
        return;
     }
    QFileInfo info(fileName);

    ui->tw_2->verticalHeader()->setVisible(true);   //隐藏列表头
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

    int num = ui->num_label->text().toUInt();
    num += info.size();
    ui->num_label->setText(QString::number(num));

    ui->delteFileNamesButton_2->setEnabled(true);
}

void DecomDialog::on_delteFileNamesButton_2_clicked()
{
    int rows = ui->tw_2->rowCount();
    int currentrow = ui->tw_2->currentRow();
    int targetrow = currentrow<=0 ? rows - 1 : currentrow;

    int num = ui->num_label->text().toUInt();
    num -= ui->tw_2->item(targetrow,1)->text().toInt();
    ui->num_label->setText(QString::number(num));

    ui->tw_2->removeRow(targetrow);
    if(rows < 1){
        ui->delteFileNamesButton_2->setEnabled(false);
    }
}

void DecomDialog::on_choseFilePathButton_2_clicked()
{
    QString filesPath = QFileDialog::getExistingDirectory(this, "chose path","../");
    if(filesPath.isNull()){
        //QMessageBox::warning(this,"警告","文件路径为空");
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
    if(savepath.isNull()){
        QMessageBox::warning(this,"警告","文件路径为空");
        return;
    }

    //进度条初始设置,暂时先这样，如果想达到，一边翻译，一边加载进度条的效果的话，要用到多线程。
    QProgressDialog * pro = new QProgressDialog(this);
    pro->setWindowModality(Qt::WindowModal);
    pro->setWindowTitle(tr("Please Wait"));
    pro->setLabelText(tr("Copressing..."));
    pro->setCancelButtonText(tr("Cancel"));
    pro->setRange(0,currentrow*10000);

    for(int i = 1; i <= currentrow; ++i){

        QString path = ui->tw_2->item(i-1,4)->text();
        QString filename = ui->tw_2->item(i-1,0)->text();
        QString fromfile = path + QString(QLatin1Char('/')) + filename;

        FileRW fi;
        if(!fi.initFileRW( fromfile.toStdString().c_str()  )){
            QMessageBox::warning(this,tr("warning"),tr("can't open %1").arg(filename));
            delete pro;
            return;
        }

        if(!fi.to_codeF(savepath.toStdString().c_str()) ){
            QMessageBox::warning(this,tr("fail"),tr("%1 decompress fail").arg(filename));
            delete pro;
            return;
        }

        for(int ii = 1; ii <= 10000; ++ii){
            pro->setValue((i-1)*10000 + ii);
            if(pro->wasCanceled()){
                delete pro;
                return;
            }
            for(int j = 0; j < 250; j++)
                for(int jj = 0; jj < 100; jj++);
        }

    }
    QMessageBox::information(this,tr("Gragulations"),tr("all files save sucessfully"));
}
