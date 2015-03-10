#include "database.h"

database::database()
{
    connect();
    //query.exec("SELECT name, salary FROM employee WHERE salary > 50000");
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
    }
    else
    {
        qDebug()<<"fail";
    }
}

database::~database()
{

}

