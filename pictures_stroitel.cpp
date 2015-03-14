#include "pictures_stroitel.h"
#include "mainwindow.h"

pictures_stroitel::pictures_stroitel(QWidget *parent) :
    QMainWindow(parent)
{

    emit IncCount();
     QMovie *mov = new QMovie(":/pictures/res/ILLITA_STPOITEL3.gif");

        QLabel *label=new QLabel;
        mov->start();
        label->setMovie(mov);
        QHBoxLayout *QHBl=new QHBoxLayout;
        QHBl->addWidget(label);
        splash=new QSplashScreen;
        splash->setLayout(QHBl);

        splash->setToolTip("ПРИВЕТСТВИЕ");

        splash->move(300,50);
        splash->show();

}
void pictures_stroitel::IncCount()
{
    this->hide();
    static int n=0;
    n++;
    static QTimer *time=new QTimer(this);
    if (n==1)
    {
        time->start(1000);
    }
    connect(time,SIGNAL(timeout()),this,SLOT(IncCount()));
    if (n==40)
    {
        //close
        delete splash;
        delete time;

        this->stat_now();
    }
}

void pictures_stroitel::stat_now()
{
   MW.show();
}

pictures_stroitel::~pictures_stroitel()
{

}
