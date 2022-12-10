#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<iostream>
#include<ctime>
#include<cstdlib>
#include <database.h>

using namespace std;

int coinToss()
{
    int num;

        rand();

    num = rand() % 2;

    //if (num)
    //	cout << "Heads" << endl;
    //else
    //	cout << "Tails" << endl;
    return num;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTable("./test.db");
    searchEmployee();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_coinflipbtn_clicked()
{
    int times = 51;
    int i = 0;
float avgnum=0;
    int count = 0;

    srand(static_cast<size_t>(time(nullptr)));  // <--- Noved and changed.
ui->tosslst->clear();

    while (i < times)      //It shows the same answer 'x' times :(
    {

        int result = coinToss();
        if (result){
avgnum++;
            ui->tosslst->addItem(QString::number(result));
        }else{
            ui->tosslst->addItem(QString::number(result));
        };

        i++;
    }

    QString resultcoin;

    if ((avgnum/times) >= .5)
    //	cout << "Heads" << endl;
        resultcoin += "Saved";
    else
        //cout << "Tails" << endl;
            resultcoin += "Fired";



    //db.setDatabaseName("test.db");
    db.open();
    db.transaction();
        QSqlQuery query4;
      //  query4.exec("SELECT origid FROM employee; WHERE ORDER BY RANDOM() LIMIT 1");
        query4.exec("SELECT * FROM employee ORDER BY random() LIMIT 1");
     // select.prepare(query);
        while (query4.next()) {
         //   yeardb = query.value(0).toInt();
          //  qDebug() << "employee " << query4.value(1).toString();
            ui->label_2->setText( query4.value(1).toString()+ " "+ QString::number(avgnum/times) + " " + resultcoin.toLatin1());


        //    ui->lineEdit->setText(query4.value(1).toString() );
        //    ui->listWidget->addItem( query4.value(1).toString());
           // return yeardb.toLatin1();
        }
    db.commit();
    db.close();



}

void MainWindow::on_employeeaddbtn_clicked()
{
   // db = QSqlDatabase::addDatabase("QSQLITE");
     QVariantList employee;

     employee.append(ui->lineEdit->text());

  //  db.setDatabaseName("test.db");
    db.open();
    db.transaction();
        QSqlQuery query4;
            QString query2 = "INSERT INTO employee(origid) VALUES (?)";
        query4.exec(query2);
        QSqlQuery insert;
        insert.prepare(query2);
        insert.addBindValue(employee);

        if(insert.execBatch())
        {
            qDebug() << "Coin is properly inserted";
        }
        else
        {
 //           qDebug()<<"ERROR! "<< insert.lastError();
        }
        db.commit();
       // coins.clear();
        employee.clear();
        db.close();

        ui->listWidget->clear();
        searchEmployee();
}


void MainWindow::on_employeermbtn_clicked()
{
  //  DELETE FROM table
  //  WHERE search_condition;

    QString del_str = QString("DELETE FROM employee WHERE origid = '%1' LIMIT 1;").arg(ui->lineEdit->text());


    db.open();
    db.transaction();
        QSqlQuery query4;
            QString query2 = del_str;
        query4.exec(query2);


        db.commit();
       // coins.clear();
        //employee.clear();
        db.close();

        ui->listWidget->clear();
searchEmployee();
}

