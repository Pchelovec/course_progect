#include "query_result.h"

query_result::query_result()
{
    connect();
}
query_result::~query_result()
{
    close_connect();
}

QList <building> query_result::building_main_class_ret(building sha)
{
reset();
    QString q("SELECT building.`name`, building.building_ynical, building.`standart_time`, building.meter, building.price, building.ID_b, building.description FROM building where ");
    q=q+"name like'%"+sha.name+"%'";
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
        q=q+" and meter between "+sha.metter_pair.metter_start+" and "+sha.metter_pair.metter_fin;
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
    if (sha.ID!="")
    {
        q=q+" and ID_b = '"+sha.ID+"'";
    }
    q=q+";";
    QList <building> local_res;
    DB->query->clear();
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
    q=q+"eq_name like '%"+share.name+"%'";
    q=q+" and eq_namber like '%"+share.namber+"%' ;";
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
q=q+" fio like'%"+wor.fio+"%' "+"and post like'%"+wor.post+"%' ";
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
            s=s+"e.eq_name like '%"+sha.name+"%'";
            s=s+" and e.eq_namber like'%"+sha.namber+"%';";
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
            s=s+"w.post like'%"+sha.post+"%' ";
            s=s+"and w.fio like '%"+sha.fio+"%';";

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
    reset();
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
QString query_result::ret_building_ID_with_name(QString name)
{
    reset();
    QString s("select ID_b from building where name='");
    s=s+name+"';";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    if (DB->query->next())
        return DB->query->value(0).toString();
    else return "";
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

QList<client> query_result::is_client_with_passport(QString passport)
{
    reset();
    QList<client> result;
    QString s;
    s="select * from client where client_passport like'";
    s=s+passport+"';";
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

QString query_result::save_progect(QString client_passport, QString house_id)
{
    reset();
    QDate dat;
    QString q;
    QTime time_now=time_now.currentTime();
    q="insert into progect (oplata, passport_client, house_id, data_) values (0, ";
    q=q+"'"+client_passport+"', "+house_id+", "+"'"+QString::number(dat.currentDate().year())+"-"+QString::number(dat.currentDate().month())+"-"+QString::number(dat.currentDate().day())+" ";
    q=q+QString::number(time_now.hour())+":"+QString::number(time_now.minute())+":"+QString::number(time_now.second());
    q=q+"');";
    qDebug()<<q<<endl;
    DB->query->exec(q);

return return_progect_id(client_passport, house_id);
}

QString query_result::return_progect_id(QString client_passport, QString house_id)
{
    reset();
    //QString ID_progect;

    QString s("");
    s="select ID, data_ from progect where passport_client='"+client_passport+"' and  house_id="+house_id;
    QList <QDate> date;
    QList <QString> id;
    s=s+" order by data_ desc;";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    if (DB->query->next())
    {
        return DB->query->value(0).toString();
    }
    else
    {
        return "";
    }
}

QString query_result::ret_id_house_with_id_progect(QString ID_progect)
{
    reset();
    QString ID_house;
    QString s("");
    s="select house_id from progect where ID="+ID_progect;


    qDebug()<<s<<endl;
    DB->query->exec(s);
    if (DB->query->next())
        ID_house=DB->query->value(0).toString();
    return ID_house;
}

QList <level> query_result::ret_list_time_plan_for_b(QString ID_building)
{
    reset();
    QString s("SELECT building_plan.`level`, building_plan.`day`, building_plan.special"
              " FROM building_plan"
              " where building_id_plan=");
            s=s+ID_building+"  ORDER BY `level` ASC;";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    QList <level> result;
    while (DB->query->next())
    {
        level temp;
        temp.step=DB->query->value(0).toString();
        temp.day_count=DB->query->value(1).toString();
        temp.special_brig=DB->query->value(2).toString();
        result.push_back(temp);
    }
    return result;
}

QList<building> query_result::return_list_worked_plan_now(QString ID_special)
{
    reset();
    QString s("SELECT group_time.date_start, group_time.date_fin, group_time.id_brig"
              " FROM special_brig , group_time , special"
              " WHERE special_brig.id_brig = group_time.id_brig AND special.id = special_brig.id_special and special.id=");
            s=s+ID_special+" ORDER BY date_fin;";

     qDebug()<<s<<endl;
     DB->query->exec(s);
     QList <building> result;

     while (DB->query->next())
     {
         building temp;
            temp.time_pair_date.date_start=DB->query->value(0).toDate();
            temp.time_pair_date.date_fini=DB->query->value(1).toDate();
            temp.ID=DB->query->value(2).toString();//id бригады
         result.push_back(temp);
     }
     return result;
}

QList <QString> query_result::ret_list_brig_with_special(QString ID_special)
{
    reset();
    QString s(" SELECT s_b.id_brig FROM special_brig s_b"
              " WHERE s_b.id_brig=any(SELECT group_eq.id_brig FROM group_eq GROUP BY group_eq.id_brig) or s_b.id_brig=any (SELECT grup.group_id FROM grup GROUP BY grup.group_id)"
              " GROUP BY s_b.id_special"
              " HAVING s_b.id_special= ");
    s=s+ID_special+";";

    qDebug()<<s<<endl;
    DB->query->exec(s);
    QList <QString> result;

    while (DB->query->next())
    {
        QString temp;
           temp=DB->query->value(0).toString();
        result.push_back(temp);
    }
    return result;
}

QList <material> query_result::material_for_building(QString ID_b)
{
    reset();
    QList <material> result;
    QString s("");

    s=s+" SELECT neded_materials.namber_material, neded_materials.count"
            " FROM neded_materials"
            " WHERE neded_materials.number_of_building="+ID_b+";";


    qDebug()<<s<<endl;
    DB->query->exec(s);
    while (DB->query->next())
    {
        material temp;
            temp.ID=DB->query->value(0).toString();
            temp.count=DB->query->value(1).toString();
        result.push_back(temp);
    }
    return result;
}

QList <material> query_result::material_with_param(material val)
{
    reset();
    QList <material> result;

    QString s("select * from all_material where ");
    s=s+"name like'%"+val.name+"%' ";
    if (val.ID!="")
    {
        s=s+" and ID_material="+val.ID;
    }

    qDebug()<<s<<endl;
    DB->query->exec(s);
    while (DB->query->next())
    {
        material temp;
        temp.name=DB->query->value(0).toString();
        temp.count=DB->query->value(4).toString();
        result.push_back(temp);
    }
    return result;
}

building query_result::info_for_progect(period_date dat, bool ynic)
{
    reset();
    building result;

        QString s("SELECT SUM(progect.oplata), SUM(building.price), SUM(1)"
                  " FROM progect ,building"
                  " WHERE progect.house_id = building.ID_b and building.building_ynical");

       if (ynic)
       {
           s=s+" <>0 ";
       }
       else
       {
           s=s+"=0";
       }
       s=s+" and data_ BETWEEN '"+dat.date_start.toString("yyyy-MM-dd")+"' and '"+dat.date_fini.toString("yyyy-MM-dd")+"'";
       s=s+" GROUP BY building_ynical;";
       qDebug()<<s<<endl;
       DB->query->exec(s);
       if (DB->query->next())
       {
           result.price_pair.price_start=DB->query->value(0).toString();
           result.price_pair.price_fin=DB->query->value(1).toString();
           result.ID=DB->query->value(2).toString();
       }
    return result;
}

building query_result::info_about_progect(QString ID_P)
{
    reset();
    building result;

    QString s(" SELECT client.client_fio, building.price"
              " FROM progect , building , client"
              " WHERE progect.house_id = building.ID_b AND client.client_passport = progect.passport_client AND progect.ID=");
    s=s+ID_P+";";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    if (DB->query->next())
    {
        result.ID=DB->query->value(0).toString();
        result.price=DB->query->value(1).toString();
    }
    return result;
}

period_date query_result::min_max_date_progect(QString ID_P)
{
    reset();
    period_date result;

        QString s("SELECT max(group_time.date_fin)"
                  " FROM group_time"
                  " where group_time.id_progect=");


                s=s+ID_P+";";
                qDebug()<<s<<endl;
                DB->query->exec(s);
                if (DB->query->next())
                {
                    result.date_fini=DB->query->value(0).toDate();
                }
    reset();

    QString s2("SELECT min(group_time.date_start)"
              " FROM group_time"
              " where group_time.id_progect=");

            s2=s2+ID_P+";";
            qDebug()<<s2<<endl;
            DB->query->exec(s2);
            if (DB->query->next())
            {
                result.date_start=DB->query->value(0).toDate();
            }
        return result;
}

QList <building> query_result::info_plan_building(QString ID_b)
{
    reset();
    QList <building> result;

        QString s("SELECT group_time.date_start, group_time.date_fin, special.`name`, group_time.id_brig"
                  " FROM group_time , special , special_brig"
                  " WHERE special.id = special_brig.id_special AND group_time.id_brig = special_brig.id_brig AND group_time.id_progect=");

        s=s+ID_b+" ORDER BY date_start asc;";
        qDebug()<<s<<endl;
        DB->query->exec(s);
        while (DB->query->next())
        {
            building temp;
                temp.time_pair.date_start=DB->query->value(0).toString();
                temp.time_pair.date_fin=DB->query->value(1).toString();
                temp.name=DB->query->value(2).toString();
                temp.ID=DB->query->value(3).toString();//id бригады
            result.push_back(temp);
        }
    return result;
}
