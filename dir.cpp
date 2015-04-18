#include "dir.h"
dir::dir(){}
dir::~dir(){}
int dir::read_procent_File()
{
    QFile file("file/proc.txt");
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            while(!file.atEnd())
            {
                QString str = file.readLine();//читаем строку
                QStringList lst = str.split(" ");//Делим строку на слова разделенные пробелом

                qDebug() << lst.at(0);
                file.close();
                return lst.at(0).toInt();
            }
        }
        else
        {
            file.close();
            qDebug()<< "don't open file";
        }
}
bool dir::write_procent_File(int nac)
{
    qDebug()<<QString::number(nac);
    QFile file("file/proc.txt");
        if(file.open(QIODevice::WriteOnly |QIODevice::Text))
        {
            QTextStream out(&file);
            out << nac;
            file.close();
            return true;
        }
        else
        {
            qDebug()<< "don't open file";
            file.close();
            return false;
        }
}
QList<int> dir::read_work_process_File()
{
    QFile file("file/work_process.txt");
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            QList<int> temp ;
            while(!file.atEnd())
            {
                QString str = file.readLine();//читаем строку
                QStringList lst = str.split(" ");//Делим строку на слова разделенные пробелом
                temp.push_back(lst.at(0).toInt());
                temp.push_back(lst.at(1).toInt());
                qDebug() << lst.at(0)<<lst.at(1);
                file.close();
                return temp;
            }
        }
        else
        {
            file.close();
            qDebug()<< "don't open file";
        }
}
bool dir::write_work_process_File(QList<int> nac)
{
    QFile file("file/work_process.txt");
        if(file.open(QIODevice::WriteOnly |QIODevice::Text))
        {
            QTextStream out(&file);
            out << nac[0]<< " "<<nac[1];
            file.close();
            return true;
        }
        else
        {
            qDebug()<< "don't open file";
            file.close();
            return false;
        }
}
