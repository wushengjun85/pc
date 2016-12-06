#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include"timeset.h"

namespace Ui {
class Setup;
}

class Setup : public QDialog
{
    Q_OBJECT
    
public:
    explicit Setup(QWidget *parent = 0);
    ~Setup();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::Setup *ui;
    Timeset timesetobj;


protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SETUP_H
