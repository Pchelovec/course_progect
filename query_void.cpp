#include "query_result.h"
void query_result::reset()
{
    if(!DB->DB.open())
    {
        DB->remove();
    }
}
void query_result::connect()
{
    DB=new database;
}
void query_result::close_connect()
{
    delete DB;
}
void query_result::material_up_summ_count(QString SUM, QString ID)
{
    reset();
    QString q("update all_material set count=");
    q=q+SUM+" where id_material="+ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::insert_material(material val)
{
  reset();
    QString q("insert into all_material(name, price, naznachenie, izmerenie, count) values(");
    q=q+"'"+val.name+"', '"+val.price+"'";
    if (val.naznach!="NULL" && val.naznach!="") q=q+",'"+val.naznach+"'";
    else q=q+", NULL";
    if (val.izmer!="NULL" && val.izmer!="")q=q+", '"+val.izmer+"'";
    else q=q+", NULL";
    q=q+", "+val.count+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::material_up_2_to_1 (material val)
{
reset();
    QString q("update all_material set count=");
    q=q+val.count+", price='"+val.price+"', naznachenie='"+val.naznach+"', izmerenie='"+val.izmer+"'";
    q=q+" where ID_material= "+val.ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::insert_new_eqw(technics val)
{
  reset();
    QString q;
    q="insert into equipment (eq_name, eq_namber, eq_year, eq_buy_date) values (";
    q=q+"'"+val.name+"'"+", '"+val.namber+"', ";
    if (val.Year_vip!="NULL" && val.Year_vip!="")
    {
        q=q+"'"+val.Year_vip+"', ";
    }
    else
    {
        q=q+"NULL, ";
    }
    q=q+"' "+val.Date_pok+"');";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::insert_new_worker(worker val)
{
    reset();
    QString q;
    q="insert into worker (adress, post, birthday, fio, price) values (";
    if (val.adress!="" && val.adress!="NULL")
    {
        q=q+"'"+val.adress+"'";
    }
    else
    {
        q=q+val.adress;
    }
    if (val.post!="" && val.post!="NULL")
    {
        q=q+", '"+val.post+"'";
    }
    else
    {
        q=q+", NULL";
    }
    if (val.birthday!="" &&val.birthday!="NULL")
    {
        q=q+", '"+val.birthday+"'";
    }
    else
    {
        q=q+", NULL";
    }
    if (val.fio!="" && val.fio!="NULL")
    {
       q=q+", '"+val.fio+"'";
    }
    else
    {
        q=q+", NULL";
    }
    if (val.pay!="" && val.pay!="NULL")
    {
        q=q+",'"+val.pay+"');";
    }
    else
    {
        q=q+", NULL);";
    }
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::worker_to_brig(worker val, QString ID_brig)
{
    reset();
    QString q;
    //поиск id
    QList <QString> list_worker;
    q="select ID_worker from worker where fio='"+val.fio+"'";
    if (val.adress!="" &&val.adress!="0" &&val.adress!="NULL")
    {
        q=q+" and adress='"+val.adress+"'";
    }
    if (val.pay!="0" && val.pay!="" && val.pay!="NULL")
    {
        q=q+" and price='"+val.pay+"'";
    }
    if (val.post!="0" && val.post!="" && val.post!="NULL")
    {
        q=q+" and post='"+val.post+"'";
    }
    q=q+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
    while (DB->query->next())
    {
        list_worker.push_back(DB->query->value(0).toString());
    }
    if (list_worker.size()==1)
    {
        worker_to_brig(list_worker[0], ID_brig);
    }
}
void query_result::worker_to_brig(QString ID_w, QString ID_brig) //1
{
    reset();
    QString q("insert into grup (worker_ID, group_id) values(");
    q=q+ID_w+", "+ID_brig+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::eqw_to_brig(technics val, QString ID_brig)//name
{
reset();
    QString q;
    //поиск id
    QList <QString> list_id;
    q="select eq_namber from equipment where name='"+val.name+"';";
    qDebug()<<q<<endl;
    DB->query->exec(q);
    while (DB->query->next())
    {
        list_id.push_back(DB->query->value(0).toString());
    }
    if (list_id.size()==1)
    {
       eqw_to_brig(list_id[0], ID_brig);
    }//иначе невозможно
}
void query_result::eqw_to_brig(QString ID_e, QString ID_brig)//1
{
reset();
    QString q("insert into group_eq (id_namber, id_brig) values(");
    q=q+ID_e+", "+ID_brig+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::eqw_dell(QString ID)
{
    reset();
    QString q("delete from equipment where eq_namber=");
    q=q+ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::del_worker_from_brig(QString ID)
{
    reset();
    QString q;
    q="delete from grup where worker_ID="+ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::del_eqw_from_brig(QString ID)
{
    reset();
    QString q;
    q="delete from group_eq where id_namber="+ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::worker_del(QString ID)
{
    reset();
    QString q;
    q="delete from worker where ID_worker="+ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::new_brig_with_special(QString special_name)
{
    reset();
    QString ID;
    QString s1("SELECT special.id FROM special WHERE special.`name`='");
    s1=s1+special_name+"';";
    qDebug()<<s1<<endl;
    DB->query->exec(s1);

    if (DB->query->next() && DB->query->value(0).toString()!="")
    {
    qDebug()<<"уже есть бригада с таким именем"<<endl;
    ID=DB->query->value(0).toString();
    DB->query->clear();
    }
    else
    {
       qDebug()<<"бригады с таким именем нет"<<endl;
        QString q("insert into special (name) value('");
        q=q+special_name+"');";
        DB->query->clear();
        qDebug()<<q<<endl;
        DB->query->exec(q);

        DB->query->clear();
        qDebug()<<s1<<endl;
        DB->query->exec(s1);
        DB->query->next();

        ID=DB->query->value(0).toString();
        qDebug()<<ID<<"++++++*********++++++++="<<endl;
        DB->query->clear();
    }
    QString s("insert into special_brig (id_special) value(");
    s=s+ID+");";
    qDebug()<<s<<endl;
    DB->query->exec(s);
}
QString query_result::insert_new_building(building val)//возвращает id проекта здания
{
    reset ();
    if (val.is_ynical_bool)
    {
        val.id_ynical_string="1";
    }
    else
    {
        val.id_ynical_string="0";
    }
    QString q("insert into building (name, building_ynical, standart_time, meter, price) values(");
    q=q+"'"+val.name+"', "+val.id_ynical_string +", "+val.Standart_time_building+", "+val.metter+", '"+val.price+"');";
    qDebug()<<q<<endl;
    DB->query->exec(q);
    DB->query->clear();
    QString ID;
    ID=ret_building_ID_with_name(val.name);
    int row_level=val.time_plan.size();
    for (int i=0;i<row_level;i++)
    {
        insert_level(QString ::number(i),ID, val.time_plan[i]);
    }
    int row_worker=val.neded_material.size();
    for (int i=0;i<row_worker;i++)
    {
        insert_need_material_for_b(ID, val.neded_material[i]);
    }
    return ID;
}
void query_result::insert_level(QString lev_str, QString id_building_s,  level val)
{
    reset ();
    QString q("INSERT INTO building_plan (level, building_id_plan, day, special) VALUES (");
    QString id_special=ret_id_special_with_name(val.special_brig);
    q=q+lev_str+", "+id_building_s+", "+val.day_count+", "+id_special+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::insert_need_material_for_b(QString ID_b, material_ned material_)
{
    reset ();
    QString q("insert into neded_materials (number_of_building, namber_material, count) values(");
    material temp;
    temp.name=material_.name_material;
    QList <material> list_mat=mater_like_my(temp);
    material mat=list_mat[0];
    QString ID_M=mat.ID;
    q=q+ID_b+", "+ID_M+", "+material_.count_material+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::insert_client_info(client val)
{
    reset();
    QList <client> list=is_client_with_passport(val.passport);
    if (list.size()==1)
    {
        //клиент уже есть обновить информацию
        update_client(val);
    }
    else
    {
        //клиента нет
        QString q("insert into client (client_passport, client_fio, client_phone, client_bir, client_places_life) values(");
        q=q+"'"+val.passport+"', '"+val.FIO+"', "+val.phone;
        if (val.year_birthday!="")
        {
            q=q+", "+val.year_birthday;
        }
        else
        {
            q=q+", NULL";
        }
        if (val.plases_life!="")
        {
            q=q+", '"+val.plases_life+"'";
        }
        else
        {
            q=q+", NULL";
        }
        q=q+");";
        qDebug()<<q<<endl;
        DB->query->exec(q);
    }
}
void query_result::update_pay_sum(QString ID_b, double pay_sum)
{
    reset();
    QString q;
    q="update progect set oplata=";
    double pay_now=sum_pay(ID_b);
    q=q+QString::number(pay_sum+pay_now)+" where ID="+ID_b+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::update_client(client cl)
{
    reset();
    QString q;
    q="update client set ";
    q=q+" client_fio='"+cl.FIO+"', client_phone="+cl.phone+", client_bir=";
    if(cl.year_birthday!="" || cl.year_birthday!="0")
    {
        q=q+cl.year_birthday+", ";
    }
    else
    {
        q=q+"NULL, ";
    }
    q=q+" client_places_life=";
    if (cl.plases_life!="")
    {
        q=q+"'"+cl.plases_life+"'";
    }
    else
    {
        q=q+"NULL";
    }
    q=q+" where client_passport='"+cl.passport+"'";
    q=q+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::make_step_building(building val, QString ID_brig, QString progect_id)
{
    reset();
    QString q("insert into group_time (id_brig, date_start, date_fin, id_progect) values(");
        q=q+ID_brig+", '"+val.time_pair.date_start+"', '"+val.time_pair.date_fin+"', "+progect_id;
    q=q+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
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
void query_result::worker_change_status(QString id_worker)
{
   reset();
   QString s("update worker set worker_status=1 where worker.id_worker="+id_worker+";");
   qDebug()<<s<<endl;
   DB->query->exec(s);
}
