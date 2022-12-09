#ifndef DATABASE_H
#define DATABASE_H

#include <mainwindow.h>
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>

void MainWindow::searchEmployee()
{

//db.setDatabaseName("test.db");
db.open();
db.transaction();
    QSqlQuery query4;
  //  query4.exec("SELECT origid FROM employee; WHERE ORDER BY RANDOM() LIMIT 1");
    query4.exec("SELECT * FROM employee");
 // select.prepare(query);
    while (query4.next()) {
     //   yeardb = query.value(0).toInt();
        //qDebug() << "coin " << query4.value(1).toString();
        ui->listWidget->addItem( query4.value(1).toString());
       // return yeardb.toLatin1();
    }
db.commit();
db.close();

}


void MainWindow::createTable(QString DBname)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
  //  m_db.setDatabaseName("./voice_user.db");
    db.setDatabaseName(DBname.toLatin1());

    if(db.open())
    {
        qDebug()<<"Successful coin database connection";
    }
    else
    {
        qDebug()<<"Error: failed database connection";
    }

    QString query;
    query.append("CREATE TABLE IF NOT EXISTS employee("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "origid VARCHAR(50),""addr VARCHAR(50));");

    QSqlQuery create;

    create.prepare(query);

    if (create.exec())
    {
        qDebug()<<"Table exists or has been created";
    }
    else
    {
        qDebug()<<"Table not exists or has not been created";
        //qDebug()<<"ERROR! "<< create.lastError();
    }

    query.clear();
    db.close();

}



#endif // DATABASE_H
