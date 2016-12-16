#include "widget.h"
#include "ui_widget.h"
#include <QEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton_2->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->label->setText("Hello 3 second!");
}

//void Widget::mousePressEvent(QMouseEvent *event)
//{

//}

bool Widget::eventFilter(QObject *target, QEvent *e)
{



    if(target == ui->pushButton_3)
    {
        if(e->type() == QEvent::MouseButtonPress)//QEvent::Enter
         ui->label->setText("wushengjun");
    }
   // return Widget::eventFilter(target, e);
}



