/********************************************************************************
** Form generated from reading UI file 'setup.ui'
**
** Created: Fri Dec 16 15:42:18 2016
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
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Setup
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *Setup)
    {
        if (Setup->objectName().isEmpty())
            Setup->setObjectName(QString::fromUtf8("Setup"));
        Setup->resize(1024, 600);
        Setup->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(Setup);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(930, 532, 78, 57));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img/a4.png);"));
        pushButton_2 = new QPushButton(Setup);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(293, 142, 39, 39));
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img/timeicon.png);"));
        pushButton_3 = new QPushButton(Setup);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(560, 165, 28, 28));
        pushButton_3->setFocusPolicy(Qt::NoFocus);
        pushButton_3->setAutoRepeat(true);
        pushButton_4 = new QPushButton(Setup);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(670, 165, 28, 28));
        pushButton_4->setFocusPolicy(Qt::NoFocus);
        pushButton_4->setAutoRepeat(true);
        pushButton_5 = new QPushButton(Setup);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(642, 300, 28, 28));
        pushButton_5->setFocusPolicy(Qt::NoFocus);
        pushButton_5->setAutoRepeat(true);
        pushButton_6 = new QPushButton(Setup);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(752, 300, 28, 28));
        pushButton_6->setFocusPolicy(Qt::NoFocus);
        pushButton_6->setAutoRepeat(true);
        pushButton_7 = new QPushButton(Setup);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(665, 450, 28, 28));
        pushButton_7->setFocusPolicy(Qt::NoFocus);
        pushButton_7->setAutoRepeat(true);
        pushButton_8 = new QPushButton(Setup);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(555, 450, 28, 28));
        pushButton_8->setFocusPolicy(Qt::NoFocus);
        pushButton_8->setAutoRepeat(true);
        label = new QLabel(Setup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(600, 160, 66, 41));
        label_2 = new QLabel(Setup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(680, 300, 66, 41));
        label_3 = new QLabel(Setup);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(590, 440, 66, 41));
        pushButton_9 = new QPushButton(Setup);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(230, 358, 28, 28));
        pushButton_9->setFocusPolicy(Qt::NoFocus);
        pushButton_9->setAutoRepeat(true);
        pushButton_10 = new QPushButton(Setup);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(340, 358, 28, 28));
        pushButton_10->setFocusPolicy(Qt::NoFocus);
        pushButton_10->setAutoRepeat(true);
        pushButton_11 = new QPushButton(Setup);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(313, 454, 28, 28));
        pushButton_11->setFocusPolicy(Qt::NoFocus);
        pushButton_11->setAutoRepeat(true);
        pushButton_12 = new QPushButton(Setup);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(422, 454, 28, 28));
        pushButton_12->setFocusPolicy(Qt::NoFocus);
        pushButton_12->setAutoRepeat(true);
        label_4 = new QLabel(Setup);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(267, 354, 66, 41));
        label_5 = new QLabel(Setup);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(350, 450, 66, 41));

        retranslateUi(Setup);

        QMetaObject::connectSlotsByName(Setup);
    } // setupUi

    void retranslateUi(QDialog *Setup)
    {
        Setup->setWindowTitle(QApplication::translate("Setup", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Setup", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Setup", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Setup", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        pushButton_11->setText(QApplication::translate("Setup", "-", 0, QApplication::UnicodeUTF8));
        pushButton_12->setText(QApplication::translate("Setup", "+", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Setup", "123", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Setup", "456", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Setup: public Ui_Setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_H
