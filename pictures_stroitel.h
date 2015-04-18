#ifndef PICTURES_STROITEL_H
#define PICTURES_STROITEL_H
#include <QMainWindow>
#include "mainwindow.h"
#include <QSplashScreen>
#include <QMovie>
#include <QLabel>
#include <QHBoxLayout>
#include <QMovie>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
namespace Ui {
class pictures_stroitel;
}
class pictures_stroitel : public QMainWindow
{
    Q_OBJECT
public:
    explicit pictures_stroitel(QWidget *parent = 0);
    ~pictures_stroitel();
    MainWindow *MW;
private:
    QSplashScreen *splash;
    private slots:
    void IncCount();
    void stat_now();
};
#endif // PICTURES_STROITEL_H
