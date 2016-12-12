#include "setup.h"
#include "ui_setup.h"
#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QPainter>
#include<QtSql>
#include<QTextCodec>


bool timeSetOK = false; //时间设置完毕标志
QString DateTimeSetup;


uint bjd[6] = {0};
//uint kaku_tlgt = 88;
//uint kaku_syq = 77;
bool flag_bjd = true;


bool flagjiajia = true;
int startflag = 0;

int  tuoliguntong_zs = 80; //脱离滚筒转速  //轴流滚筒
int fenliguntong_zs = 80;//分离滚筒
int fj_zs = 80;//风机
int ftq_zs = 80;//复脱器
int syq_zs = 80; //升运器
int qsq_zs = 80; //切碎器
int gq_zs = 80;//过桥转速


int muchanliang = 80;//亩产量
int getaikuandu = 80;//割台宽度

int kaku_muchanliang;
int kaku_getaikuandu;

int ka_muchanliang;
int ka_getaikuandu;



int kaku_tlgt;//脱离滚筒转速   //轴流滚筒
int kaku_flgt;//分离滚筒
int kaku_fj;//风机
int kaku_ftq;//复脱器
int kaku_syq;//升运器

int kaku_gqzs;//过桥转速


int ka_tlgt;//脱离滚筒转速
int ka_flgt;//分离滚筒
int ka_fj;//风机
int ka_ftq;//复脱器
int ka_syq;//升运器
int ka_qsq;//切碎器
int ka_gqzs;//过桥转速








Setup::Setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setup)
{
    ui->setupUi(this);
    //解析现象，当去掉 setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); 这一句，在开发板子上能显示上方图标，但是不闪烁，
    //不注释则可以在板子上闪烁。
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮

    QTimer *tm = new QTimer(this);
    connect(tm, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
    tm->start(1000);
}

Setup::~Setup()
{
    delete ui;
}

void Setup::paintEvent(QPaintEvent *)
{
    QPainter paintersetup(this);
    QPixmap pixsetup;
    pixsetup.load("./img/setup.bmp");
    paintersetup.drawPixmap(0,0,1024,600,pixsetup);


    /**************************************************************************************************************/
    //显示时间 。2016.7.12
//        QString timeStr22= QTime::currentTime().toString();     //绘制当前的时间
//        QString dateStr22 = QDate::currentDate().toString("yyyy-MM-dd");

//        ui->label_4->setText(dateStr22);//dateStr1
//        ui->label_5->setText(timeStr22);
    /**************************************************************************************************************/

        //时间设置
    #if 1
         /*设置系统时间*/
         if(timeSetOK == true)
         {
         QString str1 = """";
         str1 += "date -s ";
         str1 += DateTimeSetup.left(10);
         str1 += """";

         //system("clock -w");
         //system("hwclock --hctosys");
         system(str1.toLatin1().data());

         //时间
         QString str2 = """";
         str2 += "date -s ";
         str2 += DateTimeSetup.mid(11,9);
         str2 += """";
         system(str2.toLatin1().data());

          system("hwclock -w");

        }
    #endif


    #if 1

         /***********************************************************************************/
         //读取报警点(报警点 == 一键设定值*打滑率)
         /***********************************************************************************/
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
     //   bool ok = query.exec("CREATE TABLE IF NOT EXISTS  myjy10 (id INTEGER PRIMARY KEY AUTOINCREMENT,"
     //                                      "name VARCHAR(20) NOT NULL,"
     //                                      "age INTEGER NULL)");
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

                //qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
                 //qDebug()<<query.value(2).toInt();

                 bjd[i++] = query.value(2).toInt();

                 //qDebug()<<"opqrst"<<endl;
             }

             ka_tlgt = bjd[0];
             ka_ftq  = bjd[1];
             ka_syq  = bjd[2];

             ka_muchanliang = bjd[3];
             ka_getaikuandu = bjd[4];

             startflag = bjd[5];

             if (flag_bjd)
             {
                 ui->label->setText(QString::number(bjd[0],10));
                 ui->label_2->setText(QString::number(bjd[1],10));
                 ui->label_3->setText(QString::number(bjd[2],10));

                ui->label_4->setText(QString::number(bjd[3],10));
                ui->label_5->setText(QString::number(bjd[4],10));

                 kaku_tlgt = bjd[0];
                 kaku_ftq = bjd[1];
                 kaku_syq = bjd[2];

                 kaku_muchanliang = bjd[3];
                 kaku_getaikuandu = bjd[4];



             }
             else
             {

                  ui->label->setText(QString::number(kaku_tlgt,10));//(ui->label->text().toInt()
                  ui->label_2->setText(QString::number(kaku_ftq,10));//kaku_qsq

                  ui->label_3->setText(QString::number(kaku_syq,10));//kaku_qsq

                  ui->label_4->setText(QString::number(kaku_muchanliang,10));
                  ui->label_5->setText(QString::number(kaku_getaikuandu,10));
             }

             query.exec(QObject::tr("drop jy8c"));
    #endif
}

void Setup::on_pushButton_clicked()
{
    //ui->pushButton_16->setStyleSheet("QPushButton{border-image:url(./imagejy/yjsd.png);background-repeat: repeat-xy;background-position: center;background-attachment: fixed;background-clip: padding}");

       //system("rm my5.db");
       QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示

       QSqlDatabase db;
       if(QSqlDatabase::contains("qt_sql_default_connection"))
         db = QSqlDatabase::database("qt_sql_default_connection");
       else
         db = QSqlDatabase::addDatabase("QSQLITE");

   //   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
      db.setDatabaseName("jy.db");
      if (!db.open())
      {
          qDebug()<<"open database failed ---"<<db.lastError().text()<<"/n";
      }
      QSqlQuery query;


   #if 0 //创建数据库
      bool ok = query.exec("create table jy8c(id INTEGER,name varchar,age INTEGER)");
      if (ok)
      {
          qDebug()<<"ceate table partition success"<<endl;
      }
      else
      {
          qDebug()<<"ceate table partition failed"<<endl;
      }
   #endif
             //query.prepare("INSERT INTO jy8c (id, name, age) VALUES (:id, :name, :age)");

             query.prepare("update jy8c set age = :age where id = :id");


             qDebug()<<"kakutlgt ---  "<<kaku_tlgt<<endl;
            qDebug()<<"syq ----- ---   "<<kaku_syq<<endl;


             query.bindValue(":id",1);
             //query.bindValue(":name", QObject::tr("轴流转速"));
             query.bindValue(":age", kaku_tlgt);//ui->label->text().toInt()
             query.exec();

             query.bindValue(":id",2);
             //query.bindValue(":name", QObject::tr("复脱塞转速"));
             query.bindValue(":age", kaku_ftq);//ui->label_3->text().toInt()
             query.exec();


             query.bindValue(":id",3);
             //query.bindValue(":name", QObject::tr("升运转速"));
             query.bindValue(":age", kaku_syq);//ui->label_3->text().toInt()
             query.exec();


             query.bindValue(":id",4);
             //query.bindValue(":name", QObject::tr("亩产量"));
             query.bindValue(":age", kaku_muchanliang);//ui->label_3->text().toInt()
             query.exec();


             query.bindValue(":id",5);
             //query.bindValue(":name", QObject::tr("割台宽度"));
             query.bindValue(":age", kaku_getaikuandu);//ui->label_3->text().toInt()
             query.exec();


             query.bindValue(":id",8);
             //query.bindValue(":name", QObject::tr("初始化标志"));
             query.bindValue(":age", 1);
             query.exec();

           query.exec("select id, name, age from jy8c");
           while (query.next())
           {

              qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
           }

           query.exec(QObject::tr("drop jy8c"));

           //ui->label->setText(QString::number(bjd[0],10));

           flag_bjd = true;

           //flag_bjd2 = true;

    this->close();
}

void Setup::on_pushButton_3_clicked()//轴流滚筒转速 -
{
    if(startflag==0)
    {

        flag_bjd = false;
        tuoliguntong_zs--;
        ui->label->setText(QString::number(tuoliguntong_zs,10));
        kaku_tlgt = tuoliguntong_zs;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_tlgt--;
             kaku_tlgt = ka_tlgt;
            flagjiajia = false;
        }
        else
        {
            kaku_tlgt--;
        }


        ui->label->setText(QString::number(kaku_tlgt,10));

        //qDebug()<<"flag_tlgt--"<<kaku_tlgt<<endl;
    }
}

void Setup::on_pushButton_4_clicked()//轴流滚筒转速 +
{
    if(startflag==0)
    {

        flag_bjd = false;
        tuoliguntong_zs++;
        ui->label->setText(QString::number(tuoliguntong_zs,10));
        kaku_tlgt = tuoliguntong_zs;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;

        if(flagjiajia)//承上启下作用标志
        {
             ka_tlgt++;
             kaku_tlgt = ka_tlgt;
            flagjiajia = false;
        }
        else
        {
            kaku_tlgt++;
        }

        ui->label->setText(QString::number(kaku_tlgt,10));



        //qDebug()<<"flag_tlgt"<<kaku_tlgt<<endl;
    }
}

void Setup::on_pushButton_5_clicked()//复脱器堵塞转速 -
{
    if(startflag==0)
    {

        flag_bjd = false;
        ftq_zs--;

        ui->label_2->setText(QString::number(ftq_zs,10));
        kaku_ftq = ftq_zs;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_ftq--;
             kaku_ftq = ka_ftq;
            flagjiajia = false;
        }
        else
        {
            kaku_ftq--;
        }
        ui->label_2->setText(QString::number(kaku_ftq,10));

        //qDebug()<<"flag_123"<<kaku_syq<<endl;
    }
}

void Setup::on_pushButton_6_clicked()//复脱器堵塞转速 +
{
    if(startflag==0)
    {

        flag_bjd = false;
        ftq_zs++;
         ui->label_2->setText(QString::number(ftq_zs,10));
        kaku_ftq = ftq_zs;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_ftq++;
             kaku_ftq = ka_ftq;
            flagjiajia = false;
        }
        else
        {
            kaku_ftq++;
        }
        ui->label_2->setText(QString::number(kaku_ftq,10));

        //qDebug()<<"flag_123"<<kaku_syq<<endl;
    }
}

void Setup::on_pushButton_8_clicked()//升运器转速 -
{
    if(startflag==0)
    {

        flag_bjd = false;
        syq_zs--;
        ui->label_3->setText(QString::number(syq_zs,10));
        kaku_syq = syq_zs;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_syq--;
             kaku_syq = ka_syq;
            flagjiajia = false;
        }
        else
        {
            kaku_syq--;
        }


        ui->label_3->setText(QString::number(kaku_syq,10));

        //qDebug()<<"flag_tlgt--"<<kaku_tlgt<<endl;
    }
}

void Setup::on_pushButton_7_clicked()//升运器转速 +
{
    if(startflag==0)
    {

        flag_bjd = false;
        syq_zs++;
        ui->label_3->setText(QString::number(syq_zs,10));
        kaku_syq = syq_zs;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;

        if(flagjiajia)//承上启下作用标志
        {
             ka_syq++;
             kaku_syq = ka_syq;
            flagjiajia = false;
        }
        else
        {
            kaku_syq++;
        }

        ui->label_3->setText(QString::number(kaku_syq,10));



        //qDebug()<<"flag_tlgt"<<kaku_tlgt<<endl;
    }
}




void Setup::on_pushButton_9_clicked()//亩产量 -
{
    if(startflag==0)
    {

        flag_bjd = false;
        muchanliang--;
        ui->label_4->setText(QString::number(muchanliang,10));
        kaku_muchanliang = muchanliang;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_muchanliang--;
             kaku_muchanliang = ka_muchanliang;
            flagjiajia = false;
        }
        else
        {
            kaku_muchanliang--;
        }


        ui->label_4->setText(QString::number(kaku_muchanliang,10));

        //qDebug()<<"flag_tlgt--"<<kaku_tlgt<<endl;
    }
}

void Setup::on_pushButton_10_clicked()//亩产量 +
{
    if(startflag==0)
    {

        flag_bjd = false;
        muchanliang++;
        ui->label_4->setText(QString::number(muchanliang,10));
        kaku_muchanliang = muchanliang;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_muchanliang++;
             kaku_muchanliang = ka_muchanliang;
            flagjiajia = false;
        }
        else
        {
            kaku_muchanliang++;
        }


        ui->label_4->setText(QString::number(kaku_muchanliang,10));

        //qDebug()<<"flag_tlgt--"<<kaku_tlgt<<endl;
    }
}

void Setup::on_pushButton_11_clicked()//割台宽度 -
{
    if(startflag==0)
    {

        flag_bjd = false;
        getaikuandu--;
        ui->label_5->setText(QString::number(getaikuandu,10));
        kaku_getaikuandu = getaikuandu;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_getaikuandu--;
             kaku_getaikuandu = ka_getaikuandu;
            flagjiajia = false;
        }
        else
        {
            kaku_getaikuandu--;
        }


        ui->label_5->setText(QString::number(kaku_getaikuandu,10));

        //qDebug()<<"flag_tlgt--"<<kaku_tlgt<<endl;
    }
}

void Setup::on_pushButton_12_clicked()//割台宽度 +
{
    if(startflag==0)
    {

        flag_bjd = false;
        getaikuandu++;
        ui->label_5->setText(QString::number(getaikuandu,10));
        kaku_getaikuandu = getaikuandu;
        startflag = 1;
    }
    else
    {
        flag_bjd = false;
        if(flagjiajia)//承上启下作用标志
        {
             ka_getaikuandu++;
             kaku_getaikuandu = ka_getaikuandu;
            flagjiajia = false;
        }
        else
        {
            kaku_getaikuandu++;
        }


        ui->label_5->setText(QString::number(kaku_getaikuandu,10));

        //qDebug()<<"flag_tlgt--"<<kaku_tlgt<<endl;
    }
}


void Setup::on_pushButton_2_clicked()//时间设置
{
    timesetobj.show();
}


