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

    QList <material> mater_like_my(QString name);//SELECT

    QList <material> material_with_function(QString function);//SELECT

    //QString material_with_name(QString name);//SELECT

    QString material_ret_naznach_with_name(QString name);//SELECT
    QList<QString> material_ret_name_with_naznach(QString naznach);//SELECT

    double sum_material(QList<material_ned> val);//SELECT

    void insert_material(material val);//INSERT

    void material_up_summ_count(QString SUM, QString ID);//update

    void material_up_2_to_1 (material val);//update

    //----------------------------------------------------------------рабочие

    QList <worker> worker_all(worker wor);//SELECT

    QList <worker> worker_with_group(QString ID_gr);//SELECT

    QList <QString> ID_group_with_name(QString name);//SELECT

    QList <worker> avto_worker_list_free(worker sha);//SELECT

    void worker_del(QString ID);//DELETE

    void del_worker_from_brig(QString ID);//DELETE

    void insert_new_worker(worker val);//INSERT

    void worker_to_brig(worker val, QString ID_brig);//INSERT
    void worker_to_brig(QString ID_w, QString ID_brig);//INSERT

    QList <QString> avto_worker_dolg_list();//AVTO

    QList <QString> avto_special_brig_list();//AVTO   бригада

    //----------------------------------------------------------------оборудование
    QList <technics> eqw_all_load(technics share);//SELECT

    QList <technics> eqw_with_group (QString ID_gr);//SELECT

    QList <technics> avto_eq_list_free(technics sha);//SELECT//переделать с учетом  верхнего

    void eqw_dell(QString ID);//DELETE

    void del_eqw_from_brig(QString ID);//DELETE

    void insert_new_eqw(technics val);//INSERT

    void eqw_to_brig(technics val, QString ID_brig);//INSERT
    void eqw_to_brig(QString ID_e, QString ID_brig);//INSERT

    //-----------------------------------------------------------постройки

    QList <building> building_main_class_ret(building sha);//SELECT

    QString ret_building_ID_with_name(QString name);//SELECT

    void insert_level(QString lev_str, QString id_building_s,  level val);//INSERT

    void insert_need_material_for_b( QString ID_b, material_ned material);//INSERT

    void insert_new_building(building val);//INSERT

    //-----------------------------------------------------------клиент
    void insert_client_info(client val);//insert

    double need_to_pay(QString ID_progect);//select
    double sum_pay(QString ID_b);//select

    void update_pay_sum(QString ID_b, double pay_sum);//update
    void update_client(client cl);
    QList<client> is_client_with_passport(QString passport);
    //-----------------------------------------------------------занятость бригады
    //
    //-----------------------------------------------------------другие
     QList <person_plas_prog> person_with_ID_building(QString ID_B);//SELECT информация о заказчике с постройкий ID_B
     void new_brig_with_special(QString special_name);//INSERT

     QString  ret_id_special_with_name(QString name_spec);

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
