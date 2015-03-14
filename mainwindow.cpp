#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUERY=new query_result;
    build=new building;
    setCentralWidget(ui->stackedWidget);
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
}
void MainWindow::on_checkBox_is_ynical_progect_clicked(bool checked)
{
    ui->groBox_Progect_Standart_progect->setVisible(!checked);
    ui->GroBox_Indiv_Prog->setVisible(checked);
}

void MainWindow::on_Butt_Buy_car_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    load_new_eqwt();
}

void MainWindow::first_initial_component()
{
    Q_Object_connect();
    set_visible_enabled();
    set_validator_all();
    clear_first();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::add_house_to_db()
{
    QTableWidgetItem *item=new QTableWidgetItem;
    load_building();
}

void MainWindow::on_material_add_PB_clicked()
{
    if ((ui->material_name_LE->text()!=0)&& (ui->dSpBo_material_price->value()!=0) && (ui->material_count_sp_box->value()!=0))
    {
        //QString lik("select * from all_material where name like ");
        //lik=lik+"'"+ui->material_name_LE->text()+"';";

        QList <material> like_my=QUERY->mater_like_my(ui->material_name_LE->text());
        if (like_my.size()==1)
        {
            material mat_like_my=like_my[0];
            if (mat_like_my.price==QString::number(ui->dSpBo_material_price->value()) && mat_like_my.izmer==ui->ed_izmeren->currentText())
            {
                //sum and apdate
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
        }
        else
        {
            //записать текущий (insert) выделить в подпрограмму
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

void MainWindow::on_nestandart_material_button_OK_clicked()
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
       temp.naznach="NULL";
    }
    if(ui->ed_izmer_c_CB->currentText()!="")
    {
       temp.izmer=ui->ed_izmer_c_CB->currentText();
    }
    else
    {
      temp.izmer="NULL";
    }
    temp.ID=QString::number(ui->material_ID->value());

    ui->statusBar->showMessage(tr("редактирование материала произведено!"));
    ui->stackedWidget->setCurrentIndex(6);
    QUERY->material_up_2_to_1(temp);
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
    //fin.close();
}

void MainWindow::on_option_worker_OK_PB_clicked()
{
    //save to file


    ui->work_day_LE->clear();
    ui->holl_day_LE->clear();
    ui->work_option_GB->setVisible(false);
    //fin.close();
}

void MainWindow::on_work_process_option_triggered()
{
    int work_day=0;
    int holl_day=0;
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

    //DB->query->clear();
//    DB->query->exec(s);

//    DB->query->clear();
//    DB->query->exec(s_brig);

    ui->statusBar->showMessage(tr("информация о сотруднике удалена"));
    ui->pusB_Sotrudnic_del->setEnabled(false);

    load_worker();
    //перезагрузка таблицы
}

void MainWindow::on_pushButton_add_ne_worker_clicked()
{
    //DB->query->clear();
    //DB->query->exec("call worker_dolg_list");
    ui->new_worker_post_Fou_CoBox->clear();
//    while (DB->query->next())
//    {
//         QString name = DB->query->value(0).toString();
//         ui->new_worker_post_Fou_CoBox->addItem(name);
//         qDebug() << name;
//    }

    ui->stackedWidget->setCurrentIndex(7);
//    DB->query->clear();
//    DB->query->exec("call special_brig_list");
//    while (DB->query->next())
//    {
//         QString name = DB->query->value(0).toString();
//         //int salary = query.value(1).toInt();
//         qDebug() << name ;
//         ui->new_worker_special_Comb_box->addItem(name);
//    }
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
            QUERY->eqw_to_brig(temp);
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
        //DB->query->clear();
        //DB->query->exec(s);
        load_worker();

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
            //DB->query->clear();
            //DB->query->exec(s);

            //DB->query->clear();
            //DB->query->exec(s2);
    ui->statusBar->showMessage(tr("информация о оборудовании удалена"));
    ui->dell_eqvmnt->setEnabled(false);
    load_technics();
}

void MainWindow::on_new_worker_team_CkBox_clicked(bool checked)
{
    ui->new_worker_team_GrBox->setVisible(checked);
}

void MainWindow::on_new_eq_Com_box_activated(const QString &arg1)
{
    //DB->query->clear();
    QString s("SELECT special_brig.id_brig FROM special_brig , special WHERE special.id = special_brig.id_special and special.`name` = '");
    s=s+arg1+"';";
    //qDebug()<<s;
    //DB->query->exec(s);
//    while (DB->query->next())
//    {
//         QString val = DB->query->value(0).toString();
//         //int salary = query.value(1).toInt();
//         qDebug() << val;
//         ui->new_eq_id_Combox->addItem(val);
//    }
}

void MainWindow::on_new_eqw_plas_team_ChBox_clicked(bool checked)
{
    ui->new_eq_team_comBOX->setVisible(checked);
}

void MainWindow::on_new_worker_special_Comb_box_activated(const QString &arg1)
{
    //DB->query->clear();
    QString s("SELECT special_brig.id_brig FROM special_brig , special WHERE special.id = special_brig.id_special and special.`name` = '");
    s=s+arg1+"';";
    qDebug()<<s;
    //DB->query->exec(s);
//    while (DB->query->next())
//    {
//         QString val = DB->query->value(0).toString();
//         //int salary = query.value(1).toInt();
//         ui->new_worker_special_CoBox->addItem(val);
//         qDebug() << val;
//         ui->new_eq_id_Combox->addItem(val);
//    }
}

void MainWindow::on_brigada_sostav_triggered()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->del_from_brig->setEnabled(false);
    //DB->query->clear();
    //DB->query->exec("SELECT special.`name` FROM special GROUP BY special.`name`;");
    ui->special_obor_brig_ComBox->clear();
//    while (DB->query->next())
//    {
//        ui->special_obor_brig_ComBox->addItem(DB->query->value(0).toString());
//        ui->new_special_brig_FCB->addItem(DB->query->value(0).toString());
//    }
}

void MainWindow::on_add_new_brigada_PB_clicked()
{
    //занесение в бд

    QString ID;
    QString s1("SELECT special.id FROM special WHERE special.`name`='");
    s1=s1+ui->new_special_brig_FCB->currentText()+"';";
    qDebug()<<s1<<endl;
    //DB->query->clear();
    //DB->query->exec(s1);

//    if (DB->query->next() && DB->query->value(0).toString()!="")
//    {
//    qDebug()<<"true"<<endl;
//    //int a=DB->query->value(0).toInt();
//    ID=QString::number(a);
//    //DB->query->clear();
//    QString s("insert into special_brig (id_special) value(");
//    s=s+ID+");";
//    qDebug()<<s<<endl;
//    DB->query->exec(s);
//    ui->statusBar->showMessage(tr("бригаа создана"));
//    }
//    else
//    {
//qDebug()<<"else"<<endl;
//        QString q("insert into special (name) value('"+ui->new_special_brig_FCB->currentText()+"');");
//        DB->query->clear();
//        qDebug()<<q<<endl;
//        DB->query->exec(q);

//        DB->query->clear();
//        qDebug()<<s1<<endl;
//        DB->query->exec(s1);
//        DB->query->next();

//        int a=DB->query->value(0).toInt();
//        qDebug()<<a<<"++++++*********++++++++="<<endl;
//        ID=QString::number(a);
//        DB->query->clear();
//        QString s("insert into special_brig (id_special) value(");
//        s=s+ID+");";
//        qDebug()<<s<<endl;
//        DB->query->exec(s);
//        ui->statusBar->showMessage(tr("бригада создана"));
//    }
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
    //DB->query->clear();
    //qDebug()<<s_3<<endl;
    //DB->query->exec(s_3);

//    while (DB->query->next())
//    {
//        ui->namber_obor_brig_ComBox->addItem(DB->query->value(0).toString());
//    }
}

void MainWindow::on_add_to_brig_clicked()
{
    if((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        ui->bezicxodnost_table_wid->clear();
        ui->bezicxodnost_table_wid->setColumnCount(3);

        if ((ui->eqw_brigada_RB->isChecked()))
        {
            //оборудование
            qDebug()<<"worker"<<endl;

            ui->bezicxodnost_table_wid->setHorizontalHeaderLabels(QStringList()<<"название"<<"дата покупки"<<"инвентарный номер");
            QList <worker> list_work=QUERY->avto_worker_list_free();
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
        else
        {
            if ((ui->worker_brigada_RB->isChecked()))
            {
                //бригада
                qDebug()<<"eqw"<<endl;

                ui->bezicxodnost_table_wid->setHorizontalHeaderLabels(QStringList()<<"должность"<<"фио"<<"ID");
                QList <technics> list_eq=QUERY->avto_eq_list_free();
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
        }
     ui->brig_obor_GRBox->setVisible(true);
     ui->pushButton->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{

    //бд добавление
    QString q("insert into ");
    if (ui->eqw_brigada_RB->isChecked())
    {
        //оборуд
        qDebug()<<"оборуд";
        q=q+"group_eq (id_namber, id_brig) value(";
        int row=ui->bezicxodnost_table_wid->currentRow();
        QTableWidgetItem * item=new QTableWidgetItem;
        item=ui->bezicxodnost_table_wid->item(row,2);
        q=q+"'"+item->text()+"',";
        q=q+" '"+ui->namber_obor_brig_ComBox->currentText()+"');";
        qDebug()<<q;
        //DB->query->clear();
        //DB->query->exec(q);
        load_obor_to_double_TabWid();
    }
    else
    {
        if (ui->worker_brigada_RB->isChecked())
        {
            //работник
            qDebug()<<"работник";
            q=q+"grup (worker_ID, group_id) value(";
            int row=ui->bezicxodnost_table_wid->currentRow();
            QTableWidgetItem * item=new QTableWidgetItem;
            item=ui->bezicxodnost_table_wid->item(row,2);
            q=q+"'"+item->text()+"',";
            q=q+" '"+ui->namber_obor_brig_ComBox->currentText()+"');";
            qDebug()<<q;
            //DB->query->clear();
            //DB->query->exec(q);
            load_worker_to_double_Tab_Wid();
        }
    }
    ui->brig_obor_GRBox->setVisible(false);
    ui->statusBar->showMessage(tr("бригада пополнена"));

}

void MainWindow::on_select_obor_eqw_clos_PB_clicked()
{
    ui->brig_obor_GRBox->setVisible(false);
}
void MainWindow::load_obor_to_double_TabWid()
{
    if ((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        //DB->query->clear();
        ui->obor_worker_table_wid->clear();
        ui->obor_worker_table_wid->setColumnCount(4);
        ui->obor_worker_table_wid->setHorizontalHeaderLabels(QStringList()<<"название"<<"инвентарный номер"<<"год выпуска"<<"дата покупки");

        //int row=0;
        QString q("SELECT equipment.eq_name, equipment.eq_namber, equipment.eq_year, equipment.eq_buy_date FROM equipment , group_eq WHERE equipment.eq_namber = group_eq.id_namber and group_eq.id_brig=");
        q=q+ui->namber_obor_brig_ComBox->currentText()+";";
        qDebug()<<q;
//        DB->query->exec(q);
//        vector <technics> list_tech;
//        while(DB->query->next())
//        {
//            technics temp;
//            temp.name=DB->query->value(0).toString();
//            temp.namber= DB->query->value(1).toInt();
//            temp.Year_vip=DB->query->value(2).toString();
//            temp.Date_pok=DB->query->value(3).toString();
//            list_tech.push_back(temp);
//        }

        //int row = list_tech.size();
        //ui->obor_worker_table_wid->setRowCount(row);

//        for (int i=0;i<row;i++)
//        {
//            technics temp=list_tech[i];

//            QTableWidgetItem *item_name = new QTableWidgetItem();
//            item_name->setText(temp.name);

//            QTableWidgetItem *item_namber=new QTableWidgetItem();
//            //item_namber->setText(QString::number(temp.namber));

//            QTableWidgetItem *item_year = new QTableWidgetItem();
//            item_year->setText(temp.Year_vip);

//            QTableWidgetItem *item_date = new QTableWidgetItem();
//            item_date->setText(temp.Date_pok);

//            ui->obor_worker_table_wid->setItem(i,0,item_name);
//            ui->obor_worker_table_wid->setItem(i,1,item_namber);
//            if (temp.Year_vip!="0")
//            ui->obor_worker_table_wid->setItem(i,2,item_year);
//            ui->obor_worker_table_wid->setItem(i,3,item_date);
//        }
    }

}

void MainWindow::load_worker_to_double_Tab_Wid()
{
    if ((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        //DB->query->clear();
        ui->obor_worker_table_wid->clear();
        QString s("SELECT worker.adress, worker.post, worker.birthday, worker.fio, worker.ID_worker, worker.price FROM worker , grup WHERE worker.ID_worker = grup.worker_ID and  grup.group_id=");
        s=s+ui->namber_obor_brig_ComBox->currentText()+";";

        qDebug()<<s;

//        DB->query->exec(s);
//        vector<worker> work_vect;
//        while(DB->query->next())
//        {
//            worker temp;
//            temp.adress=DB->query->value(0).toString();
//            temp.post=DB->query->value(1).toString();
//            temp.birthday=DB->query->value(2).toString();
//            if (temp.birthday=="0")
//            {
//                temp.birthday="";
//            }
//            temp.fio=DB->query->value(3).toString();
//            temp.id=DB->query->value(4).toInt();
//            temp.pay=DB->query->value(5).toInt();
//          work_vect.push_back(temp);
//          qDebug()<<temp.fio<<"-";
//        }

        //row_technics=list_tech.size();
        //int row=work_vect.size();
        //qDebug()<<row<<"row";
        //ui->obor_worker_table_wid->setRowCount(row);
        ui->obor_worker_table_wid->setColumnCount(6);
        ui->obor_worker_table_wid->setHorizontalHeaderLabels(QStringList()<<"адресс"<<"должность"<<"год рождения"<<"фио"<<"ID"<<"зарплата");

//        for (int i=0;i<row;i++)
//        {
//            worker temp;
//            temp=work_vect[i];
//            QTableWidgetItem *item_adress = new QTableWidgetItem();
//            item_adress->setText(temp.adress);

//            QTableWidgetItem *item_dol = new QTableWidgetItem();
//            item_dol->setText(temp.post);
//            item_dol->setTextAlignment(Qt::AlignHCenter);

//            QTableWidgetItem *item_year_bir = new QTableWidgetItem();
//            if (temp.birthday!="0")
//            {
//                item_year_bir->setText(temp.birthday);                      //наложить маски на таблицы
//            }
//            else
//            {
//                item_year_bir->setText("");
//            }
//            item_year_bir->setTextAlignment(Qt::AlignHCenter);

//            QTableWidgetItem *item_fio = new QTableWidgetItem();
//            item_fio->setText(temp.fio);
//            item_fio->setTextAlignment(Qt::AlignHCenter);

//            QTableWidgetItem *item_ID = new QTableWidgetItem();
//            //item_ID->setText(QString::number(temp.id));
//            item_ID->setTextAlignment(Qt::AlignHCenter);

//            QTableWidgetItem *item_pay = new QTableWidgetItem();
//            //item_pay->setText(QString::number(temp.pay));
//            item_pay->setTextAlignment(Qt::AlignHCenter);

//            //ui->tableWidget_worker->setItemDelegateForColumn();               //!!!!!!!!!!!!!!!!!!
//            ui->obor_worker_table_wid->setItem(i,0,item_adress);
//            ui->obor_worker_table_wid->setItem(i,1,item_dol);

//                ui->obor_worker_table_wid->setItem(i,2,item_year_bir);

//            ui->obor_worker_table_wid->setItem(i,3,item_fio);
//            ui->obor_worker_table_wid->setItem(i,4,item_ID);
//            ui->obor_worker_table_wid->setItem(i,5,item_pay);
//        }
    ui->obor_worker_table_wid->setFocusPolicy(Qt::ClickFocus);

    }
}

void MainWindow::on_eqw_brigada_RB_clicked()
{
    load_obor_to_double_TabWid();
}

void MainWindow::on_worker_brigada_RB_clicked()
{
    load_worker_to_double_Tab_Wid();
}

void MainWindow::on_bezicxodnost_table_wid_clicked(const QModelIndex &index)
{
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_obor_worker_table_wid_clicked(const QModelIndex &index)
{
    ui->del_from_brig->setEnabled(true);
}

void MainWindow::on_del_from_brig_clicked()
{
    if (ui->eqw_brigada_RB->isChecked())
    {
        //удалить оборудование от бригады
        QString s("delete from group_eq where group_eq.id_namber=");

        QTableWidgetItem *item=new QTableWidgetItem;
        int row=ui->obor_worker_table_wid->currentRow();
        item= ui->obor_worker_table_wid->item(row,1);

        s=s+item->text()+";";
        qDebug()<<s;
        //DB->query->clear();
        //DB->query->exec(s);
        load_obor_to_double_TabWid();
        ui->statusBar->showMessage("оборудование откреплено от бригады");

    }
    else
    {
        if (ui->worker_brigada_RB->isChecked())
        {
            //удалить осотрудника от бригады
            QString s("delete from grup where grup.worker_ID=");

            QTableWidgetItem *item=new QTableWidgetItem;
            int row=ui->obor_worker_table_wid->currentRow();
            item= ui->obor_worker_table_wid->item(row,4);

            s=s+item->text()+";";
            qDebug()<<s;
            //DB->query->clear();
            //DB->query->exec(s);
            load_worker_to_double_Tab_Wid();
            ui->statusBar->showMessage("сотрудник откреплен от бригады");
        }
    }
}

void MainWindow::on_tableWidget_house_poisk_itemChanged(QTableWidgetItem *item)
{
    //qDebug()<<"вызвано"<<endl;
    //qDebug()<<item->text();

    //прозод по всем столбцым + проверка если не ""
}

void MainWindow::on_new_eq_Com_box_currentTextChanged(const QString &arg1)
{
    load_brig_num_for_new_eqw(arg1);
}
