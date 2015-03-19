#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QDate>

using namespace std;
class worker
{
public:
    worker();
    ~worker();
    QString adress;
    QString post;

    QString birthday;
    QString fio;

    QString id;
    QString pay;

    QString pay_start;
    QString pay_fin;



    //QString grup;

};

#endif // WORKER_H
