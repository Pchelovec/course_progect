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
reset();
    QString q("SELECT building.`name`, building.building_ynical, building.`standart_time`, building.meter, building.price, building.ID_b, building.description FROM building;");
    QList <building> local_res;
    DB->query->clear();
    DB->query->exec(q);
    qDebug()<<q<<endl;
    //int row=0;
    while (DB->query->next())
    {
        //row++;
        //qDebug()<<row;
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
    return local_res;
}

QList <technics> query_result::eqw_all_load()
{
reset();
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
reset();
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
reset();
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
reset();
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
reset();
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
reset();
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

QList <QString> query_result::avto_worker_dolg_list()
{
reset();
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
reset();
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
reset();
    QList <material> result;
    QString q;
    q="select * from all_material ";
    if (name=="") q=q+";";
    else
    {
        q=q+"where name like '"+name+"';";
    }
    qDebug()<<q<<endl;
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
reset();
    QString s("SELECT special_brig.id_brig FROM special_brig , special WHERE special_brig.id_special = special.id AND special.`name`='");
    s=s+name+"';";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    QList <QString> result;
    while (DB->query->next())
    {
        result.push_back(DB->query->value(0).toString());
    }
  return result;
}

QList <QString> query_result::avto_special_all()
{
    reset();
    QList <QString> result;
    QString q("call special_all();");
    DB->query->exec(q);
    while (DB->query->next())
    {
        result.push_back(DB->query->value(0).toString());
    }
    return result;
}

QList <worker> query_result::worker_with_group(QString ID_gr)
{
    reset();
    QString s("SELECT worker.adress, worker.post, worker.birthday, worker.fio, worker.ID_worker, worker.price FROM worker , grup WHERE worker.ID_worker = grup.worker_ID and  grup.group_id=");
    s=s+ID_gr+";";
    QList <worker> result;
    qDebug()<<s<<endl;
    DB->query->exec(s);
    while (DB->query->next())
    {
      worker temp;
        temp.adress=DB->query->value(0).toString();
        temp.post=DB->query->value(1).toString();
        temp.birthday=DB->query->value(2).toString();
        temp.fio=DB->query->value(3).toString();
        temp.id=DB->query->value(4).toString();
        temp.pay=DB->query->value(5).toString();
      result.push_back(temp);
    }
    return result;
}

QList <technics> query_result::eqw_with_group (QString ID_gr)
{
    reset();
    QString s("SELECT equipment.eq_name, equipment.eq_namber, equipment.eq_year, equipment.eq_buy_date FROM equipment , group_eq WHERE equipment.eq_namber = group_eq.id_namber and group_eq.id_brig=");
    s=s+ID_gr+";";
    QList <technics> result;
    qDebug()<<s<<endl;
    DB->query->exec(s);
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

QList <person_plas_prog> query_result::person_with_ID_building(QString ID_B)
{
    QList<person_plas_prog> result;
    QString s("SELECT client.client_fio, client.client_phone, progect.oplata, progect.data_"
              " FROM building , progect , client"
              " WHERE client.client_passport = progect.passport_client AND progect.house_id = building.ID_b and building.ID_b=");
    s=s+ID_B+";";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    while (DB->query->next())
    {
        person_plas_prog temp;
            temp.fio=DB->query->value(0).toString();
            temp.ph=DB->query->value(1).toString();
            temp.price=DB->query->value(2).toString();
            temp.date=DB->query->value(3).toString();
        result.push_back(temp);
    }
    return result;
}
QList <material> query_result::material_with_function(QString function)
{
    reset();
    QString s("select * from all_material ");
    if (function=="") s=s+" group by naznachenie;";
    else
    {
        s=s+"where naznachenie=like'"+function+"' group by naznachenie;";
    }
    QList<material> result;
    qDebug()<<s<<endl;
    DB->query->exec(s);
    while (DB->query->next())
    {
       material temp;
        temp.name=DB->query->value(0).toString();
        temp.price=DB->query->value(1).toString();
        temp.naznach=DB->query->value(2).toString();
        temp.izmer=DB->query->value(3).toString();
        temp.count=DB->query->value(4).toString();
       result.push_back(temp);
    }
    return result;
}

QString query_result::material_ret_naznach_with_name(QString name)
{
    reset();
    QString s("select naznachenie from all_material where name='");
    s=s+name+"';";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    DB->query->next();
    return DB->query->value(0).toString();
}

QList<QString> query_result::material_ret_name_with_naznach(QString naznach)
{
    reset();
    QList <QString> result;
    QString s("select name from all_material where naznachenie='");
    if (naznach!="")
    {
    s=s+naznach+"';";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    while(DB->query->next())
    {
        QString temp;
        temp=DB->query->value(0).toString();
        result.push_back(temp);
    }
    }
    return result;
}
double query_result::sum_material(QList<material_ned> val)
{
    reset();
    int row=val.size();
    double result=0;
    for (int i=0;i<row;i++)
    {
        QString s("select price from all_material where name='");
        s=s+val[i].name_material+"';";
        qDebug()<<s<<endl;
        DB->query->exec(s);
        DB->query->next();
        result=result+DB->query->value(0).toDouble()*val[i].count_material.toInt();
    }
    return result;
}
QString query_result::ret_building_ID_with_name(QString name)
{
    reset();
    QString s("select ID_b from building where name='");
    s=s+name+"';";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    DB->query->next();
    return DB->query->value(0).toString();
}

QString  query_result::ret_id_special_with_name(QString name_spec)
{
    reset();
    QString s("select id from special where name='");
    s=s+name_spec+"';";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    DB->query->next();
    return DB->query->value(0).toString();
}
