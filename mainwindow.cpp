#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "consoleclient.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_auth = new auth;
    ui_auth->show();
    connect(ui_auth,&auth::closed, this, &MainWindow::auth_closed);
    ui_task = new Task_solution;
    //connect(this,&MainWindow::change, ui_task, &Task_solution::change_task);
    connect (ui_task, &Task_solution::back, this, &MainWindow::accept);
    connect(SingClient::getInstance(), &SingClient::msg_stat, this, &MainWindow::on_message_stat);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*! * \brief MainWindow::auth_closed сигнал на открытие основного окна после регестрации
/*! * \param log Логин (email) пользователя
/*! */void MainWindow::auth_closed(QString log){
    ui->log_lable->setText(log);
    this->show();
}
/*!
/*! * \brief MainWindow::accept открытие основного окна после окна с задачами
/*! * \param answ флаг
/*! */void MainWindow::accept(QString answ)
{
    if(answ=="*")
        this->show();
    if(answ=="was send")
    {

        SingClient::getInstance()->send_To_server("stat"+ QString("|")+ui->log_lable->text());
        this->show();
    }

}

void MainWindow::on_exit_buttom_clicked()
{
     this->close();
    qDebug("exit");

}


void MainWindow::on_task1_buttom_clicked()
{
    //emit change(ui->task1_buttom->text());
    ui_task->change_task(ui->task1_buttom->text());
    this->close();
    qDebug("task1");
}


void MainWindow::on_task2_buttom_clicked()
{
    //emit change(ui->task2_buttom->text());
    ui_task->change_task(ui->task2_buttom->text());
    this->close();
    qDebug("task2");
}


void MainWindow::on_task3_buttom_clicked()
{
    //emit change(ui->task3_buttom->text());
    ui_task->change_task(ui->task3_buttom->text());
    this->close();
    qDebug("task3");
}


void MainWindow::on_task4_buttom_clicked()
{
    //emit change(ui->task4_buttom->text());
    ui_task->change_task(ui->task4_buttom->text());
    this->close();
    qDebug("task4");
}

void MainWindow::on_message_stat(QString msg)
{
  if (msg.left(5)=="stat+")
    ui->textBrowser->setText(msg.right(msg.size()-5));
}

