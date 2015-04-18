#include "printer.h"



printer::printer()
{

}

printer::~printer()
{

}

void printer::print_contract(QString id_contract, QString id_house)
{
    NCReport *report = new NCReport();

    report->setReportFile("report/progect_total_info.ncr"); //set the report filename fullpath or relative to dir

    report->addParameter("ID", id_contract);
    report->addParameter("id_house", id_house);

    report->setZintPath("Z:/bin");
    report->runReportToShowPreview(); // run and show to preview output

    if( report->hasError())// error handling
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Report error: ") + report->lastErrorMsg());
        msgBox.exec();
    }
    delete report;
}

void printer::print_all_material()
{
    NCReport *report = new NCReport();

    report->setReportFile("report/progect_material.ncr"); //set the report filename fullpath or relative to dir

    report->runReportToShowPreview(); // run and show to preview output

    if( report->hasError())// error handling
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Report error: ") + report->lastErrorMsg());
        msgBox.exec();
    }
    delete report;
}

void printer::print_worker_time(QString id_brig)
{
    NCReport *report = new NCReport();

    report->setReportFile("report/progect_group_work.ncr"); //set the report filename fullpath or relative to dir
    report->addParameter("id_brig", id_brig);
    report->runReportToShowPreview(); // run and show to preview output

    if( report->hasError())// error handling
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Report error: ") + report->lastErrorMsg());
        msgBox.exec();
    }
    delete report;
}
