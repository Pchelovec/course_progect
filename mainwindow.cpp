#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUERY=new query_result;
    //print=new printer;
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
    clear_sh_eqw();
    load_technics();
}
void MainWindow::on_person_triggered()
{
    clear_sh_worker();
    load_worker();
}
void MainWindow::on_new_contract_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
    clear_client_info();
}
void MainWindow::on_home_progect_triggered()
{
    clear_sh_building();
    load_building();
}
void MainWindow::on_material_triggered()
{
    clear_material();
}

void MainWindow::on_Butt_Buy_car_clicked()
{
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
    save_material_all_varibl();
}

void MainWindow::on_nestandart_material_button_OK_clicked()
{
    save_nestandart_materrial_dialog();
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
    clear_st_wid_0();
    load_work_process();
}

void MainWindow::on_tableWidget_worker_clicked(const QModelIndex &index)
{
    ui->pusB_Sotrudnic_del->setEnabled(true);
}

void MainWindow::on_pusB_Sotrudnic_del_clicked()
{
    dell_sotrudnic();
//    worker_change_status();
    load_worker();                                      //перезагрузка таблицы
}

void MainWindow::on_pushButton_add_ne_worker_clicked()
{
    new_worker_initial();
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
    split_eqw();
    save_new_eqw();
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
    split_worker();
    save_worker();
}

void MainWindow::on_tableWidget_technics_clicked(const QModelIndex &index)
{
    ui->dell_eqvmnt->setEnabled(true);
}

void MainWindow::on_dell_eqvmnt_clicked()
{
    dell_eqw();
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
    add_new_brig();
}

void MainWindow::on_new_brigada_ChBox_clicked(bool checked)
{
    ui->new_brigada_GrBox->setVisible(checked);
    load_all_special_to_new_special_brig_FCB();
}

void MainWindow::on_add_to_brig_clicked()
{
    load_eqw_or_worker_small();
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->eqw_brigada_RB->isChecked())
    {
        worker_to_group();//оборуд
    }
    else
    {
        if (ui->worker_brigada_RB->isChecked())
        {
            eqw_to_group();
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
        dell_eqw_from_brig();
    }
    else
    {
        if (ui->worker_brigada_RB->isChecked())
        {
            dell_worker_from_brig();
        }
    }
    ui->del_from_brig->setEnabled(false);
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
    load_ynic_progect_building(false);
}

void MainWindow::on_Standart_progect_new_triggered()
{   
    load_ynic_progect_building(false);
}

void MainWindow::on_special_obor_brig_ComBox_currentTextChanged(const QString &arg1)
{
    load_namber_obor_brig_ComBox(arg1);
    clear_obor_worker_table_wid();
}

void MainWindow::on_namber_obor_brig_ComBox_currentTextChanged(const QString &arg1)
{
    clear_obor_worker_table_wid();
    dell_problem(arg1);
}

void MainWindow::on_post_name_sh_LE_textChanged(const QString &arg1)
{
    clear_bezicxodnost_Table_wid();
        load_eqw_or_worker_small();
    dell_problem(arg1);
}

void MainWindow::on_fio_inventarnN_LE_textChanged(const QString &arg1)
{
    clear_bezicxodnost_Table_wid();
        load_eqw_or_worker_small();
    dell_problem(arg1);
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
    set_price();
}

void MainWindow::on_new_standart_level_OK_clicked()
{
    set_day_count();
}

void MainWindow::on_new_standart_OK_PB_clicked()
{
    split_house();
    if (correct_data_new_building_progect())
    {
        //запись всего в бд о проекте здания
        save_all_info_buildin(false);
        new_standart_main_clear();
        new_standart_level_table_clear();
        new_standart_material_table_clear();
    }
    else
    {
        ui->statusBar->showMessage(tr("сформируйте информацию о проекте здания"));
    }
}

void MainWindow::on_money_for_progect_triggered()
{
    load_oplata_progecta();
}

void MainWindow::on_tableWidget_house_clicked(const QModelIndex &index)
{
    ui->show_PB->setEnabled(true);
    ui->House_progect_main_this_PB->setEnabled(true);
}

void MainWindow::on_show_PB_clicked()
{
    load_active_progect_TW();
}

void MainWindow::on_close_active_progect_PB_clicked()
{
    ui->active_progect_TW->setVisible(false);
    ui->close_active_progect_PB->setVisible(false);
}


void MainWindow::on_new_standart_level_add_to_table_PB_clicked()
{
    if (ui->new_standart_level_dayLong_SPbx->value()!=0 && ui->new_standart_need_special_worker_FCB->currentText()!="")
    {
    add_standart_grafic_TW(ui->new_standart_need_special_worker_FCB->currentText(), QString ::number(ui->new_standart_level_dayLong_SPbx->value()));
    load_info_level_building_GrBox();
    }
    else
    {
        ui->statusBar->showMessage(tr("заполните данные"));
    }
}

void MainWindow::on_new_standart_grafic_TW_clicked(const QModelIndex &index)
{
    ui->new_standart_level_dell->setEnabled(true);
}

void MainWindow::on_new_standart_level_dell_clicked()
{
    delete_current_level();
}

void MainWindow::on_new_standart_material_name_activated(const QString &arg1)
{
    set_naznachen(arg1);
}

void MainWindow::on_new_standart_ned_materisl_naznach_activated(const QString &arg1)
{
    set_name_need_material(arg1);

}

void MainWindow::on_new_standart_material_dell_PB_clicked()
{
    delete_current_material();
}


void MainWindow::on_new_standart_ned_material_add_to_table_PB_clicked()
{
    if (ui->new_standart_count_SpB->value()!=0 && ui->new_standart_material_name->currentText()!="")
    {
        add_to_need_material_TW(ui->new_standart_material_name->currentText(), QString::number(ui->new_standart_count_SpB->value()));
        ui->new_standart_ned_materisl_naznach->setEditable(true);
        load_info_material_for_building_GrBox();
    }
    else
    {
        ui->statusBar->showMessage(tr("количество или название не заполнено"));
    }
}

void MainWindow::on_order_PB_clicked()
{
    save_progect_info();
}

void MainWindow::on_new_ynic_OK_PB_clicked()
{
    split_house();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_2_clicked()
{
    bool checked=ui->checkBox_is_ynical_progect->isChecked();
    if (checked)
    {
        load_ynic_progect_building(true);
    }
    else
    {
        clear_sh_building();
        load_building();
    }
}

void MainWindow::on_House_progect_main_this_PB_clicked()
{
    set_id_progect_standart();
}

void MainWindow::on_new_standart_ned_material_TW_clicked()
{
    ui->new_standart_material_dell_PB->setEnabled(true);
}

void MainWindow::on_action_3_triggered()
{
    clear_st_wid_0();
    set_dop_price();
}

void MainWindow::on_pushButton_4_clicked()
{
    save_price_to_file();
    unshow_percent();   
}

void MainWindow::on_need_to_pay_PB_clicked()
{
    set_need_to_pay();
}


void MainWindow::on_pay_OK_PB_clicked()
{
    pay_progect();
}

void MainWindow::on_sh_worker_fam_textChanged(const QString &arg1)
{
    load_worker();
    dell_problem(arg1);
}

void MainWindow::on_sh_worker_post_textChanged(const QString &arg1)
{
    load_worker();
    dell_problem(arg1);
}

void MainWindow::on_sh_worker_start_price_SB_valueChanged(const QString &arg1)
{
    load_worker();
    dell_problem(arg1);
}

void MainWindow::on_sh_worker_fin_price_SB_valueChanged(const QString &arg1)
{
    load_worker();
    dell_problem(arg1);
}

void MainWindow::on_sh_eqw_name_textChanged(const QString &arg1)
{
    load_technics();
    dell_problem(arg1);
}

void MainWindow::on_sh_eqw_namber_textChanged(const QString &arg1)
{
    load_technics();
    dell_problem(arg1);
}

void MainWindow::on_sh_building_name_textChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}

void MainWindow::on_sh_building_time_min_valueChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}


void MainWindow::on_sh_building_time_max_valueChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}

void MainWindow::on_sh_building_metter_min_valueChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}

void MainWindow::on_sh_building_metter_max_valueChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}

void MainWindow::on_sh_building_price_min_valueChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}

void MainWindow::on_sh_building_price_max_valueChanged(const QString &arg1)
{
    load_building();
    dell_problem(arg1);
}

void MainWindow::on_CB_House_poisk_clicked(bool checked)
{
    if (!checked)
    {
        clear_sh_building();
        load_building();
    }
}

void MainWindow::on_BD_change_triggered()
{
    clear_st_wid_0();
}

void MainWindow::on_statistic_triggered()
{
    clear_statistic();
    load_statistic();
}

void MainWindow::on_lineEdit_client_pasport_input_textChanged(const QString &arg1)
{
    load_avto_client_with_pasport(arg1);
}

void MainWindow::on_statistic_time_fin_dateChanged(const QDate &date)
{
    load_statistic();
}

void MainWindow::on_statistic_time_start_dateChanged(const QDate &date)
{
    load_statistic();
}

void MainWindow::on_print_PB_clicked()
{
    printer pr;
    pr.print_contract(ui->progect_id_info->text(),QUERY->ret_id_house_with_id_progect(ui->progect_id_info->text()));
}

void MainWindow::on_actionPrint_triggered()
{ 
    QPrinter *printer=new QPrinter;
    QPainter painter(printer);
    painter.setWindow(this->rect());
    this->render(&painter);
}


void MainWindow::on_exit_programm_triggered()
{
    close();
}

void MainWindow::on_material_all_print_triggered()
{
    printer pr;
    pr.print_all_material();
}

void MainWindow::on_client_passport_textChanged(const QString &arg1)
{
    if (arg1.length()==8)
    {
        ui->progect_id->setText(QUERY->return_progect_id(ui->client_passport->text(), ""));
    }
}

void MainWindow::on_print_time_brig_clicked()
{
    printer pr;
    pr.print_worker_time(ui->namber_obor_brig_ComBox->currentText());
}
