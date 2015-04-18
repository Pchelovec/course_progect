#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include "database.h"
#include <QDebug>
#include <QString>
#include "building.h"
#include "client.h"
#include "technics.h"
#include "worker.h"
#include "material.h"
#include "client.h"
#include <QT>
#include <QAbstractItemModel>
#include <QTableWidget>

using namespace std;
class query_result
{
public:
    query_result();
    ~query_result();
    void reset();
    //--------------------------------------------------------материалы
    QList <QString> avto_material_list_izmer();//AVTO

    QList <QString> avto_material_list_naz();//AVTO

    QList <material> mater_like_my(material val);//SELECT переделать функцию под универсальную

    //QList <material> material_with_function(QString function);//SELECT   заменить использованием функции выше

    //QString material_with_name(QString name);//SELECT

    QString material_ret_naznach_with_name(QString name);//SELECT
    QList<QString> material_ret_name_with_naznach(QString naznach);//SELECT

    double sum_material(QList<material_ned> val);//SELECT

    void insert_material(material val);//INSERT

    void material_up_summ_count(QString SUM, QString ID);//update

    void material_up_2_to_1 (material val);//update

    QList <material> material_for_building(QString ID_b);

    QList <material> material_with_param(material val);

    //void sub_material (material sub_val);//update

    //----------------------------------------------------------------рабочие

    QList <worker> worker_all(worker wor);//SELECT

    QList <worker> worker_with_group(QString ID_gr);//SELECT//  заменить использованием функции выше

    QList <QString> ID_group_with_name(QString name);//SELECT 2 табл

    QList <worker> avto_worker_list_free(worker sha);//SELECT

    void worker_del(QString ID);//DELETE

    void worker_change_status(QString id_worker);//UPDATE

    void del_worker_from_brig(QString ID);//DELETE

    void insert_new_worker(worker val);//INSERT

    void worker_to_brig(worker val, QString ID_brig);//INSERT
    void worker_to_brig(QString ID_w, QString ID_brig);//INSERT

    QList <QString> avto_worker_dolg_list();//AVTO

    QList <QString> avto_special_brig_list();//AVTO   бригада

    //----------------------------------------------------------------оборудование
    QList <technics> eqw_all_load(technics share);//SELECT

    QList <technics> eqw_with_group (QString ID_gr);//SELECT//  заменить использованием функции выше

    QList <technics> avto_eq_list_free(technics sha);//SELECT

    void eqw_dell(QString ID);//DELETE

    void del_eqw_from_brig(QString ID);//DELETE

    void insert_new_eqw(technics val);//INSERT

    void eqw_to_brig(technics val, QString ID_brig);//INSERT
    void eqw_to_brig(QString ID_e, QString ID_brig);//INSERT

    //-----------------------------------------------------------постройки

    QList <building> building_main_class_ret(building sha);//SELECT

    QString ret_building_ID_with_name(QString name);//SELECT   заменить использованием функции выше

    void insert_level(QString lev_str, QString id_building_s,  level val);//INSERT

    void insert_need_material_for_b( QString ID_b, material_ned material);//INSERT

    QString insert_new_building(building val);//INSERT возвращает id здания

    //-----------------------------------------------------------клиент
    void insert_client_info(client val);//insert

    double need_to_pay(QString ID_progect);//select
    double sum_pay(QString ID_b);//select

    void update_pay_sum(QString ID_b, double pay_sum);//update
    void update_client(client cl);
    QList<client> is_client_with_passport(QString passport);
    //-----------------------------------------------------------

    //-----------------------------------------------------------проект и занятость бригады
    QString save_progect(QString client_passport, QString house_id);//insert
    QString return_progect_id(QString client_passport, QString house_id);

    QString ret_id_house_with_id_progect(QString ID_progect);
    QList <level> ret_list_time_plan_for_b(QString ID_building);

    QList<building> return_list_worked_plan_now(QString ID_special);

    QList <QString> ret_list_brig_with_special(QString ID_special);

    void make_step_building(building val, QString ID_brig, QString progect_id);

    QList <building> info_plan_building(QString ID_b);
    //-----------------------------------------------------------другие
     QList <person_plas_prog> person_with_ID_building(QString ID_B);//SELECT информация о заказчике с постройкий ID_B
     void new_brig_with_special(QString special_name);//INSERT

     QString  ret_id_special_with_name(QString name_spec);

     building info_for_progect(period_date dat, bool ynic);

     building info_about_progect(QString ID_P);//select

     period_date min_max_date_progect(QString ID_P);//select

     QList <QString> avto_special_all();//AVTO

//===============================================================================================================

    //-----------------------------------------------------------DELETE-------------------------------------

    //void delete_Building(QString ID_b);//DELETE

    //void delete_needed_material_for_building(QString ID_b);//DELETE

    //void delete_grafic_building_for_building(QString ID_b);//DELETE

    //---------------------------------------------------------------INSERT---------------------------------------


private:
    database *DB;
    void connect();
    void close_connect();
};

#endif // QUERY_RESULT_H
