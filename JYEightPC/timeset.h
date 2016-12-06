#ifndef TIMESET_H
#define TIMESET_H

#include <QDialog>

namespace Ui {
class Timeset;
}

class Timeset : public QDialog
{
    Q_OBJECT
    
public:
    explicit Timeset(QWidget *parent = 0);
    ~Timeset();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

private:
    Ui::Timeset *ui;
};

#endif // TIMESET_H
