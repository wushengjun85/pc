/********************************************************************************
** Form generated from reading UI file 'work.ui'
**
** Created: Fri Dec 16 15:42:18 2016
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

QT_BEGIN_NAMESPACE

class Ui_Work
{
public:

    void setupUi(QDialog *Work)
    {
        if (Work->objectName().isEmpty())
            Work->setObjectName(QString::fromUtf8("Work"));
        Work->resize(1024, 600);

        retranslateUi(Work);

        QMetaObject::connectSlotsByName(Work);
    } // setupUi

    void retranslateUi(QDialog *Work)
    {
        Work->setWindowTitle(QApplication::translate("Work", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Work: public Ui_Work {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORK_H
