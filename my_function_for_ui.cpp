#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

void MainWindow::load_technics()
{
    ui->tableWidget_technics->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_technics->setColumnCount(4);
    ui->tableWidget_technics->setHorizontalHeaderLabels(QStringList()<<"название"<<"инвентарный номер"<<"год выпуска"<<"дата покупки");
    QList <technics> list_tech;
    list_tech=QUERY->eqw_all_load();
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
    work_vect=QUERY->worker_all();
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

        //ui->tableWidget_worker->setItemDelegateForColumn();               //!!!!!!!!!!!!!!!!!!
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
    ui->tableWidget_house_poisk->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->show_PB->setEnabled(false);
    ui->tableWidget_house->setColumnCount(6);
    ui->tableWidget_house_poisk->setColumnCount(6);
    ui->tableWidget_house->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена"<<"ID");
    ui->tableWidget_house_poisk->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена"<<"ID");
    QList <building> table=QUERY->building_main_class_ret();
    int row=table.size();
    ui->tableWidget_house->setRowCount(row);

    building temp;
    for (int i=0;i<table.size();i++)
    {
        temp=table[i];
            QTableWidgetItem * tw_name=new QTableWidgetItem;
            tw_name->setText(temp.name);
            ui->tableWidget_house->setItem(i,0,tw_name);
            QTableWidgetItem * tw_ynic=new QTableWidgetItem;
            tw_ynic->setText(temp.id_ynical_string);
            ui->tableWidget_house->setItem(i,1,tw_ynic);
            QTableWidgetItem * tw_time_b=new QTableWidgetItem;
            tw_time_b->setText(temp.Standart_time_building);
            ui->tableWidget_house->setItem(i,2,tw_time_b);
            QTableWidgetItem * tw_metter=new QTableWidgetItem;
            tw_metter->setText(temp.metter);
            ui->tableWidget_house->setItem(i,3,tw_metter);
            QTableWidgetItem * tw_price=new QTableWidgetItem;
            tw_price->setText(temp.price);
            ui->tableWidget_house->setItem(i,4,tw_price);
            QTableWidgetItem * tw_id=new QTableWidgetItem;
            tw_id->setText(temp.ID);
            ui->tableWidget_house->setItem(i,5,tw_id);
    }
}
void MainWindow::Q_Object_connect()
{
    connect(ui->new_worker_team_CkBox,SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));

    connect(ui->new_worker_team_CkBox, SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->CB_House_poisk,SIGNAL(clicked(bool)),ui->tableWidget_house_poisk,SLOT(setVisible(bool)));
}

void MainWindow::set_visible_enabled()
{
    //ui->House_progect_main_dell_PB->setEnabled(false);
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
    //ui->groBox_Progect_Standart_progect->setVisible(true);
    ui->brig_obor_GRBox->setVisible(false);
    ui->pusB_Sotrudnic_del->setEnabled(false);
    ui->tableWidget_house_poisk->setVisible(false);//невидимость формы поиска
}
void MainWindow::set_validator_all()
{
    QRegExp name("[а-я А-Я]{20}");
    ui->lineEdit_client_fio_input->setValidator(new QRegExpValidator(name,this));

    QRegExp mesto("[а-я А-Я]{20}");
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
    ui->oborud_INV_namber_LE->setValidator(new QRegExpValidator(INN,this));
    ui->obor_ear_build_SpBx->setMaximum(2015);//текуший год

    QRegExp name_adr_post_fio("[а-я А-Я . , /]{20}");
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
    qDebug()<<"очистка безисходности";
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
    ui->active_progect_TW->setHorizontalHeaderLabels(QStringList()<<"фамилия"<<"телефон"<<"оплаченная сумма"<<"дата заключения договора");

    for (int i=0;i<table_row;i++)
    {
        QTableWidgetItem *fio=new QTableWidgetItem;
        fio->setText(list[i].fio);
        QTableWidgetItem *ph=new QTableWidgetItem;
        ph->setText(list[i].ph);
        QTableWidgetItem *price=new QTableWidgetItem;
        price->setText(list[i].price);
        QTableWidgetItem *date=new QTableWidgetItem;
        date->setText(list[i].date);
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
    ui->checkBox_is_ynical_progect->setChecked(false);
    ui->lineEdit_client_mestoJit_input->clear();
    ui->lineEdit_client_fio_input->clear();
    ui->lineEdit_client_pasport_input->clear();
    ui->lineEdit_client_yearBir_input->clear();
    ui->lineEdit_client_phone_input->clear();
}

void MainWindow::save_all_info_buildin(bool ynic)
{
  building temp;
    temp.is_ynical_bool=ynic;
    temp.name=ui->new_standart_name_LE->text();
    temp.price=QString::number(ui->new_standart_DSpBox->value());
    temp.Standart_time_building=QString::number(ui->new_standart_time_SpB->value());
    temp.metter=QString::number(ui->new_standart_metter_SpBox->value());
    temp.neded_material=return_list_need_material();
    temp.time_plan=return_time_plane();
  QUERY->insert_new_building(temp);
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
    if (ui->lineEdit_client_fio_input->text()!="" && ui->lineEdit_client_phone_input->text()!="" && ui->lineEdit_client_pasport_input->text()!="" && ui->lineEdit_client_phone_input->text().length()>=7 && ui->lineEdit_client_pasport_input->text().length()>=8)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::set_id_progect_standart()
{
QTableWidgetItem *item=new QTableWidgetItem;
item=ui->tableWidget_house->item(ui->tableWidget_house->currentRow(), 5);
ui->building_id_for_progect->setText(item->text());
ui->stackedWidget->setCurrentIndex(5);
}

void  MainWindow::unshow_percent()
{
    ui->percent->setVisible(false);

}
