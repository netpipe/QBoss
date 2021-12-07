#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<iostream>
#include<ctime>
#include<cstdlib>

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
    ui->label_2->setText(QString::number(avgnum/times));
}
