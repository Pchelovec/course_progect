#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>                          //
#include <QMainWindow>                      //
#include <QSqlTableModel>
#include <QMessageBox>                      //
#include <QtDebug>                          //
#include <QSqlTableModel>
#include <QAbstractItemModel>
#include <QTableView>
#include <QVector>                          //
#include <QT>                               //
#include <QString>                          //
#include <QHeaderView>
#include <QTableWidget>
#include <QStringList>
#include "material.h"
#include "technics.h"
#include "database.h"
#include "building.h"
#include "worker.h"
#include "material.h"
#include "query_result.h"
#include "dir.h"
#include "plan_building_time.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:                                                            //переменные

    building *build;
                                                                    //функции

    //----------------------------------------------постройки
    void split_house();
    void clear_sh_building();
    void load_building();
    void load_sarai();
    void load_dworec();

    void load_ynic_progect_building(bool checked);
    void load_main_infor_new_build_GrBox();//

    void clear_main_infor_new_build_GrBox();

    void add_standart_grafic_TW(QString Brig_special, QString Count);//--создание проекта здания
    void add_to_need_material_TW(QString Name_mater, QString Count);

    void set_naznachen(QString val);
    void set_name_need_material(QString val);
    void set_day_count();
    void set_price();
    void set_id_progect_standart();
    void set_dop_price();

    bool correct_data_new_building_progect();
    QList <material_ned> return_list_need_material();
    QList <level> return_time_plane();
    QString save_all_info_buildin(bool ynic);

    void new_standart_level_table_clear();//
    void new_standart_material_table_clear();
    void new_standart_main_clear();

    void load_material_name_all_for_need_material(QString val);
    void load_naznach_mater_standart(QString val);

    void clear_needed_material_standart();

    void load_info_level_building_GrBox();//
    void load_info_material_for_building_GrBox();

    void load_active_progect_TW();

    void minus_level();
    void minus_material();

    void delete_current_level();
    void delete_current_material();

    //----------------------------------------------работники
    void split_worker();
    void load_worker();
    void clear_obor_worker_table_wid();
    void clear_sh_worker();

    void new_worker_initial();

    void save_worker();
        void worker_to_db();

    //----------------------------------------------оборудование
    void split_eqw();
    void load_technics();
    void load_new_eqwt();

    void save_new_eqw();
    void dell_eqw();
    void clear_sh_eqw();
    void clear_eqw();
    void poisk_eqw_or_worker_with_2_string();

    //----------------------------------------------материалы
    void split_material();
    void clear_material();
    void nestandart_material_load(material mat_like_my);
    void save_nestandart_materrial_dialog();
    void load_newstandart_situat_stack_wid(material mat_like_my);
    void save_material_from_ui_to_DB();
    void save_material_all_varibl();
    void incorrect_data_material();
    void update_material(material mat_like_my);

    //----------------------------------------------бригада (оборудование + работнтки)
    void reload_double_table();

    void load_brig_num_for_new_eqw(QString val);
    void load_brig_num_for_new_worker(QString val);

    void load_obor_to_double_TabWid();
    void load_worker_to_double_Tab_Wid();

    void load_brig_name_to_new_worker_special_Comb_box();
    void load_special_obor_brig_ComBox();
    void load_namber_obor_brig_ComBox(QString s);
    void load_eqw_or_worker_small();

    void eqw_small();
    void worker_small();

    void load_all_special_to_new_special_brig_FCB();

    void clear_bezicxodnost_Table_wid();
    //----------------------------------------------клиент
    void load_avto_client_with_pasport(QString val);

    void save_progect_info();
    void save_client();

    void split_client();
    void clear_client_info();
    void clear_pay_info();
    bool correct_data_client();

    void set_need_to_pay();
    void pay_progect();
    //----------------------------------------------статистика+
    void load_statistic();
    void clear_statistic();

    void load_progect_info(QList <material_ned> table, QString ID_progect);//загрузка информации о заключеном проекте
        void set_table_total_material(QList <material_ned> table);//таблица материалов которые нужно докупить
        void set_table_grafic(QString ID_progect);
        void set_individual_info(QString ID_progect);

    void load_oplata_progecta();
    //----------------------------------------------общие
    void load_work_process();
    QString split_str(QString val);
    void clear_st_wid_0();
    void save_price_to_file();
    void  unshow_percent();

    void first_initial_component();
    void Q_Object_connect();
    void set_visible_enabled();
    void set_validator_all();
    void dell_problem(QString v);
    void dell_problem(int i);
    //--------------------------------------------------------------------

    void clear_first();

//    void reload_double_table();

    //void initial_detel_ifo_technics();

public:
    Ui::MainWindow *ui;
    //database *DB;
    query_result *QUERY;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    //void set_row_to_table(int row);
                                                                    //сигналы и слоты
//signals:

//private:
private slots:
    void add_house_to_db();
    void on_action_4_triggered();
    void on_person_triggered();
    void on_new_contract_triggered();
    void on_home_progect_triggered();
    void on_material_triggered();
    void on_Butt_Buy_car_clicked();
    //void on_checkBox_is_ynical_progect_clicked(bool checked);
    void on_material_add_PB_clicked();
    void on_nestandart_material_button_OK_clicked();
    void on_price_a_ChBox_clicked(bool checked);
    void on_price_b_ChBox_clicked(bool checked);
    void on_option_work_exit_PB_clicked();
    void on_option_worker_OK_PB_clicked();
    void on_work_process_option_triggered();
    void on_tableWidget_worker_clicked(const QModelIndex &index);
    void on_pusB_Sotrudnic_del_clicked();
    void on_pushButton_add_ne_worker_clicked();
    void on_new_eqv_exit_PB_clicked();
    void on_new_eqv_OK_PB_clicked();
    void on_new_worker_Exit_PB_clicked();
    void on_new_worker_OK_PB_clicked();
    void on_tableWidget_technics_clicked(const QModelIndex &index);
    void on_dell_eqvmnt_clicked();
    void on_new_worker_team_CkBox_clicked(bool checked);
    void on_new_eqw_plas_team_ChBox_clicked(bool checked);
    void on_brigada_sostav_triggered();
    void on_add_new_brigada_PB_clicked();
    void on_new_brigada_ChBox_clicked(bool checked);
    void on_add_to_brig_clicked();
    void on_pushButton_clicked();
    void on_select_obor_eqw_clos_PB_clicked();
    void on_eqw_brigada_RB_clicked();
    void on_worker_brigada_RB_clicked();
    void on_bezicxodnost_table_wid_clicked(const QModelIndex &index);
    void on_obor_worker_table_wid_clicked(const QModelIndex &index);
    void on_del_from_brig_clicked();
    void on_new_eq_Com_box_currentTextChanged(const QString &arg1);
    void on_new_worker_special_Comb_box_currentTextChanged(const QString &arg1);
    void on_pushButton_3_clicked();
    void on_Standart_progect_new_triggered();
    void on_special_obor_brig_ComBox_currentTextChanged(const QString &arg1);
    void on_namber_obor_brig_ComBox_currentTextChanged(const QString &arg1);
    void on_post_name_sh_LE_textChanged(const QString &arg1);
    void on_fio_inventarnN_LE_textChanged(const QString &arg1);
    void on_new_standart_level_add_clicked();
    void on_new_standart_material_add_PB_clicked();
    void on_new_standart_material_OK_PB_clicked();
    void on_new_standart_level_OK_clicked();
    void on_new_standart_OK_PB_clicked();
    void on_money_for_progect_triggered();
    void on_tableWidget_house_clicked(const QModelIndex &index);
    void on_show_PB_clicked();
    void on_close_active_progect_PB_clicked();
    void on_new_standart_level_add_to_table_PB_clicked();
    void on_new_standart_grafic_TW_clicked(const QModelIndex &index);
    void on_new_standart_level_dell_clicked();
    void on_new_standart_material_name_activated(const QString &arg1);
    void on_new_standart_ned_materisl_naznach_activated(const QString &arg1);
    void on_new_standart_material_dell_PB_clicked();
    void on_new_standart_ned_material_add_to_table_PB_clicked();
    void on_order_PB_clicked();
    void on_new_ynic_OK_PB_clicked();
    void on_pushButton_2_clicked();
    void on_House_progect_main_this_PB_clicked();
    void on_new_standart_ned_material_TW_clicked();
    void on_action_3_triggered();
    void on_pushButton_4_clicked();
    void on_need_to_pay_PB_clicked();
    void on_pay_OK_PB_clicked();
    void on_sh_worker_fam_textChanged(const QString &arg1);
    void on_sh_worker_post_textChanged(const QString &arg1);
    void on_sh_worker_start_price_SB_valueChanged(const QString &arg1);
    void on_sh_worker_fin_price_SB_valueChanged(const QString &arg1);
    void on_sh_eqw_name_textChanged(const QString &arg1);
    void on_sh_eqw_namber_textChanged(const QString &arg1);
    void on_sh_building_name_textChanged(const QString &arg1);
    void on_sh_building_time_min_valueChanged(const QString &arg1);
    void on_sh_building_time_max_valueChanged(const QString &arg1);
    void on_sh_building_metter_min_valueChanged(const QString &arg1);
    void on_sh_building_metter_max_valueChanged(const QString &arg1);
    void on_sh_building_price_min_valueChanged(const QString &arg1);
    void on_sh_building_price_max_valueChanged(const QString &arg1);
    void on_CB_House_poisk_clicked(bool checked);
    void on_BD_change_triggered();
    void on_statistic_triggered();
    void on_lineEdit_client_pasport_input_textChanged(const QString &arg1);
    void on_statistic_time_fin_dateChanged(const QDate &date);
    void on_statistic_time_start_dateChanged(const QDate &date);
};
#endif // MAINWINDOW_H
