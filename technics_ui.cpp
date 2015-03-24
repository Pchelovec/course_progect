#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::split_eqw()
{
    QString s;
    s=ui->material_name_LE->text();
    ui->material_name_LE->clear();
    ui->material_name_LE->setText(split_str(s));
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
    }
    else
    {
        ui->statusBar->showMessage(tr("Заполните ключевые поля(название и инвентарный номер!)"));
    }
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

void MainWindow::clear_sh_eqw()
{
    ui->sh_eqw_name->clear();
    ui->sh_eqw_namber->clear();
}
