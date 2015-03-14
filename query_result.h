#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include "database.h"
#include <QDebug>
#include <Qvector>
#include <QString>
#include "building.h"
#include "technics.h"
#include "worker.h"
#include "material.h"
using namespace std;
class query_result
{
public:
    query_result();
    ~query_result();
                                                        //SELECT
    QList <technics> eqw_all_load();//+
    QList <worker> worker_all();//+1
    QList <building> building_main_class_ret();//+

    QList <material> mater_like_my(QString name);

    void building_main(QVector <QString>);

    QList <QString> ID_group_with_name(QString name);
                                                        //DELETE
    void worker_del(QString ID);

    void eqw_dell(QString ID);

    void del_worker_from_brig(QString ID);

    void del_eqw_from_brig(QString ID);
                                                        //INSERT
    void insert_material(material val);

    void insert_new_eqw(technics val);

    void insert_new_worker(worker val);

    void worker_to_brig(worker val);
    void worker_to_brig(QString ID);

    void eqw_to_brig(technics val);
    void eqw_to_brig(QString ID);


                                                        //update
    void material_up_summ_count(QString SUM, QString ID);

    void material_up_2_to_1 (material val);


                                                        //AVTO
    QList <technics> avto_eq_list_free();

    QList <QString> avto_material_list_izmer();

    QList <QString> avto_material_list_naz();

    QList <QString> avto_special_brig_list();

    QList <QString> worker_dolg_list();

    QList <worker> avto_worker_list_free();



private:
    database *DB;
    void connect();
    void close_connect();
};

#endif // QUERY_RESULT_H
