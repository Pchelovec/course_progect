#include "query_result.h"
void query_result::reset()
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
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
    }
    //иначе невозможно
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
