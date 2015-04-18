#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H
#include <QString>
#include <QList>
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
    QString count_material;
    QString name_material;
    QString rebuy;
    QString now;
    QString need;
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

struct building
{
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
};
struct person_plas_prog
{
    QString fio;
    QString ph;
    QString price;
    QString date;
};
struct client
{
    QString passport;
    QString FIO;
    QString phone;
    QString year_birthday;
    QString plases_life;
};
struct material
{
    QString name;
    QString price;
    QString naznach;
    QString izmer;
    QString count;
    int count_int;
    QString ID;
};
struct worker
{
    QString adress;
    QString post;

    QString birthday;
    QString fio;

    QString id;
    QString pay;

    QString pay_start;
    QString pay_fin;
};
struct technics
{
    QString name;
    QString namber;
    QString Year_vip;
    QString Date_pok;
};
#endif // STRUCT_DATA_H
