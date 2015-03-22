#ifndef BUILDING_H
#define BUILDING_H
#include <QString>
#include "database.h"
#include <QDate>
struct level
{
    QString special_brig;
    QString day_count;
    QString step;
};

struct material_ned
{
    QString number_material;
    QString  count_material;
    QString name_material;
};

struct period
{
    QString date_start;
    QString date_fin;
};

struct period_date
{
    QDate date_start;
    QDate date_fini;
};

struct metter_double
{
    QString metter_start;
    QString metter_fin;
};
struct price_double
{
    QString price_start;
    QString price_fin;
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

    period time_pair;
    metter_double metter_pair;
    price_double price_pair;
    period_date time_pair_date;

    building();
    ~building();

};




#endif // BUILDING_H
