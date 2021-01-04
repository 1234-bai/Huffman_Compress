/********************************************************************************
** Form generated from reading UI file 'decomdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECOMDIALOG_H
#define UI_DECOMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DecomDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QTableWidget *tw_2;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *addFileNamesButton_2;
    QPushButton *delteFileNamesButton_2;
    QFrame *frame_3;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QPushButton *choseFilePathButton_2;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *StartButton_2;
    QPushButton *CanelButton_2;

    void setupUi(QDialog *DecomDialog)
    {
        if (DecomDialog->objectName().isEmpty())
            DecomDialog->setObjectName(QString::fromUtf8("DecomDialog"));
        DecomDialog->resize(870, 689);
        verticalLayout = new QVBoxLayout(DecomDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(DecomDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferAntialias);
        label_8->setFont(font);

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        tw_2 = new QTableWidget(frame);
        if (tw_2->columnCount() < 5)
            tw_2->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tw_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tw_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tw_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tw_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tw_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tw_2->setObjectName(QString::fromUtf8("tw_2"));
        tw_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tw_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        tw_2->setShowGrid(true);
        tw_2->horizontalHeader()->setVisible(false);
        tw_2->verticalHeader()->setVisible(false);

        gridLayout_6->addWidget(tw_2, 1, 0, 1, 1);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(474, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        addFileNamesButton_2 = new QPushButton(frame_5);
        addFileNamesButton_2->setObjectName(QString::fromUtf8("addFileNamesButton_2"));

        horizontalLayout_6->addWidget(addFileNamesButton_2);

        delteFileNamesButton_2 = new QPushButton(frame_5);
        delteFileNamesButton_2->setObjectName(QString::fromUtf8("delteFileNamesButton_2"));

        horizontalLayout_6->addWidget(delteFileNamesButton_2);


        gridLayout_6->addWidget(frame_5, 2, 0, 1, 1);


        verticalLayout->addWidget(frame);

        frame_3 = new QFrame(DecomDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setMaximumSize(QSize(16777215, 160));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_6->setFont(font1);

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        frame_8 = new QFrame(frame_3);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_8);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(frame_8);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(60, 0));

        horizontalLayout_5->addWidget(label_5);

        lineEdit = new QLineEdit(frame_8);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit);

        choseFilePathButton_2 = new QPushButton(frame_8);
        choseFilePathButton_2->setObjectName(QString::fromUtf8("choseFilePathButton_2"));

        horizontalLayout_5->addWidget(choseFilePathButton_2);


        gridLayout_4->addWidget(frame_8, 1, 0, 1, 1);


        verticalLayout->addWidget(frame_3);

        frame_4 = new QFrame(DecomDialog);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(494, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        StartButton_2 = new QPushButton(frame_4);
        StartButton_2->setObjectName(QString::fromUtf8("StartButton_2"));

        horizontalLayout_4->addWidget(StartButton_2);

        CanelButton_2 = new QPushButton(frame_4);
        CanelButton_2->setObjectName(QString::fromUtf8("CanelButton_2"));

        horizontalLayout_4->addWidget(CanelButton_2);


        verticalLayout->addWidget(frame_4);


        retranslateUi(DecomDialog);

        QMetaObject::connectSlotsByName(DecomDialog);
    } // setupUi

    void retranslateUi(QDialog *DecomDialog)
    {
        DecomDialog->setWindowTitle(QCoreApplication::translate("DecomDialog", "\346\226\207\344\273\266\350\247\243\345\216\213", nullptr));
        label_8->setText(QCoreApplication::translate("DecomDialog", "\346\226\260\345\212\240\350\247\243\345\216\213\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tw_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DecomDialog", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tw_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DecomDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tw_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DecomDialog", "\345\210\233\345\273\272\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tw_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DecomDialog", "\346\234\200\345\220\216\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tw_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DecomDialog", "\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        addFileNamesButton_2->setText(QCoreApplication::translate("DecomDialog", "\346\267\273\345\212\240", nullptr));
        delteFileNamesButton_2->setText(QCoreApplication::translate("DecomDialog", "\345\210\240\351\231\244", nullptr));
        label_6->setText(QCoreApplication::translate("DecomDialog", "\350\247\243\345\216\213\346\226\207\344\273\266\350\256\276\347\275\256", nullptr));
        label_5->setText(QCoreApplication::translate("DecomDialog", "\346\226\207\344\273\266\350\247\243\345\216\213\350\267\257\345\276\204\345\217\212\345\220\215\347\247\260\357\274\232", nullptr));
        choseFilePathButton_2->setText(QCoreApplication::translate("DecomDialog", "\346\265\217\350\247\210", nullptr));
        StartButton_2->setText(QCoreApplication::translate("DecomDialog", "\345\274\200\345\247\213", nullptr));
        CanelButton_2->setText(QCoreApplication::translate("DecomDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DecomDialog: public Ui_DecomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECOMDIALOG_H
