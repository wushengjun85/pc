#include "timeset.h"
#include "ui_timeset.h"

extern QString DateTimeSetup;
extern bool timeSetOK;

Timeset::Timeset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timeset)
{
    ui->setupUi(this);
}

Timeset::~Timeset()
{
    delete ui;
}

void Timeset::on_pushButton_clicked()//按键 1
{
    DateTimeSetup.append("1");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_2_clicked()//按键 2
{
    DateTimeSetup.append("2");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_3_clicked()//按键 3
{
    DateTimeSetup.append("3");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_4_clicked()//按键 4
{
    DateTimeSetup.append("4");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_5_clicked()//按键 5
{
    DateTimeSetup.append("5");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_6_clicked()//按键 6
{
    DateTimeSetup.append("6");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_7_clicked()//按键 7
{
    DateTimeSetup.append("7");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_8_clicked()//按键 8
{
    DateTimeSetup.append("8");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_9_clicked()//按键 9
{
    DateTimeSetup.append("9");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_11_clicked()//按键 0
{
    DateTimeSetup.append("0");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_10_clicked()////按键 esc
{
    DateTimeSetup = DateTimeSetup.left(DateTimeSetup.length() - 1);
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_12_clicked()//按键 ok
{
    timeSetOK = true;
    this->close();
}

void Timeset::on_pushButton_13_clicked()//按键 ：
{
    DateTimeSetup.append(":");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_14_clicked()//按键 -
{
    DateTimeSetup.append("-");
    ui->lineEdit->setText(DateTimeSetup);
}

void Timeset::on_pushButton_15_clicked()//按键 空格
{
    DateTimeSetup.append(" ");
    ui->lineEdit->setText(DateTimeSetup);
}
