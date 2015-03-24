#include "printer.h"

printer::printer()
{

}

printer::~printer()
{

}

void printer::set_info(QList <material_ned> table, QString ID_progect, building info, QList<building> list)
{
    table_material_nedost=table;
    ID=ID_progect;
    info_b=info;
    steps=list;
}

void printer::make_ntml()
{
    out.setString(&s, QIODevice::ReadWrite);
    out << "<html>\n";
          out << "<head>\n";
          out << "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />\n";

}

void printer::print()
{

QPrinter *printe=new QPrinter;
        QVector<QString> titles;
        titles.push_back("<h1><center>строительный контракт №" "ID" "<center/><h1/>");
        titles.push_back("<h2>заказчик -" "info_b.ID" "<h2/>");
        titles.push_back("<h3>общая сумма к оплате составляет: " "info_b.price" "<h3/>");
        titles.push_back("<h3>в рамках данного контракта утверждаю график выхода рабочих бригад на постройку здания:<h3/>");
        //таблица работников
        titles.push_back("<TABLE BORDER>"
                         "<TR>"
                         "        <TD><h2>специальность бригады </TD> <TD>количество</TD> <TD>дата начала</TD> <TD>дата окончания<h2/></TD>"
                         "</TR>"

                         "<TR>"
                         "        <TD><h3>строители</TD> <TD>1</TD> <TD>27.03.2015</TD> <TD>29.03.2015<h3/></TD>"
                         "</TR>"

                 "</TABLE>");



        titles.push_back("<h3>в рамках данного контракта поручаю докупить следующие строительные материалы:<h3/>");
        //таблица материалов

        titles.push_back("<TABLE BORDER>"
                         "<TR>"
                         "        <TD>материал</TD> <TD>количество</TD>"
                         "</TR>"

                         "<TR>"
                         "        <TD>доски</TD> <TD>30</TD>"
                         "</TR>"

                 "</TABLE>");
        titles.push_back("<br><br/>");
        QDate d;
        titles.push_back(d.currentDate().toString("dd.MM.yyyy")+" ____________________________");
        QString strStream;
        QTextStream out(&strStream);

        for (int i = 0; i < titles.size(); i++) {
            out << "<html><head></head><body>";
            out << "<p style=\"font-size:20pt\">" + titles.at(i) + "</p>";
            out << "</body></html>";
        }

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        //prevDlg = new QPrintPreviewDialog(printe);//
        //prevDlg->setWindowIconText(document);
        //prevDlg->exec();//
        document->print(printe);
        delete document;
}
void printer::clear()
{

}
