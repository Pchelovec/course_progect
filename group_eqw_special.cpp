#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::add_new_brig()
{
    QUERY->new_brig_with_special(ui->new_special_brig_FCB->currentText());
    ui->statusBar->showMessage("добавлена новая бригада");
    ui->new_brigada_ChBox->setChecked(false);
    ui->new_brigada_GrBox->setVisible(false);
    //перезагрузка group box
}

void MainWindow::worker_to_group()
{
    qDebug()<<"оборуд к бригаде";
    int row=ui->bezicxodnost_table_wid->currentRow();
    QTableWidgetItem * item=new QTableWidgetItem;
    item=ui->bezicxodnost_table_wid->item(row,2);
    QUERY->eqw_to_brig(item->text(),ui->namber_obor_brig_ComBox->currentText());
    load_obor_to_double_TabWid();
}
void MainWindow::eqw_to_group()
{
    //работник
    qDebug()<<"работник к бригаде";
    int row=ui->bezicxodnost_table_wid->currentRow();
    QTableWidgetItem * item=new QTableWidgetItem;
    item=ui->bezicxodnost_table_wid->item(row,2);
    QUERY->worker_to_brig(item->text(),ui->namber_obor_brig_ComBox->currentText());
    load_worker_to_double_Tab_Wid();
}

void MainWindow::dell_eqw_from_brig()
{
    QTableWidgetItem *item=new QTableWidgetItem;
    int row=ui->obor_worker_table_wid->currentRow();
    item= ui->obor_worker_table_wid->item(row,1);

    QUERY->del_eqw_from_brig(item->text());
    load_obor_to_double_TabWid();
    ui->statusBar->showMessage("оборудование откреплено от бригады");
}

void MainWindow::dell_worker_from_brig()
{
    //удалить осотрудника от бригады
    QTableWidgetItem *item=new QTableWidgetItem;
    int row=ui->obor_worker_table_wid->currentRow();
    item= ui->obor_worker_table_wid->item(row,4);
    QUERY->del_worker_from_brig(item->text());
    load_worker_to_double_Tab_Wid();
    ui->statusBar->showMessage("сотрудник откреплен от бригады");
}
