#ifndef BUILDING_H
#define BUILDING_H
#include <QString>
#include "database.h"
using namespace std;
class building
{
public:
    QString name;
    QString metter;
    bool is_ynical_bool;
    QString id_ynical_string;
    QString Standart_time_building;
    QList <QString> neded_material;
    QList <QString> time_plan;
    QString price;
    QString ID;
    building();
    ~building();
};

#endif // BUILDING_H
