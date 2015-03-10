#ifndef TECHNICS_H
#define TECHNICS_H
#include <QString>
#include <QDate>
class technics
{
public:
    QString name;
    QString gos_nomer;
    unsigned int distance;
    double gruzop;
    int year;
    QDate date_pokupki;

    technics();
    ~technics();
};

#endif // TECHNICS_H
