#include "plan_building_time.h"

plan_building_time::plan_building_time()
{
QUEry =new query_result;
}

plan_building_time::~plan_building_time()
{

}

void plan_building_time::make_and_save_time_plan_for_building(QString ID_progect, QDate user_start_date)
{
    //id здания с № проекта

//    building temp_s;
//    temp_s.ID=ID_progect;

    QString house_id=QUEry->ret_id_house_with_id_progect(ID_progect);
    if (house_id!="")
    {
    QList <level> list_need_special=QUEry->ret_list_time_plan_for_b(house_id);
    //этапы постройки (и необход специальность) с № здания
    if (list_need_special.size()!=0)
    {
        int levels_count=list_need_special.size();
        for (int i=0;i<levels_count;i++)
        {
            save_best_time_for_level(list_need_special[i], user_start_date,ID_progect);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("ошибка автоматического планирования график постройки для здания пуст");
        msgBox.exec();
        return;
    }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("ошибка автоматического планирования проект не найден");
        msgBox.exec();
        return;
    }
}

void plan_building_time::save_best_time_for_level(level val, QDate &min_start_time, QString ID_progect)
{
    QList <QDate> time_for_all_brig;
    qDebug()<<"подбор времени для этапа"<<val.step+"=============="<<endl;

    QList<building> time_list= QUEry->return_list_worked_plan_now(val.special_brig); //список бригад (и их временная занятость)

    QSet <QString> set_id_brig;

    for (int i=0;i<time_list.size();i++)
    {
        set_id_brig.insert(time_list[i].ID);
    }
    QList<QString> dop_list=QUEry->ret_list_brig_with_special(val.special_brig);
    for (int i=0;i<dop_list.size();i++)//бобавить бригады которые выходят на работу 1 раз
    {
        set_id_brig.insert(dop_list[i]);
    }
    if (set_id_brig.size()!=0)
    {
    //проверка на 0 бригад
    bool zero=false;
    int set_size=set_id_brig.size();
    for (int i=0;i<set_size;i++)
    {
        QList <period_date> list_with_id;
        for (int j=0;j<time_list.size();j++)
        {
            if (*(set_id_brig.begin()+i)==time_list[j].ID)
            {
                period_date temp;
                temp.date_start=time_list[j].time_pair_date.date_start;
                temp.date_fini=time_list[j].time_pair_date.date_fini;
                list_with_id.push_back(temp);
            }
        }
        //выбор оптимального времени для локального этапа каждой из бригады
        bool is_optimal=false;
        QDate date_start;
        int size_list_id=list_with_id.size();
            for (int j=0;j<size_list_id-1;j++)
            {
                QDate local_min=min_start_time;
                if (!is_optimal && list_with_id[j].date_fini<local_min && local_min.addDays(val.day_count.toInt())<list_with_id[j+1].date_start)
                {
                    is_optimal=true;
                    date_start=list_with_id[j].date_fini.addDays(1);
                    time_for_all_brig.push_back(date_start);
                }//сохранить для бригады
            }
            if (!is_optimal)
            {
                if (size_list_id==0)
                {
                    QDate te;
                    te=min_start_time;
                    time_for_all_brig.push_back(te);
                }
                else
                {
                    date_start=list_with_id[list_with_id.size()-1].date_fini.addDays(1);
                    time_for_all_brig.push_back(date_start);
                }
            }

    }//сохранить время для этапа,  make_step_building

    QDate min_date=time_for_all_brig[0];
    int i_min_ID_brig=0;
    for (int i=0;i<time_for_all_brig.size();i++)//сравнение и выбор минимального времени из всех возможных бригад
    {
        if (time_for_all_brig[i]<min_date)
        {
            min_date=time_for_all_brig[i];
            i_min_ID_brig=i;
        }
    }

    QDate buf_date=min_date.addDays(1);
    QDate fin_date=buf_date.addDays(val.day_count.toInt());
    building t;
    QString id_bri("");

    id_bri=*(set_id_brig.begin()+i_min_ID_brig);

    t.time_pair.date_start=QString::number(buf_date.year())+"-"+QString::number(buf_date.month())+"-"+QString::number(buf_date.day());
    t.time_pair.date_fin=QString::number(fin_date.year())+"-"+QString::number(fin_date.month())+"-"+QString::number(fin_date.day());
    QUEry->make_step_building(t, id_bri, ID_progect);

    qDebug()<<"время изменено с "<<min_start_time.toString();
    min_start_time=fin_date;//изменение временного порога проекта
    qDebug()<<"на "<<min_start_time.toString()<<endl;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("нет бригады, для строительства здания");
        msgBox.exec();
        return;
    }
}//оптимальное время постройки выбрано для этапа

//period plan_building_time::period_date_to_period_str(period_date val)
//{
//    period result;

//        result.date_start=QString::number(val.date_start.year())+"-"+QString::number(val.date_start.month())+"-"+QString::number(val.date_start.day());
//        result.date_fin=QString::number(val.date_fini.year())+"-"+QString::number(val.date_fini.month())+"-"+QString::number(val.date_fini.day());

//    return result;
//}

void plan_building_time::sub_material_for_building(QString ID_building)
{
    qDebug()<<"расчет материалов"<<endl;
}