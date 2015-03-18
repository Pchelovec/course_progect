#ifndef DIR_H
#define DIR_H
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QList>
class dir
{
public:
    int read_procent_File();
    bool write_procent_File(int nac);
    bool write_work_process_File(QList<int> nac);
    QList<int> read_work_process_File();
    dir();
    ~dir();
};

#endif // DIR_H
