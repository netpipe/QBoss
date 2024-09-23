#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <qlistwidget.h>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


    bool bLoading;
    void searchEmployee();
void createTable(QString DBname);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_coinflipbtn_clicked();

    void on_employeeaddbtn_clicked();

    void on_employeermbtn_clicked();

    void on_actionimport_csv_triggered();

    void on_actionexport_names_triggered();

   // void on_listWidget_currentRowChanged(int currentRow);

    void on_actionclear_names_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
