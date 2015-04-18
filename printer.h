#ifndef PRINTER_H
#define PRINTER_H
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include "ncreport.h"
#include "ncreportoutput.h"
#include "ncreportpreviewoutput.h"
#include "ncreportpreviewwindow.h"
class printer: QWidget
{
    Q_OBJECT
public:

    void print_contract(QString id_contract, QString id_house);
    void print_all_material();
    void print_worker_time(QString id_brig);
    printer();
    ~printer();

private:

};

#endif // PRINTER_H
