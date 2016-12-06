/********************************************************************************
** Form generated from reading UI file 'work.ui'
**
** Created: Tue Nov 29 16:18:35 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORK_H
#define UI_WORK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Work
{
public:
    QPushButton *ptn_back;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_12;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_13;
    QPushButton *pushButton_4;
    QLabel *label_14;

    void setupUi(QDialog *Work)
    {
        if (Work->objectName().isEmpty())
            Work->setObjectName(QString::fromUtf8("Work"));
        Work->resize(800, 600);
        ptn_back = new QPushButton(Work);
        ptn_back->setObjectName(QString::fromUtf8("ptn_back"));
        ptn_back->setGeometry(QRect(608, 561, 38, 28));
        ptn_back->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/backlog.png);"));
        pushButton_2 = new QPushButton(Work);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(674, 559, 34, 34));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/setlog.png);"));
        pushButton_3 = new QPushButton(Work);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(738, 561, 32, 30));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/beeplog.png);"));
        lcdNumber_2 = new QLCDNumber(Work);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(0, 573, 131, 31));
        lcdNumber_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber_2->setFrameShape(QFrame::NoFrame);
        lcdNumber_2->setNumDigits(10);
        lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber = new QLCDNumber(Work);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(0, 548, 131, 31));
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setFrameShadow(QFrame::Plain);
        lcdNumber->setNumDigits(10);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        label = new QLabel(Work);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 136, 61, 31));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(Work);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 348, 61, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(Work);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 236, 61, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(Work);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 294, 61, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(Work);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 183, 61, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(Work);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(65, 454, 111, 31));
        label_7->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(Work);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(85, 396, 101, 41));
        label_6->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(Work);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(645, 440, 111, 41));
        label_12->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(Work);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(648, 154, 71, 41));
        label_8->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_11 = new QLabel(Work);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(340, 418, 101, 41));
        label_11->setStyleSheet(QString::fromUtf8("font: 75 22pt \"Ubuntu\";"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_9 = new QLabel(Work);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(648, 242, 71, 41));
        label_9->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(Work);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(648, 330, 71, 41));
        label_10->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_13 = new QLabel(Work);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(330, 470, 111, 41));
        label_13->setStyleSheet(QString::fromUtf8("font: 75 22pt \"Ubuntu\";"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_4 = new QPushButton(Work);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(660, 390, 96, 27));
        pushButton_4->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/icon/35.png);"));
        label_14 = new QLabel(Work);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(242, 143, 323, 243));
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(Work);

        QMetaObject::connectSlotsByName(Work);
    } // setupUi

    void retranslateUi(QDialog *Work)
    {
        Work->setWindowTitle(QApplication::translate("Work", "Dialog", 0, QApplication::UnicodeUTF8));
        ptn_back->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label->setText(QApplication::translate("Work", "0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Work", "4", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Work", "2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Work", "3", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Work", "1", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Work", "6", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Work", "5", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Work", "11", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Work", "7", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Work", "10", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Work", "8", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Work", "9", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Work", "13", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QString());
        label_14->setText(QApplication::translate("Work", "16", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Work: public Ui_Work {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORK_H
