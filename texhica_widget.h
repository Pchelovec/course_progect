#ifndef TEXHICA_WIDGET_H
#define TEXHICA_WIDGET_H

#include <QWidget>

namespace Ui {
class texhica_widget;
}

class texhica_widget : public QWidget
{
    Q_OBJECT

public:
    explicit texhica_widget(QWidget *parent = 0);
    ~texhica_widget();

private slots:
    void on_pButt_buy_technics_clicked();
signals:
    void call_new_techics(QString);

private:
    Ui::texhica_widget *ui;
};

#endif // TEXHICA_WIDGET_H
