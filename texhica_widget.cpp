#include "texhica_widget.h"
#include "ui_texhica_widget.h"
#include "mainwindow.h"
#include <QRegExp>
#include <QRegularExpressionValidator>
texhica_widget::texhica_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::texhica_widget)
{
    ui->setupUi(this);
    //connect(this,call_new_techics(QString)),
    QRegExp name("[а-я А-Я]{15}");
    ui->lineEdit_technica_name->setValidator(new QRegExpValidator(name,this));

    //QRegExp nomer("[0-9]{2-3}[a-z A-Z]{4}[0-9]{2}");

    QRegExp year_vip("[1-2]{1}[9,0]{1}[0-9]{1}[0-9]{1}");
    ui->lineEdit_was_builded->setValidator(new QRegExpValidator(year_vip,this));

    QRegExp distance("[0-9]{10}");
    ui->lineEdit_distance_rans->setValidator(new QRegExpValidator(distance,this));

}

texhica_widget::~texhica_widget()
{
    delete ui;
}

void texhica_widget::on_pButt_buy_technics_clicked()
{
    //INSERT INTO building(builsing_name) VALUES('passed name');
    emit call_new_techics("INSERT INTO building(builsing_name) VALUES('passed name');");
}

