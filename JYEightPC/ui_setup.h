/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created: Tue Nov 29 16:18:35 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_H
#define UI_SETUP_H

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

class Ui_Setup
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;

    void setupUi(QDialog *Setup)
    {
        if (Setup->objectName().isEmpty())
            Setup->setObjectName(QString::fromUtf8("Setup"));
        Setup->resize(800, 600);
        pushButton = new QPushButton(Setup);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(735, 566, 35, 20));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/back.png);"));
        pushButton_2 = new QPushButton(Setup);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(170, 270, 43, 42));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/timesetlog.png);"));
        lcdNumber = new QLCDNumber(Setup);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(0, 548, 131, 31));
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setFrameShadow(QFrame::Plain);
        lcdNumber->setNumDigits(10);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_2 = new QLCDNumber(Setup);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(0, 573, 131, 31));
        lcdNumber_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber_2->setFrameShape(QFrame::NoFrame);
        lcdNumber_2->setNumDigits(10);
        lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
        label = new QLabel(Setup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(500, 260, 61, 41));
        label->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(Setup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(500, 325, 61, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Ubuntu\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(Setup);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(500, 380, 61, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Ubuntu\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_3 = new QPushButton(Setup);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(461, 264, 31, 31));
        pushButton_4 = new QPushButton(Setup);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(570, 264, 31, 31));
        pushButton_5 = new QPushButton(Setup);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(461, 327, 31, 31));
        pushButton_6 = new QPushButton(Setup);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(570, 327, 31, 31));
        pushButton_7 = new QPushButton(Setup);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(461, 384, 31, 31));
        pushButton_8 = new QPushButton(Setup);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(570, 384, 31, 31));

        retranslateUi(Setup);

        QMetaObject::connectSlotsByName(Setup);
    } // setupUi

    void retranslateUi(QDialog *Setup)
    {
        Setup->setWindowTitle(QApplication::translate("Setup", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label->setText(QApplication::translate("Setup", "11556", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Setup", "8989", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Setup", "68758", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Setup: public Ui_Setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
