#ifndef MATERIAL_H
#define MATERIAL_H
#include <QString>

class material
{
public:
    QString name;
    double price;
    QString funct;
    QString izmeren;
    int count;
    int ID;
    material();
    ~material();
};

#endif // MATERIAL_H
