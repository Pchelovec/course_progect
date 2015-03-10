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

    QString date_start_in_firm;
    QString birthday;
    QString fio;
    bool Pol;
    QString id;
    QString pay;

};

#endif // WORKER_H
