#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
class database
{
public:
    QSqlDatabase DB;
    QSqlQuery *query;
    database();
    ~database();
public:
    void connect();

    bool correct_connected;
};

#endif // DATABASE_H
