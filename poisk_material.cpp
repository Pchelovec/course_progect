#include "poisk_material.h"
#include "ui_poisk_material.h"

poisk_material::poisk_material(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::poisk_material)
{
    ui->setupUi(this);
}

poisk_material::~poisk_material()
{
    delete ui;
}
