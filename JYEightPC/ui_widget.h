/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue Nov 29 16:18:35 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_12;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(608, 561, 38, 28));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/backlog.png);"));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(674, 559, 34, 34));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/setlog.png);"));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(738, 561, 32, 30));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img2/beeplog.png);"));
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(0, 548, 131, 31));
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setFrameShadow(QFrame::Plain);
        lcdNumber->setNumDigits(10);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_2 = new QLCDNumber(Widget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(0, 573, 131, 31));
        lcdNumber_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber_2->setFrameShape(QFrame::NoFrame);
        lcdNumber_2->setNumDigits(10);
        lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 136, 61, 31));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 183, 61, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 236, 61, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 294, 61, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 348, 61, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(85, 396, 101, 41));
        label_6->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(65, 454, 111, 31));
        label_7->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(Widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(648, 154, 71, 41));
        label_8->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(648, 242, 71, 41));
        label_9->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(Widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(648, 330, 71, 41));
        label_10->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(Widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(645, 440, 111, 41));
        label_12->setStyleSheet(QString::fromUtf8("font: 75 18pt \"Ubuntu\";"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(420, 520, 98, 61));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(300, 530, 113, 51));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(420, 450, 121, 61));
        pushButton_6 = new QPushButton(Widget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(660, 400, 96, 27));
        pushButton_6->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label->setText(QApplication::translate("Widget", "0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "1", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "2", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "3", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "4", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "5", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Widget", "6", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Widget", "7", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Widget", "8", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Widget", "9", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Widget", "11", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("Widget", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("Widget", "enable shansuo", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
