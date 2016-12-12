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
    
private:
    Ui::Setup *ui;

    Timeset timesetobj;

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
};

#endif // SETUP_H
