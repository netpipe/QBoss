#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<iostream>
#include<ctime>
#include<cstdlib>
#include <database.h>
#include <QFileDialog>

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
#ifdef __APPLE__
    createTable("/Applications/QBoss.app/Contents/MacOS/test.db");
#else
    createTable("/Applications/QBoss.app/Contents/MacOS/test.db");
#endif
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
            qDebug() << "employee is properly inserted";
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

    QString del_str = QString("DELETE FROM employee WHERE origid = '%1'").arg(ui->lineEdit->text());




    db.open();
    db.transaction();
        //QSqlQuery query;
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


void MainWindow::on_actionimport_csv_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open csv"), "", tr("csv Files (*.csv)"));
    QFile file(fileName);
   // QStringList wordList;
//    while (!file.atEnd()) {
//        QByteArray line = file.readLine();
//        //wordList.append(line.split(',').first());
//        ui->lineEdit->setText(line.split(',').first());
//        on_employeeaddbtn_clicked();
//    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Clear the current list first
        ui->listWidget->clear();

        // Read the CSV and split by commas
        QString line = in.readLine();
        QStringList items = line.split(",");

        // Add each item to the QListWidget
        foreach (const QString &item, items) {
            //ui->listWidget->addItem(item);
                    ui->lineEdit->setText(item);
                   on_employeeaddbtn_clicked();
        }

        file.close();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file for reading"));
    }

}


void MainWindow::on_actionexport_names_triggered()
{
    // Open a file dialog to select the save location
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save CSV"), "", tr("CSV Files (*.csv)"));

    // Ensure the file name is valid
    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".csv", Qt::CaseInsensitive)) {
            fileName += ".csv";
        }

        // Open the file
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            // Iterate through the QListWidget items and write them to the file
            for (int i = 0; i < ui->listWidget->count(); ++i) {
                QListWidgetItem *item = ui->listWidget->item(i);
                out << item->text() << ",";
            }

            file.close();

            // Show a message box for confirmation
            QMessageBox::information(this, tr("Success"), tr("List exported to %1").arg(fileName));
        } else {
            // Show an error message if the file could not be opened
            QMessageBox::warning(this, tr("Error"), tr("Could not open file for writing"));
        }
    }
}


//void MainWindow::on_listWidget_currentRowChanged(int currentRow)
//{
//    if (bLoading = true) {
//   ui->lineEdit->setText(ui->listWidget->item(currentRow)->text());
//}
//}


void MainWindow::on_actionclear_names_triggered()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Test", "remove all ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";

      QString del_str = QString("DELETE FROM employee");

      db.open();
      db.transaction();
          //QSqlQuery query;
          QSqlQuery query4;
             QString query2 = del_str;
          query4.exec(query2);

          db.commit();
         // coins.clear();
          //employee.clear();
          db.close();

          ui->listWidget->clear();
      searchEmployee();
      } else {
        qDebug() << "Yes was *not* clicked";
      }
}



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->lineEdit->setText(item->text());
}

