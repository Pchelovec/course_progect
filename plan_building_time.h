#ifndef PLAN_BUILDING_TIME_H
#define PLAN_BUILDING_TIME_H
#include "query_result.h"
#include "struct_data.h"
#include <QMessageBox>
#include <QDate>
#include <QSet>
#include <QObject>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
class plan_building_time
{
public:
    void make_and_save_time_plan_for_building(QString ID_progect, QDate user_start_date);
    QList <material_ned> sub_material_for_building(QString ID_building);
    plan_building_time();
    ~plan_building_time();
private:
    void save_best_time_for_level(level val, QDate &min_start_time, QString ID_progect);
    query_result *QUEry;
};
#endif // PLAN_BUILDING_TIME_H
