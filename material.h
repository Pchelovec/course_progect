#include <QString>
#ifndef MATERIAL_H
#define MATERIAL_H


class material
{
public:
    QString name;
    QString price;
    QString naznach;
    QString izmer;
    QString count;
    int count_int;
    QString ID;
    material();
    ~material();
};

#endif // MATERIAL_H
