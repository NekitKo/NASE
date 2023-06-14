#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auth.h"
#include "task_solution.h"
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void auth_closed(QString log);
    void accept(QString answ);
private slots:
    void on_exit_buttom_clicked();


    void on_task1_buttom_clicked();

    void on_task2_buttom_clicked();

    void on_task3_buttom_clicked();

    void on_task4_buttom_clicked();
    void on_message_stat(QString msg);

private:
    Ui::MainWindow *ui;
    auth *ui_auth;
    Task_solution *ui_task;
    QTcpSocket *socet;
    QByteArray mTcpSocket;
signals:
    void change(QString task);

};
#endif // MAINWINDOW_H
