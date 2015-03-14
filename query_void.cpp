#include "query_result.h"


void query_result::material_up_summ_count(QString SUM, QString ID)
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QString q("update all_material set count=");
    q=q+SUM+" where id_material="+ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}

void query_result::insert_material(material val)
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QString q("insert into all_material(name,price,naznachenie,izmerenie,count) values(");
    q=q+"'"+val.name+"', '"+val.price+"', '"+val.naznach+"', '"+val.izmer+"', "+val.count+");";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}

void query_result::material_up_2_to_1 (material val)
{
    if(!DB->DB.open())
    {
        DB->connect();
    }
    QString q("update all_material set count=");
    q=q+val.count+", price='"+val.price+"', naznachenie='"+val.naznach+"', izmerenie='"+val.izmer+"'";
    q=q+" where ID_material= "+val.ID+";";
    qDebug()<<q<<endl;
    DB->query->exec(q);
}
void query_result::insert_new_eqw(technics val)
{

}

void query_result::insert_new_worker(worker val)
{

}

void query_result::worker_to_brig(worker val)
{

}

void query_result::worker_to_brig(QString ID)
{

}

void query_result::eqw_to_brig(technics val)
{

}

void query_result::eqw_to_brig(QString ID)
{

}
