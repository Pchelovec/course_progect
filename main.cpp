#include "mainwindow.h"
#include <QApplication>
#include "pictures_stroitel.h"
#include <QObject>

#include <QStyleFactory>
#include <QStyle>

int main(int argc, char *argv[])
{
//QApplication::setStyle(QStyleFactory::create("Fusion"));
    //поработать над стилем
    //многоязычность
    //отдельное дополнение для телефонов внешняя бд
    //
    //
    //

    QApplication a(argc, argv);

    pictures_stroitel ps;
    //ps.show();
    return a.exec();
}

