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
            year->setText(temp.Year_vip);
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
    ui->tableWidget_house->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_house_poisk->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    connect(ui->radioButton_fundament,SIGNAL(clicked(bool)),ui->label_3,SLOT(setVisible(bool)));
    connect(ui->new_worker_team_CkBox,SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->radioButton_fundament,SIGNAL(clicked(bool)),ui->label_swai_ynical_prog,SLOT(setVisible(bool)));
    connect(ui->new_worker_team_CkBox, SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->CB_House_poisk,SIGNAL(clicked(bool)),ui->tableWidget_house_poisk,SLOT(setVisible(bool)));
    connect(ui->pushButton_add_last_house,SIGNAL(clicked()),this,SLOT(add_house_to_db()));
}

void MainWindow::set_visible_enabled()
{
    ui->work_option_GB->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->dell_eqvmnt->setEnabled(false);
    ui->new_eq_team_comBOX->setVisible(false);
    ui->new_brigada_GrBox->setVisible(false);
    ui->GroBox_Indiv_Prog->setVisible(false);
    ui->material_nestandart_GB->setVisible(false);
    ui->groBox_Progect_Standart_progect->setVisible(true);
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
}

void MainWindow::clear_first()
{
    ui->ed_izmeren->clear();
    ui->funct_naznach->clear();
    ui->new_special_brig_FCB->clear();
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
