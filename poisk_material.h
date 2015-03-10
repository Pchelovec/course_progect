#ifndef POISK_MATERIAL_H
#define POISK_MATERIAL_H

#include <QWidget>

namespace Ui {
class poisk_material;
}

class poisk_material : public QWidget
{
    Q_OBJECT

public:
    explicit poisk_material(QWidget *parent = 0);
    ~poisk_material();

private:
    Ui::poisk_material *ui;
};

#endif // POISK_MATERIAL_H
