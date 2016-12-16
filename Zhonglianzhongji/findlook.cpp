

#include "findlook.h"
#include "ui_findlook.h"
#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QPainter>
//#include"hwlib/libshm.h"

//RAM_CAN_sData canfindlook;

uint spn[4]= {77,88,99,10};
uint fmi[4]= {11,22,33,55};

Findlook::Findlook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Findlook)
{
    ui->setupUi(this);
    //解析现象，当去掉 setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); 这一句，在开发板子上能显示上方图标，但是不闪烁，
    //不注释则可以在板子上闪烁。
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

     QTimer *timerFindlook = new QTimer(this);   //声明一个定时器
     timergzm = new QTimer();//故障码
    connect(timerFindlook, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
     connect(timergzm, SIGNAL(timeout()), this, SLOT(gzmslottest()));  //连接信号槽，定时器超时触发窗体更新
    timerFindlook->start(500);
    timergzm->start(1000);
     //Can_Ram_init();

}

Findlook::~Findlook()
{
    delete ui;
}

void Findlook::paintEvent(QPaintEvent *)
{
    QPainter painterfindlook(this);
    QPixmap pixfindlook;
    pixfindlook.load("./img/findlook.bmp");
    painterfindlook.drawPixmap(0,0,1024,600,pixfindlook);


#if 0
     Can_Ram_Get(&canfindlook);

    //高速信号 输入
    if(canfindlook.flagfastspeed)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(300,220,35,24,pixfindlook);
    }
    //卸粮筒开 输入

    if(canfindlook.flagXLTopen)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(300,258,35,24,pixfindlook);
    }
    //卸粮筒开 输出
    if(canfindlook.flagXLTopenDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(350,258,35,24,pixfindlook);
    }
    //卸粮筒合 输入

    if(canfindlook.flagXLTclose)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(300,297,35,24,pixfindlook);
    }
    //卸粮筒合 输出

    if(canfindlook.flagXLTcloseDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(350,297,35,24,pixfindlook);
    }
    //液压主力合松开 输入
    if(canfindlook.flagYYMainSK)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(346,376,35,24,pixfindlook);
    }

    //液压主力合松开 输出
    if(canfindlook.flagYYMainSKDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(393,376,35,24,pixfindlook);
    }
    //液压主力合张紧 输入
    if(canfindlook.flagYYMainZJ)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(370,415,35,24,pixfindlook);
    }
    //液压主力合张紧 输出
    if(canfindlook.flagYYMainZJDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(417,415,35,24,pixfindlook);
    }

    //右侧

    //割台升 输入
    if(canfindlook.flagGTup)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(730,210,35,24,pixfindlook);
    }
    //割台升 输出
    if(canfindlook.flagGTupDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(778,210,35,24,pixfindlook);
    }
    //割台降 输入
    if(canfindlook.flagGTdown)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(730,244,35,24,pixfindlook);
    }
    //割台降 输出

    if(canfindlook.flagGTdownDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(778,244,35,24,pixfindlook);
    }
    //拔禾轮升 输入
    if(canfindlook.flagBHLup)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(730,296,35,24,pixfindlook);
    }
    //拔禾轮升 输出
    if(canfindlook.flagBHLupDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(778,296,35,24,pixfindlook);
    }
    //拔禾轮降 输入

    if(canfindlook.flagBHLdown)
    {
        pixfindlook.load("./img/d1.png");
        painterfindlook.drawPixmap(730,330,35,24,pixfindlook);
    }
    //拔禾轮降 输出
    if(canfindlook.flagBHLdownDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(778,330,35,24,pixfindlook);
    }
    //刹车  输出
    if(canfindlook.flagSCDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(730,388,35,24,pixfindlook);
    }
    //溢流阀 输出
    if(canfindlook.flagYLDCF)
    {
        pixfindlook.load("./img/d2.png");
        painterfindlook.drawPixmap(730,421,35,24,pixfindlook);
    }
#endif

}

void Findlook::on_pushButton_clicked()//关闭查询
{
    this->close();
}
int j;
int i = 0;
void Findlook::gzmslottest()//故障码显示
{
    if(i<4)//是否有数据 0和1  1表示有数据
    {

        //for(int i = 0; i < 4; i++)
        {
            ui->label->setText(QString::number(fmi[i]));//FMI
            ui->label_2->setText(QString::number(spn[i]));//SPN

//            qDebug()<<"spn_can.fim[i]"<<fmi[i];
//            qDebug()<<"spn_can.spn[i]"<<spn[i];
//            qDebug()<<"j == "<<j++<<endl;
        }
        i++;

    }
    else
    {
         //qDebug()<<"else else else  ..."<<endl;
        //ui->label->setText(QString::number(0));//FMI
        //ui->label_2->setText(QString::number(0));//SPN
        i = 0;
    }
}
