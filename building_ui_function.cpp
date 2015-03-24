#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::split_house()
{
    QString s;
    s=ui->new_standart_name_LE->text();
    ui->new_standart_name_LE->clear();
    ui->new_standart_name_LE->setText(split_str(s));
}

void MainWindow::clear_sh_building()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->sh_house_GB->setVisible(false);
    ui->CB_House_poisk->setChecked(false);
    ui->sh_building_name->clear();
    ui->sh_building_price_min->setValue(0);
    ui->sh_building_price_min->setMaximum(99999999);
    ui->sh_building_price_max->setValue(0);
    ui->sh_building_price_max->setMaximum(99999999);
    ui->sh_building_time_min->setValue(0);
    ui->sh_building_time_min->setMaximum(9999);
    ui->sh_building_time_max->setValue(0);
    ui->sh_building_time_max->setMaximum(9999);
    ui->sh_building_metter_min->setValue(0);
    ui->sh_building_metter_min->setMaximum(99999999);
    ui->sh_building_metter_max->setValue(0);
    ui->sh_building_metter_max->setMaximum(99999999);
}

void MainWindow::load_building()
{
    ui->House_progect_main_this_PB->setEnabled(false);
    ui->active_progect_TW->setVisible(false);
    ui->close_active_progect_PB->setVisible(false);
    ui->tableWidget_house->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->show_PB->setEnabled(false);
    ui->tableWidget_house->setColumnCount(6);
    ui->tableWidget_house->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена"<<"ID");
    building sh;
                sh.name=ui->sh_building_name->text();
                sh.time_pair.date_start=QString::number(ui->sh_building_time_min->value());
                sh.time_pair.date_fin=QString::number(ui->sh_building_time_max->value());
                sh.metter_pair.metter_start=QString::number(ui->sh_building_metter_min->value());
                sh.metter_pair.metter_fin=QString::number(ui->sh_building_metter_max->value());
                sh.price_pair.price_start=QString::number(ui->sh_building_price_min->value());
                sh.price_pair.price_fin=QString::number(ui->sh_building_price_max->value());

    QList <building> table=QUERY->building_main_class_ret(sh);
    int row=table.size();
    ui->tableWidget_house->setRowCount(row);

    building temp;
    for (int i=0;i<table.size();i++)
    {
        temp=table[i];

            QTableWidgetItem * tw_name=new QTableWidgetItem;
            tw_name->setText(temp.name);
            QTableWidgetItem * tw_ynic=new QTableWidgetItem;
            tw_ynic->setText(temp.id_ynical_string);
            QTableWidgetItem * tw_time_b=new QTableWidgetItem;
            tw_time_b->setText(temp.Standart_time_building);
            QTableWidgetItem * tw_metter=new QTableWidgetItem;
            tw_metter->setText(temp.metter);
            QTableWidgetItem * tw_price=new QTableWidgetItem;
            tw_price->setText(temp.price);
            QTableWidgetItem * tw_id=new QTableWidgetItem;
            tw_id->setText(temp.ID);

            if (tw_ynic->text()=="+")
            {
                tw_name->setBackgroundColor(Qt::green);
                tw_ynic->setBackgroundColor(Qt::green);
                tw_time_b->setBackgroundColor(Qt::green);
                tw_metter->setBackgroundColor(Qt::green);
                tw_price->setBackgroundColor(Qt::green);
                tw_id->setBackgroundColor(Qt::green);
            }
            ui->tableWidget_house->setItem(i,0,tw_name);
            ui->tableWidget_house->setItem(i,1,tw_ynic);
            ui->tableWidget_house->setItem(i,2,tw_time_b);
            ui->tableWidget_house->setItem(i,3,tw_metter);
            ui->tableWidget_house->setItem(i,4,tw_price);
            ui->tableWidget_house->setItem(i,5,tw_id);
    }
}

void MainWindow::load_dworec()
{
    QPixmap pixmap(":/pictures/res/дворец.png");
    ui->pictures_expensive->setPixmap(pixmap);
}

void MainWindow::load_sarai()
{
    QPixmap pixmap(":/pictures/res/saraj.png");
    ui->pictures_expensive->setPixmap(pixmap);
}

void MainWindow::load_ynic_progect_building(bool ynic)
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->active_progect_TW->setVisible(false);
    ui->close_active_progect_PB->setVisible(false);
    if (ynic)
    {
        load_main_infor_new_build_GrBox();
        new_standart_level_table_clear();
        new_standart_material_table_clear();
        new_standart_main_clear();
        ui->new_standart_OK_PB->setVisible(false);
        ui->new_ynic_OK_PB->setVisible(true);
        load_dworec();
    }
    else
    {
        load_main_infor_new_build_GrBox();
        new_standart_level_table_clear();
        new_standart_material_table_clear();
        new_standart_main_clear();
        ui->new_standart_OK_PB->setVisible(true);
        ui->new_ynic_OK_PB->setVisible(false);
        load_sarai();
    }
}

void MainWindow::load_main_infor_new_build_GrBox()
{
    ui->main_infor_new_build_GrBox->setVisible(true);
    ui->new_standart_name_LE->clear();
    ui->new_standart_metter_SpBox->clear();
    ui->new_standart_time_SpB->clear();
    ui->new_standart_show_neded_material_ChB->setChecked(false);
    ui->new_standart_show_level_ChB->setChecked(false);
}

void MainWindow::clear_main_infor_new_build_GrBox()
{
    ui->new_standart_name_LE->clear();
    ui->new_standart_metter_SpBox->clear();
    ui->new_standart_time_SpB->clear();
}

void MainWindow::load_info_level_building_GrBox()
{
    clear_needed_material_standart();
    ui->info_level_building_GrBox->setVisible(true);
    ui->new_standart_need_special_worker_FCB->clear();
    ui->new_standart_level_dayLong_SPbx->clear();
        ui->new_standart_level_dell->setEnabled(false);
    QList <QString >list=QUERY->avto_special_brig_list();
    int row=list.size();
    for (int i=0;i<row;i++)
    {
        ui->new_standart_need_special_worker_FCB->addItem(list[i]);
    }
}

void MainWindow::load_info_material_for_building_GrBox()
{
    ui->info_material_for_building_GrBox->setVisible(true);
    ui->new_standart_ned_materisl_naznach->clear();
    ui->new_standart_material_name->clear();
    ui->new_standart_count_SpB->clear();
    ui->new_standart_ned_mater_izmer_LE->clear();
    ui->new_standart_count_SpB->setValue(0);
        ui->new_standart_material_dell_PB->setEnabled(false);

        load_material_name_all_for_need_material("");
        load_naznach_mater_standart("");
    ui->new_standart_ned_materisl_naznach->setEnabled(true);
}

void MainWindow::add_standart_grafic_TW(QString Brig_special, QString Count)
{
    int row_now=ui->new_standart_grafic_TW->rowCount();
    row_now++;
    ui->new_standart_grafic_TW->setRowCount(row_now);
    QTableWidgetItem *spec=new QTableWidgetItem;
    spec->setText(Brig_special);
    QTableWidgetItem *count=new QTableWidgetItem;
    count->setText(Count);
    ui->new_standart_grafic_TW->setItem(row_now-1,0,spec);
    ui->new_standart_grafic_TW->setItem(row_now-1,1,count);
}

void MainWindow::add_to_need_material_TW(QString Name_mater, QString Count)
{
    int row_now=ui->new_standart_ned_material_TW->rowCount();
    row_now++;
    ui->new_standart_ned_material_TW->setRowCount(row_now);
    QTableWidgetItem *TW=new QTableWidgetItem;
    TW->setText(Name_mater);
    QTableWidgetItem *TW_c=new QTableWidgetItem;
    TW_c->setText(Count);
    ui->new_standart_ned_material_TW->setItem(row_now-1,0,TW);
    ui->new_standart_ned_material_TW->setItem(row_now-1,1,TW_c);
}

void MainWindow::set_naznachen(QString val)
{
    ui->new_standart_ned_materisl_naznach->clear();
    ui->new_standart_ned_materisl_naznach->setCurrentText(QUERY->material_ret_naznach_with_name(val));
    ui->new_standart_ned_materisl_naznach->setEnabled(false);
}

void MainWindow::set_name_need_material(QString val)
{
    QList<QString> list=QUERY->material_ret_name_with_naznach(val);
    int row=list.size();
    if (row!=0)
    {
    ui->new_standart_material_name->clear();
    for (int i=0;i<row;i++)
    {
        ui->new_standart_material_name->addItem(list[i]);
    }
    }
}

void MainWindow::set_day_count()
{
    int day=0;
    int row=ui->new_standart_grafic_TW->rowCount();
    for (int i=0;i<row;i++)
    {
        QTableWidgetItem *item=new QTableWidgetItem;
        item=ui->new_standart_grafic_TW->item(i,1);
        day=day+item->text().toInt();
    }
    ui->new_standart_time_SpB->setValue(day);
}

void MainWindow::set_price()
{
    double price;
    if (ui->checkBox_is_ynical_progect->isChecked())
    {
        dir t;
        price=QUERY->sum_material(return_list_need_material());
        int n=t.read_procent_File();
        qDebug()<<n;
        double nac=n/100.0;
        qDebug()<<nac;
        price=price+nac*price;
    }
    else
    {
        price=QUERY->sum_material(return_list_need_material());
    }
    ui->new_standart_DSpBox->setValue(price);
}

void MainWindow::set_id_progect_standart()
{
    QTableWidgetItem *item=new QTableWidgetItem;
    item=ui->tableWidget_house->item(ui->tableWidget_house->currentRow(), 1);
    if (item->text()!="+")
    {
        QTableWidgetItem *item=new QTableWidgetItem;
        item=ui->tableWidget_house->item(ui->tableWidget_house->currentRow(), 5);
        ui->building_id_for_progect->setText(item->text());
        ui->stackedWidget->setCurrentIndex(5);
    }
    else
    {
        ui->statusBar->showMessage(tr("нельзя заказать уникальный проект"));
    }
}

void MainWindow::set_dop_price()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->percent->setVisible(true);
    //загрузка из файла
    ui->pore_pay_procent_SpB->clear();
    dir t;
    ui->pore_pay_procent_SpB->setValue(t.read_procent_File());
}

bool MainWindow::correct_data_new_building_progect()
{
    if (ui->new_standart_name_LE->text()!="" && ui->new_standart_metter_SpBox->value()!=0 && ui->new_standart_DSpBox->value()!=0 && ui->new_standart_time_SpB->value()!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QList <material_ned> MainWindow::return_list_need_material()
{
    QList <material_ned> result;
    for (int i=0;i<ui->new_standart_ned_material_TW->rowCount();i++)
    {
      material_ned temp;
        QTableWidgetItem *item=new QTableWidgetItem;
        item=ui->new_standart_ned_material_TW->item(i,0);
        temp.name_material=item->text();
        QTableWidgetItem *item_count=new QTableWidgetItem;
        item_count=ui->new_standart_ned_material_TW->item(i,1);
        temp.count_material=item_count->text();
      result.push_back(temp);
    }
    return result;
}

QList <level>  MainWindow::return_time_plane()
{
    QList <level> result;
    int row=ui->new_standart_grafic_TW->rowCount();
    for (int i=0;i<row;i++)
    {
        level temp;
            QTableWidgetItem *item=new QTableWidgetItem;
            item=ui->new_standart_grafic_TW->item(i,0);
            temp.special_brig=item->text();

            QTableWidgetItem *item_count=new QTableWidgetItem;
            item_count=ui->new_standart_grafic_TW->item(i,1);
            temp.day_count=item_count->text();

        result.push_back(temp);
    }
    return result;
}

QString MainWindow::save_all_info_buildin(bool ynic)
{
  building temp;
    temp.is_ynical_bool=ynic;
    temp.name=ui->new_standart_name_LE->text();
    temp.price=QString::number(ui->new_standart_DSpBox->value());
    temp.Standart_time_building=QString::number(ui->new_standart_time_SpB->value());
    temp.metter=QString::number(ui->new_standart_metter_SpBox->value());
    temp.neded_material=return_list_need_material();
    temp.time_plan=return_time_plane();
  QString ID=QUERY->insert_new_building(temp);
  return ID;
}

void MainWindow::new_standart_level_table_clear()
{
    ui->new_standart_grafic_TW->clear();
    ui->new_standart_grafic_TW->setRowCount(0);
    ui->new_standart_grafic_TW->setColumnCount(0);
}

void MainWindow::new_standart_material_table_clear()
{
    ui->new_standart_ned_material_TW->clear();
    ui->new_standart_ned_material_TW->setColumnCount(0);
    ui->new_standart_ned_material_TW->setRowCount(0);
}

void MainWindow::new_standart_main_clear()
{
    ui->level_list_GrBox->setVisible(false);
    ui->needed_material_for_bu_GrBox->setVisible(false);
    ui->info_material_for_building_GrBox->setVisible(false);
    ui->info_level_building_GrBox->setVisible(false);
    ui->new_standart_show_neded_material_ChB->setChecked(false);
    ui->new_standart_show_level_ChB->setChecked(false);
    ui->new_standart_name_LE->clear();
    ui->new_standart_metter_SpBox->clear();
    ui->new_standart_DSpBox->clear();
    ui->new_standart_time_SpB->clear();
    ui->new_standart_grafic_TW->setColumnCount(2);
    ui->new_standart_grafic_TW->setHorizontalHeaderLabels(QStringList()<<"специалист"<<"срок");
    ui->new_standart_ned_material_TW->setColumnCount(2);
    ui->new_standart_ned_material_TW->setHorizontalHeaderLabels(QStringList()<<"материал"<<"количество");
}

void MainWindow::load_material_name_all_for_need_material(QString val)
{
    ui->new_standart_material_name->clear();
    QList <material> list=QUERY->mater_like_my(val);
    int row=list.size();

    for (int i=0;i<row;i++)
    {
        ui->new_standart_material_name->addItem(list[i].name);
    }
}

void MainWindow::load_naznach_mater_standart(QString val)
{
    ui->new_standart_ned_materisl_naznach->clear();
    QList <material> list=QUERY->material_with_function(val);
    int row=list.size();

    for (int i=0;i<row;i++)
    {
        ui->new_standart_ned_materisl_naznach->addItem(list[i].naznach);
    }
}

void MainWindow::clear_needed_material_standart()
{
    ui->new_standart_level_dayLong_SPbx->setValue(0);
}

void MainWindow::load_active_progect_TW()
{
    ui->active_progect_TW->clear();
    ui->active_progect_TW->setRowCount(0);
    ui->active_progect_TW->setColumnCount(0);
    int row=ui->tableWidget_house->currentRow();
    QTableWidgetItem *tw=ui->tableWidget_house->item(row, 5);
    QList <person_plas_prog> list=QUERY->person_with_ID_building(tw->text());

    int table_row=list.size();
    ui->active_progect_TW->setRowCount(table_row);
    ui->active_progect_TW->setColumnCount(4);
    ui->active_progect_TW->setHorizontalHeaderLabels(QStringList()<<"фамилия"<<"телефон"<<"оплаченная сумма"<<"№ проекта");

    for (int i=0;i<table_row;i++)
    {
        QTableWidgetItem *fio=new QTableWidgetItem;
        fio->setText(list[i].fio);
        QTableWidgetItem *ph=new QTableWidgetItem;
        ph->setText(list[i].ph);
        QTableWidgetItem *price=new QTableWidgetItem;
        price->setText(list[i].price);
        QTableWidgetItem *date=new QTableWidgetItem;
        date->setText(list[i].date);//!!
        ui->active_progect_TW->setItem(i,0,fio);
        ui->active_progect_TW->setItem(i,1,ph);
        ui->active_progect_TW->setItem(i,2,price);
        ui->active_progect_TW->setItem(i,3,date);
    }
}

void MainWindow::minus_level()
{
    ui->new_standart_grafic_TW->removeRow(ui->new_standart_grafic_TW->currentRow());
    set_day_count();
}

void MainWindow::minus_material()
{
    ui->new_standart_ned_material_TW->removeRow(ui->new_standart_ned_material_TW->currentRow());
    set_price();
}

void MainWindow::delete_current_level()
{
    ui->new_standart_grafic_TW->removeRow(ui->new_standart_grafic_TW->currentRow());
    ui->new_standart_level_dell->setEnabled(false);
}

void MainWindow::delete_current_material()
{
    ui->new_standart_ned_material_TW->removeRow(ui->new_standart_ned_material_TW->currentRow());
    ui->new_standart_material_dell_PB->setEnabled(false);
}
