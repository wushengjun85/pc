#include "work.h"
#include "ui_work.h"

#include <QDebug>

#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QString>

#include<QtSql>
#include<QTextCodec>
#include<QMouseEvent>

#include"hwlib/camera_interface.h"

/******************************************************************/
extern uchar DC;
extern uchar flagStatus;
extern uchar ok;
/******************************************************************/
extern uchar flagMijLic;//米计里程切换标志
extern uchar flagbeep;//蜂鸣器状态标志

extern double xiaoshiJi_h;//小时

extern uint matchine[3]; //保存风机，复托器，升运器，等转速 的百分比
extern int ruby[3];

//频率量
extern ushort  shengyunqi ;    //升运器
extern ushort  futuoqi;       //复脱器
extern ushort  zhouliuguntong;//轴流滚筒
extern ushort tuoliguntong;//脱粒滚筒转速

/**************************/
//
extern uchar flagRight;
extern uchar flagLeft;


extern uchar flagFFF;
extern uchar flagRRR;
extern uchar flagNNN;

extern uchar flagwaterinoril;//油中有水


extern uchar flagzlgtzs;
extern uchar flagftqzs;
extern uchar flagsyqzs;

/***************************/
extern unsigned char  countBuff;

extern uchar fadongjiguzhang ;
//unsigned char flagLeft = 0;  //左转
extern unsigned char countLeft_W ; //左转

extern unsigned char flagBattery;//电瓶指示灯

extern unsigned char flagWidthlamp; //示宽灯

extern unsigned char  flagYG; //远光灯

extern unsigned char  flagSW ; //水温

extern unsigned char  flagJG; //近光灯

extern unsigned char  flagJY; //机油


extern unsigned char  flagLCM ; //粮仓满

extern unsigned char  flagLCM_seven ;//粮仓满70%

extern unsigned char   flagFDJYR ; //发动机预热

extern unsigned char   flagGL ; //过滤

extern unsigned char   flagYL ; //油量

extern unsigned char  flagYeyayouwen ;//液压油温

extern unsigned char    flagECU;//ecu

extern unsigned char    flagPark;//停车

extern unsigned char   flagFDJGZ; //发动机故障

//unsigned char   flagRight = 0; //右转

//unsigned char  flagyouxiangman = 0; //油量满
extern unsigned char  flagyouliangdi; // 油量低
/********************************************************************************************************************/



Work::Work(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Work)
{
    ui->setupUi(this);

    QTimer *tmwork = new QTimer(this);
    connect(tmwork, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
    tmwork->start(1000);


/***************************************************************************************************************/
    //摄像头 半初始化
    //申请提取帧缓冲区空间
    //pp = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
    p = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
    //pp1 = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));
    p1 = (unsigned char *)malloc(IMG_WIDTH * IMG_HEIGTH/*QWidget::width()*QWidget::height()*/* 3 * sizeof(char));

    frame = new QImage(p,IMG_WIDTH,IMG_HEIGTH,QImage::Format_RGB888);//定义摄像头抓取帧句柄-QImage类型
    frame1 = new QImage(p1,IMG_WIDTH,IMG_HEIGTH,QImage::Format_RGB888);//定义摄像头抓取帧句柄-QImage类型
/***************************************************************************************************************/

//    timercamera = new QTimer(this);
//    connect(timercamera,SIGNAL(timeout()),this,SLOT(cameraslot1()));//链接定时器到时间后执行的槽函数
//    timercamera2 = new QTimer(this);
//    connect(timercamera2,SIGNAL(timeout()),this,SLOT(cameraslot2()));//链接定时器到时间后执行的槽函数

    //HWE_AllVideoDev_init();
}

Work::~Work()
{
    delete ui;
}

void Work::paintEvent(QPaintEvent *event)
{
    QPainter dp(this);
    QPixmap dppix;
    dppix.load("./img2/work.bmp");
    dp.drawPixmap(0,0,800,600,dppix);

/**************************************************************************************************************/
//倒车逻辑控制

    if(DC == 1) //进入倒车界面
    {
        //打开倒车摄像头
//        timercamera->start(1);
//        timercamera2->stop();

//        HWE_Reverse_Start();
    }
    else if((DC == 0)&&(flagStatus == 1)) //返回主界面
    {
        flagStatus = 0;

        QMouseEvent* pressdialog=new QMouseEvent(QEvent::MouseButtonPress,QPoint(2,2), Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
        QApplication::postEvent(ui->ptn_back,pressdialog);
        QMouseEvent* releasedialog=new QMouseEvent(QEvent::MouseButtonRelease,QPoint(2,2),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
        QApplication::postEvent(ui->ptn_back,releasedialog);
    }
    else if((DC == 0)&&(flagStatus == 0))//还继续留在监控界面  打开监控摄像头
    {
        //打开监控摄像头
//        timercamera2->start(1);
//        timercamera->start(1);
//        HWE_Monitor_Start();
    }




/**************************************************************************************************************/



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

#if 0
        i = 0;
        for (i = 0; i < 7; i++)
            {
                qDebug()<<"matchine % bi "<<matchine[i]<<endl;
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
                paintShanshuo_W.drawPixmap(435,0,45,35,pixShanshuo_W);//正上方位置显示的图标
                //paintShanshuo_W.drawPixmap(20,180,43,43,pixShanshuo_W);//左边显示的图标
           }


           if (flagyouliangdi)//油量
           {
               pixShanshuo_W.load("./img2/icon/23.png");//14.jpg
               paintShanshuo_W.drawPixmap(246,0,43,34,pixShanshuo_W);

           }

    //闪烁 转速


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
   QString timeStr11= QTime::currentTime().toString();     //绘制当前的时间
   QString dateStr11 = QDate::currentDate().toString("yyyy-MM-dd");

   ui->lcdNumber->display(dateStr11);//dateStr1
   ui->lcdNumber_2->display(timeStr11);
   /**************************************************************************************************************/
   //
   //控件显示
   //显示 米计里程

   if (flagMijLic)// flagMijLic = 0； 显示米计
   {
       ui->pushButton_4->setStyleSheet("QPushButton{border-image:url(./img2/icon/36.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
   }
   else //显示 里程
   {
       ui->pushButton_4->setStyleSheet("QPushButton{border-image:url(./img2/icon/35.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
   }

   /**************************************************************************************************************/
   //
   //控件显示
   //显示 蜂鸣器

   if (flagbeep)// flagbeep = 0； 喇叭未摁下
   {
       ui->pushButton_3->setStyleSheet("QPushButton{border-image:url(./img2/icon/6.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
   }
   else //显示 喇叭摁下
   {
       ui->pushButton_3->setStyleSheet("QPushButton{border-image:url(./img2/beeplog.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
   }


   /****************************************************************************************************************/
   //控件显示
   //显示 油量，机油压力，水温，电池，FMI,SPN, 小时计，轴流滚筒，复脱器，升运器
//   ui->label->setText();//油量
//   ui->label_2->setText(QString::number(jiyouyali,'f',2)); //机油压力
//   ui->label_3->setText(QString::number());//水温
//   ui->label_4->setText(QString::number());//电池
//   ui->label_5->setText(QString::number());//FMI
//   ui->label_6->setText(QString::number());//SPN

   ui->label_7->setText(QString::number(xiaoshiJi_h,'f',2));//小时计


//   ui->label_8->setText(QString::number());//轴流滚筒
//   ui->label_9->setText(QString::number());//复脱器
//   ui->label_10->setText(QString::number());//升运器

//    ui->label_11->setText(QString::number());// r/min
//    ui->label_13->setText(QString::number());// km/h
   /****************************************************************************************************************/

}


void Work::on_pushButton_2_clicked()//进入设置界面
{
    this->close();
    setobjwork.show();
    setobjwork.exec();
    this->show();
}

void Work::on_pushButton_4_clicked()//米计里程切换
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

void Work::on_pushButton_3_clicked()//蜂鸣器
{
    flagbeep ^= 1;
}

void Work::on_ptn_back_clicked()//返回行走界面
{
//    timercamera->stop();
//    timercamera2->stop();

    //HWE_AllVideoDev_Exit();

    this->close();

}

void Work::cameraslot1()
{
//    uint len = 0;
//    HWE_ReleaseVideoData(CAMERA_AV_1);
//    HWE_GetVideoData(CAMERA_AV_1,&p,&len,V4L2_PIX_FMT_CSC_RGB_CUSTOM);

//    if(len > 0)
//    {
//           frame->loadFromData((uchar *)p,/*len*/IMG_WIDTH * IMG_HEIGTH * 3 * sizeof(char));//载入转换后的RGB数据到帧句柄
//           ui->label_14->setPixmap(QPixmap::fromImage(*frame));
//           ui->label_14->setScaledContents(true);
//    }
}

void Work::cameraslot2()
{

//    uint len = 0;
//    HWE_ReleaseVideoData(CAMERA_AV_2);
//    HWE_GetVideoData(CAMERA_AV_2,&p,&len,V4L2_PIX_FMT_CSC_RGB_CUSTOM);

//    if (len > 0)
//    {
//        frame1->loadFromData((uchar *)p1,IMG_WIDTH * IMG_HEIGTH * 3 * sizeof(char));//载入转换后的RGB数据到帧句柄
//        //ui->label_14->setPixmap(QPixmap::fromImage(*frame1));
//        //ui->label_14->setScaledContents(true);
//    }
}
