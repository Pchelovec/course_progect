#ifndef BUILDING_H
#define BUILDING_H
#include <QString>
#include "database.h"
using namespace std;
class building
{
public:
    QString name;
    bool is_ynical_bool;
    QString id_ynical_string;
    QString Standart_time_building;
    QString metter;
    QString price;
    QString ID;
    building();
    ~building();
};

#endif // BUILDING_H
