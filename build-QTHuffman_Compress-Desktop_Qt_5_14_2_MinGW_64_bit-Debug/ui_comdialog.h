/********************************************************************************
** Form generated from reading UI file 'comdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMDIALOG_H
#define UI_COMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_ComDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *tw;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addFileNamesButton;
    QPushButton *delteFileNamesButton;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QPushButton *choseFilePathButton;
    QLabel *label_2;
    QFrame *frame_7;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QComboBox *comboBox;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *StartButton;
    QPushButton *CanelButton;

    void setupUi(QDialog *ComDialog)
    {
        if (ComDialog->objectName().isEmpty())
            ComDialog->setObjectName(QString::fromUtf8("ComDialog"));
        ComDialog->resize(907, 776);
        verticalLayout_2 = new QVBoxLayout(ComDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(ComDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferAntialias);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tw = new QTableWidget(frame);
        if (tw->columnCount() < 5)
            tw->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tw->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tw->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tw->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tw->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tw->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tw->setObjectName(QString::fromUtf8("tw"));
        tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tw->setSelectionBehavior(QAbstractItemView::SelectRows);
        tw->setShowGrid(true);
        tw->setRowCount(0);
        tw->horizontalHeader()->setVisible(false);
        tw->verticalHeader()->setVisible(false);
        tw->verticalHeader()->setHighlightSections(true);

        gridLayout->addWidget(tw, 1, 0, 1, 1);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(474, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addFileNamesButton = new QPushButton(frame_2);
        addFileNamesButton->setObjectName(QString::fromUtf8("addFileNamesButton"));

        horizontalLayout->addWidget(addFileNamesButton);

        delteFileNamesButton = new QPushButton(frame_2);
        delteFileNamesButton->setObjectName(QString::fromUtf8("delteFileNamesButton"));
        delteFileNamesButton->setEnabled(true);
        delteFileNamesButton->setCheckable(false);
        delteFileNamesButton->setFlat(false);

        horizontalLayout->addWidget(delteFileNamesButton);


        gridLayout->addWidget(frame_2, 2, 0, 1, 1);


        verticalLayout_2->addWidget(frame);

        frame_3 = new QFrame(ComDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 0));
        frame_3->setMaximumSize(QSize(16777215, 160));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame_6 = new QFrame(frame_3);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(frame_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(60, 0));

        horizontalLayout_3->addWidget(label_3);

        lineEdit = new QLineEdit(frame_6);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(lineEdit);

        choseFilePathButton = new QPushButton(frame_6);
        choseFilePathButton->setObjectName(QString::fromUtf8("choseFilePathButton"));

        horizontalLayout_3->addWidget(choseFilePathButton);


        gridLayout_3->addWidget(frame_6, 1, 0, 1, 1);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        frame_7 = new QFrame(frame_3);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_7);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        label_4 = new QLabel(frame_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        comboBox = new QComboBox(frame_7);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(85, 0));
        comboBox->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);


        gridLayout_3->addWidget(frame_7, 2, 0, 1, 1);


        verticalLayout_2->addWidget(frame_3);

        frame_4 = new QFrame(ComDialog);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(494, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        StartButton = new QPushButton(frame_4);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));

        horizontalLayout_2->addWidget(StartButton);

        CanelButton = new QPushButton(frame_4);
        CanelButton->setObjectName(QString::fromUtf8("CanelButton"));

        horizontalLayout_2->addWidget(CanelButton);


        verticalLayout_2->addWidget(frame_4);


        retranslateUi(ComDialog);

        addFileNamesButton->setDefault(false);
        delteFileNamesButton->setDefault(false);
        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ComDialog);
    } // setupUi

    void retranslateUi(QDialog *ComDialog)
    {
        ComDialog->setWindowTitle(QCoreApplication::translate("ComDialog", "\346\226\260\345\273\272\345\216\213\347\274\251\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("ComDialog", "\346\226\260\345\212\240\345\216\213\347\274\251\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tw->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ComDialog", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tw->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ComDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tw->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ComDialog", "\345\210\233\345\273\272\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tw->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ComDialog", "\346\234\200\345\220\216\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tw->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ComDialog", "\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        addFileNamesButton->setText(QCoreApplication::translate("ComDialog", "\346\267\273\345\212\240", nullptr));
        delteFileNamesButton->setText(QCoreApplication::translate("ComDialog", "\345\210\240\351\231\244", nullptr));
        label_3->setText(QCoreApplication::translate("ComDialog", "\344\277\235\345\255\230\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        choseFilePathButton->setText(QCoreApplication::translate("ComDialog", "\346\265\217\350\247\210", nullptr));
        label_2->setText(QCoreApplication::translate("ComDialog", "\345\216\213\347\274\251\346\226\207\344\273\266\350\256\276\347\275\256", nullptr));
        label_4->setText(QCoreApplication::translate("ComDialog", "\347\233\256\346\240\207\346\226\207\344\273\266\346\240\274\345\274\217\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ComDialog", "dee", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ComDialog", "cpr", nullptr));

        StartButton->setText(QCoreApplication::translate("ComDialog", "\345\274\200\345\247\213", nullptr));
        CanelButton->setText(QCoreApplication::translate("ComDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComDialog: public Ui_ComDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMDIALOG_H
