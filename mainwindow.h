#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>                          //
#include <QMainWindow>                      //
#include <QSqlTableModel>
#include <QMessageBox>                      ////
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:                                                            //переменные

    building *build;
                                                                    //функции

    void first_initial_component();
    void Q_Object_connect();
    void set_visible_enabled();
    void set_validator_all();
    void clear_first();

    void load_technics();
    void load_building();
    void load_worker();

    void initial_detel_ifo_technics();
    void clear_material();
    //void load_spec_situat_material();
    void load_new_eqwt();
    void load_brig_num_for_new_eqw(QString val);
    void load_obor_to_double_TabWid();
    void load_worker_to_double_Tab_Wid();

public:
    Ui::MainWindow *ui;
    //database *DB;
    query_result *QUERY;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    //void set_row_to_table(int row);//
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
    void on_checkBox_is_ynical_progect_clicked(bool checked);
    //void on_radioButton_fundament_clicked(bool checked);
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
    void on_new_eq_Com_box_activated(const QString &arg1);
    void on_new_eqw_plas_team_ChBox_clicked(bool checked);
    void on_new_worker_special_Comb_box_activated(const QString &arg1);
    void on_brigada_sostav_triggered();
    void on_add_new_brigada_PB_clicked();
    void on_new_brigada_ChBox_clicked(bool checked);
    void on_special_obor_brig_ComBox_activated(const QString &arg1);
    void on_add_to_brig_clicked();
    void on_pushButton_clicked();
    void on_select_obor_eqw_clos_PB_clicked();
    void on_eqw_brigada_RB_clicked();
    void on_worker_brigada_RB_clicked();
    void on_bezicxodnost_table_wid_clicked(const QModelIndex &index);
    void on_obor_worker_table_wid_clicked(const QModelIndex &index);
    void on_del_from_brig_clicked();
    void on_tableWidget_house_poisk_itemChanged(QTableWidgetItem *item);
    void on_new_eq_Com_box_currentTextChanged(const QString &arg1);
};
#endif // MAINWINDOW_H
