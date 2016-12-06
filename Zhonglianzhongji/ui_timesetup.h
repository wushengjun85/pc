/********************************************************************************
** Form generated from reading UI file 'timesetup.ui'
**
** Created: Wed Nov 16 11:09:29 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESETUP_H
#define UI_TIMESETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Timesetup
{
public:

    void setupUi(QDialog *Timesetup)
    {
        if (Timesetup->objectName().isEmpty())
            Timesetup->setObjectName(QString::fromUtf8("Timesetup"));
        Timesetup->resize(400, 300);

        retranslateUi(Timesetup);

        QMetaObject::connectSlotsByName(Timesetup);
    } // setupUi

    void retranslateUi(QDialog *Timesetup)
    {
        Timesetup->setWindowTitle(QApplication::translate("Timesetup", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Timesetup: public Ui_Timesetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESETUP_H
