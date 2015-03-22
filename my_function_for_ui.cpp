#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

void MainWindow::load_technics()
{
    ui->tableWidget_technics->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_technics->setColumnCount(4);
    ui->tableWidget_technics->setHorizontalHeaderLabels(QStringList()<<"название"<<"инвентарный номер"<<"год выпуска"<<"дата покупки");
    QList <technics> list_tech;

    technics sh;
    sh.name=ui->sh_eqw_name->text();
    sh.namber=ui->sh_eqw_namber->text();

    list_tech=QUERY->eqw_all_load(sh);
    int row=list_tech.size();
    ui->tableWidget_technics->setRowCount(row);

    for (int i=0;i<row;i++)
    {
            technics temp=list_tech[i];
            QTableWidgetItem *name = new QTableWidgetItem();
            name->setText(temp.name);
            ui->tableWidget_technics->setItem(i,0,name);

            QTableWidgetItem *id = new QTableWidgetItem();
            id->setText(temp.namber);
            ui->tableWidget_technics->setItem(i,1,id);

            QTableWidgetItem *year = new QTableWidgetItem();
            if (temp.Year_vip!="0")
                year->setText(temp.Year_vip);
            else
                year->setText("");
            ui->tableWidget_technics->setItem(i,2,year);

            QTableWidgetItem *date = new QTableWidgetItem();
            date->setText(temp.Date_pok);
            ui->tableWidget_technics->setItem(i,3,date);
    }
}

void MainWindow::load_worker()
{
    ui->tableWidget_worker->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QList <worker> work_vect;

    worker temp;
    temp.fio=ui->sh_worker_fam->text();
    if (ui->sh_worker_start_price_SB->value()!=0 || ui->sh_worker_fin_price_SB->value()!=0)
    {
        temp.pay_start=QString::number(ui->sh_worker_start_price_SB->value());
        temp.pay_fin=QString::number(ui->sh_worker_fin_price_SB->value());
    }
    temp.post=ui->sh_worker_post->text();

    work_vect=QUERY->worker_all(temp);
    int row=work_vect.size();
    ui->tableWidget_worker->setRowCount(row);
    ui->tableWidget_worker->setColumnCount(6);
    ui->tableWidget_worker->setHorizontalHeaderLabels(QStringList()<<"адресс"<<"должность"<<"год рождения"<<"фио"<<"ID"<<"зарплата");

    for (int i=0;i<row;i++)
    {
        worker temp;
        temp=work_vect[i];
        QTableWidgetItem *item_adress = new QTableWidgetItem();
        item_adress->setText(temp.adress);

        QTableWidgetItem *item_dol = new QTableWidgetItem();
        item_dol->setText(temp.post);
        item_dol->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *item_year_bir = new QTableWidgetItem();
        if (temp.birthday!="0")
        {
            item_year_bir->setText(temp.birthday);                      //наложить маски на таблицы
        }
        else
        {
            item_year_bir->setText("");
        }
        item_year_bir->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *item_fio = new QTableWidgetItem();
        item_fio->setText(temp.fio);
        item_fio->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *item_ID = new QTableWidgetItem();
        item_ID->setText(temp.id);
        item_ID->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *item_pay = new QTableWidgetItem();
        item_pay->setText(temp.pay);
        item_pay->setTextAlignment(Qt::AlignHCenter);

        //ui->tableWidget_worker->setItemDelegateForColumn();               //
        ui->tableWidget_worker->setItem(i,0,item_adress);
        ui->tableWidget_worker->setItem(i,1,item_dol);

        ui->tableWidget_worker->setItem(i,2,item_year_bir);

        ui->tableWidget_worker->setItem(i,3,item_fio);
        ui->tableWidget_worker->setItem(i,4,item_ID);
        ui->tableWidget_worker->setItem(i,5,item_pay);
    }
ui->tableWidget_worker->setFocusPolicy(Qt::ClickFocus);
}

void MainWindow::load_building()
{
    ui->stackedWidget->setCurrentIndex(4);
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
void MainWindow::Q_Object_connect()
{
    connect(ui->new_worker_team_CkBox,SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->new_worker_team_CkBox, SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->CB_House_poisk,SIGNAL(clicked(bool)),ui->sh_house_GB,SLOT(setVisible(bool)));
}

void MainWindow::set_visible_enabled()
{
    ui->main_infor_new_build_GrBox->setVisible(false);
    ui->level_list_GrBox->setVisible(false);
    ui->needed_material_for_bu_GrBox->setVisible(false);
    ui->info_level_building_GrBox->setVisible(false);
    ui->info_material_for_building_GrBox->setVisible(false);
    ui->work_option_GB->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->dell_eqvmnt->setEnabled(false);
    ui->new_eq_team_comBOX->setVisible(false);
    ui->new_brigada_GrBox->setVisible(false);
    ui->material_nestandart_GB->setVisible(false);
    ui->brig_obor_GRBox->setVisible(false);
    ui->pusB_Sotrudnic_del->setEnabled(false);
}
void MainWindow::set_validator_all()
{
    QRegExp name("[а-я А-Я]{20}");
    ui->lineEdit_client_fio_input->setValidator(new QRegExpValidator(name,this));

    QRegExp mesto("[а-я А-Я . , 0-9]{20}");
    ui->lineEdit_client_mestoJit_input->setValidator(new QRegExpValidator(mesto,this));

    QRegExp passport("[a-zA-Z]{2}[0-9]{6}");
    ui->lineEdit_client_pasport_input->setValidator(new QRegExpValidator(passport,this));

    QRegExp phone("[0-9]{12}");
    ui->lineEdit_client_phone_input->setValidator(new QRegExpValidator(phone,this));

    QRegExp year("[1-2]{1}[0-9]{3}");
    ui->lineEdit_client_yearBir_input->setValidator(new QRegExpValidator(year,this));

    QRegExp material_name("[а-я А-Я]{20}");//
    ui->material_name_LE->setValidator(new QRegExpValidator(material_name,this));

    QRegExp ed_iz("[а-я А-Я , . 0-9]{10}");
    ui->ed_izmeren->setValidator(new QRegExpValidator(ed_iz,this));

    QRegExp F_nazn("[а-я А-Я 0-9]{15}");
    ui->ed_izmeren->setValidator(new QRegExpValidator(F_nazn,this));

    ui->oborud_name_LE->setValidator(new QRegExpValidator(F_nazn,this));
    QRegExp INN("[0-9]{6}");

    ui->summ_pay_LE->setMaximum(999999.99);

    ui->oborud_INV_namber_LE->setValidator(new QRegExpValidator(INN,this));
    ui->obor_ear_build_SpBx->setMaximum(2015);//текуший год

    QRegExp name_adr_post_fio("[а-я А-Я . , / 0-9]{20}");
    ui->new_worker_FIO_LE->setValidator(new QRegExpValidator(name_adr_post_fio,this));
    ui->new_worker_aderss_LE->setValidator(new QRegExpValidator(name_adr_post_fio,this));
    ui->new_worker_year_bir_LE->setValidator(new QRegExpValidator(year,this));

    ui->material_count_sp_box->setMaximum(99999999);
    ui->count_c_SPB->setMaximum(99999999);
    ui->dSpBo_material_price->setMaximum(999999999);
    ui->new_worker_OKLAD_doubSpBox->setMaximum(999999999);
    ui->price_a_DSB->setMaximum(999999);
    ui->price_b_DSB->setMaximum(999999);
    ui->price_c_DSB->setMaximum(999999);

    ui->new_standart_metter_SpBox->setMaximum(999999);
    ui->new_standart_DSpBox->setMaximum(99999999);
    ui->new_standart_time_SpB->setMaximum(9999);

    ui->pore_pay_procent_SpB->setMaximum(999);
}

void MainWindow::clear_first()
{
    ui->ed_izmeren->clear();
    ui->funct_naznach->clear();
    ui->new_special_brig_FCB->clear();
    ui->new_standart_DSpBox->clear();
    unshow_percent();
}

void MainWindow::load_new_eqwt()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->new_eq_Com_box->clear();
    QList<QString> list_special=QUERY->avto_special_brig_list();
    int row=list_special.size();
    for (int i=0;i<row;i++)
    {
         QString name=list_special[i];
         ui->new_eq_Com_box->addItem(name);
    }
    ui->oborud_name_LE->clear();
    ui->oborud_INV_namber_LE->clear();
    ui->obor_ear_build_SpBx->clear();
    QDate *date=new QDate;
    ui->pokupka_obor_dateE->setDate(date->currentDate());
}
void MainWindow::load_brig_num_for_new_eqw(QString val)
{
    QList <QString> list=QUERY->ID_group_with_name(val);
    int row=list.size();
    ui->new_eq_id_Combox->clear();
    for (int i=0;i<row;i++)
    {
        ui->new_eq_id_Combox->addItem(list[i]);
    }
}

void MainWindow::load_brig_name_to_new_worker_special_Comb_box()
{
    QList <QString> list=QUERY->avto_special_brig_list();
    ui->new_worker_special_Comb_box->clear();
    int row=list.size();
    for (int i=0;i<row;i++)
    {
        ui->new_worker_special_Comb_box->addItem(list[i]);
    }
}

void MainWindow::load_brig_num_for_new_worker(QString val)
{
    ui->new_worker_special_CoBox->clear();
    QList<QString> list=QUERY->ID_group_with_name(val);
    int row=list.size();
    for (int i=0;i<row;i++)
    {
        ui->new_worker_special_CoBox->addItem(list[i]);
    }
}

void MainWindow::new_worker_initial()
{  
            QList <QString> list_dol=QUERY->avto_worker_dolg_list();
            int row=list_dol.size();
            ui->new_worker_post_Fou_CoBox->clear();
            ui->new_worker_post_Fou_CoBox->addItem("");
            for (int i=0;i<row;i++)
            {
                ui->new_worker_post_Fou_CoBox->addItem(list_dol[i]);
            }
            ui->new_worker_FIO_LE->clear();
            ui->new_worker_aderss_LE->clear();
            ui->new_worker_year_bir_LE->clear();
            ui->new_worker_OKLAD_doubSpBox->clear();
}

void MainWindow::clear_material()
{
    ui->material_name_LE->setText("");
    ui->dSpBo_material_price->setValue(0);
    ui->material_count_sp_box->setValue(0);
    ui->ed_izmeren->clear();
    ui->ed_izmeren->addItem("");

    QList <QString> izmer_list=QUERY->avto_material_list_izmer();
    int row_a=izmer_list.size();
    for (int i=0;i<row_a;i++)
    {
        QString temp=izmer_list[i];
        ui->ed_izmeren->addItem(temp);
    }
    ui->funct_naznach->clear();
    ui->funct_naznach->addItem("");
    QList <QString> funct_list=QUERY->avto_material_list_naz();
    int row_b=funct_list.size();
    for (int i=0;i<row_b;i++)
    {
        QString temp=funct_list[i];
        ui->funct_naznach->addItem(temp);
    }
}
void MainWindow::load_special_obor_brig_ComBox()
{
        ui->special_obor_brig_ComBox->clear();
        QList<QString> list_val=QUERY->avto_special_all();
        int row =list_val.size();
        for (int i=0;i<row;i++)
        {
            ui->special_obor_brig_ComBox->addItem(list_val[i]);
        }
        load_namber_obor_brig_ComBox(ui->special_obor_brig_ComBox->currentText());
}

void MainWindow::load_namber_obor_brig_ComBox(QString s)
{
    QList <QString> list=QUERY->ID_group_with_name(s);
    int row=list.size();
    ui->namber_obor_brig_ComBox->clear();
    for (int i=0;i<row;i++)
    {
        ui->namber_obor_brig_ComBox->addItem(list[i]);
    }
}
void MainWindow::load_obor_to_double_TabWid()
{
    if ((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        ui->obor_worker_table_wid->clear();
        ui->obor_worker_table_wid->setColumnCount(4);
        ui->obor_worker_table_wid->setHorizontalHeaderLabels(QStringList()<<"название"<<"инвентарный номер"<<"год выпуска"<<"дата покупки");
        QList <technics> list=QUERY->eqw_with_group(ui->namber_obor_brig_ComBox->currentText());
        int row=list.size();
        ui->obor_worker_table_wid->setRowCount(row);

        for (int i=0;i<row;i++)
        {
            technics temp=list[i];

            QTableWidgetItem *item_name = new QTableWidgetItem();
            item_name->setText(temp.name);

            QTableWidgetItem *item_namber=new QTableWidgetItem();
            item_namber->setText(temp.namber);

            QTableWidgetItem *item_year = new QTableWidgetItem();
            item_year->setText(temp.Year_vip);

            QTableWidgetItem *item_date = new QTableWidgetItem();
            item_date->setText(temp.Date_pok);

            ui->obor_worker_table_wid->setItem(i,0,item_name);
            ui->obor_worker_table_wid->setItem(i,1,item_namber);
            if (temp.Year_vip!="0" && temp.Year_vip!="")
            ui->obor_worker_table_wid->setItem(i,2,item_year);
            ui->obor_worker_table_wid->setItem(i,3,item_date);
        }
    }
}

void MainWindow::load_worker_to_double_Tab_Wid()
{
    if ((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        ui->obor_worker_table_wid->clear();
        QList <worker> list=QUERY->worker_with_group(ui->namber_obor_brig_ComBox->currentText());

        int row=list.size();
        ui->obor_worker_table_wid->setRowCount(row);
        ui->obor_worker_table_wid->setColumnCount(6);
        ui->obor_worker_table_wid->setHorizontalHeaderLabels(QStringList()<<"адресс"<<"должность"<<"год рождения"<<"фио"<<"ID"<<"зарплата");

        for (int i=0;i<row;i++)
        {
            worker temp;
            temp=list[i];
            QTableWidgetItem *item_adress = new QTableWidgetItem();
            item_adress->setText(temp.adress);

            QTableWidgetItem *item_dol = new QTableWidgetItem();
            item_dol->setText(temp.post);
            item_dol->setTextAlignment(Qt::AlignHCenter);

            QTableWidgetItem *item_year_bir = new QTableWidgetItem();
            if (temp.birthday!="0" && temp.birthday!="")
            {
                item_year_bir->setText(temp.birthday);                      //наложить маски на таблицы
            }
            else
            {
                item_year_bir->setText("");
            }
            item_year_bir->setTextAlignment(Qt::AlignHCenter);

            QTableWidgetItem *item_fio = new QTableWidgetItem();
            item_fio->setText(temp.fio);
            item_fio->setTextAlignment(Qt::AlignHCenter);

            QTableWidgetItem *item_ID = new QTableWidgetItem();
            item_ID->setText(temp.id);
            item_ID->setTextAlignment(Qt::AlignHCenter);

            QTableWidgetItem *item_pay = new QTableWidgetItem();
            item_pay->setText(temp.pay);
            item_pay->setTextAlignment(Qt::AlignHCenter);

            //ui->tableWidget_worker->setItemDelegateForColumn();               //!!!!!!!!!!!!!!!!!!
            ui->obor_worker_table_wid->setItem(i,0,item_adress);
            ui->obor_worker_table_wid->setItem(i,1,item_dol);

            ui->obor_worker_table_wid->setItem(i,2,item_year_bir);

            ui->obor_worker_table_wid->setItem(i,3,item_fio);
            ui->obor_worker_table_wid->setItem(i,4,item_ID);
            ui->obor_worker_table_wid->setItem(i,5,item_pay);
        }
    }
}
void MainWindow::clear_obor_worker_table_wid()
{
    ui->obor_worker_table_wid->clear();
    ui->obor_worker_table_wid->setRowCount(0);
    ui->obor_worker_table_wid->setColumnCount(0);
}

void MainWindow::reload_double_table()
{
    if (ui->eqw_brigada_RB->isChecked())
    {
        load_obor_to_double_TabWid();
    }
    else
    {
        load_worker_to_double_Tab_Wid();
    }
}
void MainWindow::load_all_special_to_new_special_brig_FCB()
{
    ui->new_special_brig_FCB->clear();
    QList <QString> list=QUERY->avto_special_all();
    int row=list.size();
    for (int i=0;i<row;i++)
    {
        ui->new_special_brig_FCB->addItem(list[i]);
    }
}
void MainWindow::clear_bezicxodnost_Table_wid()
{
    ui->bezicxodnost_table_wid->setColumnCount(0);
    ui->bezicxodnost_table_wid->setRowCount(0);
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

void MainWindow::load_oplata_progecta()
{
    ui->stackedWidget->setCurrentIndex(10);
    ui->progect_money_add_GrBox->setVisible(true);
    ui->progect_id->clear();
    ui->summ_pay_LE->setValue(0);
}
//=========================================================================================================
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
void MainWindow::load_ynic_progect_building(bool ynic)
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->active_progect_TW->setVisible(false);
    ui->close_active_progect_PB->setVisible(false);
    load_main_infor_new_build_GrBox();
    new_standart_level_table_clear();
    new_standart_material_table_clear();
    new_standart_main_clear();
    if (ynic)
    {
        ui->new_standart_OK_PB->setVisible(false);
        ui->new_ynic_OK_PB->setVisible(true);
        load_dworec();
    }
    else
    {
        ui->new_standart_OK_PB->setVisible(true);
        ui->new_ynic_OK_PB->setVisible(false);
        load_sarai();
    }
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
void MainWindow ::clear_client_info()
{
    QDate dat;
    ui->building_id_for_progect->clear();
    ui->checkBox_is_ynical_progect->setChecked(false);
    ui->lineEdit_client_mestoJit_input->clear();
    ui->lineEdit_client_fio_input->clear();
    ui->lineEdit_client_pasport_input->clear();
    ui->lineEdit_client_yearBir_input->clear();
    ui->lineEdit_client_phone_input->clear();
    ui->date_start_w->setDate(dat.currentDate());
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
bool MainWindow::correct_data_client()
{
    QDate dat;
    if (ui->lineEdit_client_fio_input->text()!="" && ui->lineEdit_client_phone_input->text()!="" && ui->lineEdit_client_pasport_input->text()!="" &&
            ui->lineEdit_client_pasport_input->text().length()>=8 && ui->lineEdit_client_phone_input->text().size()>=7)
    {
        if (ui->date_start_w->date()<dat.currentDate())
        {
            ui->statusBar->showMessage("неверная дата начала строительства");
            return false;
        }
        else
        {
            if (ui->lineEdit_client_yearBir_input->text()!="")
            {
                if (ui->lineEdit_client_yearBir_input->text().toInt()>=1901)
                    return true;
                else return false;
            }
            else
            {
                return true;//без года рождения
            }
        }
    }
    else
    {
        ui->statusBar->showMessage("Заполите данные о клиенте (фамилия, телефон, паспорт)");
        return false;
    }
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

void  MainWindow::unshow_percent()
{
    ui->percent->setVisible(false);

}
void MainWindow::set_need_to_pay()
{
    if (ui->progect_id->text()!="")
    {
        double n_p=QUERY->need_to_pay(ui->progect_id->text());
        if (n_p>0)
        {
            QString pay;
            pay=QString::number(n_p);
            QString s;
            s="необходимо заплатить "+pay;
            ui->statusBar->showMessage(s);
            ui->summ_pay_LE->setValue(n_p);
        }
        else
        {
            if (n_p==0)
                ui->statusBar->showMessage(tr("уже оплачено"));
            else
            {
                ui->statusBar->showMessage(tr("проекта нет"));
            }
        }
    }
    else ui->statusBar->showMessage(tr("заполните № вашего проекта"));
}
void MainWindow::pay_progect()
{
    if (ui->progect_id->text()!="")
    {
        double n_p=QUERY->need_to_pay(ui->progect_id->text());
        if (n_p>0)
        {
            if (ui->summ_pay_LE->value()>n_p)
            {
                ui->statusBar->showMessage(tr("введенная вами сумма больше чем нужно!, введите корректную сумму "));
            }
            else
            {
                QUERY->update_pay_sum(ui->progect_id->text(), ui->summ_pay_LE->value());
                ui->statusBar->showMessage(tr("платеж произведен"));
                clear_pay_info();
            }
        }
        else
        {
            if (n_p==0)
                ui->statusBar->showMessage(tr("уже оплачено"));
            else
            {
                ui->statusBar->showMessage(tr("проекта нет"));
            }
        }
    }
    else ui->statusBar->showMessage(tr("заполните № вашего проекта"));
}
void MainWindow::clear_pay_info()
{
    ui->progect_id->clear();
    ui->summ_pay_LE->clear();
    ui->summ_pay_LE->setValue(0);
}

void MainWindow::clear_sh_eqw()
{
    ui->sh_eqw_name->clear();
    ui->sh_eqw_namber->clear();
}

void MainWindow::clear_sh_worker()
{
    ui->sh_worker_fam->clear();
    ui->sh_worker_post->clear();
    ui->sh_worker_start_price_SB->setValue(0);
    ui->sh_worker_fin_price_SB->setValue(0);
    ui->sh_worker_start_price_SB->setMaximum(99999);
    ui->sh_worker_fin_price_SB->setMaximum(99999);
}
void MainWindow::clear_sh_building()
{
    ui->sh_house_GB->setVisible(false);
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
void MainWindow::dell_problem(QString v)
{
    QString dell;
    dell=v;
    dell=dell+" ";
}
void MainWindow::load_eqw_or_worker_small()
{
    if((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        clear_bezicxodnost_Table_wid();
        ui->bezicxodnost_table_wid->setColumnCount(3);

        if ((ui->eqw_brigada_RB->isChecked()))
        {
            eqw_small();
        }
        else
        {
            if ((ui->worker_brigada_RB->isChecked()))
            {
                worker_small();
            }
        }
     ui->brig_obor_GRBox->setVisible(true);
     ui->pushButton->setEnabled(false);
    }
}

void MainWindow::eqw_small()
{
    qDebug()<<"eqw small"<<endl;
    ui->post_name_sh_LE->setStatusTip("название оборудования");
    ui->fio_inventarnN_LE->setStatusTip("инвентарный номер");
    ui->bezicxodnost_table_wid->setHorizontalHeaderLabels(QStringList()<<"название"<<"дата покупки"<<"инвентарный номер");

        technics sh;
            sh.name=ui->post_name_sh_LE->text();
            sh.namber=ui->fio_inventarnN_LE->text();
    QList <technics> list_eq=QUERY->avto_eq_list_free(sh);
    int row=list_eq.size();
    ui->bezicxodnost_table_wid->setRowCount(row);
    for (int i=0;i<row;i++)
    {
        technics temp;
        temp=list_eq[i];
        QTableWidgetItem * name=new QTableWidgetItem;
        name->setText(temp.name);
        ui->bezicxodnost_table_wid->setItem(i,0,name);

        QTableWidgetItem * date=new QTableWidgetItem;
        date->setText(temp.Date_pok);
        ui->bezicxodnost_table_wid->setItem(i,1,date);

        QTableWidgetItem * id=new QTableWidgetItem;
        id->setText(temp.namber);
        ui->bezicxodnost_table_wid->setItem(i,2,id);
    }
}

void MainWindow::worker_small()
{
    qDebug()<<"worker small"<<endl;
    ui->post_name_sh_LE->setStatusTip("должность сотрудника");
    ui->fio_inventarnN_LE->setStatusTip("фио сотрудника");
    ui->bezicxodnost_table_wid->setHorizontalHeaderLabels(QStringList()<<"должность"<<"фио"<<"ID");

    worker sh;
    sh.post=ui->post_name_sh_LE->text();
    sh.fio=ui->fio_inventarnN_LE->text();

    QList <worker> list_work=QUERY->avto_worker_list_free(sh);
    int row=list_work.size();
    ui->bezicxodnost_table_wid->setRowCount(row);
    for (int i=0;i<row;i++)
    {
        worker temp;
        temp=list_work[i];
        QTableWidgetItem * name=new QTableWidgetItem;
        name->setText(temp.post);
        ui->bezicxodnost_table_wid->setItem(i,0,name);

        QTableWidgetItem * fio=new QTableWidgetItem;
        fio->setText(temp.fio);
        ui->bezicxodnost_table_wid->setItem(i,1,fio);

        QTableWidgetItem * id=new QTableWidgetItem;
        id->setText(temp.id);
        ui->bezicxodnost_table_wid->setItem(i,2,id);
    }
}
void MainWindow::clear_st_wid_0()
{
    ui->material_nestandart_GB->setVisible(false);
    ui->work_option_GB->setVisible(false);
    ui->percent->setVisible(false);
}

void MainWindow::nestandart_material_load(material mat_like_my)
{
clear_st_wid_0();
    ui->stackedWidget->setCurrentIndex(0);
    ui->material_nestandart_GB->setVisible(true);
    ui->statusBar->showMessage(tr("требуется реакия пользователя на нестандартную линию поведения программы"));

    ui->name_a_LE->setText(mat_like_my.name);
    ui->name_b_LE->setText(mat_like_my.name);
    ui->name_c_LE->setText(mat_like_my.name);

    ui->price_a_DSB->setValue(mat_like_my.price.toDouble());
    ui->price_b_DSB->setValue(ui->dSpBo_material_price->value());

    ui->cocunt_a_LE->setText(mat_like_my.count);
    ui->count_b_LE->setText(QString::number(ui->material_count_sp_box->value()));
    ui->count_c_SPB->setValue(mat_like_my.count.toInt()+ui->material_count_sp_box->value());

    ui->funct_a->setText(mat_like_my.naznach);
    ui->funct_b->setText(ui->funct_naznach->currentText());
    ui->funct_c_CB->clear();
    ui->funct_c_CB->addItem(mat_like_my.naznach);
    ui->funct_c_CB->addItem(ui->funct_naznach->currentText());

    ui->ed_izmer_a->setText(mat_like_my.izmer);
    ui->ed_izmer_b->setText(ui->ed_izmeren->currentText());
    ui->ed_izmer_c_CB->clear();
    ui->ed_izmer_c_CB->addItem(mat_like_my.izmer);
    ui->ed_izmer_c_CB->addItem(ui->ed_izmeren->currentText());

    ui->price_a_ChBox->setChecked(true);
    ui->price_c_DSB->setValue(ui->price_a_DSB->value());

    ui->material_ID->display(mat_like_my.ID);
    ui->stackedWidget->setCurrentIndex(0);

clear_material();
}

void MainWindow::save_nestandart_materrial_dialog()
{
    material temp;
    temp.price=QString::number(ui->price_c_DSB->value());
    temp.count=QString::number(ui->count_c_SPB->value());
    temp.naznach=QString::number(ui->price_c_DSB->value());
    if (ui->funct_c_CB->currentText()!="")
    {
    temp.naznach=ui->funct_c_CB->currentText();
    }
    else
    {
       temp.naznach="";
    }
    if(ui->ed_izmer_c_CB->currentText()!="")
    {
       temp.izmer=ui->ed_izmer_c_CB->currentText();
    }
    else
    {
      temp.izmer="";
    }
    temp.ID=QString::number(ui->material_ID->value());

    ui->statusBar->showMessage(tr("редактирование материала произведено!"));
    ui->stackedWidget->setCurrentIndex(6);
    QUERY->material_up_2_to_1(temp);
    ui->price_b_ChBox->setChecked(false);
}

void MainWindow::save_material_from_ui_to_DB()//записать текущий (insert)
{
    material temp;
    temp.name=ui->material_name_LE->text();
    if (ui->funct_naznach->currentText()!="")
    {
         temp.naznach=ui->funct_naznach->currentText();
    }
    else temp.naznach="NULL";


    temp.price=QString::number(ui->dSpBo_material_price->value());
    if (ui->ed_izmeren->currentText()!="")
    {
        temp.izmer=ui->ed_izmeren->currentText();
    }
     else temp.izmer="NULL";
    temp.count=QString::number(ui->material_count_sp_box->value());
    QUERY->insert_material(temp);

    ui->statusBar->showMessage(tr("данные занесены успешно"));
    clear_material();
}

void MainWindow::save_material_all_varibl()
{
    split_material();
    if ((ui->material_name_LE->text()!=0)&& (ui->dSpBo_material_price->value()!=0) && (ui->material_count_sp_box->value()!=0))
    {
        QList <material> like_my=QUERY->mater_like_my(ui->material_name_LE->text());
        if (like_my.size()==1)
        {
            material mat_like_my=like_my[0];
            if (mat_like_my.price==QString::number(ui->dSpBo_material_price->value()) && mat_like_my.izmer==ui->ed_izmeren->currentText())
            {
                //sum and update
                int a=mat_like_my.count_int;
                int b=ui->material_count_sp_box->value();
                QString sum(QString::number(a+b));
                QUERY->material_up_summ_count(sum, mat_like_my.ID);
                ui->statusBar->showMessage(tr("данные занесены успешно (суммирование)"));
                clear_material();
            }
            else
            {
                //исключит  ситуация
                nestandart_material_load(mat_like_my);
            }
        }
        else
        {
            save_material_from_ui_to_DB();
        }
    }
    else
    {
        ui->statusBar->showMessage(tr("данные не занесены, Заполните ключевые поля!"));
        ui->label_10->setText("<font color=red> название </font>");
        ui->label_11->setText("<font color=red> цена </font>");
        ui->label_13->setText("<font color=red> количество </font>");
    }
}

void MainWindow::save_worker()
{
        QDate dat;
    if (ui->new_worker_FIO_LE->text()!="" && ui->new_worker_post_Fou_CoBox->currentText()!="" )
    {
        if (ui->new_worker_year_bir_LE->text()!="" && ui->new_worker_year_bir_LE->text()!=" ")
        {
            if (ui->new_worker_year_bir_LE->text()<=QString::number(dat.currentDate().year()-18))
            {
                worker_to_db();
            }
            else
            {
                ui->statusBar->showMessage(tr("принимаются сотрудники, которым исполнилось 18 лет"));
            }
        }
        else
        {
            worker_to_db();
        }
    }
    else
    {
        ui->statusBar->showMessage(tr("Заполните ключевые (ФИО сотрудника и должность)"));
    }
}

void MainWindow::worker_to_db()
{
    worker temp;
    temp.fio=ui->new_worker_FIO_LE->text();
    if (ui->new_worker_aderss_LE->text()!="")
    {
        temp.adress=ui->new_worker_aderss_LE->text();
    }
    else
    {
        temp.adress="NULL";
    }
    if (ui->new_worker_post_Fou_CoBox->currentText()!="")
    {
        temp.post=ui->new_worker_post_Fou_CoBox->currentText();
    }
    else
    {
        temp.post="NULL";
    }
    if (ui->new_worker_year_bir_LE->text()!="")
    {
        temp.birthday=ui->new_worker_year_bir_LE->text();
    }
    else
    {
        temp.birthday="NULL";
    }
    if (ui->new_worker_OKLAD_doubSpBox->value()!=0)
    {
        temp.pay=QString::number(ui->new_worker_OKLAD_doubSpBox->value());
    }
    QUERY->insert_new_worker(temp);
    load_worker();

    if(ui->new_worker_team_CkBox->checkState()==Qt::Checked)
    {
        QUERY->worker_to_brig(temp, ui->new_worker_special_CoBox->currentText());
        //связывание к группе
    }
    ui->statusBar->showMessage(tr("сотрудник успешно нанят"));
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::dell_eqw()
{
    int row=ui->tableWidget_technics->currentRow();
        QTableWidgetItem *item= new QTableWidgetItem();
        item=ui->tableWidget_technics->item(row,1);//id
        QString s;
        s=item->text();
        QUERY->del_eqw_from_brig(s); //удалить привязку к бригаде
        QUERY->eqw_dell(s);

    ui->statusBar->showMessage(tr("информация о оборудовании удалена"));
    ui->dell_eqvmnt->setEnabled(false);
    load_technics();
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

void MainWindow::split_worker()
{
    QString s;
    s=ui->new_worker_FIO_LE->text();
    ui->new_worker_FIO_LE->clear();
    ui->new_worker_FIO_LE->setText(split_str(s));
    s.clear();
    s=ui->new_worker_aderss_LE->text();
    ui->new_worker_aderss_LE->clear();
    ui->new_worker_aderss_LE->setText(split_str(s));
}

void MainWindow::split_eqw()
{    
    QString s;
    s=ui->material_name_LE->text();
    ui->material_name_LE->clear();
    ui->material_name_LE->setText(split_str(s));
}

void MainWindow::split_client()
{
    QString s;
    s=ui->lineEdit_client_mestoJit_input->text();
    ui->lineEdit_client_mestoJit_input->clear();
    ui->lineEdit_client_mestoJit_input->setText(split_str(s));

    s=ui->lineEdit_client_fio_input->text();
    ui->lineEdit_client_fio_input->clear();
    ui->lineEdit_client_fio_input->setText(split_str(s));
}

void MainWindow::split_house()
{  
    QString s;
    s=ui->new_standart_name_LE->text();
    ui->new_standart_name_LE->clear();
    ui->new_standart_name_LE->setText(split_str(s));
}

void MainWindow::split_material()
{   
    QString s;
    s=ui->material_name_LE->text();
    ui->material_name_LE->clear();
    ui->material_name_LE->setText(split_str(s));
}

void MainWindow::save_new_eqw()
{
    if ((ui->oborud_INV_namber_LE->text()!="") && (ui->oborud_name_LE->text()!=""))
    {
        technics temp;
        temp.namber=ui->oborud_INV_namber_LE->text();
        temp.name=ui->oborud_name_LE->text();
        if (ui->obor_ear_build_SpBx->value()>=1901)
        {
            temp.Year_vip=QString::number(ui->obor_ear_build_SpBx->value());
        }
        else temp.Year_vip="NULL";
        if(ui->pokupka_obor_dateE->date().year()>=2015)
        {
            QDate dat=ui->pokupka_obor_dateE->date();
            temp.Date_pok=QString::number(dat.year())+"-"+QString::number(dat.month())+"-"+QString::number(dat.day());
        }
        else temp.Date_pok="NULL";
        QUERY->insert_new_eqw(temp);
        if (ui->new_eqw_plas_team_ChBox->checkState()==Qt::Checked)
        {
            //закрепить за бригадой
            QUERY->eqw_to_brig(ui->oborud_INV_namber_LE->text(), ui->new_eq_id_Combox->currentText());
        }
        ui->new_eq_team_comBOX->setVisible(false);
        ui->new_eqw_plas_team_ChBox->setChecked(false);
        ui->statusBar->showMessage(tr("оборудоание успешно куплено"));
        load_technics();
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->statusBar->showMessage(tr("Заполните ключевые поля(название и инвентарный номер!)"));
    }
}

void MainWindow::load_statistic()
{

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

void MainWindow::load_avto_client_with_pasport(QString var)
{
    if (var.length()==8)
    {
        QList <client> list=QUERY->is_client_with_passport(var);
        if (list.size()==1)
        {
            ui->lineEdit_client_mestoJit_input->setText(list[0].plases_life);
            ui->lineEdit_client_fio_input->setText(list[0].FIO);
            ui->lineEdit_client_yearBir_input->setText(list[0].year_birthday);
            ui->lineEdit_client_phone_input->setText(list[0].phone);
        }
    }
}


void MainWindow::save_progect_info()
{
    QString ID;
    split_client();
    if (correct_data_client())
    {
        save_client();//клиент
        if (ui->checkBox_is_ynical_progect->isChecked()) //проверка типа проекта
        {//уникальный
            if (correct_data_new_building_progect())
            {
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //занесение информации о постройке
                //вернуть id постройки
                ID=save_all_info_buildin(true);
                QString progect_id;
                progect_id=QUERY->save_progect(ui->lineEdit_client_pasport_input->text(), ID);
                qDebug()<<"сохранение уникальной постройки и создание проекта"<<endl;
                plan_building_time b;
                b.make_and_save_time_plan_for_building(progect_id, ui->date_start_w->date());
                //b.sub_material_for_building(ID);
                //расчет графика работ и вывод данных на печать

            }
            else
            {
                ui->statusBar->showMessage(tr("заполните данные уникального проекта"));
            }
        }
        else
        {//стандартный
            if (ui->building_id_for_progect->text()!="")
            {
                ID=ui->building_id_for_progect->text();//постройки
                QString progect_id;
                progect_id=QUERY->save_progect(ui->lineEdit_client_pasport_input->text(), ID);
                //building b;
                plan_building_time b;
                b.make_and_save_time_plan_for_building(progect_id, ui->date_start_w->date());
                //b.sub_material_for_building(ID);
                qDebug()<<"проект стандартной постройки"<<endl;
                //расчет графика работ и вывод данных на печать
                //qDebug()<<"расчет графика"<<endl;
            }
            else
            {
                ui->statusBar->showMessage("стандартный проект не выбран");
            }
        }

    }
}

void MainWindow::save_client()
{
    client temp;
    temp.FIO=ui->lineEdit_client_fio_input->text();
    temp.plases_life=ui->lineEdit_client_mestoJit_input->text();
    temp.passport=ui->lineEdit_client_pasport_input->text();
    temp.phone=ui->lineEdit_client_phone_input->text();
    temp.year_birthday=ui->lineEdit_client_yearBir_input->text();
    QUERY->insert_client_info(temp);
}
