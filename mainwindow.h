#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QMessageBox>
//#include <QDebug>
#include <QSqlTableModel>
#include <QAbstractItemModel>
#include <QTableView>
#include <vector>
#include "database.h"
#include "building.h"
#include "worker.h"
#include <QString>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QTableView>
#include <QTableWidget>
#include <QStringList>
#include <QStandardItemModel>
#include <Qt>
#include <QRegExp>
#include <QRegExpValidator>
#include "material.h"
#include <QtDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:                                                            //переменные
    Ui::MainWindow *ui;
    database *DB;
    int row_technics;
    int row_worker;
    int row_building;
    building *build;

                                                                    //функции

    void connect_to_DB();
    void first_initial_component();
    void load_technics();
    void load_building();
    void load_worker();
    void initial_detel_ifo_technics();
    void clear_material();

public:
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
    void on_radioButton_fundament_clicked(bool checked);
    void on_material_add_PB_clicked();
    void on_nestandart_material_button_OK_clicked();
    void on_price_a_ChBox_clicked(bool checked);
    void on_price_b_ChBox_clicked(bool checked);
};
#endif // MAINWINDOW_H
