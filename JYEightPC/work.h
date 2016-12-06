#ifndef WORK_H
#define WORK_H
#include"setup.h"
#include <QDialog>

namespace Ui {
class Work;
}

class Work : public QDialog
{
    Q_OBJECT
    
public:
    explicit Work(QWidget *parent = 0);
    ~Work();
    
private:
    Ui::Work *ui;
    Setup setobjwork;


    //摄像头
    QImage *frame;//定义抓取帧
    QImage *frame1;//定义抓取帧
    QTimer *timercamera;//定时器
    QTimer *timercamera2;//定时器

    uchar * p;//转换RGB指针
    uchar * p1;//转换RGB指针

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_ptn_back_clicked();

    void cameraslot1();
    void cameraslot2();
};

#endif // WORK_H
