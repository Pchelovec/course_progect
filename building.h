#ifndef BUILDING_H
#define BUILDING_H
#include <QString>

class building
{
public:
    QString name;
    bool is_ynical;
    QString Standart_time_building;
    double metter;
    double price;
    int ID;
    bool fundament;

    building();
    ~building();


};

#endif // BUILDING_H
