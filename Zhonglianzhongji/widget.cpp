#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QtSql>
#include<QTextCodec>
#include<QMouseEvent>
//#include"hwlib/libshm.h"
/********************************************************************************************************************/
//定义时间变量用于各界面传递
//2016.7.11

//RAM_CAN_sData cantest;
//uchar flagLeftqt = 0;
QString  Datesetup;

long long xiaoshiJi_m;//分钟
double xiaoshiJi_h;//小时
float fadongzhuansu; //发动机转速

//uchar flagadd = 1;//转速方向标志位
uchar flagaddnum = 1;//转速方向标志位
uchar flagnum;

int nu2;
uchar nu1;

int nu4;
uchar nu3;

int num = 0;
int numtmp = 0;

uint matchine[3] = {0}; //保存风机，复托器，升运器，等转速 的百分比
int ruby[3] = {0};
//频率量
ushort  shengyunqi =7;    //升运器
ushort  futuoqi =9;       //复脱器
ushort  zhouliuguntong=55;//轴流滚筒
ushort tuoliguntong=8;//脱粒滚筒转速

//米计 里程
//

double MIJILICHENG[3] = {0}; //保存风机，复托器，升运器，等转速 的百分比
uint clearflag;//清零标志
uint  clearSave;//存储清零标志
uchar clearCount;

uint mijisum;//米计和， 用于显示
double licheng = 1;//里程
double lichengsum;//里程和，用于显示

//闪烁标志
//
uchar shanshuoSW;//水温闪烁
uchar shanshuoJYYL;//机油压力闪烁
uchar shanshuoYL;//油量闪烁

uchar shanshuozlzs;//轴流滚筒转速
uchar shanshuoftqzs;//复托器转速
uchar shanshuosyqzs;//升运器转速




//uchar flagMijLic = 0;//米计里程切换标志
uchar flagbeep = 0;//蜂鸣器状态标志

/**************************/

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(1024,600);

    //解析现象，当去掉 setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); 这一句，在开发板子上能显示上方图标，但是不闪烁，
    //不注释则可以在板子上闪烁。
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

    QTimer *timer = new QTimer(this);   //声明一个定时器
    timer_xiaoshiji = new QTimer(); //声明小时计定时器
    timer_shanhua = new QTimer();//闪烁
    timer_Licheng = new QTimer();//里程

    connect(timer_Licheng,SIGNAL(timeout()),this,SLOT(Licheng()));//里程
    connect(timer_xiaoshiji,SIGNAL(timeout()),this,SLOT(xiaoshiji()));//小时计
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新

    connect(timer_shanhua, SIGNAL(timeout()), this, SLOT(shanhua()));  //连接信号槽，定时器超时触发窗体更新
    //connect(testtimergzm, SIGNAL(timeout()), this, SLOT(gzmslottest()));  //连接信号槽，定时器超时触发窗体更新

    timer->start(30);   //启动定时器
    timer_xiaoshiji->start(1000);
    timer_Licheng->start(1000);
    timer_shanhua->start(30);

    //Can_Ram_init();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QTime time = QTime::currentTime();   //获取当前的时间
    QPainter painter(this);
    QPixmap pix;
    pix.load("./img/xingzou.bmp");
    painter.drawPixmap(0,0,1024,600,pix);

   // Can_Ram_Get(&cantest);

#if 1
    //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

    painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
    //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

    painter.translate(511, 264);//重新定位坐标起始点，把坐标原点放到窗体的中央
    //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

    //下面两个数组用来定义表针的两个顶点，以便后面的填充
    static const QPoint hourHand[4] = {
        QPoint(18, 0),
        QPoint(-18,0),
        QPoint(-2, -170),
        QPoint(2, -170)
    };
    static const QPoint minuteHand[4] = {
        QPoint(18, 0),
        QPoint(-18, 0),
        QPoint(-2, -114),
        QPoint(2, -114)
    };

    //km r/mini
    painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();
    painter.rotate(-98);

    //painter.rotate(16.0 *time.second());
    painter.rotate(7.5*nu1);
    painter.drawConvexPolygon(hourHand, 4);  //填充分针部分
    painter.restore();

    /***********************************************/
    //2016.6.25   画白圈
    painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),20,20);
    painter.restore();

    //画白圈
    /***********************************************/

    painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),20,20);
    painter.restore();


    //km/h
    painter.translate(3,148);//重新定位坐标起始点，把坐标原点放到窗体的中央
    //painter.scale(side / 400.0, side / 300.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.save();

    //painter.rotate(16.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
    painter.rotate(-95);
    painter.rotate(7.5*nu3);
    //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
    //内测用
    /****************************************************************************/
    //qDebug()<<"time: "<<time.second()<<endl;

    /****************************************************************************/

    painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.restore();

    /***********************************************/
    //2016.6.25   画白圈
    painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
    painter.save();
    painter.drawEllipse(QPoint(0,0),13,13);
    painter.restore();

    //画白圈
    /***********************************************/


    painter.setBrush(Qt::black);
    painter.save();//画上中心原点
    painter.drawEllipse(QPoint(0,0),10,10);
    painter.restore();

    //chuli pupian shansuo
    painter.translate(-405,-432);//平移到左上角

#endif

    //大图
    pix.load("./img/bigpan.png");
    painter.drawPixmap(273,160,260,203,pix);


    //小图
    pix.load("./img/smallpan.png");
    painter.drawPixmap(316,347,175,174,pix);

/****************************************************************************************************************************************************/

/**************************************************************************************************************/
//
//
//控件显示
//显示时间 。2016.7.12
QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");//yyyy-MM-dd

ui->label_12->setText(dateStr1);//dateStr1
ui->label_11->setText(timeStr1);
/**************************************************************************************************************/
//上方灯

//左转

//比较can传过来的值 ，实现闪烁

QPainter paintShanshuo_W(this);
QPixmap pixShanshuo_W;

if(1)//cantest.flagLeft
{
    pixShanshuo_W.load("./img/dqbj/01.png");
    paintShanshuo_W.drawPixmap(37,30,33,34,pixShanshuo_W);
}
//远光灯

if(1)
{
    pixShanshuo_W.load("./img/dqbj/02.png");
    paintShanshuo_W.drawPixmap(81,37,38,23,pixShanshuo_W);
}
//近光灯

if(1)
{
    pixShanshuo_W.load("./img/dqbj/03.png");
    paintShanshuo_W.drawPixmap(130,36,37,27,pixShanshuo_W);
}
//示宽灯
if(1)
{
    pixShanshuo_W.load("./img/dqbj/04.png");
    paintShanshuo_W.drawPixmap(178,36,43,24,pixShanshuo_W);
}
//充电指示灯
if(1)
{
    pixShanshuo_W.load("./img/dqbj/05.png");
    paintShanshuo_W.drawPixmap(233,37,34,24,pixShanshuo_W);
}
//MCU

if(1)
{
    pixShanshuo_W.load("./img/dqbj/06.png");
    paintShanshuo_W.drawPixmap(280,38,49,21,pixShanshuo_W);
}
//ECU
if(1)//cantest.flagECU
{
    pixShanshuo_W.load("./img/dqbj/07.png");
    paintShanshuo_W.drawPixmap(340,38,42,21,pixShanshuo_W);
}
//高速信号
if(1)
{
    pixShanshuo_W.load("./img/dqbj/08.png");
    paintShanshuo_W.drawPixmap(393,33,33,30,pixShanshuo_W);
}

//右侧
//水温
if(1)
{
    pixShanshuo_W.load("./img/dqbj/09.png");
    paintShanshuo_W.drawPixmap(606,33,31,28,pixShanshuo_W);
}
//油量  闪烁
if(1)
{
    pixShanshuo_W.load("./img/dqbj/10.png");
    paintShanshuo_W.drawPixmap(648,33,24,28,pixShanshuo_W);
}
//预热
if(1)
{
    pixShanshuo_W.load("./img/dqbj/11.png");
    paintShanshuo_W.drawPixmap(682,36,37,23,pixShanshuo_W);
}
//机油压力 闪烁
if(1)
{
    pixShanshuo_W.load("./img/dqbj/12.png");
    paintShanshuo_W.drawPixmap(729,38,48,20,pixShanshuo_W);
}
//手刹
if(1)
{
    pixShanshuo_W.load("./img/dqbj/13.png");
    paintShanshuo_W.drawPixmap(787,35,37,29,pixShanshuo_W);
}
//发动机故障
if(1)
{
    pixShanshuo_W.load("./img/dqbj/14.png");
    paintShanshuo_W.drawPixmap(834,37,36,23,pixShanshuo_W);
}
//粮满
if(1)
{
    pixShanshuo_W.load("./img/dqbj/15.png");
    paintShanshuo_W.drawPixmap(880,33,32,32,pixShanshuo_W);
}
//油中右水  油水分离
if(1)
{
    pixShanshuo_W.load("./img/dqbj/16.png");
    paintShanshuo_W.drawPixmap(922,33,29,31,pixShanshuo_W);
}
//右转
if(1)
{
    pixShanshuo_W.load("./img/dqbj/17.png");
    paintShanshuo_W.drawPixmap(959,31,34,35,pixShanshuo_W);
}

//测试 ，洒粮损失率
if(1)
{
    pixShanshuo_W.load("./img/saliang/01.png");
    paintShanshuo_W.drawPixmap(64,168,156,27,pixShanshuo_W);
}

/*************************************************************************************/
//水温格数

QPainter paintSuiWen(this);
QPixmap pixSuiWen;

switch(8)//shuiwen
{
    case 0:

    case 1:
    pixSuiWen.load("./img/shuiwen/01.png");
    paintSuiWen.drawPixmap(263,317,45,24,pixSuiWen);
    break;

    case 2:
    pixSuiWen.load("./img/shuiwen/02.png");
    paintSuiWen.drawPixmap(259,290,49,50,pixSuiWen);
    break;

    case 3:
    pixSuiWen.load("./img/shuiwen/03.png");
    paintSuiWen.drawPixmap(257,263,50,76,pixSuiWen);
    break;

    case 4:
    pixSuiWen.load("./img/shuiwen/04.png");
    paintSuiWen.drawPixmap(257,239,50,101,pixSuiWen);
    break;

    case 5:
    pixSuiWen.load("./img/shuiwen/05.png");
    paintSuiWen.drawPixmap(257,212,50,127,pixSuiWen);
    break;

    case 6:
    pixSuiWen.load("./img/shuiwen/06.png");
    paintSuiWen.drawPixmap(257,187,56,153,pixSuiWen);
    break;

    case 7:
    pixSuiWen.load("./img/shuiwen/07.png");
    paintSuiWen.drawPixmap(257,160,69,179,pixSuiWen);
    break;

    case 8:
    pixSuiWen.load("./img/shuiwen/08.png");
    paintSuiWen.drawPixmap(257,137,79,204,pixSuiWen);
    break;

    default:
    //qDebug()<<"VOL sW sw SW SW SW "<<cantest.VolSW<<endl;
    break;
}

//水温报警
if(shanshuoSW)
{
    pixSuiWen.load("./img/zjmbj/04.png");
    paintSuiWen.drawPixmap(272,350,31,28,pixSuiWen);
}
/*************************************************************************************/
/*************************************************************************************/
//油量格数
switch(7)
{
    case 1:
    pixSuiWen.load("./img/youliang/01.png");
    paintSuiWen.drawPixmap(716,316,46,24,pixSuiWen);
    break;

    case 2:
    pixSuiWen.load("./img/youliang/02.png");
    paintSuiWen.drawPixmap(716,290,50,50,pixSuiWen);
    break;

    case 3:
    pixSuiWen.load("./img/youliang/03.png");
    paintSuiWen.drawPixmap(715,265,51,75,pixSuiWen);
    break;

    case 4:
    pixSuiWen.load("./img/youliang/04.png");
    paintSuiWen.drawPixmap(716,239,51,101,pixSuiWen);
    break;

    case 5:
    pixSuiWen.load("./img/youliang/05.png");
    paintSuiWen.drawPixmap(716,214,51,127,pixSuiWen);
    break;

    case 6:
    pixSuiWen.load("./img/youliang/06.png");
    paintSuiWen.drawPixmap(710,188,57,153,pixSuiWen);
    break;

    case 7:
    pixSuiWen.load("./img/youliang/07.png");
    paintSuiWen.drawPixmap(698,162,69,179,pixSuiWen);
    break;

    case 8:
    pixSuiWen.load("./img/youliang/08.png");
    paintSuiWen.drawPixmap(688,136,79,205,pixSuiWen);
    break;

    default:
    break;

}

//油量报警

if(shanshuoYL)
{
    pixSuiWen.load("./img/zjmbj/05.png");
    paintSuiWen.drawPixmap(716,355,24,29,pixSuiWen);

}
/*************************************************************************************/


/***************************************************************************************************************************************************/
//读取数据库信息
//
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示

        QSqlDatabase db;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
          db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName("jy.db");
       if (!db.open())
       {
           qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
       }
       QSqlQuery query;

    #if 0
       bool ok = query.exec("create table myjy10(id INTEGER,name varchar,age INTEGER)");
       if (ok)
       {
           qDebug()<<"ceate table partition success"<<endl;
       }
       else
       {
           qDebug()<<"ceate table partition failed"<<endl;
       }
    #endif
            //query.prepare("INSERT INTO myjy10 (id, name, age) VALUES (:id, :name, :age)");

            uchar i = 0;
            query.exec("select id, name, age from jy8c");
            while (query.next())
            {
                matchine[i++] = query.value(2).toInt();
            }

    #if 1
            i = 0;
            for (i = 0; i < 3; i++)
                {
                    //qDebug()<<"matchine % bi "<<matchine[i]<<endl;
                }
            i = 0;
    #endif



            query.exec(QObject::tr("drop jy8c"));

    /*******************************************************************/

                   ruby[0] = matchine[0];
                   ruby[1] = matchine[1];
                   ruby[2] = matchine[2];

                  //比较can传过来的值 ，实现闪烁

//                   QPainter paintShanshuo_W(this);
//                   QPixmap pixShanshuo_W;

              //if(can_retern != 0)

              {
                  //qDebug()<<"return != 0"<<endl;

                   if(tuoliguntong<ruby[0])//轴流滚筒转速
                   {
                       if (tuoliguntong != 0)
                       {
                           pixShanshuo_W.load("./img/zjmbj/03.png");//11.   jpgenglish/shanshuo/
                           paintShanshuo_W.drawPixmap(802,294,89,21,pixShanshuo_W);
                       }

                       // qDebug()<<"bpj"<<endl;
                   }

                   if(futuoqi<ruby[1])//复脱器转速
                   {
                       if (futuoqi != 0)
                       {
                           pixShanshuo_W.load("./img/zjmbj/01.png");//11.jpg
                           paintShanshuo_W.drawPixmap(803,139,88,20,pixShanshuo_W);
                       }

                       //qDebug()<<"syqzs"<<endl;
                   }

                   if(shengyunqi<ruby[2])//升运器堵塞转速
                   {
                       if (shengyunqi != 0)
                       {
                           pixShanshuo_W.load("./img/zjmbj/02.png");//11.jpg
                           paintShanshuo_W.drawPixmap(802,216.5,90,20,pixShanshuo_W);
                       }

                       //qDebug()<<"syqzs"<<endl;
                   }

              }//endof if(can_return != 0)

     //闪烁 转速

#if 1
     if(shanshuozlzs)//轴流滚筒转速
     {
         pixShanshuo_W.load("./img/zjmbj/03.png");//11.   jpgenglish/shanshuo/
         paintShanshuo_W.drawPixmap(802,294,89,21,pixShanshuo_W);
     }

     if(shanshuoftqzs)//复托器转速
     {
         pixShanshuo_W.load("./img/zjmbj/01.png");//11.jpg
         paintShanshuo_W.drawPixmap(803,139,88,20,pixShanshuo_W);
     }

     if(shanshuosyqzs)//升运器转速
     {
         pixShanshuo_W.load("./img/zjmbj/02.png");//11.jpg
         paintShanshuo_W.drawPixmap(802,216.5,90,20,pixShanshuo_W);
     }

#endif


//label 显示
//2016.11.18
//ui->label->setText(QString::number(cantest.MIJI));//米计
//ui->label_2->setText(QString::number(lichengsum)); //里程
//ui->label_3->setText(QString::number());//电池电压

float JYYL = 1000;//cantest.VolJYYL/
ui->label_4->setText(QString::number(JYYL,'f',2));//机油压力

//ui->label_5->setText(QString::number());//洒粮损失率cantest.SaLiangLV
//ui->label_6->setText(QString::number());//割茬高度 cmcantest.GeChaheight
//ui->label_7->setText(QString::number());//小时计


//ui->label_8->setText(QString::number(cantest.FTspeed));//复脱器
//ui->label_9->setText(QString::number(cantest.SYspeed));//升运器
//ui->label_10->setText(QString::number(cantest.ZLspeed));//轴流滚筒


}

void Widget::on_pushButton_clicked()//查询界面
{
    this->close();
    findlookobj.show();
    findlookobj.exec();
    this->show();
}

void Widget::on_pushButton_2_clicked()//设置界面
{
    this->close();
    setupobj.show();
    setupobj.exec();
    this->show();
}


//里程 槽函数
void Widget::Licheng()//里程
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");


   //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("jy.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
   }
   QSqlQuery query;
   #if 0
   bool ok = query.exec("create table licheng(id INTEGER,name varchar,age INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }
   #endif

   uchar j = 0;
   query.exec("select id, name, age from licheng");
   while (query.next())
   {

     // qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
     //xiaoshiJi_m = query.value(2).toInt();

       MIJILICHENG[j++] = query.value(2).toDouble();

   }
   j = 0;

    clearflag = MIJILICHENG[2];
    mijisum = MIJILICHENG[1];
    lichengsum = MIJILICHENG[0];

    clearCount++;
    if((clearCount==1)&&(clearflag == 1))
    {
        clearSave = 1;
    }
    qDebug()<<"MIJILICHENG[2];clearflag ----- = "<<clearflag<<endl;

    if(clearflag)
    {
        mijisum += 1;//cantest.MIJI;
        ui->label->setText(QString::number(mijisum));//米计

    }
    else
    {
        mijisum = 0;//cantest.MIJI;
        ui->label->setText(QString::number(mijisum));//米计
    }
    //licheng = (cantest.MIJI/1000)*1000+(cantest.MIJI%1000);

//    lockshm();//加共享内存锁
//    cantest.MIJI = 0;
//    unlockshm();//解共享内存锁
    //licheng /= 1000;
    lichengsum += licheng;
    ui->label_2->setText(QString::number(lichengsum,'f',1));
          //query.prepare("INSERT INTO licheng (id, name, age) VALUES (:id, :name, :age)");

          query.prepare("update licheng set age = :age where id = :id");

          //query.prepare(update_sql);
          query.bindValue(":id",1);
          //query.bindValue(":name", QObject::tr("里程"));
          query.bindValue(":age", lichengsum);
          query.exec();

          query.bindValue(":id",2);
          //query.bindValue(":name", QObject::tr("米计"));
          query.bindValue(":age", mijisum);
          query.exec();

          query.bindValue(":id",3);
          //query.bindValue(":name", QObject::tr("状态值"));
          query.bindValue(":age", clearSave);
          query.exec();

        query.exec("select id, name, age from licheng");
        while (query.next())
        {

           //qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        }

        query.exec(QObject::tr("drop licheng"));

/*******************************************************************/

}

//小时计 槽函数
void Widget::xiaoshiji()//小时计
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");


   //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("jy.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
   }
   QSqlQuery query;
   #if 0
   bool ok = query.exec("create table xsj(id INTEGER,name varchar,age INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }
   #endif

   query.exec("select id, name, age from xsj");
   while (query.next())
   {

     // qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
     //xiaoshiJi_m = query.value(2).toInt();

       xiaoshiJi_m = query.value(2).toLongLong();

   }

   //if (fadongzhuansu>350)//
   if (fadongzhuansu==0)//
   {
        xiaoshiJi_m++;
   }
    xiaoshiJi_h = (xiaoshiJi_m/3600)*1000 + ((xiaoshiJi_m%3600)*1000)/3600;
    xiaoshiJi_h /= 1000;
    ui->label_7->setText(QString::number(xiaoshiJi_h,'f',1));

          //query.prepare("INSERT INTO xsj (id, name, age) VALUES (:id, :name, :age)");

          query.prepare("update xsj set age = :age where id = :id");

          //query.prepare(update_sql);
          query.bindValue(":id",1);
         // query.bindValue(":name", QObject::tr("小时计"));
          query.bindValue(":age", xiaoshiJi_m);
          query.exec();

        query.exec("select id, name, age from xsj");
        while (query.next())
        {

           //qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        }

        query.exec(QObject::tr("drop xsj"));

/*******************************************************************/

}

void Widget::shanhua()//闪烁和平滑转动
{


#if 0
    if(flagadd)
    {
        numtmp++;
        if(numtmp>132)
        {
            flagadd = 0;
        }
    }
    else
    {
        numtmp--;
        if(numtmp==0)
        {
            flagadd = 1;
        }
    }

#endif

    //nu2 = (cantest.FDJ_speed/100);
    if(nu1 < nu2)//cantest.FDJ_speed
    {
        nu1++;
        //qDebug()<<"++"<<cantest.FDJ_speed<<endl;
    }
    else if(nu1 > nu2)//cantest.FDJ_speed
    {
        nu1--;

        //qDebug()<<"------"<<cantest.FDJ_speed<<endl;
    }

    //nu2 = (cantest.HourSpeed);///100
    if(nu3 < nu4)//cantest.FDJ_speed
    {
        nu3++;
        //qDebug()<<"3++"<<cantest.FDJ_speed<<endl;
    }
    else if(nu3 > nu4)//cantest.FDJ_speed
    {
        nu3--;

        //qDebug()<<"4------"<<cantest.FDJ_speed<<endl;
    }



//    if(enableflag)
//    {

    if(flagaddnum)
    {
//        cantest.flagRight = 1;
//        cantest.flagLeft = 1;

        //cantest.flagSW = 1;
        //cantest.flagJY = 1;
        //cantest.flagyouliangdi =1;

        //闪烁控制

//        if(cantest.VolSW == 8)//水温
//        {
//            shanshuoSW = 1;
//        }
//        if(cantest.VolJYYL < 0.8)//机油
//        {
//            shanshuoJYYL = 1;
//        }
//        if(cantest.VolYL <= 1)//油量
//        {
//            shanshuoYL = 1;
//        }

        if(tuoliguntong<ruby[0])//轴流滚筒转速
        {
            if (tuoliguntong != 0)
            {
                shanshuozlzs = 1;//轴流滚筒转速
            }

        }

        if(futuoqi<ruby[1])//复脱器转速
        {
            if (futuoqi != 0)
            {
                shanshuoftqzs = 1;//复托器转速
            }

        }

        if(shengyunqi<ruby[2])//升运器堵塞转速
        {
            if (shengyunqi != 0)
            {
                 shanshuosyqzs = 1;//升运器转速
            }

        }


        flagnum++;
        if(flagnum>30)
        {
            flagaddnum = 0;
        }
    }
    else
    {
        shanshuoSW = 0;//水温
        shanshuoJYYL = 0;//机油
        shanshuoYL = 0;//油量

        flagnum--;
        if(flagnum==0)
        {
            flagaddnum = 1;
        }
    }
//  }
//    else
//    {
//        flagRight = 0;

//        flagLeft = 0;

//        flagSW = 0;
//        flagJY = 0;
//        flagyouliangdi =0;

//    }
}

void Widget::on_pushButton_3_clicked()//蜂鸣器
{
    /**************************************************************************************************************/
    //
    //控件显示
    //显示 蜂鸣器

    flagbeep ^= 1;

    if (flagbeep)// flagbeep = 0； 喇叭未摁下
    {
        ui->pushButton_3->setStyleSheet("QPushButton{border-image:url(./img/a1.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
    }
    else //显示 喇叭摁下
    {
        ui->pushButton_3->setStyleSheet("QPushButton{border-image:url(./img/labano.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
    }

    /****************************************************************************************************************/
}

void Widget::on_pushButton_4_clicked()//米计清零
{
    mijisum = 0;
    //clearflag = 0;
    clearflag ^= 1;
    clearSave = clearflag;
    qDebug()<<"clearflag ----- = "<<clearflag<<endl;
    //ui->label->setText("007");

    if (clearflag)// flagbeep = 0； 喇叭未摁下
    {
        ui->pushButton_4->setStyleSheet("QPushButton{border-image:url(./img/miji.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
    }
    else //显示 喇叭摁下
    {
        ui->pushButton_4->setStyleSheet("QPushButton{border-image:url(./img/mijibai.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
    }
}
