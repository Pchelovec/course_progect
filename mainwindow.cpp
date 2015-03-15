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
    ui->statusBar->showMessage(tr("приложение запущено"));
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
    //QTableWidgetItem *item=new QTableWidgetItem;
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
    //настройки интенсивности занятости бригад

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
    QTableWidgetItem *item= new QTableWidgetItem();
    item=ui->tableWidget_worker->item(row,4);
    QUERY->worker_del(item->text());                //удаление из табл работники
    QUERY->del_worker_from_brig(item->text());      //удаление из бригады

    ui->statusBar->showMessage(tr("информация о сотруднике удалена"));
    ui->pusB_Sotrudnic_del->setEnabled(false);
    load_worker();                                      //перезагрузка таблицы
}

void MainWindow::on_pushButton_add_ne_worker_clicked()
{
    new_worker_initial();
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_new_eqv_exit_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_new_worker_Exit_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->statusBar->showMessage(tr("отмена добавления работника!"));
}

void MainWindow::on_new_worker_OK_PB_clicked()
{
    //занести в БД
    //скрыть 2 часть, очистить
    worker temp;
    if (ui->new_worker_FIO_LE->text()!="")
    {
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

void MainWindow::on_new_worker_team_CkBox_clicked(bool checked)
{
    ui->new_worker_team_GrBox->setVisible(checked);
    if (checked)
    {
        load_brig_name_to_new_worker_special_Comb_box();
    }
}

void MainWindow::on_new_eqw_plas_team_ChBox_clicked(bool checked)
{
    ui->new_eq_team_comBOX->setVisible(checked);
}


void MainWindow::on_brigada_sostav_triggered()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->del_from_brig->setEnabled(false);
    load_special_obor_brig_ComBox();
}

void MainWindow::on_add_new_brigada_PB_clicked()
{
    //занесение в бд
    QUERY->new_brig_with_special(ui->new_special_brig_FCB->currentText());
    ui->statusBar->showMessage("добавлена новая бригада");
    ui->new_brigada_ChBox->setChecked(false);
    ui->new_brigada_GrBox->setVisible(false);
    //перезагрузка group box
}

void MainWindow::on_new_brigada_ChBox_clicked(bool checked)
{
    ui->new_brigada_GrBox->setVisible(checked);
    load_all_special_to_new_special_brig_FCB();
}


void MainWindow::on_add_to_brig_clicked()
{
    if((ui->special_obor_brig_ComBox->currentText()!="") && (ui->namber_obor_brig_ComBox->currentText()!="") && ( (ui->eqw_brigada_RB->isChecked()) || (ui->worker_brigada_RB->isChecked())))
    {
        ui->bezicxodnost_table_wid->clear();
        ui->bezicxodnost_table_wid->setColumnCount(3);

        if ((ui->eqw_brigada_RB->isChecked()))
        {
            qDebug()<<"eqw small"<<endl;
            ui->post_name_sh_LE->setStatusTip("название оборудования");
            ui->fio_inventarnN_LE->setStatusTip("инвентарный номер");
            ui->bezicxodnost_table_wid->setHorizontalHeaderLabels(QStringList()<<"название"<<"дата покупки"<<"инвентарный номер");
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
        else
        {
            if ((ui->worker_brigada_RB->isChecked()))
            {
                qDebug()<<"worker small"<<endl;
                ui->post_name_sh_LE->setStatusTip("должность сотрудника");
                ui->fio_inventarnN_LE->setStatusTip("фио сотрудника");
                ui->bezicxodnost_table_wid->setHorizontalHeaderLabels(QStringList()<<"должность"<<"фио"<<"ID");

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
        }  
     ui->brig_obor_GRBox->setVisible(true);
     ui->pushButton->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->eqw_brigada_RB->isChecked())
    {
        //оборуд
        qDebug()<<"оборуд к бригаде";
        int row=ui->bezicxodnost_table_wid->currentRow();
        QTableWidgetItem * item=new QTableWidgetItem;
        item=ui->bezicxodnost_table_wid->item(row,2);
        QUERY->eqw_to_brig(item->text(),ui->namber_obor_brig_ComBox->currentText());
        load_obor_to_double_TabWid();
    }
    else
    {
        if (ui->worker_brigada_RB->isChecked())
        {
            //работник
            qDebug()<<"работник к бригаде";
            int row=ui->bezicxodnost_table_wid->currentRow();
            QTableWidgetItem * item=new QTableWidgetItem;
            item=ui->bezicxodnost_table_wid->item(row,2);
            QUERY->worker_to_brig(item->text(),ui->namber_obor_brig_ComBox->currentText());
            load_worker_to_double_Tab_Wid();
        }
    }
    reload_double_table();
    ui->brig_obor_GRBox->setVisible(false);
    ui->statusBar->showMessage(tr("бригада пополнена"));
}

void MainWindow::on_select_obor_eqw_clos_PB_clicked()
{
    ui->brig_obor_GRBox->setVisible(false);
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

        QTableWidgetItem *item=new QTableWidgetItem;
        int row=ui->obor_worker_table_wid->currentRow();
        item= ui->obor_worker_table_wid->item(row,1);

        QUERY->del_eqw_from_brig(item->text());
        load_obor_to_double_TabWid();
        ui->statusBar->showMessage("оборудование откреплено от бригады");
    }
    else
    {
        if (ui->worker_brigada_RB->isChecked())
        {
            //удалить осотрудника от бригады
            QTableWidgetItem *item=new QTableWidgetItem;
            int row=ui->obor_worker_table_wid->currentRow();
            item= ui->obor_worker_table_wid->item(row,4);
            QUERY->del_worker_from_brig(item->text());
            load_worker_to_double_Tab_Wid();
            ui->statusBar->showMessage("сотрудник откреплен от бригады");
        }
    }
    ui->del_from_brig->setEnabled(false);
}

void MainWindow::on_tableWidget_house_poisk_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"вызвать динамический поиск по домам"<<endl;
    //qDebug()<<item->text();
    //clear_obor_worker_table_wid();

    //прозод по всем столбцым + проверка если не ""
}

void MainWindow::on_new_eq_Com_box_currentTextChanged(const QString &arg1)
{
    load_brig_num_for_new_eqw(arg1);
}

void MainWindow::on_new_worker_special_Comb_box_currentTextChanged(const QString &arg1)
{
    load_brig_num_for_new_worker(arg1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    load_main_infor_new_build_GrBox();
}

void MainWindow::on_Standart_progect_new_triggered()
{
    ui->stackedWidget->setCurrentIndex(9);
    load_main_infor_new_build_GrBox();
}

void MainWindow::on_special_obor_brig_ComBox_currentTextChanged(const QString &arg1)
{
    load_namber_obor_brig_ComBox(arg1);
    clear_obor_worker_table_wid();
}


void MainWindow::on_namber_obor_brig_ComBox_currentTextChanged(const QString &arg1)
{
    clear_obor_worker_table_wid();
}

void MainWindow::on_post_name_sh_LE_textChanged(const QString &arg1)
{
    clear_bezicxodnost_Table_wid();
    if (ui->eqw_brigada_RB->isChecked())
    {
        //оборудование с поиском в безисходность
    }
    else
    {
        //работник с поиском в безисходность
    }
}

void MainWindow::on_fio_inventarnN_LE_textChanged(const QString &arg1)
{
    clear_bezicxodnost_Table_wid();
    if (ui->eqw_brigada_RB->isChecked())
    {
        //оборудование с поиском в безисходность
    }
    else
    {
        //работник с поиском в безисходность
    }
}

void MainWindow::on_new_standart_level_add_clicked()
{
    load_info_level_building_GrBox();
}

void MainWindow::on_new_standart_material_add_PB_clicked()
{
    load_info_material_for_building_GrBox();
}

void MainWindow::on_new_standart_material_OK_PB_clicked()
{
    ui->info_material_for_building_GrBox->setVisible(false);
}

void MainWindow::on_new_standart_level_OK_clicked()
{
    ui->info_level_building_GrBox->setVisible(false);
}

void MainWindow::on_new_standart_OK_PB_clicked()
{
    //запись всего в бд о проекте здания
    new_standart_level_table_clear();
    new_standart_material_table_clear();
}

void MainWindow::on_House_progect_main_dell_PB_clicked()
{
    //удаления проекта здания из бд+ графика и материалов
}
