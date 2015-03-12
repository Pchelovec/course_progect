#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_person.h"
#include "poisk_material.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    build=new building;
    ui->setupUi(this);
    setCentralWidget(ui->stackedWidget);
    connect_to_DB();
    first_initial_component();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_4_triggered()
{
        ui->stackedWidget->setCurrentIndex(1);
        load_technics("SELECT * FROM equipment;");
}
void MainWindow::on_person_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
    load_worker("SELECT * FROM worker;");
}
void MainWindow::on_new_contract_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::on_home_progect_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
    load_building("SELECT * FROM building;");
}
void MainWindow::on_material_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);
    clear_material();
    ui->ed_izmeren->activateWindow();

}
void MainWindow::on_checkBox_is_ynical_progect_clicked(bool checked)
{
    ui->groBox_Progect_Standart_progect->setVisible(!checked);
    ui->GroBox_Indiv_Prog->setVisible(checked);
}

void MainWindow::on_Butt_Buy_car_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    DB->query->clear();
    DB->query->exec("call special_brig_list");
    //QString s;
    list<QString> list_special;
    while (DB->query->next())
    {
         QString name = DB->query->value(0).toString();
         //ui->new_eq_team_comBOX->
         //ui->new_eq_team_comBOX
         ui->new_eq_Com_box->addItem(name);
         list_special.push_back(name);
         qDebug() << name << endl;
     }
}

void MainWindow::connect_to_DB()
{
    DB=new database;
    //DB->connect();
    if(DB->correct_connected)//если не ошибка подключения
        ui->statusBar->showMessage(tr("Готов к работе!"));
    else
    {
        ui->statusBar->showMessage(tr("НЕ Готов к работе, БД не открыта!!!"));
        ui->stackedWidget->setVisible(false);
    }
}

void MainWindow::first_initial_component()
{
    ui->new_special_brig_FCB->clear();
    ui->new_eq_team_comBOX->setVisible(false);
    ui->new_brigada_GrBox->setVisible(false);
    ui->GroBox_Indiv_Prog->setVisible(false);
    ui->material_nestandart_GB->setVisible(false);
    ui->groBox_Progect_Standart_progect->setVisible(true);
    ui->brig_obor_GRBox->setVisible(false);
    ui->pusB_Sotrudnic_del->setEnabled(false);

    ui->stackedWidget->setCurrentIndex(0);

    ui->GroopBox_techicaDETAI_INFO_3->setVisible(false);//невидимость подробной инфы об оборудовании

    ui->tableWidget_house_poisk->setVisible(false);//невидимость формы поиска

    connect(ui->CB_House_poisk,SIGNAL(clicked(bool)),ui->tableWidget_house_poisk,SLOT(setVisible(bool)));

    //ui->toolBtt_sell_technics->setEnabled(false);

    ui->tableWidget_worker->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_house->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_house_poisk->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_technics->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->pushButton_add_last_house,SIGNAL(clicked()),this,SLOT(add_house_to_db()));

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

    connect(ui->radioButton_fundament,SIGNAL(clicked(bool)),ui->label_3,SLOT(setVisible(bool)));
    connect(ui->new_worker_team_CkBox,SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->radioButton_fundament,SIGNAL(clicked(bool)),ui->label_swai_ynical_prog,SLOT(setVisible(bool)));
    //connect(ui->new_eqw_plas_team_ChBox,SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));
    connect(ui->new_worker_team_CkBox, SIGNAL(clicked(bool)),ui->new_worker_team_GrBox,SLOT(setVisible(bool)));

    ui->new_worker_team_GrBox->setVisible(false);
    //ui->new_worker_team_GrBox->setVisible();
    ui->material_count_sp_box->setMaximum(99999999);
    ui->count_c_SPB->setMaximum(99999999);
    ui->dSpBo_material_price->setMaximum(999999999);
    ui->new_worker_OKLAD_doubSpBox->setMaximum(999999999);

    ui->ed_izmeren->clear();
    ui->funct_naznach->clear();
    ui->work_option_GB->setVisible(false);

    ui->new_worker_team_GrBox->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->dell_eqvmnt->setEnabled(false);
}

void MainWindow::load_building(QString q)
{
    ui->tableWidget_house->setColumnCount(5);
    //ui->tableWidget_house->setVerticalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена");
    ui->tableWidget_house_poisk->setColumnCount(5);
    ui->tableWidget_house->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена");
    ui->tableWidget_house_poisk->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена");
    ui->tableWidget_house_poisk->setRowCount(1);

    int All_row=0;                              //не оптимально
    int row=0;
    DB->query->exec(q);
    while(DB->query->next())
    {
        All_row++;
    }
    All_row++;
    row_building=All_row;
    //qDebug()<<"rows="<<All_row;
    ui->tableWidget_house->setRowCount(All_row);
    DB->query->clear();
    DB->query->exec("SELECT * FROM building;");
    while(DB->query->next())
    {
        QString name = DB->query->value(0).toString();
        bool ynic=DB->query->value(1).toBool();
        QString st_time=DB->query->value(2).toString();
        QString tech_metter=DB->query->value(3).toString();
        QString tech_price=DB->query->value(4).toString();

        QTableWidgetItem *item_name = new QTableWidgetItem();
        item_name->setText(name);

        QWidget *pWidget = new QWidget();
        QCheckBox *pCheckBox = new QCheckBox();
        pCheckBox->setChecked(ynic);
        QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(pCheckBox);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        pWidget->setLayout(pLayout);
        ui->tableWidget_house->setCellWidget(row,1,pWidget);

        QTableWidgetItem *item_time = new QTableWidgetItem();
        item_time->setText(st_time);

        QTableWidgetItem *item_metter = new QTableWidgetItem();
        item_metter->setText(tech_metter);

        QTableWidgetItem *item_price = new QTableWidgetItem();
        item_price->setText(tech_price);

        ui->tableWidget_house->setItem(row,0,item_name);

        ui->tableWidget_house->setItem(row,2,item_time);
        ui->tableWidget_house->setItem(row,3,item_metter);
        ui->tableWidget_house->setItem(row,4,item_price);
        //ui->tableWidget_house->setRowCount(row);
        row++;
    }
}

void MainWindow::load_technics(QString q)
{
    ui->tableWidget_technics->setColumnCount(4);
    ui->tableWidget_technics->setHorizontalHeaderLabels(QStringList()<<"название"<<"инвентарный номер"<<"год выпуска"<<"дата покупки");
    ui->tableWidget_technics->setRowCount(1);
    //int row=0;
    DB->query->exec(q);
    vector <technics> list_tech;
    while(DB->query->next())
    {
        technics temp;
        temp.name=DB->query->value(0).toString();
        temp.namber= DB->query->value(1).toInt();
        temp.Year_vip=DB->query->value(2).toString();
        temp.Date_pok=DB->query->value(3).toString();
        list_tech.push_back(temp);
    }

    row_technics=list_tech.size();
    ui->tableWidget_technics->setRowCount(row_technics);

    for (int i=0;i<row_technics;i++)
    {
        technics temp=list_tech[i];

        QTableWidgetItem *item_name = new QTableWidgetItem();
        item_name->setText(temp.name);

        QTableWidgetItem *item_namber=new QTableWidgetItem();
        item_namber->setText(QString::number(temp.namber));

        QTableWidgetItem *item_year = new QTableWidgetItem();
        item_year->setText(temp.Year_vip);

        QTableWidgetItem *item_date = new QTableWidgetItem();
        item_date->setText(temp.Date_pok);

        ui->tableWidget_technics->setItem(i,0,item_name);
        ui->tableWidget_technics->setItem(i,1,item_namber);
        if (temp.Year_vip!="0")
        ui->tableWidget_technics->setItem(i,2,item_year);
        ui->tableWidget_technics->setItem(i,3,item_date);
    }
}

void MainWindow::load_worker(QString q)
{

    DB->query->exec(q);
    vector<worker> work_vect;
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
        temp.id=DB->query->value(4).toInt();
        temp.pay=DB->query->value(5).toInt();
      work_vect.push_back(temp);
    }
    int row=work_vect.size();
    row_worker=row;
    //qDebug()<<row;
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
        item_ID->setText(QString::number(temp.id));
        item_ID->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *item_pay = new QTableWidgetItem();
        item_pay->setText(QString::number(temp.pay));
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

void MainWindow::add_house_to_db()
{
    QTableWidgetItem *item=new QTableWidgetItem;
    qDebug()<<ui->tableWidget_house->itemAt(row_building,1);
    load_building("SELECT * FROM building;");
}

void MainWindow::on_radioButton_fundament_clicked(bool checked)
{
    build->fundament=checked;
}

void MainWindow::on_material_add_PB_clicked()
{
    if ((ui->material_name_LE->text()!=0)&& (ui->dSpBo_material_price->value()!=0) && (ui->material_count_sp_box->value()!=0))
    {
        QString lik("select * from all_material where name like ");
        lik=lik+"'"+ui->material_name_LE->text()+"';";
        DB->query->exec(lik);
        if (DB->query->next())
        {
        material mat_like_my;
        mat_like_my.name=DB->query->value(0).toString();
        mat_like_my.price=DB->query->value(1).toDouble();
        mat_like_my.funct=DB->query->value(2).toString();
        mat_like_my.izmeren=DB->query->value(3).toString();
        mat_like_my.count=DB->query->value(4).toInt();
        mat_like_my.ID=DB->query->value(5).toInt();
        if (mat_like_my.price==ui->dSpBo_material_price->value() && mat_like_my.izmeren==ui->ed_izmeren->currentText())
        {
            DB->query->clear();
            QString updt("update all_material set count=");
            updt=updt+QString::number(mat_like_my.count+ui->material_count_sp_box->value())+" where id_material="+QString::number(mat_like_my.ID)+";";
            DB->query->exec(updt);
            ui->statusBar->showMessage(tr("данные занесены успешно (суммирование)"));
            qDebug()<<updt<<endl;
            clear_material();
        }
        else
        {
            ui->material_nestandart_GB->setVisible(true);
            ui->name_a_LE->setText(mat_like_my.name);
            ui->name_b_LE->setText(mat_like_my.name);
            ui->name_c_LE->setText(mat_like_my.name);

            ui->price_a_DSB->setValue(mat_like_my.price);
            ui->price_b_DSB->setValue(ui->dSpBo_material_price->value());

            ui->cocunt_a_LE->setText(QString::number(mat_like_my.count));
            ui->count_b_LE->setText(QString::number(ui->material_count_sp_box->value()));
            ui->count_c_SPB->setValue(mat_like_my.count+(ui->material_count_sp_box->value()));

            ui->funct_a->setText(mat_like_my.funct);
            ui->funct_b->setText(ui->funct_naznach->currentText());
            ui->funct_c_CB->clear();
            ui->funct_c_CB->addItem(mat_like_my.funct);
            ui->funct_c_CB->addItem(ui->funct_naznach->currentText());

            ui->ed_izmer_a->setText(mat_like_my.izmeren);
            ui->ed_izmer_b->setText(ui->ed_izmeren->currentText());
            ui->ed_izmer_c_CB->clear();
            ui->ed_izmer_c_CB->addItem(mat_like_my.izmeren);
            ui->ed_izmer_c_CB->addItem(ui->ed_izmeren->currentText());

            ui->price_a_ChBox->setChecked(true);
            ui->price_c_DSB->setValue(ui->price_a_DSB->value());

            ui->material_ID->display(mat_like_my.ID);
            ui->stackedWidget->setCurrentIndex(0);
            //solution
            clear_material();
            ui->statusBar->showMessage(tr("требуется реакия пользователя на нестандартную линию поведения программы"));
        }
        }
        else
        {
        QString s;
        s="insert into all_material(name,price,naznachenie,izmerenie,count)values('";
        s=s+ui->material_name_LE->text()+"'";
        s=s+",'"+QString::number(ui->dSpBo_material_price->value())+"'";
        if (ui->funct_naznach->currentText()!="")
        {
          s=s+",'"+ui->funct_naznach->currentText()+"'";
        }
        else s=s+",NULL";
        if (ui->ed_izmeren->currentText()!="")
        {
           s=s+",'"+ui->ed_izmeren->currentText()+"'";
        }
        else s=s+",NULL";
        s=s+","+QString::number(ui->material_count_sp_box->value())+");";
        qDebug()<<s;
        DB->query->exec(s);
        DB->query->clear();
        ui->statusBar->showMessage(tr("данные занесены успешно"));
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
void MainWindow::clear_material()
{
ui->material_name_LE->setText("");
ui->dSpBo_material_price->setValue(0);
ui->material_count_sp_box->setValue(0);
DB->query->clear();
ui->ed_izmeren->addItem("");
DB->query->exec("call material_list_izmer();");
while (DB->query->next())
{
     QString name = DB->query->value(0).toString();
     ui->ed_izmeren->addItem(name);
     //qDebug() << name<<endl;
}
DB->query->clear();
ui->funct_naznach->addItem("");
DB->query->exec("call material_list_naz();");
while (DB->query->next())
{
     QString name = DB->query->value(0).toString();
     ui->funct_naznach->addItem(name);
     //qDebug() << name<<endl;
}
DB->query->clear();
}

void MainWindow::on_nestandart_material_button_OK_clicked()
{
    //запись в бд
    QString s;
    s=s+"update all_material set count=";
    s=s+QString::number(ui->count_c_SPB->value())+", price='";
    s=s+QString::number(ui->price_c_DSB->value())+"', naznachenie='";
    if (ui->funct_c_CB->currentText()!="")
    {
    s=s+ui->funct_c_CB->currentText()+"',";
    }
    else
    {
       s=s+"NULL',";
    }
    if(ui->ed_izmer_c_CB->currentText()!="")
    {
       s=s+ " izmerenie='"+ui->ed_izmer_c_CB->currentText();
    }
    else
    {
      s=s+" izmerenie='"+"NULL";
    }
    s=s+"' where name like '";
    s=s+ui->name_c_LE->text()+"';";
    DB->query->exec(s);
    qDebug()<<s<<endl;

    ui->statusBar->showMessage(tr("редактирование материала произведено!"));
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_price_a_ChBox_clicked(bool checked)
{
    ui->price_c_DSB->setValue(ui->price_a_DSB->value());
    ui->price_b_ChBox->setChecked(!checked);
}

void MainWindow::on_price_b_ChBox_clicked(bool checked)
{
    ui->price_c_DSB->setValue(ui->price_b_DSB->value());
    ui->price_a_ChBox->setChecked(!checked);
}

void MainWindow::on_option_work_exit_PB_clicked()
{
    ui->work_day_LE->clear();
    ui->holl_day_LE->clear();
    ui->work_option_GB->setVisible(false);
    fin.close();
}

void MainWindow::on_option_worker_OK_PB_clicked()
{
    //save to file


    ui->work_day_LE->clear();
    ui->holl_day_LE->clear();
    ui->work_option_GB->setVisible(false);
    fin.close();
}

void MainWindow::on_work_process_option_triggered()
{
    int work_day=0;
    int holl_day=0;

        fin.open("work_process.txt", ios::in);
        qDebug() << "fie opened";

        fin >> work_day >> holl_day;
    ui->work_day_LE->setText(QString::number(work_day));
    ui->holl_day_LE->setText(QString::number(holl_day));
    ui->work_option_GB->setVisible(true);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_tableWidget_worker_clicked(const QModelIndex &index)
{
    ui->pusB_Sotrudnic_del->setEnabled(true);
}

void MainWindow::on_pusB_Sotrudnic_del_clicked()
{
    int row=ui->tableWidget_worker->currentRow();
    QString s("delete from worker where id_worker=");//удаление из табл работники
    QString s_brig("delete from grup where id_worker="); //удаление из бригады
    QTableWidgetItem *item= new QTableWidgetItem();
    item=ui->tableWidget_worker->item(row,4);
    s=s+item->text()+";";
    s_brig=s_brig+item->text()+";";
    //qDebug()<<s;

    DB->query->clear();
    DB->query->exec(s);

    DB->query->clear();
    DB->query->exec(s_brig);

    ui->statusBar->showMessage(tr("информация о сотруднике удалена"));
    ui->pusB_Sotrudnic_del->setEnabled(false);

    load_worker("SELECT * FROM worker;");
    //перезагрузка таблицы
}

void MainWindow::on_pushButton_add_ne_worker_clicked()
{
    DB->query->clear();
    DB->query->exec("call worker_dolg_list");
    ui->new_worker_post_Fou_CoBox->clear();
    while (DB->query->next())
    {
         QString name = DB->query->value(0).toString();
         ui->new_worker_post_Fou_CoBox->addItem(name);
         qDebug() << name;
    }

    ui->stackedWidget->setCurrentIndex(7);
    DB->query->clear();
    DB->query->exec("call special_brig_list");
    while (DB->query->next())
    {
         QString name = DB->query->value(0).toString();
         //int salary = query.value(1).toInt();
         qDebug() << name ;
         ui->new_worker_special_Comb_box->addItem(name);
    }
}

void MainWindow::on_new_eqv_exit_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->statusBar->showMessage(tr("покупка оборудования отменена"));
}

void MainWindow::on_new_eqv_OK_PB_clicked()
{
    //занести в БД
    //скрыть 2 часть, очистить
    QString s_1("insert into equipment (eq_name, eq_namber");
    QString s_2("values (");

    if ((ui->oborud_INV_namber_LE->text()!="") && (ui->oborud_name_LE->text()!=""))
    {
        s_2=s_2+"'"+ui->oborud_name_LE->text()+"'";
        s_2=s_2+",'"+ui->oborud_INV_namber_LE->text()+"'";
        if (ui->obor_ear_build_SpBx->value()>=1900)
        {
            s_1=s_1+", eq_year ";
            s_2=s_2+","+QString::number(ui->obor_ear_build_SpBx->value());
        }
        if(ui->pokupka_obor_dateE->date().year()>=2015)
        {
            QDate dat=ui->pokupka_obor_dateE->date();
            s_1=s_1+", eq_buy_date ";
            s_2=s_2+",'"+QString::number(dat.year())+"-"+QString::number(dat.month())+"-"+QString::number(dat.day())+"'";
        }
        s_1=s_1+") ";
        s_2=s_2+");";
        QString s(s_1+s_2);
        qDebug()<<s;
        DB->query->clear();
        DB->query->exec(s);
        load_technics("SELECT * FROM equipment;");

        if (ui->new_eqw_plas_team_ChBox->checkState()==Qt::Checked)
        {
            QString qe("insert into grup (worker_ID, group_id) values (");
            //if ()//связывание к группе
        }

        ui->statusBar->showMessage(tr("оборудоание успешно куплено"));
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->statusBar->showMessage(tr("Заполните ключевые поля(название и инвентарный номер!)"));
    }
}

void MainWindow::on_new_worker_Exit_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->statusBar->showMessage(tr("отмена добавления работника!"));
}

void MainWindow::on_new_worker_OK_PB_clicked()
{
    //занести в БД
    //скрыть 2 часть, очистить
    QString s_1("insert into worker (");
    QString s_2("values (");
    if (ui->new_worker_FIO_LE->text()!="")
    {
        s_1=s_1+"fio";
        s_2=s_2+"'"+ui->new_worker_FIO_LE->text()+"'";
        if (ui->new_worker_aderss_LE->text()!="")
        {
            s_1=s_1+",adress";
            s_2=s_2+",'"+ui->new_worker_aderss_LE->text()+"'";
        }
        if (ui->new_worker_post_Fou_CoBox->currentText()!="")
        {
            s_1=s_1+",post";
            s_2=s_2+",'"+ui->new_worker_post_Fou_CoBox->currentText()+"'";
        }
        if (ui->new_worker_year_bir_LE->text()!="")
        {
            s_1=s_1+",birthday";
            s_2=s_2+",'"+ui->new_worker_year_bir_LE->text()+"'";
        }
        if (ui->new_worker_OKLAD_doubSpBox->value()!=0)
        {
            s_1=s_1+",price";
            s_2=s_2+",'"+QString::number(ui->new_worker_OKLAD_doubSpBox->value())+"'";
        }
        s_1=s_1+") ";
        s_2=s_2+");";
        QString s(s_1+s_2);
        qDebug()<<s;
        DB->query->clear();
        DB->query->exec(s);
        load_worker("SELECT * FROM worker;");

        if(ui->new_worker_team_CkBox->checkState()==Qt::Checked)
        {
            //QString qe("insert into grup (worker_ID, group_id) values (");

            //if ()//связывание к группе
        }
        ui->new_worker_FIO_LE->clear();
        ui->new_worker_aderss_LE->clear();
        ui->new_worker_post_Fou_CoBox->clear();
        ui->new_worker_year_bir_LE->clear();
        ui->new_worker_OKLAD_doubSpBox->clear();
        ui->statusBar->showMessage(tr("сотрудник успешно нанят"));
        ui->stackedWidget->setCurrentIndex(3);
    }
    else
    {
        ui->statusBar->showMessage(tr("Заполните ключевые (ФИО сотрудника)"));
    }
}

void MainWindow::on_tableWidget_technics_clicked(const QModelIndex &index)
{
    ui->dell_eqvmnt->setEnabled(true);
}

void MainWindow::on_dell_eqvmnt_clicked()
{
    QString s("delete from equipment where eq_namber=");
    QString s2("delete from group_eq where id_namber=");
    int row=ui->tableWidget_technics->currentRow();
            QTableWidgetItem *item= new QTableWidgetItem();
            item=ui->tableWidget_technics->item(row,1);
            s=s+item->text()+";";
            s2=s2+item->text()+";";
            qDebug()<<s<<endl;
            DB->query->clear();
            DB->query->exec(s);

            DB->query->clear();
            DB->query->exec(s2);
    ui->statusBar->showMessage(tr("информация о оборудовании удалена"));
    ui->dell_eqvmnt->setEnabled(false);
    load_technics("SELECT * FROM equipment;");
}

void MainWindow::on_new_worker_team_CkBox_clicked(bool checked)
{
    ui->new_worker_team_GrBox->setVisible(checked);
}

void MainWindow::on_new_eq_Com_box_activated(const QString &arg1)
{
    DB->query->clear();
    QString s("SELECT special_brig.id_brig FROM special_brig , special WHERE special.id = special_brig.id_special and special.`name` = '");
    s=s+arg1+"';";
    qDebug()<<s;
    DB->query->exec(s);
    while (DB->query->next())
    {
         QString val = DB->query->value(0).toString();
         //int salary = query.value(1).toInt();
         qDebug() << val;
         ui->new_eq_id_Combox->addItem(val);
    }
}

void MainWindow::on_new_eqw_plas_team_ChBox_clicked(bool checked)
{
    ui->new_eq_team_comBOX->setVisible(checked);
}

void MainWindow::on_new_worker_special_Comb_box_activated(const QString &arg1)
{
    DB->query->clear();
    QString s("SELECT special_brig.id_brig FROM special_brig , special WHERE special.id = special_brig.id_special and special.`name` = '");
    s=s+arg1+"';";
    qDebug()<<s;
    DB->query->exec(s);
    while (DB->query->next())
    {
         QString val = DB->query->value(0).toString();
         //int salary = query.value(1).toInt();
         ui->new_worker_special_CoBox->addItem(val);
         qDebug() << val;
         ui->new_eq_id_Combox->addItem(val);
    }
}

void MainWindow::on_brigada_sostav_triggered()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->del_from_brig->setEnabled(false);
    DB->query->clear();
    DB->query->exec("SELECT special.`name` FROM special GROUP BY special.`name`;");
    ui->special_obor_brig_ComBox->clear();
    while (DB->query->next())
    {
        ui->special_obor_brig_ComBox->addItem(DB->query->value(0).toString());
        ui->new_special_brig_FCB->addItem(DB->query->value(0).toString());
    }
}

void MainWindow::on_add_new_brigada_PB_clicked()
{
    //занесение в бд

    QString ID;
    QString s1("SELECT special.id FROM special WHERE special.`name`='");
    s1=s1+ui->new_special_brig_FCB->currentText()+"';";
    qDebug()<<s1<<endl;
    DB->query->clear();
    DB->query->exec(s1);

    if (DB->query->next() && DB->query->value(0).toString()!="")
    {
    qDebug()<<"true"<<endl;
    int a=DB->query->value(0).toInt();
    ID=QString::number(a);
    DB->query->clear();
    QString s("insert into special_brig (id_special) value(");
    s=s+ID+");";
    qDebug()<<s<<endl;
    DB->query->exec(s);
    ui->statusBar->showMessage(tr("бригаа создана"));
    }
    else
    {
qDebug()<<"else"<<endl;
        QString q("insert into special (name) value('"+ui->new_special_brig_FCB->currentText()+"');");
        DB->query->clear();
        qDebug()<<q<<endl;
        DB->query->exec(q);

        DB->query->clear();
        qDebug()<<s1<<endl;
        DB->query->exec(s1);
        DB->query->next();

        int a=DB->query->value(0).toInt();
        qDebug()<<a<<"++++++*********++++++++="<<endl;
        ID=QString::number(a);
        DB->query->clear();
        QString s("insert into special_brig (id_special) value(");
        s=s+ID+");";
        qDebug()<<s<<endl;
        DB->query->exec(s);
        ui->statusBar->showMessage(tr("бригада создана"));
    }
    ui->new_brigada_ChBox->setChecked(false);
    ui->new_brigada_GrBox->setVisible(false);
    //перезагрузка group box
}

void MainWindow::on_new_brigada_ChBox_clicked(bool checked)
{
    ui->new_brigada_GrBox->setVisible(checked);
}

void MainWindow::on_special_obor_brig_ComBox_activated(const QString &arg1)
{
    ui->namber_obor_brig_ComBox->clear();
    QString res;
    QString s_3;
    s_3="SELECT special_brig.id_brig FROM special , special_brig WHERE special.id = special_brig.id_special and special.name='";
    s_3=s_3+arg1+"';";
    DB->query->clear();
    qDebug()<<s_3<<endl;
    DB->query->exec(s_3);

    while (DB->query->next())
    {
        ui->namber_obor_brig_ComBox->addItem(DB->query->value(0).toString());
    }
}

void MainWindow::on_obor_worker_table_wid_activated(const QModelIndex &index)
{
    ui->del_from_brig->setEnabled(true);
}

void MainWindow::on_add_to_brig_clicked()
{
    if((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->obor_brigada_RB->isChecked())))
    {
        ui->brig_obor_GRBox->setVisible(true);
        ui->pushButton->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{

    //бд

    ui->brig_obor_GRBox->setVisible(false);
    ui->statusBar->showMessage(tr("бригада пополнена"));

}

void MainWindow::on_tableWidget_activated(const QModelIndex &index)
{

    ui->pushButton->setEnabled(true);
}

void MainWindow::on_select_obor_eqw_clos_PB_clicked()
{
    ui->brig_obor_GRBox->setVisible(false);
}
