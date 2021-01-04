#include "comdialog.h"
#include "ui_comdialog.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "../FileRW.h"
#include <QProgressDialog>

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
    ui->delteFileNamesButton->setEnabled(false);
}

ComDialog::~ComDialog()
{
    delete ui;
}

void ComDialog::on_addFileNamesButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "chose files", ".../", "( *.txt);;(*.bmp)");
    if(fileName.isNull()){
        //QMessageBox::warning(this,tr("warning"),tr("the file is not exist"));
        return;
     }
    QFileInfo info(fileName);
    int row = ui->tw->rowCount();
        ui->tw->verticalHeader()->setVisible(false);   //隐藏列表头
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
    if(filesPath.isEmpty()){
        //QMessageBox::warning(this,"警告","文件路径为空");
        return;
    }
    ui->lineEdit->setText(filesPath);
}

void ComDialog::on_CanelButton_clicked()
{
    this->close();
}

//写文件不全，是深浅拷贝的问题
void ComDialog::on_StartButton_clicked()
{
    int currentrow = ui->tw->rowCount();
    if(currentrow < 1){
        QMessageBox::warning(this,tr("warning"),tr("no file"));
        return;
    }

    //进度条初始设置,暂时先这样，如果想达到，一边翻译，一边加载进度条的效果的话，要用到多线程。
    QProgressDialog * pro = new QProgressDialog(this);
    pro->setWindowModality(Qt::WindowModal);
    pro->setWindowTitle(tr("Please Wait"));
    pro->setLabelText(tr("Copressing..."));
    pro->setCancelButtonText(tr("Cancel"));
    pro->setRange(0,currentrow*10000);

    //获得保存路径
    QString savepath = ui->lineEdit->text();
    if(savepath.isNull()){
        //QMessageBox::warning(this,"警告","文件路径为空");
        return;
    }

    for(int i = 1; i <= currentrow; ++i){
        //获得源文件，目标文件路径
        QString path = ui->tw->item(i-1,4)->text();
        QString filename = ui->tw->item(i-1,0)->text();
        QString filetype = ui->comboBox->currentText();

        QString tofile = savepath + QString(QLatin1Char('/')) +
                         filename.left( filename.lastIndexOf(".")+1 ) + filetype;

        QString fromfile = path + QString(QLatin1Char('/')) + filename;

        FileRW fi;
        if(!fi.initFileRW( fromfile.toStdString().c_str()  )){
            QMessageBox::warning(this,tr("warning"),tr("can't open %1").arg(filename));
            return;
        }
        //检测文件类型，选择对应的函数进行操作
        bool warn = false;
        if(filetype == "cpr"){
            warn = !fi.codeF2comF( tofile.toStdString().c_str() );
        }
        else if(filetype == "dee"){
            warn = !fi.codeF2decodF( tofile.toStdString().c_str() );
        }
        else{
            QMessageBox::warning(this,tr("warning"),tr("目标文件格式错误"));
            return;
        }

        if(warn){
            QMessageBox::warning(this,tr("Pity"),filename + tr(" save fail"));
            return;
        }

        //进度条模块
        for(int ii = 1; ii <= 10000; ++ii){
            pro->setValue((i-1)*10000 + ii);
            if(pro->wasCanceled()){
                return;
            }
            for(int j = 0; j < 250; j++)
                for(int jj = 0; jj < 100; jj++);
        }

    }
    QMessageBox::information(this,tr("Gragulations"),tr("all files save sucessfully"));
}
