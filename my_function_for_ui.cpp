#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

void MainWindow::load_technics()
{
    ui->stackedWidget->setCurrentIndex(1);
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
//=========================================================================================================
void MainWindow::dell_problem(QString v)
{
    QString dell;
    dell=v;
    dell=dell+" ";
}
