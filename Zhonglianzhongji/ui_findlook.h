/********************************************************************************
** Form generated from reading UI file 'findlook.ui'
**
** Created: Tue Dec 6 09:10:27 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDLOOK_H
#define UI_FINDLOOK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Findlook
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *Findlook)
    {
        if (Findlook->objectName().isEmpty())
            Findlook->setObjectName(QString::fromUtf8("Findlook"));
        Findlook->resize(1024, 600);
        Findlook->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(Findlook);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(930, 532, 78, 57));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/img/a4.png);"));
        label = new QLabel(Findlook);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(368, 135, 75, 36));
        label->setStyleSheet(QString::fromUtf8("font: 75 italic 20pt \"Ubuntu\";"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(Findlook);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(557, 135, 121, 34));
        label_2->setStyleSheet(QString::fromUtf8("font: 75 italic 20pt \"Ubuntu\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(Findlook);

        QMetaObject::connectSlotsByName(Findlook);
    } // setupUi

    void retranslateUi(QDialog *Findlook)
    {
        Findlook->setWindowTitle(QApplication::translate("Findlook", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        label->setText(QApplication::translate("Findlook", "102", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Findlook", "55", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Findlook: public Ui_Findlook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDLOOK_H
