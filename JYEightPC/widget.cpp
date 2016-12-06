#include "widget.h"
#include "ui_widget.h"
#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QtSql>
#include<QTextCodec>
#include<QMouseEvent>

/******************************************************************/
uchar DC;
uchar flagStatus;
uchar ok;



double licheng;
double lichengsum;
long long MIJI = 1001;
/******************************************************************/

//2016.11.2 开始构建程序框架
//
//行走界面
//

/********************************************************************************************************************/
//定义时间变量用于各界面传递
//2016.7.11

QString  Datesetup;


long long xiaoshiJi_m;//分钟
double xiaoshiJi_h;//小时
float fadongzhuansu; //发动机转速


uchar flagadd = 1;//转速方向标志位
uchar flagaddnum = 1;//转速方向标志位
uchar flagnum;
uchar enableflag = 0;

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



uchar flagMijLic = 0;//米计里程切换标志
uchar flagbeep = 0;//蜂鸣器状态标志

/**************************/
//
uchar flagRight = 1;
uchar flagLeft = 1;


uchar flagFFF = 1;//前进档
uchar flagRRR = 0;//倒档
uchar flagNNN = 0;//空档

uchar flagwaterinoril = 1;//油中有水


uchar flagzlgtzs = 0;
uchar flagftqzs =0;
uchar flagsyqzs = 0;

/***************************/
unsigned char  countBuff = 0;

uchar fadongjiguzhang =1; //发动机故障
//unsigned char flagLeft = 0;  //左转
unsigned char countLeft_W = 0; //左转

unsigned char flagBattery = 1;//电瓶指示灯

unsigned char flagWidthlamp = 1; //示宽灯

unsigned char  flagYG = 1; //远光灯

unsigned char  flagSW  = 1; //水温

unsigned char  flagJG = 1; //近光灯

unsigned char  flagJY = 1; //机油


unsigned char  flagLCM = 1; //粮仓满

unsigned char  flagLCM_seven = 0;//粮仓满70%

unsigned char   flagFDJYR = 1; //发动机预热

unsigned char   flagGL = 1; //过滤

unsigned char   flagYL = 1; //油量

unsigned char  flagYeyayouwen = 1;//液压油温

unsigned char    flagECU = 1;//ecu

unsigned char    flagPark = 1;//停车

unsigned char   flagFDJGZ = 1; //发动机故障

//unsigned char   flagRight = 0; //右转

//unsigned char  flagyouxiangman = 0; //油量满
unsigned char  flagyouliangdi  = 1; // 油量低
/********************************************************************************************************************/


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

       //setWindowTitle(tr("Haovel"));  //设置窗体名称
       resize(800,600);

       QTimer *timer = new QTimer(this);   //声明一个定时器
       timer_xiaoshiji = new QTimer(); //声明小时计定时器
       timer_shanhua = new QTimer();
       timer_Licheng = new QTimer();

       connect(timer_Licheng,SIGNAL(timeout()),this,SLOT(Licheng()));//小时计

       connect(timer_xiaoshiji,SIGNAL(timeout()),this,SLOT(xiaoshiji()));//小时计
       connect(timer, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新

       connect(timer_shanhua, SIGNAL(timeout()), this, SLOT(shanhua()));  //连接信号槽，定时器超时触发窗体更新
       //connect(testtimergzm, SIGNAL(timeout()), this, SLOT(gzmslottest()));  //连接信号槽，定时器超时触发窗体更新

       timer->start(30);   //启动定时器
       timer_xiaoshiji->start(1000);

       timer_Licheng->start(1000);

       timer_shanhua->start(30);

       //解析现象，当去掉 setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); 这一句，在开发板子上能显示上方图标，但是不闪烁，
       //不注释则可以在板子上闪烁。
       //setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

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
        pix.load("./img2/xingzou.bmp");
        painter.drawPixmap(0,0,800,600,pix);

#if 1
        //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

        painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
        //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

        painter.translate(405, 284);//重新定位坐标起始点，把坐标原点放到窗体的中央
        //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

        //下面两个数组用来定义表针的两个顶点，以便后面的填充
        static const QPoint hourHand[4] = {
            QPoint(8, 0),
            QPoint(-8,0),
            QPoint(-1.5, -160),
            QPoint(1.5, -160)
        };
        static const QPoint minuteHand[4] = {
            QPoint(4, 0),
            QPoint(-4, 0),
            QPoint(-1, -90),
            QPoint(1, -90)
        };

        //km r/mini

        painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
        painter.setBrush(Qt::red);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.save();
        //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
        painter.rotate(-120);
        //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
        //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
        //painter.rotate(4.0 );//*shisu

        painter.rotate(2.9*nu1);
        painter.drawConvexPolygon(hourHand, 4);  //填充分针部分
        painter.restore();

        /***********************************************/
        //2016.6.25   画白圈
        painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
        painter.save();
        painter.drawEllipse(QPoint(0,0),25,25);
        painter.restore();

        //画白圈
        /***********************************************/

        painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
        painter.save();
        painter.drawEllipse(QPoint(0,0),20,20);
        painter.restore();


        //km/h
        painter.translate(0,148);//重新定位坐标起始点，把坐标原点放到窗体的中央
        //painter.scale(side / 400.0, side / 300.0);

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.save();

        //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
        painter.rotate(-125);
        painter.rotate(2.9*nu3);
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

/****************************************************************************************************************************************************/
//倒车控制逻辑
#if 1
        if((DC==1)&&(flagStatus == 0))
        {

            //DC = 0;
            //emit sendcamersignal();
             ok = true;

             QMouseEvent* press=new QMouseEvent(QEvent::MouseButtonPress,QPoint(2,2), Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
             QApplication::postEvent(ui->pushButton,press);
             QMouseEvent* release=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(2,2),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
             QApplication::postEvent(ui->pushButton,release);

             flagStatus = 1;

        }

#endif

/****************************************************************************************************************************************************/


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

                   QPainter paintShanshuo_W(this);
                   QPixmap pixShanshuo_W;

              //if(can_retern != 0)
              {
                  //qDebug()<<"return != 0"<<endl;

                   if(tuoliguntong<ruby[0])//轴流滚筒转速
                   {
                       if (tuoliguntong != 0)
                       {
                           pixShanshuo_W.load("./img2/icon/37.png");//11.   jpgenglish/shanshuo/
                           paintShanshuo_W.drawPixmap(631,126,117,24,pixShanshuo_W);
                       }

                       // qDebug()<<"bpj"<<endl;
                   }

                   if(futuoqi<ruby[1])//复脱器转速
                   {
                       if (futuoqi != 0)
                       {
                           pixShanshuo_W.load("./img2/icon/38.png");//11.jpg
                           paintShanshuo_W.drawPixmap(631,215,99,24,pixShanshuo_W);
                       }

                       //qDebug()<<"syqzs"<<endl;
                   }

                   if(shengyunqi<ruby[2])//升运器堵塞转速
                   {
                       if (shengyunqi != 0)
                       {
                           pixShanshuo_W.load("./img2/icon/39.png");//11.jpg
                           paintShanshuo_W.drawPixmap(631,305,101,24,pixShanshuo_W);
                       }

                       //qDebug()<<"syqzs"<<endl;
                   }

              }//endof if(can_return != 0)

 #if 1

            if(flagSW)//水温 0~120度  95度以上报警。
            {
                 pixShanshuo_W.load("./img2/icon/13.png");//07.jpg
                 paintShanshuo_W.drawPixmap(88,-6,38,41,pixShanshuo_W);//正上方位置显示的图标
            }

            if(flagJY) //机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。
            {
                 pixShanshuo_W.load("./img2/icon/90.png");//08.jpg
                 paintShanshuo_W.drawPixmap(340,0,45,35,pixShanshuo_W);//正上方位置显示的图标
                 //paintShanshuo_W.drawPixmap(20,180,43,43,pixShanshuo_W);//左边显示的图标
            }


            if (flagyouliangdi)//油量
            {
                pixShanshuo_W.load("./img2/icon/23.png");//14.jpg
                paintShanshuo_W.drawPixmap(246,0,43,34,pixShanshuo_W);

            }

     //闪烁 转速0

#if 1
     if(flagzlgtzs)//轴流滚筒
     {
         pixShanshuo_W.load("./img2/icon/37.png");//11.   jpgenglish/shanshuo/
         paintShanshuo_W.drawPixmap(631,126,117,24,pixShanshuo_W);
     }

     if(flagftqzs)//复脱器
     {
         pixShanshuo_W.load("./img2/icon/38.png");//11.jpg
         paintShanshuo_W.drawPixmap(631,215,99,24,pixShanshuo_W);
     }

     if(flagsyqzs)//升运器
     {
         pixShanshuo_W.load("./img2/icon/39.png");//11.jpg
         paintShanshuo_W.drawPixmap(631,305,101,24,pixShanshuo_W);
     }

#endif
    //不用闪烁



    if(flagFFF)//前进档位
    {
        pixShanshuo_W.load("./img2/icon/59.png");//14.jpg 
        paintShanshuo_W.drawPixmap(710,50,50,50,pixShanshuo_W);
        //paintShanshuo_W.drawPixmap(285,0,50,50,pixShanshuo_W);
    }
    if(flagRRR)//倒档
    {
        pixShanshuo_W.load("./img2/icon/61.png");//14.jpg
        paintShanshuo_W.drawPixmap(710,50,50,50,pixShanshuo_W);
        //paintShanshuo_W.drawPixmap(335,0,50,50,pixShanshuo_W);
    }
    if(flagNNN)//空档
    {
        pixShanshuo_W.load("./img2/icon/60.png");//14.jpg
        paintShanshuo_W.drawPixmap(710,50,50,50,pixShanshuo_W);
        //paintShanshuo_W.drawPixmap(385,0,50,50,pixShanshuo_W);
    }


    if(flagwaterinoril)//油中有水指示灯
    {
        pixShanshuo_W.load("./img2/icon/9.png");//14.jpg
        paintShanshuo_W.drawPixmap(285,0,50,50,pixShanshuo_W);
    }

    if(flagLeft)//左转灯闪烁
    {
        pixShanshuo_W.load("./img2/icon/27.png");//14.jpg
        paintShanshuo_W.drawPixmap(0,0,43,34,pixShanshuo_W);
    }
    if(flagBattery)//电瓶指示灯  flagBattery
    {
        pixShanshuo_W.load("./img2/icon/21.png");//14.jpg
        paintShanshuo_W.drawPixmap(44,0,43,34,pixShanshuo_W);//正上方图片显示
        //paintShanshuo_W.drawPixmap(20,335,43,34,pixShanshuo_W);//左边图片显示
    }
    if(flagGL)//空 滤
    {
        pixShanshuo_W.load("./img2/icon/20.png");//04.jpg
        paintShanshuo_W.drawPixmap(390,0,43,43,pixShanshuo_W);
    }
    if(flagLCM)//flagLCM = 1; //粮仓满
    {
        pixShanshuo_W.load("./img2/icon/7.png");//13.jpg
        paintShanshuo_W.drawPixmap(439,0,43,43,pixShanshuo_W);
    }

//            if(flagLCM_seven)//flagLCM = 1; //粮仓满7000000000
//            {
//                pixShanshuo_W.load("./imagezl/66/70.png");//13.jpg
//                paintShanshuo_W.drawPixmap(542,15,42,41,pixShanshuo_W);
//            }

    if(flagFDJYR)//flagFDJYR = 1; //发动机预热
    {
        pixShanshuo_W.load("./img2/icon/17.png");//15.jpg
        paintShanshuo_W.drawPixmap(589,-6,43,43,pixShanshuo_W);
    }

    if(flagYeyayouwen)//液压油温
    {
         pixShanshuo_W.load("./img2/icon/16.png");//10.jpg
         paintShanshuo_W.drawPixmap(539,0,43,43,pixShanshuo_W);//上边图标
         //paintShanshuo_W.drawPixmap(423,216,49,38,pixShanshuo_W);//左边图标
    }

    if(flagECU)//ecu
    {
        pixShanshuo_W.load("./img2/icon/28.png");//03.jpg
        paintShanshuo_W.drawPixmap(490,0,43,32,pixShanshuo_W);
    }

    if(fadongjiguzhang)//发动机故障
    {
        pixShanshuo_W.load("./img2/icon/32.png");//16.jpg
        paintShanshuo_W.drawPixmap(690,-2,43,34,pixShanshuo_W);
    }


    if(flagWidthlamp)//示宽灯
    {
        pixShanshuo_W.load("./img2/icon/25.png");//06.jpg
        paintShanshuo_W.drawPixmap(126,0,43,34,pixShanshuo_W);
    }

    if(flagJG)//近光灯flagJG
    {
        pixShanshuo_W.load("./img2/icon/15.png");//12.jpg
        paintShanshuo_W.drawPixmap(169,-6,38,41,pixShanshuo_W);
    }

    if(flagYG)//远光灯
    {
        pixShanshuo_W.load("./img2/icon/24.png");//05.jpg
        paintShanshuo_W.drawPixmap(207,0,43,34,pixShanshuo_W);
    }

    if(flagPark)//停车 刹车
    {
        pixShanshuo_W.load("./img2/icon/18.png");//11.jpg
        paintShanshuo_W.drawPixmap(639,0,43,34,pixShanshuo_W);
    }

    if(flagRight)//右转
    {
        pixShanshuo_W.load("./img2/icon/26.png");//14.jpg
        paintShanshuo_W.drawPixmap(758,0,43,34,pixShanshuo_W);
    }

#endif


    /**************************************************************************************************************/
    //
    //
    //控件显示
    //显示时间 。2016.7.12
    QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
    QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");

    ui->lcdNumber->display(dateStr1);//dateStr1
    ui->lcdNumber_2->display(timeStr1);
    /**************************************************************************************************************/
    //
    //控件显示
    //显示 米计里程

    if (flagMijLic)// flagMijLic = 0； 显示米计
    {
        //ui->pushButton_6->setStyleSheet("QPushButton{border-image:url(./img2/icon/36.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
        //ui->pushButton_6->setStyleSheet("border-image:url(./img2/icon/36.png);");

    }
    else //显示 里程
    {
        //ui->pushButton_6->setStyleSheet("QPushButton{border-image:url(./img2/icon/35.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
        //ui->pushButton_6->setStyleSheet("border-image:url(./img2/icon/35.png);");

    }

    /**************************************************************************************************************/
    //
    //控件显示
    //显示 蜂鸣器

    if (flagbeep)// flagbeep = 0； 喇叭未摁下
    {
        //ui->pushButton_3->setStyleSheet("QPushButton{border-image:url(./img2/icon/6.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
    }
    else //显示 喇叭摁下
    {
        //ui->pushButton_3->setStyleSheet("QPushButton{border-image:url(./img2/beeplog.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
    }

    /****************************************************************************************************************/
    //控件显示
    //显示 油量，机油压力，水温，电池，FMI,SPN，轴流滚筒，复脱器，升运器

//ui->label->setText();//油量
//ui->label_2->setText(QString::number(jiyouyali,'f',2)); //机油压力
//ui->label_3->setText(QString::number());//水温
//ui->label_4->setText(QString::number());//电池
//ui->label_5->setText(QString::number());//FMI
//ui->label_6->setText(QString::number());//SPN


//ui->label_8->setText(QString::number());//轴流滚筒
//ui->label_9->setText(QString::number());//复脱器
//ui->label_10->setText(QString::number());//升运器

/****************************************************************************************************************/

}

void Widget::on_pushButton_clicked()//进入监控界面
{

#if 1
    this->close();
    workobj.show();
    workobj.exec();
    this->show();
#endif

//    Work *pWorkDlg = new Work();
//    pWorkDlg->setAttribute(Qt::WA_DeleteOnClose);
//    pWorkDlg->show();
}

void Widget::on_pushButton_2_clicked()//进入设置界面
{
    this->close();
    setobjwidget.show();
    setobjwidget.exec();
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

   query.exec("select id, name, age from licheng");
   while (query.next())
   {

     // qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
     //xiaoshiJi_m = query.value(2).toInt();

       lichengsum = query.value(2).toLongLong();

   }


    licheng = (MIJI/1000)*1000+(MIJI%1000);
    licheng /= 1000;
    lichengsum += licheng;
    ui->label_12->setText(QString::number(lichengsum,'f',1));

        //query.prepare("INSERT INTO licheng (id, name, age) VALUES (:id, :name, :age)");

        query.prepare("update licheng set age = :age where id = :id");

          //query.prepare(update_sql);
          query.bindValue(":id",1);
          //query.bindValue(":name", QObject::tr("里程"));
          query.bindValue(":age", lichengsum);
          query.exec();

        query.exec("select id, name, age from licheng");
        while (query.next())
        {

           qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
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
    ui->label_7->setText(QString::number(xiaoshiJi_h,'f',2));

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
        qDebug()<<"flagflagflag add  =  "<<numtmp<<endl;
        if(numtmp>132)
        {
            flagadd = 0;

        }
    }
    else
    {
        numtmp--;
         qDebug()<<".............&&&&&&&&&&&&&&&.......  = "<<numtmp<<endl;
        if(numtmp==0)
        {
            flagadd = 1;
        }
    }
#endif

    if(nu3 < nu4)
    {
        nu3++;
        qDebug()<<"3++"<<endl;
    }
    else if(nu3 >nu2 )
    {
        nu3--;

        qDebug()<<"4------"<<endl;
    }

    //////////////////////////////////////
    if(nu1 < nu2)
    {
        nu1++;
        qDebug()<<"++"<<endl;
    }
    else if(nu1 >nu2 )
    {
        nu1--;

        qDebug()<<"------"<<endl;
    }



    if(enableflag)
    {

    if(flagaddnum)
    {
        flagRight = 1;
        flagLeft = 1;

        flagSW = 1;
        flagJY = 1;
        flagyouliangdi =1;

        /**************************************/
         flagzlgtzs = 1;
         flagftqzs =1;
         flagsyqzs = 1;
        /**************************************/


        flagnum++;
        if(flagnum>30)
        {
            flagaddnum = 0;
        }
    }
    else
    {
        flagRight = 0;
        flagLeft = 0;

        flagSW = 0;
        flagJY = 0;
        flagyouliangdi =0;

        /**************************************/
         flagzlgtzs = 0;
         flagftqzs =0;
         flagsyqzs = 0;
        /**************************************/


        flagnum--;
        if(flagnum==0)
        {
            flagaddnum = 1;
        }
    }
  }
    else
    {
        flagRight = 0;

        flagLeft = 0;

        flagSW = 0;
        flagJY = 0;
        flagyouliangdi =0;

        /**************************************/
         flagzlgtzs = 0;
         flagftqzs =0;
         flagsyqzs = 0;
        /**************************************/

    }




}

void Widget::on_pushButton_4_clicked()
{
    enableflag = 0;
#if 1
    QString wtmp = ui->lineEdit->text();
    nu2 = wtmp.toInt();

    nu4 = wtmp.toInt();

    //nu1 = nu2;
    qDebug()<<"nu2 = "<<nu2<<endl;
#endif
}

void Widget::on_pushButton_5_clicked()
{
    enableflag = 1;
}

void Widget::on_pushButton_6_clicked()//米计里程切换
{
    flagMijLic ^= 1;
    if (flagMijLic)// flagMijLic = 0； 显示米计
    {
        ui->label_12->setText("miji");
    }
    else //显示 里程
    {
        ui->label_12->setText("licheng");
    }

}

void Widget::on_pushButton_3_clicked()//蜂鸣器
{
    flagbeep ^= 1;
}
