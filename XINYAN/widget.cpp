#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QtSql>
#include <QKeyEvent>
#include <QTextCodec>


//#include"hwlib/libshm.h"

static float floatnu1 = 0;
int focuseflag;
uchar valueprogressbar;

//有光标移动的菜单选项
uchar LCClearMenuRow = 0;
uchar LCSwitchmatchineRow = 0;
uchar LCMachineModeMenu = 0;
uchar LCEngineSwitchMenu = 0;
bool LCBoolMachineModenu = true;

//2017.5.4  割台设置
uchar LCGetaiSetup = 0;
uchar GeFuWidth = 0;
uchar Zaihexishu = 0;
uchar Autospeed = 0;
//

uchar LCZhujiFault = 0;
uchar LCEngineFault = 0;

//2017.4.7 add
uchar LCBiaoDingRow = 0;
uchar LCPiPeixingBiaoDing = 0;

//2017.4.8
//标定 标志判断
uchar FlagShouBing = 0;
uchar FlagXingzouBeng = 0;
uchar FlagAoBanjianxi = 0;


//蜂鸣器状态标志
uchar flagbeep = 0;


//焦距焦点获取
bool f1;
bool f2;
bool f3;
bool f4;

//2017.4.6
//
//主离合
int zlh = 80;
QString strzlh = QString("%1").arg(zlh);
//卸粮离合
int xllh = 80;
QString strxllh = QString("%1").arg(xllh);
//过桥离合
int gqlh = 80;
QString strgqlh = QString("%1").arg(gqlh);

//滚筒
int gtzs = 80;
QString strgtzs = QString("%1").arg(gtzs);
//风机
int fjzs = 80;
QString strfjzs = QString("%1").arg(fjzs);
//搅龙
int jlzs = 80;
QString strjlzs = QString("%1").arg(jlzs);
//过桥
int gqzs = 80;
QString strgqzs = QString("%1").arg(gqzs);

//过渡变量 //临时变量

int tempzlh;
int tempxllh;
int tempgqlh;
int tempgtzs;
int tempfjzs;
int tempjlzs;
int tempgqzs;

//标志变量
bool FaZhiReadOK = true;
//bool FlagFaZhirecover = false;

//3秒内无变化函数
int Shijizhi;
int TempShijizhi;
bool FlagNext = false;
uchar ThreeOut;

//2017.4.28
bool tempflagShoubing = false;


//bool ShouBingZuixiao = false;
//bool ShouBingWangcheng = false;

//bool TuiGanZuixiao = false;
//bool TuiGanWancheng = false;

//bool AoBanZuixiao = false;
//bool AoBanWancheng = false;



/*******************************************************************************************************************/
//2017.1.14 wsj
//uchar flagFrame;
//界面选择标志
enum uiFlag
{                                   /*对应stacked 页面页数*/
    xingZouWidget = 0, //行走主工作界面   0
    UserMenu,   //用户菜单               1
    MainMenu,  //主菜单                  2
    ClearMenu,      //清零菜单           3
    SystemMenu, //系统设置菜单            4
    SwitchMachineMenu,//机型选择菜单      5
    MachineModeMenu,//整机型号           6
    HelpMenu,      //帮助菜单            7
    DiagnosisMenu,//故障查询菜单          8
    EngineSwitchMenu,//发动机选择         9
    VideoSetupMenu,   //视频设置         10
    PipeixingbiaodingMenu,//匹配性标定    11
    FazhibiaodingMenu,    //阀值标定       12
    EngineFault,         //发动机故障查询   13
    ZhujiFault,           //主机故障查询    14
    JiQiXinXi,        //机器信息           15
    BiaoDing,          //标定菜单           16
    Shaomiao,           //扫描菜单          17
    Getai              //割台参数设置        18
};
uiFlag flagwidget;

//从setup 界面返回上一级界面标志
struct flagSwitch
{
    uchar flagwidget;
    uchar flagwork;
};
flagSwitch flagswitch;

enum matchion
{
    YZB_3A_B = 0,
    YZT_10,
    YZB_4_5_7_8,
    //
    //2017.4.2
    JZ_3600,
    YZBT_5,
    YZT_5,
    YZT_10_1,
    S3000
};
matchion flagmatchion = YZT_10;


//发动机厂家选择
enum CJ
{
    YuCai = 0,
    WeiCai,
    XiCai,
    HangFa,
    DongfangHong
};
CJ CJSwitch = YuCai;

/**************************/
//摄像头开始标志位
uchar flagvedio = 1;

//设置超时标志
bool flagtimeout = false;
bool flagaction = false;
uchar flagtimeoutnum = 0;

/***************************************************************************************************/

/***************************************************************************************************/

long long xiaoshiJi_m;//分钟
double xiaoshiJi_h;//小时
float fadongzhuansu; //发动机转速


//uchar flagadd = 1;//转速方向标志位
uchar flagaddnum = 1;//转速方向标志位
uchar flagnum;
uchar flagDelay;//延时标志
uchar DelayCount;//延时六秒


uchar DelayYLcounter;//油量延时10秒响一次
uchar Delagbeepoff;//关之前延时
uchar flagbeepzero = 0;
//uchar flagYs;//延时2秒 防止一上电出现 蜂鸣器一直响。


int nu4;
uchar nu3;
float floatnu3=30;


uint nu2;
uint nu1;

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

double MIJILICHENG[3] = {0}; //米计 里程 状态标志
uint clearflag;//清零标志
uint  clearSave;//存储清零标志
uchar clearCount;

uint mijisum;//米计和， 用于显示
double licheng;//里程
int lichengsum;//里程和，用于显示

//水温 机油压力,电压数据
int NumSW;
float JYYL;
float DCDY;//电池电压

float YLBFB;//油量百分比

//闪烁标志
//
uchar shanshuoSW;//水温闪烁
uchar shanshuoJYYL;//机油压力闪烁
uchar shanshuoYL;//油量闪烁
uchar shanshuoYZYS;//油中有水
uchar shanshuoYYYW;//液压油温

uchar shanshuoLM;//粮满
uchar shanshuoSS;//手刹

uchar shanshuoTXGZ;//通信故障

uchar shanshuozlzs;//轴流滚筒转速
uchar shanshuoftqzs;//复托器转速
uchar shanshuosyqzs;//升运器转速



uchar flagMijLic = 0;//米计里程切换标志

uchar j=0;
uchar jflag = 0;
uint mm=0;
uchar jjjflag = 0;
unsigned char  mybufflag[15] = {0};
unsigned char  myindex[15] = {0};

/**************************/

uchar Led = 0;
/**************************************************************************************************************/
uint bjd[4] = {0};
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

/**************************************************************************************************************/

////时间设置 变量
QString  Datesetup;
bool timeSetOK = false; //时间设置完毕标志
QString DateTimeSetup;


QString dateBuffer;
QString timeBuffer;
QDateTime MyDatetimeSetup;

long long spnItem[10];
unsigned char fmiItem[10];
QString gzmItem[10];
unsigned char un = 0;

//
//发动机厂家，机器型号，语言选择
//
unsigned char ConfigArray[3] = {0};



/**************************************************************************************************************/

/**************************************************************************************************************/


/*******************************************************************************************************************/



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint); //删除 最小化、最大化、关闭按钮


#ifdef CAMERAFLAG
    //can 初始化
    Can_Ram_init();
    //摄像头初始化
    //摄像头初始化
    m_camerobj.Init(ui->label,NULL,HWE_PRODUCT_800X480_YM);
#endif


    timer_Main = new QTimer(this);   //声明一个定时器
    timer_Timeout = new QTimer(this);

    timer_xiaoshiji = new QTimer(); //声明小时计定时器
    timer_shanhua = new QTimer();
    timer_Licheng = new QTimer();//里程
    timergzm = new QTimer();//故障码

    ThreeSecondNoChangeTimer = new QTimer();//3秒内无边化 定时器
    connect(ThreeSecondNoChangeTimer, SIGNAL(timeout()), this, SLOT(NoChangeFun()));  //连接信号槽，定时器超时触发窗体更新
    ThreeSecondNoChangeTimer->start(1000);

    connect(timer_Main, SIGNAL(timeout()), this, SLOT(update()));  //连接信号槽，定时器超时触发窗体更新
    connect(timer_Timeout,SIGNAL(timeout()),this,SLOT(timeoutfun()));
    connect(timergzm, SIGNAL(timeout()), this, SLOT(gzmslottest()));  //连接信号槽，定时器超时触发窗体更新
    connect(timer_Licheng,SIGNAL(timeout()),this,SLOT(Licheng()));//里程
    connect(timer_xiaoshiji,SIGNAL(timeout()),this,SLOT(xiaoshiji()));//小时计
    connect(timer_shanhua, SIGNAL(timeout()), this, SLOT(shanhua()));  //连接信号槽，定时器超时触发窗体更新

    timer_Main->start(30);   //启动定时器
    //设置超时判断
    timer_Timeout->start(1000);

    timer_xiaoshiji->start(1000);//小时计
    timer_Licheng->start(1000);//里程
    timergzm->start(3000);//故障码//3000
    timer_shanhua->start(600);


    //gundongbofang
    m_timer = new QTimer(this);
    connect(m_timer,  SIGNAL(timeout()),  this,  SLOT(myscroll()));
    m_timer->start(300);



    //过滤器安装
    ui->label_2->installEventFilter(this);
    ui->label_5->installEventFilter(this);

    ui->label_2->setAttribute(Qt::WA_PaintOutsidePaintEvent,true);
    ui->label_5->setAttribute(Qt::WA_PaintOutsidePaintEvent,true);



    //2017.4.6
    //过滤器安装
    ui->lineEdit_3->installEventFilter(this);
    ui->lineEdit_4->installEventFilter(this);
    ui->lineEdit_5->installEventFilter(this);
    ui->lineEdit_6->installEventFilter(this);
    ui->lineEdit_7->installEventFilter(this);
    ui->lineEdit_8->installEventFilter(this);
    ui->lineEdit_9->installEventFilter(this);
    ui->lineEdit_10->installEventFilter(this);

    //2017.5.4
    ui->lineEdit_12->installEventFilter(this);
    ui->lineEdit_13->installEventFilter(this);
    ui->lineEdit_14->installEventFilter(this);
    ui->lineEdit_15->installEventFilter(this);


    //2017.4.22    //读取阀值设定数据库
    #if 1

     if(FaZhiReadOK)
     {
      //static unsigned char nn = 1;
      QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
      QSqlDatabase db;
      if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
      else
        db = QSqlDatabase::addDatabase("QSQLITE");

     db.setDatabaseName("jy.db");
     if (!db.open())
     {
         qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
     }
     QSqlQuery query;
     #if 0
     bool ok = query.exec("create table FaZhiBingBD(ZLH INTEGER,XLLH INTEGER,GQLH INTEGER,LmdGTZS INTEGER,LmdFengJi INTEGER,LmdJiaoLong INTEGER,LmdGuoQiao INTEGER)");
     if (ok)
     {
         qDebug()<<"ceate table partition success"<<endl;
     }
     else
     {
         qDebug()<<"ceate table partition failed"<<endl;
     }
     #endif

#if 0
     //query.prepare("INSERT INTO FaZhiBingBD(ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao) VALUES (:ZLH, :XLLH, :GQLH, :LmdGQZS, :LmdFengJi, :LmdJiaoLong, :LmdGuoQiao)");
     query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGQZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where

     query.bindValue(":ZLH",10);
     query.bindValue(":XLLH", 11);
     query.bindValue(":GQLH", 12);
     query.bindValue(":LmdGTZS", 13);
     query.bindValue(":LmdFengJi", 14);
     query.bindValue(":LmdJiaoLong", 15);
     query.bindValue(":LmdGuoQiao", 16);
     query.exec();
#endif

    query.exec("select ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao from FaZhiBingBD");
    while (query.next())
    {

      qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
      tempzlh = query.value(0).toInt();
      tempxllh = query.value(1).toInt();
      tempgqlh = query.value(2).toInt();
      tempgtzs = query.value(3).toInt();
      tempfjzs = query.value(4).toInt();
      tempjlzs = query.value(5).toInt();
      tempgqzs = query.value(6).toInt();


    }
    query.exec(QObject::tr("drop FaZhiBingBD"));

    zlh  = tempzlh;
    xllh = tempxllh;
    gqlh = tempgqlh;
    gtzs = tempgtzs;
    fjzs = tempfjzs;
    jlzs = tempjlzs;
    gqzs = tempgqzs;

    //FaZhiReadOK = false;
}
    #endif


    //2017.4.6
    //
    //主离合
    //int zlh = 80;
    QString strzlh = QString("%1").arg(zlh);
    //卸粮离合
    //int xllh = 80;
    QString strxllh = QString("%1").arg(xllh);
    //过桥离合
    //int gqlh = 80;
    QString strgqlh = QString("%1").arg(gqlh);

    //滚筒
    //int gtzs = 80;
    QString strgtzs = QString("%1").arg(gtzs);
    //风机
    //int fjzs = 80;
    QString strfjzs = QString("%1").arg(fjzs);
    //搅龙
    //int jlzs = 80;
    QString strjlzs = QString("%1").arg(jlzs);
    //过桥
    //int gqzs = 80;
    QString strgqzs = QString("%1").arg(gqzs);

    ui->lineEdit_3->setText(strzlh);
    ui->lineEdit_4->setText(strgtzs);
    ui->lineEdit_5->setText(strxllh);
    ui->lineEdit_6->setText(strfjzs);
    ui->lineEdit_7->setText(strgqlh);
    ui->lineEdit_8->setText(strjlzs);
    ui->lineEdit_9->setText(strgqzs);



    /**************************************************************/

    //2017.4.7
    //过滤器安装

    /*设置中文显示编码，否则为乱码*/
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf8"));

    ui->listWidget_6->installEventFilter(this);

    //标定选择
    QListWidgetItem * BiaoItem1 = new QListWidgetItem;
    QListWidgetItem * BiaoItem2 = new QListWidgetItem;
    QListWidgetItem * BiaoItem3 = new QListWidgetItem;

    BiaoItem1->setSizeHint(QSize(30, 52));  //每次改变Item的高度
    BiaoItem1->setText("匹配性标定");//

    BiaoItem2->setSizeHint(QSize(30, 52));  //每次改变Item的高度
    BiaoItem2->setText("阀值标定");//

    //2017.5.4
    BiaoItem3->setSizeHint(QSize(30, 52));  //每次改变Item的高度
    BiaoItem3->setText("收割参数设定");//

    ui->listWidget_6->insertItem(0,BiaoItem1);
    ui->listWidget_6->insertItem(1,BiaoItem2);
    ui->listWidget_6->insertItem(2,BiaoItem3);


    /**************************************************************/

    //过滤器安装
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->dateTimeEdit->installEventFilter(this);
    ui->progressBar->installEventFilter(this);

    ui->listWidget->installEventFilter(this);
    ui->listWidget_2->installEventFilter(this);
    ui->listWidget_3->installEventFilter(this);
    ui->listWidget_4->installEventFilter(this);
    ui->listWidget_5->installEventFilter(this);

    //2017.5.4
    ui->listWidget_7->installEventFilter(this);
    //


    ui->tableWidget->installEventFilter(this);
    ui->tableWidget_2->installEventFilter(this);



    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

//    ui->lineEdit->setAutoFillBackground(true);
//    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);


//    /*设置中文显示编码，否则为乱码*/
//    QTextCodec::setCodecForCStrings( QTextCodec::codecForName("utf8"));
    //清零 里程 米计
    QListWidgetItem * pItem1 = new QListWidgetItem;
    QListWidgetItem * pItem2 = new QListWidgetItem;
    QListWidgetItem * pItem3 = new QListWidgetItem;

    pItem1->setSizeHint(QSize(40, 43));  //每次改变Item的高度
    pItem1->setText("单次里程清零");//

    pItem2->setSizeHint(QSize(40, 43));  //每次改变Item的高度
    pItem2->setText("单次计数器清零");//

    pItem3->setSizeHint(QSize(40, 43));  //每次改变Item的高度
    pItem3->setText("单次计时器清零");//

    ui->listWidget->insertItem(0,pItem1);
    ui->listWidget->insertItem(1,pItem2);
    ui->listWidget->insertItem(2,pItem3);


    //机型选择
    QListWidgetItem * AItem1 = new QListWidgetItem;
    QListWidgetItem * AItem2 = new QListWidgetItem;
    //QListWidgetItem * pItem3 = new QListWidgetItem;

    AItem1->setSizeHint(QSize(30, 34));  //每次改变Item的高度
    AItem1->setText("整机型号");//

    AItem2->setSizeHint(QSize(30, 34));  //每次改变Item的高度
    AItem2->setText("发动机品牌");//

    ui->listWidget_2->insertItem(0,AItem1);
    ui->listWidget_2->insertItem(1,AItem2);



    //整机型号选择
    //机型选择
    QListWidgetItem * SItem1 = new QListWidgetItem;
    QListWidgetItem * SItem2 = new QListWidgetItem;
    QListWidgetItem * SItem3 = new QListWidgetItem;
    QListWidgetItem * SItem4 = new QListWidgetItem;
    QListWidgetItem * SItem5 = new QListWidgetItem;
    QListWidgetItem * SItem6 = new QListWidgetItem;

    //QListWidgetItem * pItem3 = new QListWidgetItem;

    SItem1->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem1->setText("4YZT-10");//

    SItem2->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem2->setText("4YZB-4/5/7/8");//

    SItem3->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem3->setText("4YZB-3A/B");//


    SItem4->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem4->setText("4JZ-3600");//

    SItem5->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem5->setText("4QZ-2200/2200A");//

    SItem6->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    SItem6->setText("4YZB-6/4(560)");//


    ui->listWidget_3->insertItem(0,SItem1);
    ui->listWidget_3->insertItem(1,SItem2);
    ui->listWidget_3->insertItem(2,SItem3);
    ui->listWidget_3->insertItem(3,SItem4);
    ui->listWidget_3->insertItem(4,SItem5);
    ui->listWidget_3->insertItem(5,SItem6);


    //整机型号选择
    //机型选择
    QListWidgetItem * TItem1 = new QListWidgetItem;
    QListWidgetItem * TItem2 = new QListWidgetItem;
    QListWidgetItem * TItem3 = new QListWidgetItem;
    QListWidgetItem * TItem4 = new QListWidgetItem;
    QListWidgetItem * TItem5 = new QListWidgetItem;
    QListWidgetItem * TItem6 = new QListWidgetItem;

    //QListWidgetItem * pItem3 = new QListWidgetItem;

    TItem1->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem1->setText("4YZBT-5");//

    TItem2->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem2->setText("4YZT-5");//

    TItem3->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem3->setText("4YZT-7/4LZ-8");//


    TItem4->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem4->setText("4QZ-3000/3000A");//

    TItem5->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem5->setText("4YZB-4A/B");//

    TItem6->setSizeHint(QSize(30, 37));  //每次改变Item的高度
    TItem6->setText("4YZ-3");//


    ui->listWidget_4->insertItem(0,TItem1);
    ui->listWidget_4->insertItem(1,TItem2);
    ui->listWidget_4->insertItem(2,TItem3);
    ui->listWidget_4->insertItem(3,TItem4);
    ui->listWidget_4->insertItem(4,TItem5);
    ui->listWidget_4->insertItem(5,TItem6);


    //
    //整机型号选择
    //机型选择
    QListWidgetItem * UItem1 = new QListWidgetItem;
    QListWidgetItem * UItem2 = new QListWidgetItem;
    QListWidgetItem * UItem3 = new QListWidgetItem;
    QListWidgetItem * UItem4 = new QListWidgetItem;
    QListWidgetItem * UItem5 = new QListWidgetItem;


    //QListWidgetItem * pItem3 = new QListWidgetItem;

    UItem1->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem1->setText("玉柴");//

    UItem2->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem2->setText("潍柴");//

    UItem3->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem3->setText("锡柴");//


    UItem4->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem4->setText("行发");//

    UItem5->setSizeHint(QSize(30, 42));  //每次改变Item的高度
    UItem5->setText("东方红");//


    ui->listWidget_5->insertItem(0,UItem1);
    ui->listWidget_5->insertItem(1,UItem2);
    ui->listWidget_5->insertItem(2,UItem3);
    ui->listWidget_5->insertItem(3,UItem4);
    ui->listWidget_5->insertItem(4,UItem5);


    //tablewidget
   // ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnWidth(1,198);

//    QTableWidgetItem *item0, *item1;
//    item0 = new QTableWidgetItem;
//    item1 = new QTableWidgetItem;

//    QString txt = QString("%1").arg(6);
//    item0->setText(txt);

//    QString txt2 = QString("%1").arg(9);
//    item1->setText(txt2);

//    ui->tableWidget->setItem(0,0,item0);
//    ui->tableWidget->setItem(1,0,item1);


//    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
//    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
//    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));
        ui->tableWidget_2->setColumnWidth(1,60);
        ui->tableWidget_2->setColumnWidth(2,249);

        ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("Jan"));
        ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("Feb"));
        ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("Mar"));


        //2017.4.6
        ui->tableWidget_3->setColumnWidth(0,70);
        ui->tableWidget_3->setColumnWidth(1,74);
        ui->tableWidget_3->setColumnWidth(2,74);
        ui->tableWidget_3->setColumnWidth(3,79);
        ui->tableWidget_3->setColumnWidth(4,79);
        ui->tableWidget_3->setColumnWidth(5,70);

        ui->tableWidget_3->setRowHeight(0,43);
        ui->tableWidget_3->setRowHeight(1,43);
        ui->tableWidget_3->setRowHeight(2,43);

        //2017.4.8
        //匹配性标定
        ui->tableWidget_3->installEventFilter(this);
        ui->lineEdit_11->installEventFilter(this); //ui->label_21
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    #if 1
    QPixmap pix;
    //图片选择
    switch(flagwidget)
    {
        case xingZouWidget:

        //机型选择
        switch(flagmatchion)
        {
            case YZT_10:
            pix.load("./img/jiemian/YZT_10.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");

            break;
            case YZB_3A_B:
            pix.load("./img/jiemian/YZB_3A_B.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            case YZB_4_5_7_8:
            pix.load("./img/jiemian/4YZB_4_5_7_8.bmp");
            //切换到YZBHaishan界面小表盘
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            //2017.4.2 add
            case JZ_3600:
            pix.load("./img/jiemian/JZ_3600.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");
            break;

            case YZBT_5:
            pix.load("./img/jiemian/YZBT_5.bmp");
            //切换到YZBHaishan界面小表盘
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;

            case YZT_5:
            pix.load("./img/jiemian/YZT_5.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");
            break;

            case YZT_10_1:
            pix.load("./img/jiemian/YZT_10_1.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/shuiwen.png);");

            case S3000:
            pix.load("./img/jiemian/S3000.bmp");
            ui->label_5->setStyleSheet("border-image: url(:/new/prefix1/img/icon/jiyouyali.png);");
            break;


            default:
            break;
        }
        break;
        case SystemMenu:
        pix.load("./img/jiemian/SystemMenu.bmp");
        break;
        case MainMenu:
        pix.load("./img/jiemian/MainMenu.bmp");
        break;
        case UserMenu:
        pix.load("./img/jiemian/UserMenu.bmp");
        break;

        case MachineModeMenu:
        pix.load("./img/jiemian/machineswitch.bmp");
        break;

        case ClearMenu:
        pix.load("./img/jiemian/ClearMenu.bmp");
        break;

        case HelpMenu:
        pix.load("./img/jiemian/HelpMenu.bmp");
        break;

        case DiagnosisMenu:
        pix.load("./img/jiemian/DiagnosisMenu.bmp");
        break;

        case SwitchMachineMenu:
        pix.load("./img/jiemian/SwitchMachineMenu.bmp");
        break;

        case EngineSwitchMenu:
        pix.load("./img/jiemian/EngineSwitchMenu.bmp");
        break;

        case VideoSetupMenu:
        pix.load("./img/jiemian/VideoSetupMenu.bmp");
        break;

        case PipeixingbiaodingMenu:
        pix.load("./img/jiemian/PipeixingbiaodingMenu.bmp");
        break;


        case FazhibiaodingMenu:
        pix.load("./img/jiemian/FazhibiaodingMenu.bmp");
        break;

        case EngineFault:
        pix.load("./img/jiemian/EngineFault.bmp");
        break;

        case ZhujiFault:
        pix.load("./img/jiemian/ZhujiFault.bmp");
        break;

        //2017.4.7
        case JiQiXinXi:
        pix.load("./img/jiemian/JiQiXinXi.bmp");
        break;

        case BiaoDing:
        pix.load("./img/jiemian/BiaoDing.bmp");
        break;

        case Shaomiao:
        pix.load("./img/jiemian/Shaomiao.bmp");
        break;

        //2017.5.4
        case Getai:
        pix.load("./img/jiemian/Getai.bmp");//
        break;

        default:
        break;
    }
    painter.drawPixmap(0,0,800,480,pix);

#endif

    /**************************************************************************************************************/
    //2017.1.18
    //摄像头 监控画面
#ifdef CAMERAFLAG
    #if 1
        if(flagwidget == xingZouWidget)
        {
            if(flagvedio)
            {
                m_camerobj.Jobs_Monitor(CAMERA_AV_2);      /*作业监控*/
                flagvedio = 0;
            }
        }
    #endif
#endif

    /**************************************************************************************************************/
#if 1
        if(flagwidget == xingZouWidget)
           {

            /*******************************************************************************************************/
            //
            //
            //2017.3.11
            //读数据库

                //语言选择 发动机厂家 机器型号
                //

            #if 1
                QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");

               db.setDatabaseName("jy.db");
               if (!db.open())
               {
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;

             query.exec("select cjswitch, engineswitch, langswitch from config");
             while (query.next())
             {
                ConfigArray[0] = query.value(0).toInt();
                ConfigArray[1] = query.value(1).toInt();
                ConfigArray[2] = query.value(2).toInt();
                //qDebug()<<"ConfigArray(0)"<<query.value(0).toInt()<<"ConfigArray[1]:"<<query.value(1).toString()<<"ConfigArray[2]:"<<query.value(2).toInt();

             }

              query.exec(QObject::tr("drop config"));

            #endif

              switch(ConfigArray[1])
              {
                  case 0:
                  flagmatchion = YZB_3A_B;
                  break;
                  case 1:
                  flagmatchion = YZT_10;
                  break;
                  case 2:
                  flagmatchion = YZB_4_5_7_8;
                  break;

                  case 3:
                  flagmatchion = JZ_3600;
                  break;

                  case 4:
                  flagmatchion = YZBT_5;
                  break;

                  case 5:
                  flagmatchion = YZT_5;
                  break;

                  case 6:
                  flagmatchion = YZT_10_1;
                  break;

                  case 7:
                  flagmatchion = S3000;
                  break;

                  default:
                  break;
              }

             //机型选择
            if(flagmatchion == YZT_10)
            {
               //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

               painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
               //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

               //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                   QPoint(-1, -55),
                   QPoint(1, -55)
               };

               //机油压力

               painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
               painter.setBrush(Qt::red);
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.save();
               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painter.rotate(-120);
               //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
               //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
               //painter.rotate(4.0 );//*shisu

               painter.rotate(8*60);//floatnu2
               //painter.rotate(8*floatnu1);//floatnu1

               painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
               painter.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painter.save();
               painter.drawEllipse(QPoint(0,0),13,13);
               painter.restore();

               //画白圈
               /***********************************************/

               painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painter.save();
               painter.drawEllipse(QPoint(0,0),10,10);
               painter.restore();


               //风机转速
               painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);

               painter.setPen(Qt::NoPen);
               painter.setBrush(Qt::red);
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.save();

               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painter.rotate(-120);
               painter.rotate(8*60);
              // painter.rotate(8*floatnu1);//



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

               //KM/H
               painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);

               painter.setPen(Qt::NoPen);
               painter.setBrush(Qt::red);
               painter.setRenderHint(QPainter::Antialiasing, true);
               painter.save();

               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painter.rotate(-120);
               painter.rotate(8*60);
               //painter.rotate(8*floatnu1);//



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

               //处理图片闪烁
               painter.translate(-390,-226);//平移到左边角

               //喂入
               QPainter paintShanshuo_W(this);
               QPixmap pixShanshuo_W;
               pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
               paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

               //粮损
               pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
               paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);

               //油量
               pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
               paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

               //凹槽
               pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
               paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);



           //报警灯

          QPainter paintdeng(this);
          QPixmap pixdeng;
          //左转灯
          if(1)
          {
              pixdeng.load("./img/dengshan/01.png");//
              paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
          }
          //发动机故障
          if(1)
          {
              pixdeng.load("./img/dengshan/14.png");//
              paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
          }
          //充电指示灯
          if(1)
          {
              pixdeng.load("./img/dengshan/17.png");//
              paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
          }
          //水温
          if(1)
          {
              pixdeng.load("./img/dengshan/09.png");//
              paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
          }
          //油压
          if(1)
          {
              pixdeng.load("./img/dengshan/12.png");//
              paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
          }
          //油量
          if(1)
          {
              pixdeng.load("./img/dengshan/10.png");//
              paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
          }
          //手刹
          if(1)
          {
              pixdeng.load("./img/dengshan/13.png");//
              paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
          }
          //远光
          if(1)
          {
              pixdeng.load("./img/dengshan/02.png");//
              paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
          }
          //示宽灯
          if(1)
          {
              pixdeng.load("./img/dengshan/04.png");//
              paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
          }
          //近光灯
          if(1)
          {
              pixdeng.load("./img/dengshan/03.png");//
              paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
          }
          //发动机预热灯
          if(1)
          {
              pixdeng.load("./img/dengshan/11.png");//
              paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
          }
          //量满
          if(1)
          {
              pixdeng.load("./img/dengshan/15.png");//
              paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
          }
          //粮仓满
          if(1)
          {
              pixdeng.load("./img/dengshan/08.png");//
              paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
          }
          //燃油进水指示灯
          if(1)
          {
              pixdeng.load("./img/dengshan/07.png");//
              paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
          }
          //液压油压力
          if(1)
          {
              pixdeng.load("./img/dengshan/99.png");//
              paintdeng.drawPixmap(619,432,15,28,pixdeng);//正上方位置显示的图标
          }
          //空滤灯
          if(1)
          {
              pixdeng.load("./img/dengshan/05.png");//
              paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
          }
          //主机故障灯
          if(1)
          {
              pixdeng.load("./img/dengshan/06.png");//
              paintdeng.drawPixmap(680,430,44,29,pixdeng);//正上方位置显示的图标
          }
          //右转灯
          if(1)
          {
              pixdeng.load("./img/dengshan/18.png");//
              paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
          }



          //主界面中央灯区
          //粮筒摆出
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/01.png");//
              paintdeng.drawPixmap(255,266,30,19,pixdeng);//正上方位置显示的图标
          }
          //过桥故障
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/02.png");//
              paintdeng.drawPixmap(307,258,32,29,pixdeng);//正上方位置显示的图标
          }
          //风机故障
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/03.png");//
              paintdeng.drawPixmap(273,281,31,32,pixdeng);//正上方位置显示的图标
          }

          //滚筒故障
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/04.png");//
              paintdeng.drawPixmap(288,322,31,28,pixdeng);//正上方位置显示的图标
          }
          //刹车盘磨损
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/05.png");//
              paintdeng.drawPixmap(294,355,30,24,pixdeng);//正上方位置显示的图标
          }
          //升运器故障
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/06.png");//
              paintdeng.drawPixmap(463,258,31,25,pixdeng);//正上方位置显示的图标
          }

          //卸粮中
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/07.png");//
              paintdeng.drawPixmap(513,260,34,24,pixdeng);//正上方位置显示的图标
          }
          //粮仓盖
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/08.png");//
              paintdeng.drawPixmap(499,292,27,23,pixdeng);//正上方位置显示的图标
          }
          //液压滤清
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/09.png");//
              paintdeng.drawPixmap(490,319,16,28,pixdeng);//正上方位置显示的图标
          }
          //刹车制动故障
          if(1)
          {
              pixdeng.load("./img/zhujiemianicon/10.png");//
              paintdeng.drawPixmap(475,355,31,24,pixdeng);//正上方位置显示的图标
          }

         }//end of if(flagmatchion == YZT_10)
         else if(flagmatchion == YZB_3A_B)
         {
                //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                 painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                    QPoint(-1, -55),
                    QPoint(1, -55)
                };

                //机油压力

                painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();
                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-120);
                //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                //painter.rotate(4.0 );//*shisu

                painter.rotate(8*60);//floatnu2
                //painter.rotate(8*floatnu1);//floatnu1

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/

                painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();


                //油量
                painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-120);
                painter.rotate(8*60);
                //painter.rotate(8*floatnu1);//



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

                //KM/H
                painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-120);
                painter.rotate(8*60);
                //painter.rotate(8*floatnu1);//



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

                //处理图片闪烁
                painter.translate(-390,-226);//平移到左边角

#if 0

                //喂入
                QPainter paintShanshuo_W(this);
                QPixmap pixShanshuo_W;
                pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                //粮损
                pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
                paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);

                //油量
                pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                //凹槽
                pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
                paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);
#endif
                 #if 0
                         //
                         //控件显示
                         //显示时间 。2017.1.14
                 //        QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
                 //        QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");

                         QString  timeStr1 = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd");

                         //不同界面显示时间

                         if(flagwidget == xingZouWidget)
                         {
                             ui->label_3->setText(timeStr1);//dateStr1
                         }
                 #endif


            //报警灯
           QPainter paintdeng(this);
           QPixmap pixdeng;
           //左转灯
           if(1)
           {
               pixdeng.load("./img/dengshan/01.png");//
               paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
           }
           //发动机故障
           if(1)
           {
               pixdeng.load("./img/dengshan/14.png");//
               paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
           }
           //充电指示灯
           if(1)
           {
               pixdeng.load("./img/dengshan/17.png");//
               paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
           }
           //水温
           if(1)
           {
               pixdeng.load("./img/dengshan/09.png");//
               paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
           }
           //油压
           if(1)
           {
               pixdeng.load("./img/dengshan/12.png");//
               paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
           }
           //油量
           if(1)
           {
               pixdeng.load("./img/dengshan/10.png");//
               paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
           }
           //手刹
           if(1)
           {
               pixdeng.load("./img/dengshan/13.png");//
               paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
           }
           //远光
           if(1)
           {
               pixdeng.load("./img/dengshan/02.png");//
               paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
           }
           //示宽灯
           if(1)
           {
               pixdeng.load("./img/dengshan/04.png");//
               paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
           }
           //近光灯
           if(1)
           {
               pixdeng.load("./img/dengshan/03.png");//
               paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
           }
           //发动机预热灯
           if(1)
           {
               pixdeng.load("./img/dengshan/11.png");//
               paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
           }
//           //量满
//           if(1)
//           {
//               pixdeng.load("./img/dengshan/15.png");//
//               paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
//           }
//           //粮仓满
//           if(1)
//           {
//               pixdeng.load("./img/dengshan/08.png");//
//               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
//           }
           //燃油进水指示灯
           if(1)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }
           //液压油压力
           if(1)
           {
               pixdeng.load("./img/dengshan/99.png");//
               paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
           }
           //空滤灯
           if(1)
           {
               pixdeng.load("./img/dengshan/05.png");//
               paintdeng.drawPixmap(510,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //草箱限制
           if(1)
           {
               pixdeng.load("./img/dengshan/19.png");//
               paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
           }
           //右转灯
           if(1)
           {
               pixdeng.load("./img/dengshan/18.png");//
               paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
           }

#if 0
           //主界面中央灯区
           //粮筒摆出
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/01.png");//
               paintdeng.drawPixmap(255,266,30,19,pixdeng);//正上方位置显示的图标
           }
           //过桥故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/02.png");//
               paintdeng.drawPixmap(307,258,32,29,pixdeng);//正上方位置显示的图标
           }
           //风机故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/03.png");//
               paintdeng.drawPixmap(273,281,31,32,pixdeng);//正上方位置显示的图标
           }

           //滚筒故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/04.png");//
               paintdeng.drawPixmap(288,322,31,28,pixdeng);//正上方位置显示的图标
           }
           //刹车盘磨损
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/05.png");//
               paintdeng.drawPixmap(294,355,30,24,pixdeng);//正上方位置显示的图标
           }
           //升运器故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/06.png");//
               paintdeng.drawPixmap(463,258,31,25,pixdeng);//正上方位置显示的图标
           }

           //卸粮中
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/07.png");//
               paintdeng.drawPixmap(513,260,34,24,pixdeng);//正上方位置显示的图标
           }
           //粮仓盖
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/08.png");//
               paintdeng.drawPixmap(499,292,27,23,pixdeng);//正上方位置显示的图标
           }
           //液压滤清
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/09.png");//
               paintdeng.drawPixmap(490,319,16,28,pixdeng);//正上方位置显示的图标
           }
           //刹车制动故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/10.png");//
               paintdeng.drawPixmap(475,355,31,24,pixdeng);//正上方位置显示的图标
           }
#endif
         }//end of if(flagmatchion == YZT_3)

            else if(flagmatchion == YZB_4_5_7_8)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //机油压力

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(8*floatnu1);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(Led)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(1)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }
              //水温
              if(1)
              {
                  pixdeng.load("./img/dengshan/09.png");//
                  paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
              }
              //油压
              if(1)
              {
                  pixdeng.load("./img/dengshan/12.png");//
                  paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
              }
              //油量
              if(1)
              {
                  pixdeng.load("./img/dengshan/10.png");//
                  paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
              }
              //手刹
              if(1)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(1)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
              //量满
              if(1)
              {
                  pixdeng.load("./img/dengshan/15.png");//
                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
              }
   //           //粮仓满
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/08.png");//
   //               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
   //           }
              //燃油进水指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }
              //液压油压力
              if(1)
              {
                  pixdeng.load("./img/dengshan/99.png");//
                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
              //草箱限制
              if(1)
              {
                  pixdeng.load("./img/dengshan/19.png");//
                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
              }
              //右转灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZB_4_5_7_8)

            //
            //2017.4.2
            else if(flagmatchion == JZ_3600)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //水温

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(8*floatnu1);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(Led)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(1)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }
              //水温
              if(1)
              {
                  pixdeng.load("./img/dengshan/09.png");//
                  paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
              }
              //油压
              if(1)
              {
                  pixdeng.load("./img/dengshan/12.png");//
                  paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
              }
              //油量
              if(1)
              {
                  pixdeng.load("./img/dengshan/10.png");//
                  paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
              }
              //手刹
              if(1)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(1)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
//              //量满
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/15.png");//
//                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
//              }
   //           //粮仓满
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/08.png");//
   //               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
   //           }
              //燃油进水指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }
              //液压油压力
              if(1)
              {
                  pixdeng.load("./img/dengshan/99.png");//
                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
//              //草箱限制
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/19.png");//
//                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
//              }

              //刹车自动故障
              if(1)
              {
                  pixdeng.load("./img/zhujiemianicon/10.png");//
                  paintdeng.drawPixmap(643,434,31,24,pixdeng);//正上方位置显示的图标
              }

              //右转灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZB_4_5_7_8)

            else if(flagmatchion == YZBT_5)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //机油压力

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(8*floatnu1);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(Led)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(1)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }
              //水温
              if(1)
              {
                  pixdeng.load("./img/dengshan/09.png");//
                  paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
              }
              //油压
              if(1)
              {
                  pixdeng.load("./img/dengshan/12.png");//
                  paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
              }
              //油量
              if(1)
              {
                  pixdeng.load("./img/dengshan/10.png");//
                  paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
              }
              //手刹
              if(1)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(1)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
              //粮满
              if(1)
              {
                  pixdeng.load("./img/dengshan/15.png");//
                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
              }
              //粮仓满
              if(1)
              {
                  pixdeng.load("./img/dengshan/08.png");//
                  paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
              }
              //燃油进水指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }

              //液压滤清
              if(1)
              {
                  pixdeng.load("./img/zhujiemianicon/09.png");//
                  //paintdeng.drawPixmap(586,432,12,28,pixdeng);//正上方位置显示的图标
                  paintdeng.drawPixmap(616,432,16,28,pixdeng);//正上方位置显示的图标
              }


//              //液压油压力
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/99.png");//
//                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
//              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
//              //草箱限制
//              if(0)
//              {
//                  pixdeng.load("./img/dengshan/19.png");//
//                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
//              }
              //右转灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZBT_5)

            else if(flagmatchion == YZT_5)
            {
                //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                 painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                    QPoint(-1, -55),
                    QPoint(1, -55)
                };

                //机油压力

                painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();
                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-120);
                //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                //painter.rotate(4.0 );//*shisu

                painter.rotate(8*60);//floatnu2
                //painter.rotate(8*floatnu1);//floatnu1

                painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                painter.restore();

                /***********************************************/
                //2016.6.25   画白圈
                painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),13,13);
                painter.restore();

                //画白圈
                /***********************************************/

                painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                painter.save();
                painter.drawEllipse(QPoint(0,0),10,10);
                painter.restore();


                //风机转速
                painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-120);
                painter.rotate(8*60);
               // painter.rotate(8*floatnu1);//



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

                //KM/H
                painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                //painter.scale(side / 400.0, side / 300.0);

                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::red);
                painter.setRenderHint(QPainter::Antialiasing, true);
                painter.save();

                //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                painter.rotate(-120);
                painter.rotate(8*60);
                //painter.rotate(8*floatnu1);//



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

                //处理图片闪烁
                painter.translate(-390,-226);//平移到左边角

                //喂入
                QPainter paintShanshuo_W(this);
                QPixmap pixShanshuo_W;
                pixShanshuo_W.load("./img/weiruliang/09.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,110,28,121,pixShanshuo_W);

                //粮损
                pixShanshuo_W.load("./img/liangshun/06.png");//07.jpg
                paintShanshuo_W.drawPixmap(760,110,27,120,pixShanshuo_W);

                //油量
                pixShanshuo_W.load("./img/ranyou/07.png");//07.jpg
                paintShanshuo_W.drawPixmap(10,275,27,118,pixShanshuo_W);

                //凹槽
                pixShanshuo_W.load("./img/aocao/05.png");//07.jpg
                paintShanshuo_W.drawPixmap(760,275,28,119,pixShanshuo_W);


            //报警灯

           QPainter paintdeng(this);
           QPixmap pixdeng;
           //左转灯
           if(1)
           {
               pixdeng.load("./img/dengshan/01.png");//
               paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
           }
           //发动机故障
           if(1)
           {
               pixdeng.load("./img/dengshan/14.png");//
               paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
           }
           //充电指示灯
           if(1)
           {
               pixdeng.load("./img/dengshan/17.png");//
               paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
           }
           //水温
           if(1)
           {
               pixdeng.load("./img/dengshan/09.png");//
               paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
           }
           //油压
           if(1)
           {
               pixdeng.load("./img/dengshan/12.png");//
               paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
           }
           //油量
           if(1)
           {
               pixdeng.load("./img/dengshan/10.png");//
               paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
           }
           //手刹
           if(1)
           {
               pixdeng.load("./img/dengshan/13.png");//
               paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
           }
           //远光
           if(1)
           {
               pixdeng.load("./img/dengshan/02.png");//
               paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
           }
           //示宽灯
           if(1)
           {
               pixdeng.load("./img/dengshan/04.png");//
               paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
           }
           //近光灯
           if(1)
           {
               pixdeng.load("./img/dengshan/03.png");//
               paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
           }
           //发动机预热灯
           if(1)
           {
               pixdeng.load("./img/dengshan/11.png");//
               paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
           }
           //量满
           if(1)
           {
               pixdeng.load("./img/dengshan/15.png");//
               paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //粮仓满
           if(1)
           {
               pixdeng.load("./img/dengshan/08.png");//
               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
           }
           //燃油进水指示灯
           if(1)
           {
               pixdeng.load("./img/dengshan/07.png");//
               paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
           }
           //液压油压力
           if(1)
           {
               pixdeng.load("./img/dengshan/99.png");//
               paintdeng.drawPixmap(619,432,15,28,pixdeng);//正上方位置显示的图标
           }
           //空滤灯
           if(1)
           {
               pixdeng.load("./img/dengshan/05.png");//
               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
           }
           //主机故障灯
           if(1)
           {
               pixdeng.load("./img/dengshan/06.png");//
               paintdeng.drawPixmap(680,430,44,29,pixdeng);//正上方位置显示的图标
           }
           //右转灯
           if(1)
           {
               pixdeng.load("./img/dengshan/18.png");//
               paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
           }



           //主界面中央灯区
           //粮筒摆出
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/01.png");//
               paintdeng.drawPixmap(255,266,30,19,pixdeng);//正上方位置显示的图标
           }
           //过桥故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/02.png");//
               paintdeng.drawPixmap(307,258,32,29,pixdeng);//正上方位置显示的图标
           }
           //风机故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/03.png");//
               paintdeng.drawPixmap(273,281,31,32,pixdeng);//正上方位置显示的图标
           }

           //滚筒故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/04.png");//
               paintdeng.drawPixmap(288,322,31,28,pixdeng);//正上方位置显示的图标
           }
           //刹车盘磨损
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/05.png");//
               paintdeng.drawPixmap(294,355,30,24,pixdeng);//正上方位置显示的图标
           }
           //升运器故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/06.png");//
               paintdeng.drawPixmap(463,258,31,25,pixdeng);//正上方位置显示的图标
           }

           //卸粮中
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/07.png");//
               paintdeng.drawPixmap(513,260,34,24,pixdeng);//正上方位置显示的图标
           }
           //粮仓盖
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/08.png");//
               paintdeng.drawPixmap(499,292,27,23,pixdeng);//正上方位置显示的图标
           }
           //液压滤清
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/09.png");//
               paintdeng.drawPixmap(490,319,16,28,pixdeng);//正上方位置显示的图标
           }
           //刹车制动故障
           if(1)
           {
               pixdeng.load("./img/zhujiemianicon/10.png");//
               paintdeng.drawPixmap(475,355,31,24,pixdeng);//正上方位置显示的图标
           }

            }//end of if(flagmatchion == YZB_4_5_7_8)


            else if(flagmatchion == YZT_10_1)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //机油压力

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(8*floatnu1);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(Led)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(1)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }
              //水温
              if(1)
              {
                  pixdeng.load("./img/dengshan/09.png");//
                  paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
              }
              //油压
              if(1)
              {
                  pixdeng.load("./img/dengshan/12.png");//
                  paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
              }
              //油量
              if(1)
              {
                  pixdeng.load("./img/dengshan/10.png");//
                  paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
              }
              //手刹
              if(1)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(1)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
              //量满
              if(1)
              {
                  pixdeng.load("./img/dengshan/15.png");//
                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
              }
   //           //粮仓满
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/08.png");//
   //               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
   //           }
              //燃油进水指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }
              //液压油压力
              if(1)
              {
                  pixdeng.load("./img/dengshan/99.png");//
                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
              //草箱限制
              if(1)
              {
                  pixdeng.load("./img/dengshan/19.png");//
                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
              }
              //右转灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZB_4_5_7_8)

            else if(flagmatchion == S3000)
            {
                   //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

                   painter.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
                   //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

                   //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                    painter.translate(210, 363);//重新定位坐标起始点，把坐标原点放到窗体的中央
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
                       QPoint(-1, -55),
                       QPoint(1, -55)
                   };

                   //机油压力

                   painter.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();
                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(6.0 *numtmp);  //设置旋转(6° * 秒)
                   //painter.rotate(numtmp++);  //设置旋转(6° * 秒)
                   //painter.rotate(4.0 );//*shisu

                   //painter.rotate(8*nu1);//floatnu2
                   painter.rotate(8*floatnu1);//floatnu1

                   painter.drawConvexPolygon(minuteHand, 4);  //填充分针部分
                   painter.restore();

                   /***********************************************/
                   //2016.6.25   画白圈
                   painter.setBrush(Qt::darkGray); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),13,13);
                   painter.restore();

                   //画白圈
                   /***********************************************/

                   painter.setBrush(Qt::black);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
                   painter.save();
                   painter.drawEllipse(QPoint(0,0),10,10);
                   painter.restore();


                   //油量
                   painter.translate(380,3);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //KM/H
                   painter.translate(-190,-36);//重新定位坐标起始点，把坐标原点放到窗体的中央
                   //painter.scale(side / 400.0, side / 300.0);

                   painter.setPen(Qt::NoPen);
                   painter.setBrush(Qt::red);
                   painter.setRenderHint(QPainter::Antialiasing, true);
                   painter.save();

                   //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
                   painter.rotate(-120);
                   //painter.rotate(8*nu3);
                   painter.rotate(8*floatnu1);//



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

                   //处理图片闪烁
                   painter.translate(-390,-226);//平移到左边角


               //报警灯
              QPainter paintdeng(this);
              QPixmap pixdeng;
              //左转灯
              if(Led)
              {
                  pixdeng.load("./img/dengshan/01.png");//
                  paintdeng.drawPixmap(5,415,49,55,pixdeng);//正上方位置显示的图标
              }
              //发动机故障
              if(1)
              {
                  pixdeng.load("./img/dengshan/14.png");//
                  paintdeng.drawPixmap(73,435,36,23,pixdeng);//正上方位置显示的图标
              }
              //充电指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/17.png");//
                  paintdeng.drawPixmap(118,434,34,24,pixdeng);//正上方位置显示的图标
              }
              //水温
              if(1)
              {
                  pixdeng.load("./img/dengshan/09.png");//
                  paintdeng.drawPixmap(161,432,31,28,pixdeng);//正上方位置显示的图标
              }
              //油压
              if(1)
              {
                  pixdeng.load("./img/dengshan/12.png");//
                  paintdeng.drawPixmap(200,436,39,20,pixdeng);//正上方位置显示的图标
              }
              //油量
              if(1)
              {
                  pixdeng.load("./img/dengshan/10.png");//
                  paintdeng.drawPixmap(248,430,24,28,pixdeng);//正上方位置显示的图标
              }
              //手刹
              if(1)
              {
                  pixdeng.load("./img/dengshan/13.png");//
                  paintdeng.drawPixmap(278,433,37,29,pixdeng);//正上方位置显示的图标
              }
              //远光
              if(1)
              {
                  pixdeng.load("./img/dengshan/02.png");//
                  paintdeng.drawPixmap(322,434,38,23,pixdeng);//正上方位置显示的图标
              }
              //示宽灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/04.png");//
                  paintdeng.drawPixmap(367,434,43,24,pixdeng);//正上方位置显示的图标
              }
              //近光灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/03.png");//
                  paintdeng.drawPixmap(418,433,37,27,pixdeng);//正上方位置显示的图标
              }
              //发动机预热灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/11.png");//
                  paintdeng.drawPixmap(463,434,37,23,pixdeng);//正上方位置显示的图标
              }
//              //量满
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/15.png");//
//                  paintdeng.drawPixmap(509,430,32,32,pixdeng);//正上方位置显示的图标
//              }
   //           //粮仓满
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/08.png");//
   //               paintdeng.drawPixmap(550,435,29,20,pixdeng);//正上方位置显示的图标
   //           }
              //燃油进水指示灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/07.png");//
                  paintdeng.drawPixmap(586,432,24,28,pixdeng);//正上方位置显示的图标
              }
              //液压油压力
              if(1)
              {
                  pixdeng.load("./img/dengshan/99.png");//
                  paintdeng.drawPixmap(616,432,15,28,pixdeng);//正上方位置显示的图标
              }
   //           //空滤灯
   //           if(1)
   //           {
   //               pixdeng.load("./img/dengshan/05.png");//
   //               paintdeng.drawPixmap(640,430,32,32,pixdeng);//正上方位置显示的图标
   //           }
//              //草箱限制
//              if(1)
//              {
//                  pixdeng.load("./img/dengshan/19.png");//
//                  paintdeng.drawPixmap(643,431,34,26,pixdeng);//正上方位置显示的图标
//              }

              //刹车自动故障
              if(1)
              {
                  pixdeng.load("./img/zhujiemianicon/10.png");//
                  paintdeng.drawPixmap(643,434,31,24,pixdeng);//正上方位置显示的图标
              }

              //右转灯
              if(1)
              {
                  pixdeng.load("./img/dengshan/18.png");//
                  paintdeng.drawPixmap(740,415,49,55,pixdeng);//正上方位置显示的图标
              }

              //显示油量，机油压力，小时计 等要显示的值
              //
              //机油压力
              ui->label_7->setText("jiyouyali");


            }//end of if(flagmatchion == YZB_4_5_7_8)


        }//end of if(flagwidget == xingZouWidget)




/*************************************************************************************************************/
     /*设置系统时间*/
    if(timeSetOK == true)
    {
        //日期
        QString str1 = """";
        str1 += "date -s ";
        str1 += dateBuffer;
        str1 += """";
        system(str1.toLatin1().data());

        //时间
        QString str2 = """";
        str2 += "date -s ";
        //str2 += DateTimeSetup.mid(11,9);
        str2 += timeBuffer;

        str2 += """";
        system(str2.toLatin1().data());
        system("hwclock -w");
        timeSetOK = false;

    }
/*****************************************************************************************************************/

/*****************************************************************************************************************/
//处理 Label 数据
//
//
//日期 时间 处理
    //控件显示
    //显示时间 。2017.1.14
    QString timeStr1= QTime::currentTime().toString();     //绘制当前的时间
    QString dateStr1 = QDate::currentDate().toString("yyyy-MM-dd");//dddd
    QString dddd = QDate::currentDate().toString("dddd");//



    ui->label_3->setText(dateStr1);
    ui->label_13->setText(timeStr1);

    //qDebug()<<"dddd == "<<dddd<<endl;

    //arm 板子汉化
    if(dddd == "Monday")
    {
        ui->label_12->setText("星期一");
    }
    else if(dddd == "Tuesday")
    {
        ui->label_12->setText("星期二");
    }
    else if(dddd == "Wednesday")
    {
        ui->label_12->setText("星期三");
    }
    else if(dddd == "Thursday")
    {
        ui->label_12->setText("星期四");
    }
    else if(dddd == "Friday")
    {
        ui->label_12->setText("星期五");
    }
    else if(dddd == "Saturday")
    {
        ui->label_12->setText("星期六");
    }
    else if(dddd == "Sunday")
    {
        ui->label_12->setText("星期日");
    }

/***************************************************************************************************************/
              //if(flagwidget == PipeixingbiaodingMenu)
    if(1)
               {
                  /****************************添加最小值，最大值，中间值，偏移量*******************************************************/
                  //2017.4.26
                      //ui->tableWidget_3->setItem(0,0,new QTableWidgetItem("99"));
                      ui->tableWidget_3->setItem(0,1,new QTableWidgetItem("10"));
                      ui->tableWidget_3->setItem(0,2,new QTableWidgetItem("11"));
                      ui->tableWidget_3->setItem(0,3,new QTableWidgetItem("12"));
                      ui->tableWidget_3->setItem(0,4,new QTableWidgetItem("13"));
                      ui->tableWidget_3->setItem(0,5,new QTableWidgetItem("14"));


                      //ui->tableWidget_3->setItem(1,0,new QTableWidgetItem(10));
                      ui->tableWidget_3->setItem(1,1,new QTableWidgetItem("15"));
                      ui->tableWidget_3->setItem(1,2,new QTableWidgetItem("16"));
                      ui->tableWidget_3->setItem(1,3,new QTableWidgetItem("17"));
                      ui->tableWidget_3->setItem(1,4,new QTableWidgetItem("18"));
                      ui->tableWidget_3->setItem(1,5,new QTableWidgetItem("19"));

                      //ui->tableWidget_3->setItem(2,0,new QTableWidgetItem(10));
                      ui->tableWidget_3->setItem(2,1,new QTableWidgetItem("20"));
                      ui->tableWidget_3->setItem(2,2,new QTableWidgetItem("21"));
                      ui->tableWidget_3->setItem(2,3,new QTableWidgetItem("22"));
                      ui->tableWidget_3->setItem(2,4,new QTableWidgetItem("23"));
                      ui->tableWidget_3->setItem(2,5,new QTableWidgetItem("24"));

                  /***************************************************************************************************************/
                    if((LCPiPeixingBiaoDing == 1)&&(FlagShouBing ==0))
                    {
                        ui->label_16->setText("请按F5开始标定手柄");
                    }
                    else if((LCPiPeixingBiaoDing == 1)&&(FlagShouBing ==1))
                    {
                        ui->label_16->setText("请推动手柄到最大位置等待");
                    }

                    //2017.4.28
                    else if((tempflagShoubing ==true)&&(LCPiPeixingBiaoDing ==1)&&(FlagShouBing ==1))
                    {
                        ui->label_16->setText("请推动手柄到最小位置等待");
                        qDebug()<<"jddddddddddddddddddddddddddddddddddddddddddddddddddddd ====  "<<LCPiPeixingBiaoDing<<endl;
                    }
                    else if((FlagNext == true)&&(FlagShouBing ==1)&&(LCPiPeixingBiaoDing ==1)&&(FlagShouBing ==1))
                    {
                       ui->label_16->setText("手柄标定完成");
                    }
                    //

                    else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==0))
                    {
                        ui->label_16->setText("按F5键开始标定行走泵杆");
                    }
                    else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==1))
                    {
                         ui->label_16->setText("请推动手柄到最大位置等待");
                    }
                    else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==0))
                    {
                        ui->label_16->setText("按F5键开始标定凹板间隙");
                    }
                    else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==1))
                    {
                        ui->label_16->setText("请按住凹板间隙增大调整开关并等待");
                    }

                    //偏移量
                    else if((LCPiPeixingBiaoDing == 4)||(LCPiPeixingBiaoDing == 5))
                    {
                        ui->label_16->setText(" ");
                    }

               }

    /**************************************************************************************************/

        if(flagwidget == SystemMenu)
        {

        }

#endif

}

//按键事件
void Widget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {

    case Qt::Key_F1:

         switch(flagwidget)
         {
            case xingZouWidget:

             flagvedio = 1;
             #ifdef CAMERAFLAG
             m_camerobj.Jobs_Monitor_Stop();      /*停止作业监控*/
             #endif

              flagwidget = MainMenu;
              ui->stackedWidget->setCurrentIndex(2);
              break;

             case MainMenu:
                 flagwidget = HelpMenu;
                 ui->stackedWidget->setCurrentIndex(7);
                 break;

         case UserMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case ClearMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case SystemMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case SwitchMachineMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case MachineModeMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case EngineSwitchMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case ZhujiFault:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case EngineFault:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

             //2017.4.6 暂时添加
         case HelpMenu:
             flagwidget = Shaomiao;
             ui->stackedWidget->setCurrentIndex(17);
             break;

         case BiaoDing:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case FazhibiaodingMenu:
         flagwidget = MainMenu;
         ui->stackedWidget->setCurrentIndex(2);
         break;

         case PipeixingbiaodingMenu:
         flagwidget = MainMenu;
         ui->stackedWidget->setCurrentIndex(2);
         break;

         case Getai:
         flagwidget = MainMenu;
         ui->stackedWidget->setCurrentIndex(2);
         break;

         default:
             break;

         }

         break;

    case Qt::Key_F2:

         switch(flagwidget)
         {
            case MainMenu:
             flagwidget = SystemMenu;
             ui->stackedWidget->setCurrentIndex(4);
             break;

             case SystemMenu:
              flagwidget = UserMenu;
              ui->stackedWidget->setCurrentIndex(1);
              ui->lineEdit->setFocus();
              //设置时间时显示当前时间
              ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

              break;

         case HelpMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

         case DiagnosisMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;


         case VideoSetupMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

             default:
                 break;
         }

         break;

    case Qt::Key_F3:

         flagvedio = 1;
         switch(flagwidget)
         {
             case MainMenu:
              flagwidget = DiagnosisMenu;
              ui->stackedWidget->setCurrentIndex(8);
              break;

             case DiagnosisMenu:
              flagwidget = ZhujiFault;
              ui->stackedWidget->setCurrentIndex(14);
              ui->tableWidget->setFocus();
              break;

              //进入视频界面
             case SystemMenu:
              flagwidget = VideoSetupMenu;
              ui->stackedWidget->setCurrentIndex(10);
              break;

             default:
             break;
         }
         break;


    case Qt::Key_F4:
        switch(flagwidget)
        {
            case MainMenu:
             flagwidget = ClearMenu;
             ui->stackedWidget->setCurrentIndex(3);
             ui->listWidget->setFocus();
             break;

            case SystemMenu:
            flagwidget = SwitchMachineMenu;
            ui->stackedWidget->setCurrentIndex(5);
            ui->listWidget_2->setFocus();
            break;

            case DiagnosisMenu:
            flagwidget = EngineFault;
            ui->stackedWidget->setCurrentIndex(13);
            ui->tableWidget_2->setFocus();
            break;

            case HelpMenu:
            flagwidget = EngineFault;
            ui->stackedWidget->setCurrentIndex(13);
            ui->tableWidget_2->setFocus();
            break;


            default:
            break;
        }
        break;

    case Qt::Key_F5:
        switch(flagwidget)
        {
            case MainMenu:  //静音
            flagbeep ^= 1;
            if(flagbeep)
            {
                ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(./img/jiemian/labano.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
            }
            else
            {
                ui->pushButton_2->setStyleSheet("QPushButton{border-image:url(./img/jiemian/labayes.png);background-repeat: background-xy;background-position: center;background-attachment: fixed;background-clip: padding}");
            }
             break;

             case SwitchMachineMenu: //机型选择菜单
                if(LCSwitchmatchineRow == 1)//整机型号
                {
                  flagwidget = MachineModeMenu;
                  ui->stackedWidget->setCurrentIndex(6);
                }
                else if(LCSwitchmatchineRow == 2) //发动机品牌
                {
                    flagwidget = EngineSwitchMenu;
                    ui->stackedWidget->setCurrentIndex(9);
                }
              break;

                //机器型号
            case MachineModeMenu:
            {

               if((LCMachineModeMenu == 1)&&(LCBoolMachineModenu == true))
                {
                    flagmatchion = YZT_10;
                }
                else if((LCMachineModeMenu == 2)&&(LCBoolMachineModenu == true))
                {
                    flagmatchion = YZB_4_5_7_8;
                }
                else if((LCMachineModeMenu == 3)&&(LCBoolMachineModenu == true))
                {
                    flagmatchion = YZB_3A_B;
                }

               //
               //2017.4.2
               else if((LCMachineModeMenu == 4)&&(LCBoolMachineModenu == true))
               {
                   flagmatchion = JZ_3600;
               }
               //
               //ui->listwidget4
               else if((LCMachineModeMenu == 1)&&(LCBoolMachineModenu == false))
               {
                   flagmatchion = YZBT_5;
                   qDebug()<<"Hao hao xue xi ... tian tian .. . xiang shang ....."<<endl;
               }
               else if((LCMachineModeMenu == 2)&&(LCBoolMachineModenu == false))
               {
                   flagmatchion = YZT_5;
               }
               else if((LCMachineModeMenu == 3)&&(LCBoolMachineModenu == false))
               {
                   flagmatchion = YZT_10_1;
               }
               else if((LCMachineModeMenu == 4)&&(LCBoolMachineModenu == false))
               {
                   flagmatchion = S3000;
               }


                qDebug()<<"LCMachineModeMenuLCMachineModeMenuLCMachineModeMenu ======"<<LCMachineModeMenu<<endl;

                //存储数据
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
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;
               query.prepare("update config set engineswitch = :engineswitch");//cjswitch = :cjswitch,,langswitch = :langswitch
               //query.bindValue(":cjswitch",77);
               query.bindValue(":engineswitch", flagmatchion);
              // query.bindValue(":langswitch", 55);
               query.exec();

             query.exec("select cjswitch, engineswitch, langswitch from config");
             while (query.next())
             {
                //qDebug()<<"matchine.......  ==  "<<query.value(0).toInt()<<endl;
             }
             query.exec(QObject::tr("drop config"));

          }
         break;


            //发动机厂家
            case EngineSwitchMenu:
            {
                if(LCEngineSwitchMenu == 0)
                {
                    CJSwitch = YuCai;
                }
                else if(LCEngineSwitchMenu == 1)
                {
                    CJSwitch = WeiCai;
                }
                else if(LCEngineSwitchMenu == 2)
                {
                    CJSwitch = XiCai;
                }
                else if(LCEngineSwitchMenu == 3)
                {
                    CJSwitch = HangFa;
                }
                else if(LCEngineSwitchMenu == 4)
                {
                    CJSwitch = DongfangHong;
                }
                //存储数据
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
                   qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
               }
               QSqlQuery query;
               query.prepare("update config set cjswitch = :cjswitch");//,engineswitch = :engineswitch,langswitch = :langswitch
               query.bindValue(":cjswitch",CJSwitch);
               //query.bindValue(":engineswitch", flagmatchion);
              // query.bindValue(":langswitch", 55);
               query.exec();

             query.exec("select cjswitch, engineswitch, langswitch from config");
             while (query.next())
             {
                qDebug()<<"matchine.......  ==  "<<query.value(0).toInt()<<endl;
             }
             query.exec(QObject::tr("drop config"));
            }
            break;

//            //故障码清除
//            case DiagnosisMenu:
//            break;

        case DiagnosisMenu:
        {
            //flagGzmclear = true;

            //存储数据
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
               qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
           }
           QSqlQuery query;
           query.prepare("delete from fdjgz");//
           query.exec();
           qDebug()<<"kdddddddddddddddddddddddddddddddddddddddddddddddddddddd"<<endl;
           query.exec(QObject::tr("drop fdjgz"));
        }
        break;

            //系统标定
//            case :
//            flagwidget = PipeixingbiaodingMenu;
//            ui->stackedWidget->setCurrentIndex(11);
//            break;

            //2017.4.7
            //系统标定
            case SystemMenu:
            {
                flagwidget = BiaoDing;
                ui->stackedWidget->setCurrentIndex(16);
                ui->listWidget_6->setFocus();
            }
            break;

            //xitongbiaoding 确认
            case BiaoDing:
            if(LCBiaoDingRow == 1)//匹配性标定
            {
              flagwidget = PipeixingbiaodingMenu;
              ui->stackedWidget->setCurrentIndex(11);

              ui->tableWidget_3->setFocus();
            }
            else if(LCBiaoDingRow == 2) //阀值标定
            {
                flagwidget = FazhibiaodingMenu;
                ui->stackedWidget->setCurrentIndex(12);
            }
            //2017.5.4
            else if(LCBiaoDingRow == 3) //割台设定
            {
                qDebug()<<"GETATI)))))))))))))))))))))))))))))))))))))))))))))))";
                flagwidget = Getai;
                ui->stackedWidget->setCurrentIndex(18);

                //2017.5.4
                ui->listWidget_7->setFocus();
            }
          break;


            /*********************************************************/
            //确定键
            case UserMenu:
            timeSetOK = true;
            break;
            /*********************************************************/


/**************************************************************************************************/
        case PipeixingbiaodingMenu:
           {
                if((LCPiPeixingBiaoDing == 1)&&(FlagShouBing ==0))
                {
                    FlagShouBing = 1;
                    //ui->label_16->setText("请推动手柄到最大位置等待");
                    FlagXingzouBeng = 0;
                    FlagAoBanjianxi = 0;
                }
                else if((LCPiPeixingBiaoDing == 2)&&(FlagXingzouBeng ==0))
                {
                    FlagXingzouBeng = 1;
                    //ui->label_16->setText("请推动手柄到最大位置等待");
                     FlagShouBing = 0;
                      FlagAoBanjianxi = 0;
                }
                else if((LCPiPeixingBiaoDing == 3)&&(FlagAoBanjianxi ==0))
                {
                    FlagAoBanjianxi = 1;
                    //ui->label_16->setText("请按住凹板间隙增大调整开关并等待");
                     FlagShouBing = 0;
                     FlagXingzouBeng = 0;
                }

                //2017.4.28

                //手柄标定数据库创建

                    //static unsigned char nn = 1;
                    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                    QSqlDatabase db;
                    if(QSqlDatabase::contains("qt_sql_default_connection"))
                      db = QSqlDatabase::database("qt_sql_default_connection");
                    else
                      db = QSqlDatabase::addDatabase("QSQLITE");

                   db.setDatabaseName("jy.db");
                   if (!db.open())
                   {
                       qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                   }
                   QSqlQuery query;
                   #if 0
                   bool ok = query.exec("create table ShouBingBD(TrueValue INTEGER,SmallValue INTEGER,MiddleValue INTEGER,BigValue INTEGER,OffSetValue INTEGER)");
                   if (ok)
                   {
                       qDebug()<<"ceate table partition success"<<endl;
                   }
                   else
                   {
                       qDebug()<<"ceate table partition failed"<<endl;
                   }
                   #endif

                   //query.prepare("INSERT INTO ShouBingBD(TrueValue, SmallValue, MiddleValue,BigValue,OffSetValue) VALUES (:TrueValue, :SmallValue,:MiddleValue, :BigValue,:OffSetValue)");
                   query.prepare("update ShouBingBD set TrueValue = :TrueValue,SmallValue = :SmallValue,MiddleValue = :MiddleValue,BigValue = :BigValue,OffSetValue = :OffSetValue");//where

                   query.bindValue(":TrueValue",55);
                   query.bindValue(":SmallValue", 55);
                   query.bindValue(":MiddleValue", 55);
                   query.bindValue(":BigValue", 55);
                   query.bindValue(":OffSetValue", 55);
                   query.exec();


                   query.bindValue(":TrueValue",55);
                   query.bindValue(":SmallValue", 55);
                   query.bindValue(":MiddleValue", 55);
                   query.bindValue(":BigValue", 55);
                   query.bindValue(":OffSetValue", 55);
                   query.exec();

                 query.exec("select TrueValue, SmallValue,MiddleValue,BigValue,OffSetValue from ShouBingBDS");
                 while (query.next())
                 {

                    qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();

                 }

                  query.exec(QObject::tr("drop ShouBingBDS"));


           }
            break;
/**************************************************************************************************/
//阀值标定
           case FazhibiaodingMenu:
            {
            //2017.4.22    //更新阀值设定数据库
            #if 1

             if(FaZhiReadOK)
             {

              QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
              QSqlDatabase db;
              if(QSqlDatabase::contains("qt_sql_default_connection"))
                db = QSqlDatabase::database("qt_sql_default_connection");
              else
                db = QSqlDatabase::addDatabase("QSQLITE");

             db.setDatabaseName("jy.db");
             if (!db.open())
             {
                 qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
             }
             QSqlQuery query;
             #if 0
             bool ok = query.exec("create table FaZhiBingBD(ZLH INTEGER,XLLH INTEGER,GQLH INTEGER,LmdGTZS INTEGER,LmdFengJi INTEGER,LmdJiaoLong INTEGER,LmdGuoQiao INTEGER)");
             if (ok)
             {
                 qDebug()<<"ceate table partition success"<<endl;
             }
             else
             {
                 qDebug()<<"ceate table partition failed"<<endl;
             }
             #endif

        #if 1
             //query.prepare("INSERT INTO FaZhiBingBD(ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao) VALUES (:ZLH, :XLLH, :GQLH, :LmdGQZS, :LmdFengJi, :LmdJiaoLong, :LmdGuoQiao)");
             query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGTZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where

             query.bindValue(":ZLH",zlh);
             query.bindValue(":XLLH", xllh);
             query.bindValue(":GQLH", gqlh);
             query.bindValue(":LmdGTZS", gtzs);
             query.bindValue(":LmdFengJi", fjzs);
             query.bindValue(":LmdJiaoLong", jlzs);
             query.bindValue(":LmdGuoQiao", gqzs);
             query.exec();

        #endif

             #if 0
            query.exec("select ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao from FaZhiBingBD");
            while (query.next())
            {

              qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
              tempzlh = query.value(0).toInt();
              tempxllh = query.value(1).toInt();
              tempgqlh = query.value(2).toInt();
              tempgtzs = query.value(3).toInt();
              tempfjzs = query.value(4).toInt();
              tempjlzs = query.value(5).toInt();
              tempgqzs = query.value(6).toInt();


            }
            #endif
            query.exec(QObject::tr("drop FaZhiBingBD"));

//            zlh  = tempzlh;
//            xllh = tempxllh;
//            gqlh = tempgqlh;
//            gtzs = tempgtzs;
//            fjzs = tempfjzs;
//            jlzs = tempjlzs;
//            gqzs = tempgqzs;

//            FaZhiReadOK = false;
        }
            #endif
            }
            break;


/**************************************************************************************************/

            //2017.4.10
            case HelpMenu:
            flagwidget = JiQiXinXi;
            ui->stackedWidget->setCurrentIndex(15);
            break;



            default:
            break;
        }
        break;

    case Qt::Key_F6:
        switch(flagwidget)
        {
            case MainMenu://确认键 返回到行走工作界面
             flagwidget = xingZouWidget;
             ui->stackedWidget->setCurrentIndex(0);
             break;

            case UserMenu:
             flagwidget = SystemMenu;
             ui->stackedWidget->setCurrentIndex(4);
             break;

             case SwitchMachineMenu:
              flagwidget = SystemMenu;
              ui->stackedWidget->setCurrentIndex(4);
              break;

            case SystemMenu:
             flagwidget = MainMenu;
             ui->stackedWidget->setCurrentIndex(2);
             break;

            case EngineSwitchMenu:
                flagwidget =  SwitchMachineMenu;
                ui->stackedWidget->setCurrentIndex(5);
                break;

            case MachineModeMenu:
                flagwidget = SwitchMachineMenu;
                ui->stackedWidget->setCurrentIndex(5);
            break;

        case ZhujiFault:
            flagwidget = DiagnosisMenu;
            ui->stackedWidget->setCurrentIndex(8);
            break;

            case EngineFault:
            flagwidget = DiagnosisMenu;
            ui->stackedWidget->setCurrentIndex(8);
            break;

            //视频界面返回到系统设置界面
            case VideoSetupMenu:
            flagwidget = SystemMenu;
            ui->stackedWidget->setCurrentIndex(4);
            break;

            case DiagnosisMenu:
            flagwidget = MainMenu;
            ui->stackedWidget->setCurrentIndex(2);
            break;

            case ClearMenu:
            flagwidget = MainMenu;
            ui->stackedWidget->setCurrentIndex(2);
            break;

//        case PipeixingbiaodingMenu:
//            flagwidget = MainMenu;
//            ui->stackedWidget->setCurrentIndex(2);
//            break;

            case Shaomiao:
            flagwidget = HelpMenu;
            ui->stackedWidget->setCurrentIndex(7);
            break;

            case FazhibiaodingMenu:
            flagwidget = BiaoDing;
            ui->stackedWidget->setCurrentIndex(16);
            break;

            case PipeixingbiaodingMenu:
            flagwidget = BiaoDing;
            ui->stackedWidget->setCurrentIndex(16);
            break;

            case BiaoDing:
            flagwidget = SystemMenu;
            ui->stackedWidget->setCurrentIndex(4);
            break;

            //2017.4.10
            case JiQiXinXi:
            flagwidget = HelpMenu;
            ui->stackedWidget->setCurrentIndex(7);
            break;

            //2017.5.4
            case Getai:
            flagwidget = BiaoDing;
            ui->stackedWidget->setCurrentIndex(16);
            break;

            default:
            break;
        }
        break;

    }
    flagaction = true;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{

    if((watched == ui->label_2 && (event->type() == QEvent::Paint)))//||(watched == ui->label_5 && event->type() == QEvent::Paint))
    {
        magicTime();
    }
    else if((watched == ui->label_5 && (event->type() == QEvent::Paint)))
    {
        fun2();
    }//主界面选择
    else if((watched == ui->lineEdit)||(watched == ui->lineEdit_2)||(watched == ui->dateTimeEdit)||(watched == ui->progressBar))
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    bool f1 = ui->lineEdit->hasFocus();
                    bool f2 = ui->lineEdit_2->hasFocus();
                    bool f3 = ui->dateTimeEdit->hasFocus();
                    bool f4 = ui->progressBar->hasFocus();

                    if(f1)
                    {
                    focusNextChild();
                    ui->lineEdit_2->setFocus();
                    }
                    if(f2)
                    {
                        focusNextChild();
                        ui->dateTimeEdit->setFocus();
                    }
                    if(f3)
                    {
                        focuseflag = ui->dateTimeEdit->currentSectionIndex();
                        ui->dateTimeEdit->setCurrentSectionIndex(++focuseflag);
                        ui->dateTimeEdit->setFocus();
                        qDebug()<<"focuseflag == "<<focuseflag<<endl;
                        if(focuseflag>=6)
                        {
                            focusNextChild();
                            ui->progressBar->setFocus();
                        }
                    }
                    if(f4)
                    {
                        focusNextChild();
                        ui->lineEdit->setFocus();
                    }

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F4)
                {
                    bool ff3 = ui->dateTimeEdit->hasFocus();
                    bool ff4 = ui->progressBar->hasFocus();
                    if(ff3)
                    ui->dateTimeEdit->stepBy(1);
                    else if (ff4)
                        ui->progressBar->setValue(++valueprogressbar);

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F3)
                {
                    bool ff3 = ui->dateTimeEdit->hasFocus();
                    bool ff4 = ui->progressBar->hasFocus();
                    if(ff3)
                    ui->dateTimeEdit->stepBy(-1);
                    else if (ff4)
                        ui->progressBar->setValue(--valueprogressbar);

                    flagaction = true;
                    return true;
                }

            }
        }
    } //clearmenu F2键过滤
    else if(watched == ui->listWidget)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCClearMenuRow>2)
                    {
                        LCClearMenuRow = 0;
                        ui->listWidget->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(2)->setTextColor(Qt::black);
                    }

                    ui->listWidget->item(LCClearMenuRow)->setBackgroundColor(Qt::yellow);
                    ui->listWidget->item(LCClearMenuRow)->setTextColor(Qt::red);

                    if(LCClearMenuRow == 1)
                    {
                        ui->listWidget->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(0)->setTextColor(Qt::black);
                    }
                    else if(LCClearMenuRow == 2)
                    {

                        ui->listWidget->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(1)->setTextColor(Qt::black);
                        ui->listWidget->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget->item(0)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCClearMenuRow++;

                }

            }
        }
    }// end of else if(watched == ui->listWidget)
    //机型选择
    else if(watched == ui->listWidget_2)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCSwitchmatchineRow>1)
                    {
                        LCSwitchmatchineRow = 0;
                        ui->listWidget_2->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_2->item(1)->setTextColor(Qt::black);
                    }

                    ui->listWidget_2->item(LCSwitchmatchineRow)->setBackgroundColor(Qt::yellow);
                    ui->listWidget_2->item(LCSwitchmatchineRow)->setTextColor(Qt::red);

                    if(LCSwitchmatchineRow == 1)
                    {
                        ui->listWidget_2->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_2->item(0)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCSwitchmatchineRow++;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_2)

    //机器型号选择
    else if(watched == ui->listWidget_3)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    LCBoolMachineModenu = true;

                    if(LCMachineModeMenu>5)
                    {
                        LCMachineModeMenu = 0;
                        ui->listWidget_3->item(5)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(5)->setTextColor(Qt::black);

                        ui->listWidget_4->setFocus();
                        ui->listWidget_4->item(LCMachineModeMenu)->setBackgroundColor(Qt::yellow);
                        ui->listWidget_4->item(LCMachineModeMenu)->setTextColor(Qt::red);
                        LCBoolMachineModenu = false;
                    }

                    else
                    {
                        ui->listWidget_3->item(LCMachineModeMenu)->setBackgroundColor(Qt::yellow);
                        ui->listWidget_3->item(LCMachineModeMenu)->setTextColor(Qt::red);
                    }

                    if(LCMachineModeMenu == 1)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 2)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 3)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                        ui->listWidget_3->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(2)->setTextColor(Qt::black);
                    }

                    if(LCMachineModeMenu == 4)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                        ui->listWidget_3->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(2)->setTextColor(Qt::black);
                        ui->listWidget_3->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(3)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 5)
                    {
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(0)->setTextColor(Qt::black);
                        ui->listWidget_3->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(1)->setTextColor(Qt::black);
                        ui->listWidget_3->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(2)->setTextColor(Qt::black);
                        ui->listWidget_3->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(3)->setTextColor(Qt::black);
                        ui->listWidget_3->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_3->item(4)->setTextColor(Qt::black);
                    }
                    flagaction = true;
                    LCMachineModeMenu++;

                }
            }
        }
    }//end of else if(watched == ui->listWidget_3)

    //机器型号选择
    else if(watched == ui->listWidget_4)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCMachineModeMenu>5)
                    {

                        LCMachineModeMenu = 0;
                        ui->listWidget_4->item(5)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(5)->setTextColor(Qt::black);

                        ui->listWidget_3->setFocus();
                        ui->listWidget_3->item(0)->setBackgroundColor(Qt::yellow);
                        ui->listWidget_3->item(0)->setTextColor(Qt::red);
                        LCBoolMachineModenu = true;
                    }
                    else
                    {
                        ui->listWidget_4->item(LCMachineModeMenu)->setBackgroundColor(Qt::yellow);
                        ui->listWidget_4->item(LCMachineModeMenu)->setTextColor(Qt::red);
                    }

                    if(LCMachineModeMenu == 1)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 2)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 3)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                        ui->listWidget_4->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(2)->setTextColor(Qt::black);
                    }

                    if(LCMachineModeMenu == 4)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                        ui->listWidget_4->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(2)->setTextColor(Qt::black);
                        ui->listWidget_4->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(3)->setTextColor(Qt::black);
                    }
                    if(LCMachineModeMenu == 5)
                    {
                        ui->listWidget_4->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(0)->setTextColor(Qt::black);
                        ui->listWidget_4->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(1)->setTextColor(Qt::black);
                        ui->listWidget_4->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(2)->setTextColor(Qt::black);
                        ui->listWidget_4->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(3)->setTextColor(Qt::black);
                        ui->listWidget_4->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_4->item(4)->setTextColor(Qt::black);
                    }
                    flagaction = true;
                    LCMachineModeMenu++;
                }
            }
        }
    }//end of else if(watched == ui->listWidget_4)

    //机型选择
    else if(watched == ui->listWidget_5)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    if(LCEngineSwitchMenu>4)
                    {
                        LCEngineSwitchMenu = 0;
                        ui->listWidget_5->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(4)->setTextColor(Qt::black);
                    }

                    ui->listWidget_5->item(LCEngineSwitchMenu)->setBackgroundColor(Qt::yellow);
                    ui->listWidget_5->item(LCEngineSwitchMenu)->setTextColor(Qt::red);

                    if(LCEngineSwitchMenu == 1)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                    }
                    if(LCEngineSwitchMenu == 2)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                        ui->listWidget_5->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(1)->setTextColor(Qt::black);
                    }
                    if(LCEngineSwitchMenu == 3)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                        ui->listWidget_5->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(1)->setTextColor(Qt::black);
                        ui->listWidget_5->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(2)->setTextColor(Qt::black);
                    }

                    if(LCEngineSwitchMenu == 4)
                    {
                        ui->listWidget_5->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(0)->setTextColor(Qt::black);
                        ui->listWidget_5->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(1)->setTextColor(Qt::black);
                        ui->listWidget_5->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(2)->setTextColor(Qt::black);
                        ui->listWidget_5->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_5->item(3)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCEngineSwitchMenu++;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_2)

    //主机故障查询
    else if(watched == ui->tableWidget)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

                    if(LCZhujiFault>=10)
                    {
                        LCZhujiFault = 0;
                       // ui->tableWidget->setStyleSheet("background-color:red;");//selection-
                        ui->tableWidget->hasFocus();
                        ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

                    }
                    else
                    {
                        ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                    }

                    flagaction = true;
                    LCZhujiFault++;

                }
                //向下键
                else if (key_event->key() == Qt::Key_F3)
                {
                    LCZhujiFault--;
                    if(LCZhujiFault <= 0)
                    {
                        LCZhujiFault = 0;
                    }
                    ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }//向上键
                else if (key_event->key() == Qt::Key_F4)
                {
                    LCZhujiFault++;

                    if(LCZhujiFault >= 10)
                    {
                        LCZhujiFault = 0;
                    }

                    ui->tableWidget->setCurrentCell(LCZhujiFault,0);
                    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }

            }
        }
    }//end of  else if(watched == ui->tableWidget)

    //发动机故障查询
    else if(watched == ui->tableWidget_2)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

                    if(LCEngineFault>=10)
                    {
                        LCEngineFault = 0;
                       // ui->tableWidget->setStyleSheet("background-color:red;");//selection-
                        ui->tableWidget_2->hasFocus();
                        ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                        ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    }
                    else
                    {
                        ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                        ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    }

                    flagaction = true;
                    LCEngineFault++;

                }
                //向下键
                else if (key_event->key() == Qt::Key_F3)
                {
                    LCEngineFault--;
                    if(LCEngineFault <= 0)
                    {
                        LCEngineFault = 0;
                    }
                    ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }//向上键
                else if (key_event->key() == Qt::Key_F4)
                {
                    LCEngineFault++;

                    if(LCEngineFault >= 10)
                    {
                        LCEngineFault = 0;
                    }

                    ui->tableWidget_2->setCurrentCell(LCEngineFault,0);
                    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }

            }
        }
    }//end of  else if(watched == ui->tableWidget_2)

    //2017.4.6
    //阀值标定
    else if((watched == ui->lineEdit_3)||(watched ==ui->lineEdit_4)||(watched == ui->lineEdit_5)||(watched == ui->lineEdit_6)||(watched == ui->lineEdit_7)||(watched == ui->lineEdit_8)||(watched == ui->lineEdit_9)||(watched == ui->lineEdit_10))
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                    bool m1 = ui->lineEdit_3->hasFocus();
                    bool m2 = ui->lineEdit_4->hasFocus();
                    bool m3 = ui->lineEdit_5->hasFocus();
                    bool m4 = ui->lineEdit_6->hasFocus();
                    bool m5 = ui->lineEdit_7->hasFocus();
                    bool m6 = ui->lineEdit_8->hasFocus();
                    bool m7 = ui->lineEdit_9->hasFocus();
                    bool m8 = ui->lineEdit_10->hasFocus();

                    if(m1)
                    {
                    focusNextChild();
                    ui->lineEdit_4->setFocus();
                    }
                    if(m2)
                    {
                        focusNextChild();
                        ui->lineEdit_5->setFocus();
                    }
                    if(m3)
                    {
                        focusNextChild();
                        ui->lineEdit_6->setFocus();
                    }
                    if(m4)
                    {
                        focusNextChild();
                        ui->lineEdit_7->setFocus();
                    }
                    if(m5)
                    {
                        focusNextChild();
                        ui->lineEdit_8->setFocus();
                    }
                    if(m6)
                    {
                        focusNextChild();
                        ui->lineEdit_9->setFocus();
                    }
                    if(m7)
                    {
                        focusNextChild();
                        ui->lineEdit_10->setFocus();
                    }
                    if(m8)
                    {
                        focusNextChild();
                        ui->lineEdit_3->setFocus();
                    }

                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F4)
                {
                    bool mm1 = ui->lineEdit_3->hasFocus();
                    bool mm2 = ui->lineEdit_4->hasFocus();
                    bool mm3 = ui->lineEdit_5->hasFocus();
                    bool mm4 = ui->lineEdit_6->hasFocus();
                    bool mm5 = ui->lineEdit_7->hasFocus();
                    bool mm6 = ui->lineEdit_8->hasFocus();
                    bool mm7 = ui->lineEdit_9->hasFocus();

                    if(mm1)
                    {
                        zlh++;
                        QString strzlh = QString("%1").arg(zlh);
                        ui->lineEdit_3->setText(strzlh);
                    }
                    if(mm2)
                    {
                        gtzs++;
                        QString strgtzs = QString("%1").arg(gtzs);
                        ui->lineEdit_4->setText(strgtzs);
                    }
                    if(mm3)
                    {
                        xllh++;
                        QString strxllh = QString("%1").arg(xllh);
                        ui->lineEdit_5->setText(strxllh);
                    }
                    if(mm4)
                    {
                        fjzs++;
                        QString strfjzs = QString("%1").arg(fjzs);
                        ui->lineEdit_6->setText(strfjzs);
                    }
                    if(mm5)
                    {
                        gqlh++;
                        QString strgqlh = QString("%1").arg(gqlh);
                        ui->lineEdit_7->setText(strgqlh);
                    }
                    if(mm6)
                    {
                        jlzs++;
                        QString strjlzs = QString("%1").arg(jlzs);
                        ui->lineEdit_8->setText(strjlzs);
                    }
                    if(mm7)
                    {
                        gqzs++;
                        QString strgqzs = QString("%1").arg(gqzs);
                        ui->lineEdit_9->setText(strgqzs);
                    }


                    flagaction = true;
                    return true;
                }
                else if (key_event->key() == Qt::Key_F3)
                {
                    bool mm1 = ui->lineEdit_3->hasFocus();
                    bool mm2 = ui->lineEdit_4->hasFocus();
                    bool mm3 = ui->lineEdit_5->hasFocus();
                    bool mm4 = ui->lineEdit_6->hasFocus();
                    bool mm5 = ui->lineEdit_7->hasFocus();
                    bool mm6 = ui->lineEdit_8->hasFocus();
                    bool mm7 = ui->lineEdit_9->hasFocus();

                    if(mm1)
                    {
                        zlh--;
                        QString strzlh = QString("%1").arg(zlh);
                        ui->lineEdit_3->setText(strzlh);
                    }
                    if(mm2)
                    {
                        gtzs--;
                        QString strgtzs = QString("%1").arg(gtzs);
                        ui->lineEdit_4->setText(strgtzs);
                    }
                    if(mm3)
                    {
                        xllh--;
                        QString strxllh = QString("%1").arg(xllh);
                        ui->lineEdit_5->setText(strxllh);
                    }
                    if(mm4)
                    {
                        fjzs--;
                        QString strfjzs = QString("%1").arg(fjzs);
                        ui->lineEdit_6->setText(strfjzs);
                    }
                    if(mm5)
                    {
                        gqlh--;
                        QString strgqlh = QString("%1").arg(gqlh);
                        ui->lineEdit_7->setText(strgqlh);
                    }
                    if(mm6)
                    {
                        jlzs--;
                        QString strjlzs = QString("%1").arg(jlzs);
                        ui->lineEdit_8->setText(strjlzs);
                    }
                    if(mm7)
                    {
                        gqzs--;
                        QString strgqzs = QString("%1").arg(gqzs);
                        ui->lineEdit_9->setText(strgqzs);
                    }

                    flagaction = true;
                    return true;
                }
                else if ((key_event->key() == Qt::Key_F5)&&(watched == ui->lineEdit_10))
                {
                    bool mm8 = ui->lineEdit_10->hasFocus();
                    if(mm8)
                    {

                        qDebug()<<"kddddddddddddddddddddddddddddddddddddddddddddddddd"<<endl;
                    }

                    zlh  = 80;
                    xllh = 80;
                    gqlh = 80;
                    gtzs = 80;
                    fjzs = 80;
                    jlzs = 80;
                    gqzs = 80;

                    //2017.4.22    //更新阀值设定数据库

                      QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                      QSqlDatabase db;
                      if(QSqlDatabase::contains("qt_sql_default_connection"))
                        db = QSqlDatabase::database("qt_sql_default_connection");
                      else
                        db = QSqlDatabase::addDatabase("QSQLITE");

                     db.setDatabaseName("jy.db");
                     if (!db.open())
                     {
                         qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                     }
                     QSqlQuery query;

                     query.prepare("update FaZhiBingBD set ZLH = :ZLH,XLLH = :XLLH,GQLH = :GQLH,LmdGTZS = :LmdGQZS,LmdFengJi = :LmdFengJi,LmdJiaoLong = :LmdJiaoLong,LmdGuoQiao = :LmdGuoQiao");//where
                     query.bindValue(":ZLH",zlh);
                     query.bindValue(":XLLH", xllh);
                     query.bindValue(":GQLH", gqlh);
                     query.bindValue(":LmdGTZS", gtzs);
                     query.bindValue(":LmdFengJi", fjzs);
                     query.bindValue(":LmdJiaoLong", jlzs);
                     query.bindValue(":LmdGuoQiao", gqzs);
                     query.exec();

                    query.exec(QObject::tr("drop FaZhiBingBD"));

                    ui->lineEdit_3->setText("80");
                    ui->lineEdit_4->setText("80");
                    ui->lineEdit_5->setText("80");
                    ui->lineEdit_6->setText("80");
                    ui->lineEdit_7->setText("80");
                    ui->lineEdit_8->setText("80");
                    ui->lineEdit_9->setText("80");

                    flagaction = true;
                    return true;
                }
            }
        }

    } //clearmenu F2键过滤

    //标定菜单
    else if(watched == ui->listWidget_6)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {
                     qDebug()<<"Biaodingcaidan"<<endl;
                    if(LCBiaoDingRow>2)
                    {
                        LCBiaoDingRow = 0;
                        ui->listWidget_6->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_6->item(2)->setTextColor(Qt::black);
                    }


                    ui->listWidget_6->item(LCBiaoDingRow)->setBackgroundColor(Qt::blue);
                    ui->listWidget_6->item(LCBiaoDingRow)->setTextColor(Qt::red);

                    if(LCBiaoDingRow == 1)
                    {
                        ui->listWidget_6->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_6->item(0)->setTextColor(Qt::black);
                    }
                    if(LCBiaoDingRow == 2)
                    {
                        ui->listWidget_6->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_6->item(1)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCBiaoDingRow++;
                    //return true;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_6)

    //2017.5.4
    //割台参数设置
    else if((watched == ui->listWidget_7)||(watched == ui->lineEdit_12)||(watched == ui->lineEdit_13)||(watched == ui->lineEdit_14)||(watched == ui->lineEdit_15))
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

//                    bool GetaiFocus1 = ui->listWidget_7->hasFocus();
//                    bool GetaiFocus2 = ui->lineEdit_12->hasFocus();
//                    bool GetaiFocus3 = ui->lineEdit_13->hasFocus();
//                    bool GetaiFocus4 = ui->lineEdit_14->hasFocus();
//                    bool GetaiFocus5 = ui->lineEdit_15->hasFocus();

                    if(LCGetaiSetup>7)
                    {

                        //LCGetaiSetup = 0;
                        ui->listWidget_7->item(7)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(7)->setTextColor(Qt::black);

                       if(LCGetaiSetup == 8)
                       {
                           ui->lineEdit_12->setFocus();
                           //focusNextChild();
                           ui->lineEdit_12->hasFocus();
                       }
                       else if(LCGetaiSetup == 9)
                       {
                           ui->lineEdit_13->setFocus();
                           //focusNextChild();
                           ui->lineEdit_13->hasFocus();
                       }
                       else if(LCGetaiSetup == 10)
                       {
                           ui->lineEdit_14->setFocus();
                           //focusNextChild();
                           ui->lineEdit_14->hasFocus();
                       }
                       else if(LCGetaiSetup == 11)
                       {
                           ui->lineEdit_15->setFocus();

                           ui->lineEdit_15->hasFocus();
                           //focusNextChild();
                           //LCGetaiSetup = 0;
                          // ui->listWidget_7->setFocus();

                       }
                       else if(LCGetaiSetup == 12)
                       {
                           LCGetaiSetup = 0;
                       }

                    }

                    if(LCGetaiSetup<=7)
                    {
                        ui->listWidget_7->item(LCGetaiSetup)->setBackgroundColor(Qt::yellow);
                        ui->listWidget_7->item(LCGetaiSetup)->setTextColor(Qt::red);
                    }

                    if(LCGetaiSetup == 1)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                    }
                    if(LCGetaiSetup == 2)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                        ui->listWidget_7->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(1)->setTextColor(Qt::black);
                    }
                    if(LCGetaiSetup == 3)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                        ui->listWidget_7->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(1)->setTextColor(Qt::black);
                        ui->listWidget_7->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(2)->setTextColor(Qt::black);
                    }

                    if(LCGetaiSetup == 4)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                        ui->listWidget_7->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(1)->setTextColor(Qt::black);
                        ui->listWidget_7->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(2)->setTextColor(Qt::black);
                        ui->listWidget_7->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(3)->setTextColor(Qt::black);
                    }
                    if(LCGetaiSetup == 5)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                        ui->listWidget_7->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(1)->setTextColor(Qt::black);
                        ui->listWidget_7->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(2)->setTextColor(Qt::black);
                        ui->listWidget_7->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(3)->setTextColor(Qt::black);
                        ui->listWidget_7->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(4)->setTextColor(Qt::black);
                    }
                    if(LCGetaiSetup == 6)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                        ui->listWidget_7->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(1)->setTextColor(Qt::black);
                        ui->listWidget_7->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(2)->setTextColor(Qt::black);
                        ui->listWidget_7->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(3)->setTextColor(Qt::black);
                        ui->listWidget_7->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(4)->setTextColor(Qt::black);
                        ui->listWidget_7->item(5)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(5)->setTextColor(Qt::black);

                    }
                    if(LCGetaiSetup == 7)
                    {
                        ui->listWidget_7->item(0)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(0)->setTextColor(Qt::black);
                        ui->listWidget_7->item(1)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(1)->setTextColor(Qt::black);
                        ui->listWidget_7->item(2)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(2)->setTextColor(Qt::black);
                        ui->listWidget_7->item(3)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(3)->setTextColor(Qt::black);
                        ui->listWidget_7->item(4)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(4)->setTextColor(Qt::black);
                        ui->listWidget_7->item(5)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(5)->setTextColor(Qt::black);
                        ui->listWidget_7->item(6)->setBackgroundColor(Qt::transparent);
                        ui->listWidget_7->item(6)->setTextColor(Qt::black);
                    }

                    flagaction = true;
                    LCGetaiSetup++;
                }

                //2017.5.4
                else if (key_event->key() == Qt::Key_F3)
                {
                    if(LCGetaiSetup == 9)
                    {
                        GeFuWidth--;
                        QString strGeFuWidth = QString("%1").arg(GeFuWidth);
                        ui->lineEdit_12->setText(strGeFuWidth);
                    }
                    if(LCGetaiSetup == 10)
                    {
                         Zaihexishu--;
                        QString strZaihexishu = QString("%1").arg(Zaihexishu);
                        ui->lineEdit_13->setText(strZaihexishu);
                    }
                    if(LCGetaiSetup == 11)
                    {
                        Autospeed--;
                        QString strAutospeed = QString("%1").arg(Autospeed);
                        ui->lineEdit_14->setText(strAutospeed);
                    }
                    flagaction = true;
                }
                else if (key_event->key() == Qt::Key_F4)
                {
                    if(LCGetaiSetup == 9)
                    {
                        GeFuWidth++;
                        QString strGeFuWidth = QString("%1").arg(GeFuWidth);
                        ui->lineEdit_12->setText(strGeFuWidth);
                    }
                    if(LCGetaiSetup == 10)
                    {
                         Zaihexishu++;
                        QString strZaihexishu = QString("%1").arg(Zaihexishu);
                        ui->lineEdit_13->setText(strZaihexishu);
                    }
                    if(LCGetaiSetup == 11)
                    {
                        Autospeed++;
                        QString strAutospeed = QString("%1").arg(Autospeed);
                        ui->lineEdit_14->setText(strAutospeed);
                    }
                    flagaction = true;
                }

            }
        }
    }//end of else if(watched == ui->listWidget_7)

//    else if(watched == ui->lineEdit_12)
//    {
//        if(event->type() == QEvent::KeyPress)
//        {
//            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
//            {
//                if(key_event->key() == Qt::Key_F2)//下键
//                {
//                    if(LCGetaiSetup == 8)
//                    {
//                        qDebug()<<" kdjsksksksksksssssssssssssssssssssssssssssssssssssss == "<<LCGetaiSetup<<endl;

//                        focusNextChild();
//                        ui->lineEdit_12->hasFocus();
//                    }
//                }
//                flagaction = true;
//                LCGetaiSetup++;
//            }
//        }
//    }
//    else if(watched == ui->lineEdit_13)
//    {
//        if(event->type() == QEvent::KeyPress)
//        {
//            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
//            {
//                if(key_event->key() == Qt::Key_F2)//下键
//                {
//                    if(LCGetaiSetup == 9)
//                    {
//                        qDebug()<<" kdjsksksksksksssssssssssssssssssssssssssssssssssssss == "<<LCGetaiSetup<<endl;

//                        focusNextChild();
//                        ui->lineEdit_13->hasFocus();
//                    }
//                }
//                flagaction = true;
//                LCGetaiSetup++;
//            }
//        }
//    }



    //匹配性标定

    else if((watched == ui->tableWidget_3)||(watched == ui->lineEdit_11))//
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
            {
                if(key_event->key() == Qt::Key_F2)//下键
                {

                    bool mm1 = ui->tableWidget_3->hasFocus();
                    bool mm2 = ui->lineEdit_11->hasFocus();
                    if(mm1)
                    {
//                        focusNextChild();
//                        ui->lineEdit_11->hasFocus();

#if 1
                    if(LCPiPeixingBiaoDing>=6)
                    {
                        LCPiPeixingBiaoDing = 0;
                       // ui->tableWidget->setStyleSheet("background-color:red;");//selection-
                        ui->tableWidget_3->hasFocus();

                        #if 0
                        ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                        ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);
                        #endif

                        ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                        ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);

                    }
                    else
                    {
                        if(LCPiPeixingBiaoDing>=3)
                        {
                                ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing-3,5);
                                ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);//SelectRows
                                if(LCPiPeixingBiaoDing == 5)
                                {
                                    focusNextChild();
                                    ui->lineEdit_11->setFocus();
                                }
                        }
                        else
                        {
                            qDebug()<<"k666666666666666666666666666kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;

                            ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                            ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);//SelectRows
                            //ui->tableWidget_3->hasFocus();
                        }

                    }
//                    flagaction = true;
                    LCPiPeixingBiaoDing++;
#endif
                    }
                    if(mm2)
                    {
                        LCPiPeixingBiaoDing = 0;
                        focusNextChild();
                        ui->tableWidget_3->hasFocus();
                        ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                        ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectItems);//SelectRows
                        LCPiPeixingBiaoDing++;
                    }

                    flagaction = true;
                    return true;
                }

                //向下键
                else if (key_event->key() == Qt::Key_F3)
                {
                    LCPiPeixingBiaoDing--;
                    if(LCPiPeixingBiaoDing <= 0)
                    {
                        LCPiPeixingBiaoDing = 0;
                    }
                    ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);

                    /********************2017.4.27************************************/
                     ui->tableWidget_3->setItem(0,5,new QTableWidgetItem("Mar"));
                     ui->tableWidget_3->setItem(1,5,new QTableWidgetItem("lskdkdk"));
                     /*****************************************************************/

                    flagaction = true;
                    return true;
                }//向上键
                else if (key_event->key() == Qt::Key_F4)
                {
                    LCPiPeixingBiaoDing++;

                    if(LCPiPeixingBiaoDing >= 3)
                    {
                        LCPiPeixingBiaoDing = 0;
                    }

                    ui->tableWidget_3->setCurrentCell(LCPiPeixingBiaoDing,0);
                    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);
                    flagaction = true;
                    return true;
                }
                else if ((key_event->key() == Qt::Key_F5)&&(watched == ui->lineEdit_11))
                {

                    //2017.4.28    //更新匹配性标定设定数据库

                    //手柄标定数据库创建

                        //static unsigned char nn = 1;
                        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
                        QSqlDatabase db;
                        if(QSqlDatabase::contains("qt_sql_default_connection"))
                          db = QSqlDatabase::database("qt_sql_default_connection");
                        else
                          db = QSqlDatabase::addDatabase("QSQLITE");

                       db.setDatabaseName("jy.db");
                       if (!db.open())
                       {
                           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
                       }
                       QSqlQuery query;
                       #if 0
                       bool ok = query.exec("create table ShouBingBD(TrueValue INTEGER,SmallValue INTEGER,MiddleValue INTEGER,BigValue INTEGER,OffSetValue INTEGER)");
                       if (ok)
                       {
                           qDebug()<<"ceate table partition success"<<endl;
                       }
                       else
                       {
                           qDebug()<<"ceate table partition failed"<<endl;
                       }
                       #endif

                       //query.prepare("INSERT INTO ShouBingBD(TrueValue, SmallValue, MiddleValue,BigValue,OffSetValue) VALUES (:TrueValue, :SmallValue,:MiddleValue, :BigValue,:OffSetValue)");
                       query.prepare("update ShouBingBD set TrueValue = :TrueValue,SmallValue = :SmallValue,MiddleValue = :MiddleValue,BigValue = :BigValue,OffSetValue = :OffSetValue");//where

                       query.bindValue(":TrueValue",66);
                       query.bindValue(":SmallValue", 66);
                       query.bindValue(":MiddleValue", 66);
                       query.bindValue(":BigValue", 66);
                       query.bindValue(":OffSetValue", 66);
                       query.exec();


                       query.bindValue(":TrueValue",66);
                       query.bindValue(":SmallValue", 66);
                       query.bindValue(":MiddleValue", 66);
                       query.bindValue(":BigValue", 66);
                       query.bindValue(":OffSetValue", 66);
                       query.exec();

                     query.exec("select TrueValue, SmallValue,MiddleValue,BigValue,OffSetValue from ShouBingBDS");
                     while (query.next())
                     {

                        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();

                     }

                      query.exec(QObject::tr("drop ShouBingBDS"));


                    /****************************添加最小值，最大值，中间值，偏移量*******************************************************/
                    //2017.4.26
                        //ui->tableWidget_3->setItem(0,0,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,1,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,2,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,3,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,4,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(0,5,new QTableWidgetItem("99"));


                        //ui->tableWidget_3->setItem(1,0,new QTableWidgetItem(10));
                        ui->tableWidget_3->setItem(1,1,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,2,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,3,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,4,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(1,5,new QTableWidgetItem("99"));

                        //ui->tableWidget_3->setItem(2,0,new QTableWidgetItem(10));
                        ui->tableWidget_3->setItem(2,1,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(2,2,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(2,3,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(2,4,new QTableWidgetItem("99"));
                        ui->tableWidget_3->setItem(2,5,new QTableWidgetItem("99"));

                    /***************************************************************************************************************/

                }
            }
        }
    }//end of  else if(watched == ui->tableWidget_3)

    return QWidget::eventFilter(watched,event);
}

//绘制label_5 上的指针
void Widget::fun2()
{
#if 1
               QPainter painterlabel5(ui->label_5);
               //km/h
               painterlabel5.translate(103, 102);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);

               static const QPoint hourHand[4] = {
                   QPoint(8, 0),
                   QPoint(-8,0),
                   QPoint(-1.5, -80),
                   QPoint(1.5, -80)
               };

               painterlabel5.setPen(Qt::NoPen);
               painterlabel5.setBrush(Qt::red);
               painterlabel5.setRenderHint(QPainter::Antialiasing, true);
               painterlabel5.save();

               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painterlabel5.rotate(-114.5);
               painterlabel5.rotate(8*floatnu1);



               //painter.rotate(4.0 );  //设旋转(角度 = 6° * (分钟 + 秒 / 60))*shisu
               //内测用
               /****************************************************************************/
               //qDebug()<<"time: "<<time.second()<<endl;

               /****************************************************************************/

               painterlabel5.drawConvexPolygon(hourHand, 4);  //填充分针部分
               painterlabel5.setRenderHint(QPainter::Antialiasing, true);
               painterlabel5.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painterlabel5.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painterlabel5.save();
               painterlabel5.drawEllipse(QPoint(0,0),18,18);
               painterlabel5.restore();

               //画白圈
               /***********************************************/


               painterlabel5.setBrush(Qt::darkGray);
               painterlabel5.save();//画上中心原点
               painterlabel5.drawEllipse(QPoint(0,0),15,15);
               painterlabel5.restore();

               //chuli pupian shansuo
              // painter.translate(-405,-432);//平移到左上角
#endif
}

//绘制label_2 上的指针
void Widget::magicTime()
{
    QPainter painterlabel2(ui->label_2);

#if 1

        if(flagwidget == xingZouWidget)
           {

               //int side = qMin(width(), height());  //绘制的范围(宽、高中最小值)

               painterlabel2.setRenderHint(QPainter::Antialiasing);//绘制的图像反锯齿
               //painter.translate(width() / 2, height() / 2);//重新定位坐标起始点，把坐标原点放到窗体的中央

               //painter.translate(405, 184);//重新定位坐标起始点，把坐标原点放到窗体的中央
                painterlabel2.translate(103, 102);//重新定位坐标起始点，把坐标原点放到窗体的中央
               //painter.scale(side / 400.0, side / 300.0);//设定画布的边界,用窗体宽高的最小值来计算时钟的大小，防止窗体拉伸导致的时钟变形以及显示不全

               //下面两个数组用来定义表针的两个顶点，以便后面的填充
               static const QPoint hourHand[4] = {
                   QPoint(8, 0),
                   QPoint(-8,0),
                   QPoint(-1.5, -80),
                   QPoint(1.5, -80)
               };
               static const QPoint minuteHand[4] = {
                   QPoint(4, 0),
                   QPoint(-4, 0),
                   QPoint(-1, -80),
                   QPoint(1, -80)
               };

               //km r/mini

               painterlabel2.setPen(Qt::NoPen);//填充时针，不需要边线所以NoPen
               painterlabel2.setBrush(Qt::red);
               painterlabel2.setRenderHint(QPainter::Antialiasing, true);
               painterlabel2.save();
               //painter.rotate(6.0 *time.second());  //设旋转(角度 = 6° * (分钟 + 秒 / 60))
               painterlabel2.rotate(-114.5);

               painterlabel2.rotate(8*floatnu1);//floatnu1  *floatnu1

               painterlabel2.drawConvexPolygon(hourHand, 4);  //填充分针部分
               painterlabel2.restore();

               /***********************************************/
               //2016.6.25   画白圈
               painterlabel2.setBrush(Qt::green); //画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painterlabel2.save();
               painterlabel2.drawEllipse(QPoint(0,0),18,18);
               painterlabel2.restore();

               //画白圈
               /***********************************************/

               painterlabel2.setBrush(Qt::darkGray);//画上中心原点/home/vmuser/qtworkplace/chanpin/img2
               painterlabel2.save();
               painterlabel2.drawEllipse(QPoint(0,0),15,15);
               painterlabel2.restore();

           }
#endif
}

//暂时测试用到 加加时指针会转动
//void Widget::on_pushButton_clicked()
//{
//    floatnu1++;
//}

//listwidget 光标移动触发事件
void Widget::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
#if 0
    if(current== NULL)return;
    if(previous!= NULL)
    {
        previous->setBackgroundColor(Qt::transparent);
        previous->setTextColor(Qt::black);
    }
    current->setBackgroundColor(Qt::red);
    current->setTextColor(Qt::blue);
#endif
}


//超时判断 在没有任何按键按下时计数器开始计数
void Widget::timeoutfun()
{
    if(flagaction)
    {
        flagtimeoutnum = 0;
        flagaction = false;
        qDebug()<<"flagtimeoutnum = "<<flagtimeoutnum<<endl;
    }
    else
    {
        flagtimeoutnum++;
        qDebug()<<"flagaction false .......... = "<<flagtimeoutnum<<endl;
        if(flagtimeoutnum == 15)
        {
            flagtimeout = true;

        }

    }

    if(flagtimeout)
    {
        flagwidget = xingZouWidget;
        ui->stackedWidget->setCurrentIndex(0);
        flagtimeout = false;
        flagtimeoutnum = 0;
    }
    qDebug()<<"timeout"<<endl;
}


/******************************************************************************************************/
//信号槽
//
//故障码
uchar i = 0;
void Widget::gzmslottest()//故障码显示
{
     qDebug()<<"mm ++ == "<<mm++<<endl;
     if (mm>=6)//312
     {
         mm = 0;
     }
}

//平滑转动
void Widget::shanhua()//闪烁和平滑转动
{

    Led ^= 1;
#if 0

    nu2 = (ecutest.FDJ_speed/100);
    //nu2 = ecutest.FDJ_speed;
    if(nu2 > 30)
    {
        nu2 = 30;
    }

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


    floatnu1 = ecutest.FDJ_speed;
    floatnu1 = floatnu1/100;
    if(floatnu1 >30)
    {
        floatnu1 = 30;
    }


    nu4 = (cantest.HourSpeed/10);///100

    floatnu3 = cantest.HourSpeed;
    floatnu3 /= 10;

    if(floatnu3 >30)
    {
        floatnu3 = 30;
    }

    //qDebug()<<"cantest.HourSpeed------ =  "<<cantest.HourSpeed<<endl;

    if(nu4>30)
    {
        nu4 = 30;
    }
    if(nu4<0)
    {
        nu4 = 0;
    }
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

    if(flagaddnum)
    {

        //闪烁控制

        if(ecutest.flagECU == 0)
        {
            if(ecutest.VolSW > 102)//水温
            {
                shanshuoSW = 1;
            }

            if(JYYL < 0.08)//机油
            {
                shanshuoJYYL = 1;
            }
        }


        if(cantest.flagTXCS == 0)//cantest.flagTXCS == 1 mcu  故障
        {
            if(cantest.VolYL <= 1)//油量
            {
                shanshuoYL = 1;
            }
        }

        //油中有水
        if(ecutest.flagYSFL_ECU == 1)//油中有水
        {
            shanshuoYZYS = 1;
        }

        //液压油温
        if(cantest.VolYeyayouwen > 90)
        {
            shanshuoYYYW = 1;
        }

        //手刹
        if(cantest.flagSS)
        {
            shanshuoSS = 1;
        }
        //粮满
        if(cantest.flagLCM)
        {
            shanshuoLM = 1;
        }


        if(flagDelay)//第一次上电
        {

            if(cantest.ZLspeed<ruby[0])//轴流滚筒转速
            {
                //if (cantest.ZLspeed != 0)
                {
                    shanshuozlzs = 1;//轴流滚筒转速
                }

            }

            if(cantest.FTspeed<ruby[1])//复脱器转速
            {
                //if (cantest.FTspeed != 0)
                {
                    shanshuoftqzs = 1;//复托器转速
                }

            }

            if(cantest.SYspeed<ruby[2])//升运器堵塞转速
            {
                //if (cantest.SYspeed != 0)
                {
                     shanshuosyqzs = 1;//升运器转速
                }

            }

        }





        //显示  汉字 报警

                mybufflag[0] = shanshuoSW;//水温报警
                mybufflag[1] = shanshuoJYYL;//机油  油压报警 0～1 MPa,在0.1 MPa 以下为报警区。

                mybufflag[2] = shanshuoYL;//及时加油 油量低报警
                mybufflag[3] = shanshuoYYYW;////液压油温

                mybufflag[4] =  shanshuoLM; //粮箱满 报警

                if((ecutest.flagECU == 1)||(cantest.flagTXCS == 1))
                {
                    shanshuoTXGZ = 1;//通信故障
                }
                else
                {
                    shanshuoTXGZ = 0;
                }

                mybufflag[5] =  shanshuoTXGZ;  //通信故障

                mybufflag[6] =  shanshuoSS;  //手刹


                //建立索引 对mybufflag进行提取。
                for (mm = 0; mm < 15; mm++)
                {
                    if(mybufflag[mm])
                    {
                        myindex[jflag] = mm;
                        jflag++;

                    }

                }

                if(jflag == 0)
                {
                    memset(myindex,0,15);
                }


                jjjflag = jflag;
                jflag = 0;

                if (j >= jjjflag)
                {
                    j = 0;
                    memset(myindex,0,15);
                }
        /**********************************************************************************************************/





        //闪烁算法
        flagnum++;
        if(flagnum>15)//30
        {
            flagaddnum = 0;
        }
    }
    else
    {
        shanshuoSW = 0;//水温
        shanshuoJYYL = 0;//机油
        shanshuoYL = 0;//油量
        shanshuoYZYS = 0;// 油中有水

        shanshuoSS = 0;//手刹
        shanshuoLM = 0;//粮满

        shanshuozlzs = 0;//轴流滚筒转速
        shanshuoftqzs = 0;//复托器转速
        shanshuosyqzs = 0;//升运器转速

        flagnum--;
        if(flagnum==0)
        {
            flagaddnum = 1;
        }
    }
    #endif
}

//里程 槽函数
//里程 槽函数

#if 0
void Widget::Licheng()//里程
{
        static unsigned char nn = 1;
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
        QSqlDatabase db;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
          db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName("jy.db");
       if (!db.open())
       {
           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
       }
       QSqlQuery query;
       #if 0
       bool ok = query.exec("create table fdjgz(spn INTEGER,fmi INTEGER,gzms varchar)");
       if (ok)
       {
           qDebug()<<"ceate table partition success"<<endl;
       }
       else
       {
           qDebug()<<"ceate table partition failed"<<endl;
       }
       #endif

       //query.prepare("INSERT INTO fdjgz (spn, fmi, gzms) VALUES (:spn, :fmi, :gzms)");

       //query.prepare("update fdjgz set fmi = :fmi,gzms = :gzms where spn = :spn ");//
       query.prepare("UPDATE fdjgz SET fmi = :fmi,gzms = :gzms where spn = :spn ");//
       //query.prepare("UPDATE fdjgz SET fmi = :fmi where spn = :spn ");//,gzms = :gzms
       query.bindValue(":spn",66);
       query.bindValue(":fmi", 888);
       query.bindValue(":gzms", QObject::tr("%1").arg(555));

       query.exec();

       query.bindValue(":spn",77);
       query.bindValue(":fmi", 77);
       query.bindValue(":gzms", QObject::tr("%1").arg(77));

       query.exec();


     query.exec("select spn, fmi, gzms from fdjgz");
     while (query.next())
     {

        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
        spnItem[un] = query.value(0).toInt();
        fmiItem[un] = query.value(1).toInt();
        gzmItem[un] = query.value(2).toString();

        ui->tableWidget->setItem(un,0,new QTableWidgetItem(QString::number(spnItem[un])));
        //ui->tableWidget->setItem(un,1,new QTableWidgetItem(QString::number(fmiItem[un])));
        ui->tableWidget->setItem(un,1,new QTableWidgetItem(gzmItem[un]));

        un++;
        if(un>=10)
        {
            un = 0;
        }
     }

      query.exec(QObject::tr("drop fdjgz"));
}
#endif

#if 0
void Widget::Licheng()//里程
{
    static unsigned char nn = 1;
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
          //query.prepare("INSERT INTO jy8c (id, name, age) VALUES (:id, :name, :age)");

          query.prepare("update jy8c set age = :age,name = :name where id = :id");


          qDebug()<<"kakutlgt ---  "<<kaku_tlgt<<endl;
         qDebug()<<"syq ----- ---   "<<kaku_syq<<endl;


          query.bindValue(":id",1);
          query.bindValue(":name", QObject::tr("88888888888888"));
          query.bindValue(":age", 556);//ui->label->text().toInt()
          query.exec();

          query.bindValue(":id",2);
          //query.bindValue(":name", QObject::tr("复脱塞转速"));
          query.bindValue(":age", 33);//ui->label_3->text().toInt()
          query.exec();


          query.bindValue(":id",3);
          //query.bindValue(":name", QObject::tr("升运转速"));
          query.bindValue(":age", 11);//ui->label_3->text().toInt()
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

}
#endif

//里程 槽函数


void Widget::Licheng()//语言，发动机厂家，机器型号
{
    //手柄标定数据库创建
    #if 0

        //static unsigned char nn = 1;
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
        QSqlDatabase db;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
          db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName("jy.db");
       if (!db.open())
       {
           qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
       }
       QSqlQuery query;
       #if 1
       bool ok = query.exec("create table ShouBingBD(TrueValue INTEGER,SmallValue INTEGER,MiddleValue INTEGER,BigValue INTEGER,OffSetValue INTEGER)");
       if (ok)
       {
           qDebug()<<"ceate table partition success"<<endl;
       }
       else
       {
           qDebug()<<"ceate table partition failed"<<endl;
       }
       #endif

       query.prepare("INSERT INTO ShouBingBD(TrueValue, SmallValue, MiddleValue,BigValue,OffSetValue) VALUES (:TrueValue, :SmallValue,:MiddleValue, :BigValue,:OffSetValue)");
       //query.prepare("update config set cjswitch = :cjswitch,engineswitch = :engineswitch,langswitch = :langswitch");//where

       query.bindValue(":TrueValue",22);
       query.bindValue(":SmallValue", 11);
       query.bindValue(":MiddleValue", 66);
       query.bindValue(":BigValue", 77);
       query.bindValue(":OffSetValue", 88);
       query.exec();


       query.bindValue(":TrueValue",33);
       query.bindValue(":SmallValue", 44);
       query.bindValue(":MiddleValue", 55);
       query.bindValue(":BigValue", 99);
       query.bindValue(":OffSetValue", 100);
       query.exec();

     query.exec("select TrueValue, SmallValue,MiddleValue,BigValue,OffSetValue from ShouBingBDS");
     while (query.next())
     {

        qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();
//        spnItem[un] = query.value(0).toInt();
//        fmiItem[un] = query.value(1).toInt();
//        gzmItem[un] = query.value(2).toString();

//        ui->tableWidget->setItem(un,0,new QTableWidgetItem(QString::number(spnItem[un])));
//        //ui->tableWidget->setItem(un,1,new QTableWidgetItem(QString::number(fmiItem[un])));
//        ui->tableWidget->setItem(un,1,new QTableWidgetItem(gzmItem[un]));

//        un++;
//        if(un>=10)
//        {
//            un = 0;
//        }
     }

      query.exec(QObject::tr("drop ShouBingBDS"));

      #endif

      //阀值设定数据库创建
#if 0
    //static unsigned char nn = 1;
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());//汉字显示
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");

   db.setDatabaseName("jy.db");
   if (!db.open())
   {
       qDebug()<<"open database failed ---"<<db.lastError().text()<<endl;
   }
   QSqlQuery query;
   #if 1
   bool ok = query.exec("create table FaZhiBingBD(ZLH INTEGER,XLLH INTEGER,GQLH INTEGER,LmdGTZS INTEGER,LmdFengJi INTEGER,LmdJiaoLong INTEGER,LmdGuoQiao INTEGER)");
   if (ok)
   {
       qDebug()<<"ceate table partition success"<<endl;
   }
   else
   {
       qDebug()<<"ceate table partition failed"<<endl;
   }
   #endif

   query.prepare("INSERT INTO FaZhiBingBD(ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao) VALUES (:ZLH, :XLLH, :GQLH, :LmdGQZS, :LmdFengJi, :LmdJiaoLong, :LmdGuoQiao)");
   //query.prepare("update config set cjswitch = :cjswitch,engineswitch = :engineswitch,langswitch = :langswitch");//where

   query.bindValue(":ZLH",55);
   query.bindValue(":XLLH", 66);
   query.bindValue(":GQLH", 66);
   query.bindValue(":LmdGTZS", 77);
   query.bindValue(":LmdFengJi", 88);
   query.bindValue(":LmdJiaoLong", 99);
   query.bindValue(":LmdGuoQiao", 99);
   query.exec();


   query.bindValue(":ZLH",11);
   query.bindValue(":XLLH", 12);
   query.bindValue(":GQLH", 13);
   query.bindValue(":LmdGTZS", 14);
   query.bindValue(":LmdFengJi", 15);
   query.bindValue(":LmdJiaoLong", 16);
   query.bindValue(":LmdGuoQiao", 17);
   query.exec();

 query.exec("select ZLH, XLLH, GQLH,LmdGTZS,LmdFengJi,LmdJiaoLong,LmdGuoQiao from FaZhiBingBD");
 while (query.next())
 {

    qDebug()<<"id("<<query.value(0).toInt()<<")  name:"<<query.value(1).toString()<<"  age:"<<query.value(2).toInt();

 }

  query.exec(QObject::tr("drop FaZhiBingBD"));

  #endif

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

   /*测试*/
   xiaoshiJi_m++;
   xiaoshiJi_h = (xiaoshiJi_m/3600)*1000 + ((xiaoshiJi_m%3600)*1000)/3600;
   xiaoshiJi_h /= 1000;

   if(flagmatchion == YZB_4_5_7_8)
   {
        ui->label_10->setText(QString::number(xiaoshiJi_h,'f',3));
   }
   else if(flagmatchion == YZT_10)
   {
        ui->label_7->setText(QString::number(xiaoshiJi_h,'f',3));
   }
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
#if 0
  if(ecutest.FDJ_speed>350)
   {
        xiaoshiJi_m++;
   }
    xiaoshiJi_h = (xiaoshiJi_m/3600)*1000 + ((xiaoshiJi_m%3600)*1000)/3600;
    xiaoshiJi_h /= 1000;

    if(flagwidget == xingZouWidget)
    {
        ui->label_33->setText(QString::number(xiaoshiJi_h,'f',1));
    }
    else if(flagwidget == workWidget)
    {
        ui->label_7->setText(QString::number(xiaoshiJi_h,'f',1));
    }
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

        if((cantest.ZLspeed != 0)||(cantest.FTspeed != 0) ||(cantest.SYspeed != 0))
        {
            DelayCount++;
            if(DelayCount == 7)
            {
                flagDelay = 1;
            }
        }
        else if((cantest.ZLspeed == 0)&&(cantest.FTspeed == 0)&&(cantest.SYspeed == 0))
        {
            flagDelay = 0;
            DelayCount = 0;
           // qDebug()<<"delay ........                        ...................."<<endl;

        }

#endif
}

//故障码索引

uint Widget::GuzhangmaIndex(long spn, uchar fmi)
{

}
//
uint Widget::GuzhangmaYucaiIndex(long spn, uchar fmi)
{

}

void Widget::myscroll()
{
    //QString 数组
    QString CeshiZM[7] = {"空调压缩机开路","空调压缩机对电源短路","空调压缩机对地短路"};//{,"空气质量流量传感器电压超上限"};
    static int nPos = 0;
    //if (nPos > m_scrollCaptionStr.length())
    if (nPos > CeshiZM[mm].length())
    {
        nPos = 0;
    }
    nPos++;
    ui->label_4->setText(CeshiZM[mm].mid(nPos));
}
//时间设置
void Widget::on_dateTimeEdit_dateTimeChanged(const QDateTime &date)
{
    MyDatetimeSetup =date;// QDateTime::currentDateTime();
    dateBuffer = MyDatetimeSetup.toString("yyyy-MM-dd ");//
    timeBuffer = MyDatetimeSetup.toString("hh:mm:ss");
}



bool ShouBingZuixiao = false;
bool ShouBingWangcheng = false;

bool TuiGanZuixiao = false;
bool TuiGanWancheng = false;

bool AoBanZuixiao = false;
bool AoBanWancheng = false;



//3秒内无边化函数
void Widget::NoChangeFun()
{
    if(LCPiPeixingBiaoDing == 1)
    {
        if(FlagNext == false)
        {
            if(Shijizhi == TempShijizhi)
            {
                ThreeOut++;
                 //qDebug()<<"ppppppppppppppppppppppppppppppppppppppppp = "<<LCPiPeixingBiaoDing<<endl;
            }
            else
            {
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
           // ui->label_16->setText("请推动手柄到最小位置");
            FlagNext = true;
            ThreeOut = 0;
            tempflagShoubing = true;
        }
        else
        {
            //ui->label_16->setText("请推动手柄到最大位置");
        }

        //标定完成
        if(FlagNext == true)
        {
            if(Shijizhi == TempShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            //ui->label_16->setText("手柄标定完成");
            FlagNext = false;
            ThreeOut = 0;
        }
        else
        {
            //ui->label_16->setText("请推动手柄到最大位置");
        }
    }
    else if(LCPiPeixingBiaoDing == 2)//行走泵标定
    {
        if(FlagNext == false)
        {
            if(Shijizhi == TempShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            ui->label_16->setText("请推动手柄到最小位置");
            FlagNext = true;
            ThreeOut = 0;
        }
        else
        {
            ui->label_16->setText("请推动手柄到最大位置");
        }

        //标定完成
        if(FlagNext == true)
        {
            if(Shijizhi == TempShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            ui->label_16->setText("手柄标定完成");
            FlagNext = false;
            ThreeOut = 0;
        }
        else
        {
            //ui->label_16->setText("请推动手柄到最大位置");
        }
    }
    else if(LCPiPeixingBiaoDing == 3)//凹板间隙
    {
        if(FlagNext == false)
        {
            if(Shijizhi == TempShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            ui->label_16->setText("请推动手柄到最小位置");
            FlagNext = true;
            ThreeOut = 0;
        }
        else
        {
            ui->label_16->setText("请推动手柄到最大位置");
        }

        //凹板间隙标定完成
        if(FlagNext == true)
        {
            if(Shijizhi == TempShijizhi)
            {
                ThreeOut++;
            }
            else
            {
                ThreeOut = 0;
            }
        }
        if(ThreeOut == 3)
        {
            ui->label_16->setText("凹板间隙标定完成");
            FlagNext = false;
            ThreeOut = 0;
        }
        else
        {
            //ui->label_16->setText("请推动手柄到最大位置");
        }
    }
}
