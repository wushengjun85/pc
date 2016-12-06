#ifndef FINDLOOK_H
#define FINDLOOK_H

#include <QDialog>

namespace Ui {
class Findlook;
}

class Findlook : public QDialog
{
    Q_OBJECT
    
public:
    explicit Findlook(QWidget *parent = 0);
    ~Findlook();
    
private:
    Ui::Findlook *ui;

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();
};

#endif // FINDLOOK_H
