#include "query_result.h"

query_result::query_result()
{
    connect();
}
query_result::~query_result()
{
    close_connect();
}
void query_result::connect()
{
DB=new database;
}

void query_result::close_connect()
{
    delete DB;
}

QList <building> query_result::building_main_class_ret()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QString q("SELECT building.`name`, building.building_ynical, building.`standart-time`, building.meter, building.price, building.ID_b, building.description FROM building;");
    QList <building> local_res;
    DB->query->clear();
    DB->query->exec(q);
    int row=0;
    while (DB->query->next())
    {
        row++;
        qDebug()<<row;
        building temp;
            temp.name=DB->query->value(0).toString();
            temp.is_ynical_bool=DB->query->value(1).toBool();
            if (temp.is_ynical_bool)
            {
                temp.id_ynical_string="+";
            }
            else
            {
                temp.id_ynical_string="_";
            }
            temp.Standart_time_building=DB->query->value(2).toString();
            temp.metter=DB->query->value(3).toString();
            temp.price=DB->query->value(4).toString();
            temp.ID=DB->query->value(5).toString();
        local_res.push_back(temp);
    }
    DB->query->clear();
    return local_res;
}

QList <technics> query_result::eqw_all_load()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <technics> result;
    QString q("select * from equipment;");
    DB->query->clear();
    DB->query->exec(q);
    while (DB->query->next())
    {
        technics temp;
        temp.name=DB->query->value(0).toString();
        temp.namber=DB->query->value(1).toString();
        temp.Year_vip=DB->query->value(2).toString();
        temp.Date_pok=DB->query->value(3).toString();
        result.push_back(temp);
    }
    return result;
}

QList <worker> query_result::worker_all()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
QList <worker> result;
QString q("select * from worker;");
DB->query->exec(q);
while(DB->query->next())
{
    worker temp;
    temp.adress=DB->query->value(0).toString();
    temp.post=DB->query->value(1).toString();
    temp.birthday=DB->query->value(2).toString();
    if (temp.birthday=="0")
    {
        temp.birthday="";
    }
    temp.fio=DB->query->value(3).toString();
    temp.id=DB->query->value(4).toString();
    temp.pay=DB->query->value(5).toString();
  result.push_back(temp);
}
return result;
}

QList <technics> query_result::avto_eq_list_free()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <technics> result;
    DB->query->clear();
    DB->query->exec("call eq_list_free();");
    while (DB->query->next())
    {
        technics temp;
        temp.name = DB->query->value(0).toString();
        temp.Date_pok=DB->query->value(1).toString();
        temp.namber=DB->query->value(2).toString();
      result.push_back(temp);
    }
    return result;
}

QList <QString> query_result::avto_material_list_izmer()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <QString> result;
    DB->query->clear();
    DB->query->exec("call material_list_izmer();");
    while (DB->query->next())
    {
        QString temp;
        temp = DB->query->value(0).toString();
      result.push_back(temp);
    }
    return result;
}

QList <QString> query_result::avto_material_list_naz()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <QString> result;
    DB->query->clear();
    DB->query->exec("call material_list_naz();");
    while (DB->query->next())
    {
        QString temp;
        temp = DB->query->value(0).toString();
      result.push_back(temp);
    }
    return result;
}

QList <QString> query_result::avto_special_brig_list()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <QString> result;
    DB->query->clear();
    DB->query->exec("call special_brig_list();");
    while (DB->query->next())
    {
        QString temp;
        temp = DB->query->value(0).toString();
      result.push_back(temp);
    }
    return result;
}

QList <QString> query_result::worker_dolg_list()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <QString> result;
    DB->query->clear();
    DB->query->exec("call worker_dolg_list();");
    while (DB->query->next())
    {
        QString temp;
        temp = DB->query->value(0).toString();
      result.push_back(temp);
    }
    return result;
}

QList <worker> query_result::avto_worker_list_free()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <worker> result;
    DB->query->clear();
    DB->query->exec("call worker_list_free();");
    while (DB->query->next())
    {
        worker temp;
        temp.post = DB->query->value(0).toString();
        temp.fio=DB->query->value(1).toString();
        temp.id=DB->query->value(2).toString();
      result.push_back(temp);
    }
    return result;
}


QList <material> query_result::mater_like_my(QString name)
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QList <material> result;
    DB->query->clear();
    QString q;
    q="select * from all_material where name like '"+name+"';";
    DB->query->exec(q);
    while (DB->query->next())
    {
        material temp;
        temp.name=DB->query->value(0).toString();
        temp.price=DB->query->value(1).toString();
        temp.naznach=DB->query->value(2).toString();
        temp.izmer=DB->query->value(3).toString();
        temp.count=DB->query->value(4).toString();
        temp.count_int=DB->query->value(4).toInt();
        temp.ID=DB->query->value(5).toString();
      result.push_back(temp);
    }
    return result;
}

QList <QString> query_result::ID_group_with_name(QString name)
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QString s("SELECT special_brig.id_brig FROM special_brig , special WHERE special_brig.id_special = special.id AND special.`name`='");
    s=s+name+"';";
    DB->query->exec(s);
    QList <QString> result;
    while (DB->query->next())
    {
        result.push_back(DB->query->value(0).toString());
    }
  return result;
}
