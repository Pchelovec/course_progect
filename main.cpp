#include "mainwindow.h"
#include <QApplication>
#include "pictures_stroitel.h"
#include <QStyleFactory>
#include <QPalette>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));        //нестандартные цвета и стиль интерфейса
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::WindowText,QColor(0,100,100));
    p.setColor(QPalette::Window, QColor(240,255,245));
    p.setColor(QPalette::Button, QColor(255,255,190));
    p.setColor(QPalette::HighlightedText, QColor(150,0,0));
    p.setColor(QPalette::Highlight, QColor(200,200,200));
    qApp->setPalette(p);

    QApplication a(argc, argv);
    //основа c заставкой
    pictures_stroitel ps;

    //без заставки отладочный режим
//    MainWindow MW;
//    MW.show();
    return a.exec();
}
