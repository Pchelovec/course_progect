#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::split_worker()
{
    ui->new_worker_FIO_LE->setText(split_str(ui->new_worker_FIO_LE->text()));
    ui->new_worker_aderss_LE->setText(split_str(ui->new_worker_aderss_LE->text()));
}
void MainWindow::load_worker()
{
    ui->stackedWidget->setCurrentIndex(3);
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
    ui->tableWidget_worker->setHorizontalHeaderLabels(QStringList()<<"фио"<<"должность"<<"адресс"<<"год рождения"<<"ID"<<"зарплата");

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

        ui->tableWidget_worker->setItem(i,0,item_fio);
        ui->tableWidget_worker->setItem(i,1,item_dol);
        ui->tableWidget_worker->setItem(i,2,item_adress);
        ui->tableWidget_worker->setItem(i,3,item_year_bir);
        ui->tableWidget_worker->setItem(i,4,item_ID);
        ui->tableWidget_worker->setItem(i,5,item_pay);
    }
ui->tableWidget_worker->setFocusPolicy(Qt::ClickFocus);
}
void MainWindow::clear_obor_worker_table_wid()
{
    ui->obor_worker_table_wid->clear();
    ui->obor_worker_table_wid->setRowCount(0);
    ui->obor_worker_table_wid->setColumnCount(0);
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
void MainWindow::new_worker_initial()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->new_worker_team_CkBox->setChecked(false);
            QList <QString> list_dol=QUERY->avto_worker_dolg_list();
            int row=list_dol.size();
            ui->new_worker_post_Fou_CoBox->clear();
            ui->new_worker_post_Fou_CoBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            ui->new_worker_post_Fou_CoBox->view()->setCornerWidget(new QSizeGrip(ui->new_worker_post_Fou_CoBox));
            for (int i=0;i<row;i++)
            {
                ui->new_worker_post_Fou_CoBox->addItem(list_dol[i]);
            }
            ui->new_worker_FIO_LE->clear();
            ui->new_worker_aderss_LE->clear();
            ui->new_worker_year_bir_LE->clear();
            ui->new_worker_OKLAD_doubSpBox->clear();
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
        QUERY->worker_to_brig(temp, ui->new_worker_special_CoBox->currentText());//связывание к группе
    }
    ui->statusBar->showMessage(tr("сотрудник успешно нанят"));
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::dell_sotrudnic()
{
    int row=ui->tableWidget_worker->currentRow();
    QTableWidgetItem *item= new QTableWidgetItem();
    item=ui->tableWidget_worker->item(row,4);
        QUERY->worker_del(item->text());                //удаление из табл работники
        QUERY->del_worker_from_brig(item->text());      //удаление из бригады
    ui->statusBar->showMessage(tr("информация о сотруднике удалена"));
    ui->pusB_Sotrudnic_del->setEnabled(false);
}
void MainWindow::worker_change_status()
{
    int row=ui->tableWidget_worker->currentRow();
    QTableWidgetItem *item= new QTableWidgetItem();
    item=ui->tableWidget_worker->item(row,4);
        QUERY->del_worker_from_brig(item->text());      //удаление из бригады
    ui->statusBar->showMessage(tr("информация о сотруднике удалена"));
    ui->pusB_Sotrudnic_del->setEnabled(false);
}
