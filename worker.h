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

    int id;
    double pay;

};

#endif // WORKER_H
