#include "mainwindow.h"
#include <QApplication>
#include "pictures_stroitel.h"
#include <QObject>
#include <QStyleFactory>
#include <QStyle>
#include "mainwindow.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//основа
    //pictures_stroitel ps;
    //ps.show();

    MainWindow MW;
    MW.show();

//    MW.show();

    return a.exec();
}

