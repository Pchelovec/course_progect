#include "mainwindow.h"
#include <QApplication>
#include "pictures_stroitel.h"
//#include <QObject>
#include <QStyleFactory>
//#include <QStyleOption>
//#include <QStyle>
//#include <QProxyStyle>
#include <QPalette>
#include "mainwindow.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::WindowText,QColor(0,100,100));
    p.setColor(QPalette::Window, QColor(240,255,245));
    p.setColor(QPalette::Button, QColor(255,255,190));
    p.setColor(QPalette::HighlightedText, QColor(150,0,0));
    p.setColor(QPalette::Highlight, QColor(200,200,200));
    qApp->setPalette(p);
    QApplication a(argc, argv);
    //основа
    //pictures_stroitel ps;
    //ps.show();

    //без заставки
    MainWindow MW;
    MW.show();


//    MW.show();

    return a.exec();
}

