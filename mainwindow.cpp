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
        load_technics();
}
void MainWindow::on_person_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
    load_worker();
}
void MainWindow::on_new_contract_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::on_home_progect_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
    load_building();
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
//void MainWindow::on_toolButton_Raport_clicked()
//{
//    poisk_material *poi=new poisk_material;
//    poi->show();
//}
void MainWindow::on_Butt_Buy_car_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    //texhica_widget *tec=new texhica_widget;
    //tec->show();
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
    ui->GroBox_Indiv_Prog->setVisible(false);
    ui->material_nestandart_GB->setVisible(false);
    ui->groBox_Progect_Standart_progect->setVisible(true);

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
    connect(ui->new_eqw_plas_team_ChBox,SIGNAL(clicked(bool)),ui->new_eq_team_GrBox,SLOT(setVisible(bool)));

    ui->material_count_sp_box->setMaximum(99999999);
    ui->count_c_SPB->setMaximum(99999999);
    ui->dSpBo_material_price->setMaximum(999999999);
    ui->new_worker_OKLAD_doubSpBox->setMaximum(999999999);

    ui->ed_izmeren->clear();
    ui->funct_naznach->clear();
    ui->work_option_GB->setVisible(false);
    ui->new_eq_team_GrBox->setVisible(false);
    ui->new_worker_team_GrBox->setVisible(false);
    ui->dell_eqvmnt->setEnabled(false);
}

void MainWindow::load_building()
{
    ui->tableWidget_house->setColumnCount(5);
    //ui->tableWidget_house->setVerticalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена");
    ui->tableWidget_house_poisk->setColumnCount(5);
    ui->tableWidget_house->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена");
    ui->tableWidget_house_poisk->setHorizontalHeaderLabels(QStringList()<<"имя"<<"уникальность"<<"ср t постройки"<<"м/кв"<<"цена");
    ui->tableWidget_house_poisk->setRowCount(1);

    int All_row=0;                              //не оптимально
    //ui->tableWidget_house->setRowCount(All_row);
    //DB->query->exec("SELECT COUNT (*) FROM building;");
    //qDebug()<<"rows="<<All_row;
    //qDebug()<<"selected7= "<<DB->query->isSelect();

    int row=0;
    DB->query->exec("SELECT * FROM building;");
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

void MainWindow::load_technics()
{
    ui->tableWidget_technics->setColumnCount(4);
    ui->tableWidget_technics->setHorizontalHeaderLabels(QStringList()<<"название"<<"инвентарный номер"<<"год выпуска"<<"дата покупки");
    ui->tableWidget_technics->setRowCount(1);
    //int row=0;
    DB->query->exec("SELECT * FROM equipment;");
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
        ui->tableWidget_technics->setItem(i,2,item_year);
        ui->tableWidget_technics->setItem(i,3,item_date);
    }
}

void MainWindow::load_worker()
{

    DB->query->exec("SELECT * FROM worker;");
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
    load_building();
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

    load_worker();
    //перезагрузка таблицы
}

void MainWindow::on_pushButton_add_ne_worker_clicked()
{

    ui->stackedWidget->setCurrentIndex(7);

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

    ui->statusBar->showMessage(tr("оборудоание успешно куплено"));
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_new_worker_Exit_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->statusBar->showMessage(tr("отмена добавления работника!"));
}

void MainWindow::on_new_worker_OK_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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
    load_technics();
}
