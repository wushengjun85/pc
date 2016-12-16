#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"work.h"
#include"setup.h"
#include"findlook.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private:
    Ui::Widget *ui;
    Findlook findlookobj;
    Setup   setupobj;


    QTimer *timer_xiaoshiji;
    QTimer *timer_shanhua;
    //QTimer *timergzm;

    QTimer *timer_Licheng;

      QTimer *timer_eventmouse;


protected:
    void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *target, QEvent *e);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void xiaoshiji();//小时计
    void shanhua();//闪烁和平滑转动
    void Licheng();
    void slotmouse();

    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // WIDGET_H
