#ifndef WORK_H
#define WORK_H

#include <QDialog>

namespace Ui {
class Work;
}

class Work : public QDialog
{
    Q_OBJECT
    
public:
    explicit Work(QWidget *parent = 0);
    ~Work();
    
private:
    Ui::Work *ui;

    QTimer *timer_xiaoshiji;
    QTimer *timer_shanhua;
};

#endif // WORK_H
