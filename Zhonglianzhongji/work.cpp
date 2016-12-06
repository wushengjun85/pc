#include "work.h"
#include "ui_work.h"

Work::Work(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Work)
{
    ui->setupUi(this);
}

Work::~Work()
{
    delete ui;
}
