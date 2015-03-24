#ifndef PRINTER_H
#define PRINTER_H
#include <QString>
#include <QList>
#include "building.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QPrintPreviewDialog>
class printer
{
public:

    void set_info(QList <material_ned> table, QString ID_progect, building info, QList<building> list);

    void make_ntml();

    void print();

    void clear();
    printer();
    ~printer();

private:
    QList <material_ned> table_material_nedost;
    QString ID;
    building info_b;
    QList<building> steps;


    QTextStream out;

    QString s;

    QPrintPreviewDialog * prevDlg;
};

#endif // PRINTER_H
