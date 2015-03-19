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

QList <building> query_result::building_main_class_ret(building sha)
{
reset();
    QString q("SELECT building.`name`, building.building_ynical, building.`standart_time`, building.meter, building.price, building.ID_b, building.description FROM building where ");
    q=q+"name like'"+sha.name+"%'";
    if (sha.time_pair.date_start!="0" && sha.time_pair.date_start!="" && sha.time_pair.date_fin!="0" && sha.time_pair.date_fin!="")
    {
        q=q+" and standart_time between "+sha.time_pair.date_start+" and "+sha.time_pair.date_fin;
    }
    else
    {
        if (sha.time_pair.date_start!="0" && sha.time_pair.date_start!="")
        {
            q=q+" and standart_time>"+sha.time_pair.date_start;
        }
        else
        {
            if (sha.time_pair.date_fin!="0" && sha.time_pair.date_fin!="")
            {
                q=q+" and standart_time<"+sha.time_pair.date_fin;
            }
        }
    }

    if (sha.metter_pair.metter_start!="0" && sha.metter_pair.metter_start!="" && sha.metter_pair.metter_fin!="0" && sha.metter_pair.metter_fin!="")
    {
        q=q+" and meter between "+sha.time_pair.date_start+" and "+sha.time_pair.date_fin;
    }
    else
    {
        if (sha.metter_pair.metter_start!="0" && sha.metter_pair.metter_start!="")
        {
            q=q+" and meter>"+sha.metter_pair.metter_start;
        }
        else
        {
            if (sha.metter_pair.metter_fin!="0" && sha.metter_pair.metter_fin!="")
            {
                q=q+" and meter<"+sha.metter_pair.metter_fin;
            }
        }
    }
    if (sha.price_pair.price_start!="0" && sha.price_pair.price_start!="" && sha.price_pair.price_fin!="0" && sha.price_pair.price_fin!="")
    {
        q=q+" and price between "+sha.price_pair.price_start+" and "+sha.price_pair.price_fin;
    }
    else
    {
        if (sha.price_pair.price_start!="0" && sha.price_pair.price_start!="")
        {
            q=q+" and price>"+sha.price_pair.price_start;
        }
        else
        {
            if (sha.price_pair.price_fin!="0" && sha.price_pair.price_fin!="")
            {
                q=q+" and price<"+sha.price_pair.price_fin;
            }
        }
    }
    q=q+";";
    QList <building> local_res;
    //DB->query->clear();
    DB->query->exec(q);
    qDebug()<<q<<endl;
    while (DB->query->next())
    {
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

QList <technics> query_result::eqw_all_load(technics share)
{
reset();
    QList <technics> result;
    QString q("select * from equipment where ");
    q=q+"eq_name like '"+share.name+"%'";
    q=q+" and eq_namber like '"+share.namber+"%' ;";
    qDebug()<<q<<endl;
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

QList <worker> query_result::worker_all(worker wor)
{
reset();
QList <worker> result;
QString q("select * from worker where");
q=q+" fio like'"+wor.fio+"%' "+"and post like'"+wor.post+"%' ";
if (wor.pay_fin!="0" && wor.pay_fin!="" && wor.pay_start!="0" && wor.pay_start!="")
{
    q=q+"and price between "+wor.pay_start+" and "+wor.pay_fin;
}
else
{
    if (wor.pay_start!="0" && wor.pay_start!="")
    {
        q=q+"and price>"+wor.pay_start;
    }
    else
    {
        if (wor.pay_fin!="0" && wor.pay_fin!="")
        {
            q=q+"and price<"+wor.pay_fin;
        }
    }
}

q=q+";";
qDebug()<<q<<endl;
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

QList <technics> query_result::avto_eq_list_free(technics sha)
{
reset();
QString s("SELECT e.eq_name, e.eq_buy_date, e.eq_namber FROM equipment e"
          " WHERE e.eq_namber <> ALL ( SELECT group_eq.id_namber from group_eq ) and ");
            s=s+"e.eq_name like '"+sha.name+"%'";
            s=s+" and e.eq_namber like'"+sha.namber+"%';";
            qDebug()<<s;
        QList <technics> result;

    DB->query->exec(s);

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

QList <worker> query_result::avto_worker_list_free(worker sha)
{
reset();
    QList <worker> result;
    DB->query->clear();
    QString s("SELECT w.post, w.fio, w.ID_worker FROM worker w"
              " WHERE w.ID_worker <> ALL (SELECT grup.worker_ID FROM grup) and ");
            s=s+"w.post like'"+sha.post+"%' ";
            s=s+"and w.fio like '"+sha.fio+"%';";

    qDebug()<<s<<endl;
    DB->query->exec(s);
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
    QString s("SELECT client.client_fio, client.client_phone, progect.oplata, progect.ID"
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
double query_result::need_to_pay(QString ID_progect)
{
    reset();
    QString s("SELECT (building.price-progect.oplata) FROM building , progect WHERE progect.house_id = building.ID_b and progect.ID=");
    s=s+ID_progect+";";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    if(DB->query->next())
    {
        return DB->query->value(0).toDouble();
    }
    else return -1;
}
double query_result::sum_pay(QString ID_b)
{
    reset();
    QString q;
    q="select oplata from progect where ID="+ID_b+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
    if (DB->query->next())
        return DB->query->value(0).toDouble();
    else
        return -1;
}
QList<client> query_result::is_client_with_passport(QString passport)
{
    reset();
    QList<client> result;
    QString s;
    s="select * from client where client_passport=";
    s=s+passport+";";
        qDebug()<<s<<endl;
        DB->query->exec(s);
        while(DB->query->next())
        {
            client temp;
            temp.passport=DB->query->value(0).toString();
            temp.FIO=DB->query->value(1).toString();
            temp.phone=DB->query->value(2).toString();
            temp.year_birthday=DB->query->value(3).toString();
            temp.plases_life=DB->query->value(4).toString();
            result.push_back(temp);
        }
    return result;
}
