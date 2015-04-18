#include "database.h"
database::database()
{
    correct_connected=true;
    connect();
    query=new QSqlQuery;
}
void database::connect()
{
    DB=QSqlDatabase::addDatabase("QMYSQL");
    DB.setHostName("localhost");
    DB.setDatabaseName("kursovoi");
    DB.setUserName("root");
    DB.setPassword("root");
    if(DB.open())
    {
        qDebug()<<"OK";
        correct_connected=true;
    }
    else
    {
        qDebug()<<"fail";
        correct_connected=false;
    }
}
void database::remove()
{
    QSqlDatabase::removeDatabase("QMYSQL");
    delete query;
    query=new QSqlQuery;
    qDebug()<<"remove DB";
}
database::~database(){}
