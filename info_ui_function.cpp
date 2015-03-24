#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::load_progect_info(QList <material_ned> table,QString ID_progect)
{
    set_table_total_material(table);
    set_table_grafic(ID_progect);
    set_individual_info(ID_progect);
    print->set_info(table, ID_progect, QUERY->info_about_progect(ID_progect),QUERY->info_plan_building(ID_progect));
}
void MainWindow::set_table_total_material(QList <material_ned> table)
{
ui->stackedWidget->setCurrentIndex(12);
int table_row=table.size();
if (table_row>0)
{
    ui->material_need_but_out_->clear();
    ui->material_need_but_out_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->material_need_but_out_->setVisible(true);
    ui->material_need_but_out_->setColumnCount(4);
    ui->material_need_but_out_->setHorizontalHeaderLabels(QStringList()<<"название материала"<<"необходимо"<<"есть на складе"<<"докупить");
    ui->material_need_but_out_->setRowCount(table_row);
    ui->material_need_but_out_->setToolTip(tr("материалы для допокупки"));
    for (int i=0;i<table_row;i++)
    {
    QTableWidgetItem *name=new QTableWidgetItem;

         name->setText(table[i].name_material);
         name->setBackgroundColor(Qt::green);

    QTableWidgetItem *need=new QTableWidgetItem;
        need->setText(table[i].count_material);
        need->setBackgroundColor(Qt::green);

    QTableWidgetItem *now=new QTableWidgetItem;
        now->setText(table[i].now);
        now->setBackgroundColor(Qt::yellow);

    QTableWidgetItem *rebuy=new QTableWidgetItem;
        rebuy->setText(table[i].rebuy);
        rebuy->setBackgroundColor(Qt::red);

    ui->material_need_but_out_->setItem(i,0,name);
    ui->material_need_but_out_->setItem(i,1,need);
    ui->material_need_but_out_->setItem(i,2,now);
    ui->material_need_but_out_->setItem(i,3,rebuy);
    }
}
else
{
    ui->material_need_but_out_->setVisible(false);
}
}

void MainWindow::set_table_grafic(QString ID_progect)
{
    QList<building> list=QUERY->info_plan_building(ID_progect);
    ui->steps_info->clear();
    ui->steps_info->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int row=list.size();
    ui->steps_info->setRowCount(row);
    ui->steps_info->setColumnCount(4);
    ui->steps_info->setHorizontalHeaderLabels(QStringList()<<"имя бригады"<<"№ бригады"<<"дата начала"<<"дата окончания");
        for (int i=0;i<row;i++)
        {
            ui->steps_info->setItem(i,0, new QTableWidgetItem (list[i].name));
            ui->steps_info->setItem(i,1,new QTableWidgetItem(list[i].ID));
            ui->steps_info->setItem(i,2,new QTableWidgetItem(list[i].time_pair.date_start));
            ui->steps_info->setItem(i,3,new QTableWidgetItem(list[i].time_pair.date_fin));
        }
}

void MainWindow::set_individual_info(QString ID_progect)
{
    ui->progect_id_info->setText(ID_progect);
    building info=QUERY->info_about_progect(ID_progect);
    ui->client_name_info->setText(info.ID);
    ui->sum_info->setText(info.price);

    period_date d=QUERY->min_max_date_progect(ID_progect);
    ui->date_start_work_info->setDate(d.date_start);
    ui->date_fin_work_info->setDate(d.date_fini);
}

void MainWindow::load_statistic()
{
    period_date dat;
    dat.date_start=ui->statistic_time_start->date();
    dat.date_fini=ui->statistic_time_fin->date();

    building statistic_ynic=QUERY->info_for_progect(dat,true);
    building statistic_standart=QUERY->info_for_progect(dat,false);

    ui->progect_count_all_type->setText(QString::number(statistic_standart.ID.toInt()+statistic_ynic.ID.toInt()));
        ui->progect_count_standart->setText(statistic_standart.ID);
        ui->progect_count_ynic->setText(statistic_ynic.ID);

    ui->progect_sum_money_all_type->setText(QString::number(statistic_standart.price_pair.price_fin.toDouble()+statistic_ynic.price_pair.price_fin.toDouble()));
        ui->progect_standart_money->setText(statistic_standart.price_pair.price_fin);
        ui->progect_ynic_money->setText(statistic_ynic.price_pair.price_fin);

    ui->progect_info_money_pay->setText(QString::number(statistic_standart.price_pair.price_start.toDouble()+statistic_ynic.price_pair.price_start.toDouble()));
        ui->progect_info_money_pay_standart->setText(statistic_standart.price_pair.price_start);
        ui->progect_info_money_pay_ynic->setText(statistic_ynic.price_pair.price_start);
}

void MainWindow::clear_statistic()
{
    ui->stackedWidget->setCurrentIndex(11);
    QDate date;
    ui->statistic_time_start->setDate(date.currentDate());
    ui->statistic_time_fin->setDate(date.currentDate());
    ui->progect_count_all_type->setText("");
    ui->progect_count_standart->setText("");
    ui->progect_count_ynic->setText("");
    ui->progect_info_money_pay->setText("");
    ui->progect_info_money_pay_standart->setText("");
    ui->progect_info_money_pay_ynic->setText("");
    ui->progect_sum_money_all_type->setText("");
    ui->progect_ynic_money->setText("");
    ui->progect_standart_money->setText("");
}

void MainWindow::load_work_process()
{
    int work_day=0;
    int holl_day=0;
    //считывание из файла
    ui->work_day_LE->setText(QString::number(work_day));
    ui->holl_day_LE->setText(QString::number(holl_day));
    ui->work_option_GB->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
}

QString MainWindow::split_str(QString val)
{
    QString split_dell_sp;
    split_dell_sp=val;
    QStringList list;
    list=split_dell_sp.split(QRegularExpression("\\s+"));
    split_dell_sp.clear();
    for (int i=0;i<list.size();i++)
    {
        if (i!=0)
            split_dell_sp=split_dell_sp+" "+list[i];
        else
            split_dell_sp=split_dell_sp+list[i];
    }
    list.clear();
    return split_dell_sp;
}

void MainWindow::clear_st_wid_0()
{
    ui->material_nestandart_GB->setVisible(false);
    ui->work_option_GB->setVisible(false);
    ui->percent->setVisible(false);
}

void MainWindow::save_price_to_file()
{
    dir d;//сохранение в файл
    if (d.write_procent_File(ui->pore_pay_procent_SpB->value()))
        ui->statusBar->showMessage(tr("наценка сохранена"));
    else
    {
        ui->statusBar->showMessage(tr("наценка не охранена"));
    }
}

void  MainWindow::unshow_percent()
{
    ui->percent->setVisible(false);
}

void MainWindow::load_oplata_progecta()
{
    ui->stackedWidget->setCurrentIndex(10);
    ui->progect_money_add_GrBox->setVisible(true);
    ui->progect_id->clear();
    ui->summ_pay_LE->setValue(0);
}
