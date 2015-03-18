#ifndef BUILDING_H
#define BUILDING_H
#include <QString>
#include "database.h"
#include <QDate>
struct level
{
    QString special_brig;
    QString day_count;
};

struct material_ned
{
    QString number_material;
    QString  count_material;
    QString name_material;
};

struct period
{
    QDate date_start;
    QDate date_fin;
};

using namespace std;
class building
{
public:
    QString name;
    QString metter;
    bool is_ynical_bool;
    QString id_ynical_string;
    QString Standart_time_building;
    QList <material_ned> neded_material;
    QList <level> time_plan;
    QString price;
    QString ID;
    building();
    ~building();
};

#endif // BUILDING_H
