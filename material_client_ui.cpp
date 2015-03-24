#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::split_client()
{
    QString s;
    s=ui->lineEdit_client_mestoJit_input->text();
    ui->lineEdit_client_mestoJit_input->clear();
    ui->lineEdit_client_mestoJit_input->setText(split_str(s));

    s=ui->lineEdit_client_fio_input->text();
    ui->lineEdit_client_fio_input->clear();
    ui->lineEdit_client_fio_input->setText(split_str(s));
}

void MainWindow::split_material()
{
    QString s;
    s=ui->material_name_LE->text();
    ui->material_name_LE->clear();
    ui->material_name_LE->setText(split_str(s));
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

void MainWindow::nestandart_material_load(material mat_like_my)
{
clear_st_wid_0();
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

void MainWindow::save_nestandart_materrial_dialog()
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

void MainWindow::save_material_from_ui_to_DB()//записать текущий (insert)
{
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

void MainWindow::save_material_all_varibl()
{
    split_material();
    if ((ui->material_name_LE->text()!=0)&& (ui->dSpBo_material_price->value()!=0) && (ui->material_count_sp_box->value()!=0))
    {
        QList <material> like_my=QUERY->mater_like_my(ui->material_name_LE->text());
        if (like_my.size()==1)
        {
            material mat_like_my=like_my[0];
            if (mat_like_my.price==QString::number(ui->dSpBo_material_price->value()) && mat_like_my.izmer==ui->ed_izmeren->currentText())
            {
                //sum and update
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
                nestandart_material_load(mat_like_my);
            }
        }
        else
        {
            save_material_from_ui_to_DB();
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


//==============================================================

void MainWindow::load_avto_client_with_pasport(QString var)
{
    if (var.length()==8)
    {
        QList <client> list=QUERY->is_client_with_passport(var);
        if (list.size()==1)
        {
            ui->lineEdit_client_mestoJit_input->setText(list[0].plases_life);
            ui->lineEdit_client_fio_input->setText(list[0].FIO);
            ui->lineEdit_client_yearBir_input->setText(list[0].year_birthday);
            ui->lineEdit_client_phone_input->setText(list[0].phone);
        }
    }
}

void MainWindow::save_progect_info()
{
    QString ID;
    split_client();
    if (correct_data_client())
    {
        save_client();//клиент
        if (ui->checkBox_is_ynical_progect->isChecked()) //проверка типа проекта
        {//уникальный
            if (correct_data_new_building_progect())
            {
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //занесение информации о постройке

                ID=save_all_info_buildin(true);//вернуть id постройки
                QString progect_id;
                progect_id=QUERY->save_progect(ui->lineEdit_client_pasport_input->text(), ID);
                qDebug()<<"сохранение уникальной постройки и создание проекта"<<endl;
                plan_building_time b;
                b.make_and_save_time_plan_for_building(progect_id, ui->date_start_w->date());//расчет графика работ
                QList <material_ned> material=b.sub_material_for_building(ID);

                load_progect_info(material, progect_id);//вывод данных на печать
            }
            else
            {
                ui->statusBar->showMessage(tr("заполните данные уникального проекта"));
            }
        }
        else
        {//стандартный
            if (ui->building_id_for_progect->text()!="")
            {
                ID=ui->building_id_for_progect->text();//постройки
                QString progect_id;
                progect_id=QUERY->save_progect(ui->lineEdit_client_pasport_input->text(), ID);

                plan_building_time b;
                b.make_and_save_time_plan_for_building(progect_id, ui->date_start_w->date());
                QList <material_ned> material=b.sub_material_for_building(ID);
                qDebug()<<"проект стандартной постройки"<<endl;
                //расчет графика работ и вывод данных на печать
                load_progect_info(material, progect_id);
            }
            else
            {
                ui->statusBar->showMessage("стандартный проект не выбран");
            }
        }
    }
}

void MainWindow::save_client()
{
    client temp;
    temp.FIO=ui->lineEdit_client_fio_input->text();
    temp.plases_life=ui->lineEdit_client_mestoJit_input->text();
    temp.passport=ui->lineEdit_client_pasport_input->text();
    temp.phone=ui->lineEdit_client_phone_input->text();
    temp.year_birthday=ui->lineEdit_client_yearBir_input->text();
    QUERY->insert_client_info(temp);
}

void MainWindow ::clear_client_info()
{
    QDate dat;
    ui->building_id_for_progect->clear();
    ui->checkBox_is_ynical_progect->setChecked(false);
    ui->lineEdit_client_mestoJit_input->clear();
    ui->lineEdit_client_fio_input->clear();
    ui->lineEdit_client_pasport_input->clear();
    ui->lineEdit_client_yearBir_input->clear();
    ui->lineEdit_client_phone_input->clear();
    ui->date_start_w->setDate(dat.currentDate());
}

void MainWindow::clear_pay_info()
{
    ui->progect_id->clear();
    ui->summ_pay_LE->clear();
    ui->summ_pay_LE->setValue(0);
}

bool MainWindow::correct_data_client()
{
    QDate dat;
    if (ui->lineEdit_client_fio_input->text()!="" && ui->lineEdit_client_phone_input->text()!="" && ui->lineEdit_client_pasport_input->text()!="" &&
            ui->lineEdit_client_pasport_input->text().length()>=8 && ui->lineEdit_client_phone_input->text().size()>=7)
    {
        if (ui->date_start_w->date()<dat.currentDate())
        {
            ui->statusBar->showMessage("неверная дата начала строительства");
            return false;
        }
        else
        {
            if (ui->lineEdit_client_yearBir_input->text()!="")
            {
                if (ui->lineEdit_client_yearBir_input->text().toInt()>=1901)
                    return true;
                else return false;
            }
            else
            {
                return true;//без года рождения
            }
        }
    }
    else
    {
        ui->statusBar->showMessage("Заполите данные о клиенте (фамилия, телефон, паспорт)");
        return false;
    }
}

void MainWindow::set_need_to_pay()
{
    if (ui->progect_id->text()!="")
    {
        double n_p=QUERY->need_to_pay(ui->progect_id->text());
        if (n_p>0)
        {
            QString pay;
            pay=QString::number(n_p);
            QString s;
            s="необходимо заплатить "+pay;
            ui->statusBar->showMessage(s);
            ui->summ_pay_LE->setValue(n_p);
        }
        else
        {
            if (n_p==0)
                ui->statusBar->showMessage(tr("уже оплачено"));
            else
            {
                ui->statusBar->showMessage(tr("проекта нет"));
            }
        }
    }
    else ui->statusBar->showMessage(tr("заполните № вашего проекта"));
}

void MainWindow::pay_progect()
{
    if (ui->progect_id->text()!="")
    {
        double n_p=QUERY->need_to_pay(ui->progect_id->text());
        if (n_p>0)
        {
            if (ui->summ_pay_LE->value()>n_p)
            {
                ui->statusBar->showMessage(tr("введенная вами сумма больше чем нужно!, введите корректную сумму "));
            }
            else
            {
                QUERY->update_pay_sum(ui->progect_id->text(), ui->summ_pay_LE->value());
                ui->statusBar->showMessage(tr("платеж произведен"));
                clear_pay_info();
            }
        }
        else
        {
            if (n_p==0)
                ui->statusBar->showMessage(tr("уже оплачено"));
            else
            {
                ui->statusBar->showMessage(tr("проекта нет"));
            }
        }
    }
    else ui->statusBar->showMessage(tr("заполните № вашего проекта"));
}
