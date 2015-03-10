#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
class client
{
public:
    QString passport;
    QString FIO;
    unsigned long int phone;
    QDate year_birthday;
    QString plases_life;
    client();
    ~client();
};

#endif // CLIENT_H
