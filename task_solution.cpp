#include "task_solution.h"
#include "ui_task_solution.h"
#include <QDebug>
#include "consoleclient.h"
Task_solution::Task_solution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Task_solution)
{
    ui->setupUi(this);
    connect(SingClient::getInstance(), &SingClient::msg_task, this, &Task_solution::on_message_task);
}

Task_solution::~Task_solution()
{
    delete ui;
}

void Task_solution::change_task(QString task)
{

    QString otvet;
    ui->label->setText(task);
    if(task == "Task №1")
    {
       otvet = SingClient::getInstance()->send_To_server("task1|email");

       ui->text->setText(otvet);
    }
    if(task == "Task №2")
    {
       otvet = SingClient::getInstance()->send_To_server("task2|email");

       ui->text->setText(otvet);
    }
    if(task == "Task №3")
    {
       otvet = SingClient::getInstance()->send_To_server("task3");

       ui->text->setText(otvet);
    }
    if(task == "Task №4")
    {
       otvet = SingClient::getInstance()->send_To_server("task4|email");

       ui->text->setText(otvet);
    }


    //посмотреть номер задания и измниеть ui->text соответствено с текстом задания
    this->show();


}


void Task_solution::on_send_Button_clicked()
{
    QString txt;
    QString otvet;
    txt = QString("task"+ui->label->text().right(1));
    otvet = QString(ui->text->text());
    otvet.resize(otvet.size()-2);
    qDebug() << txt;
    qDebug() << otvet;
   // SingClient::getInstance()->send_To_server("task"+ui->label->text().right(1)+QString("|")+ui->line_answer->text());
    //qDebug()<<"task"+ui->label->text().right(1);
    //emit back("was send");
    qDebug("it was send");
    if (txt == "task1")
    {
        QString ugol;
        ugol = ui->lineEdit->text();
        otvet = SingClient::getInstance()->send_To_server(QString("checktask1") + QString("|") +QString("email")+ QString("|") + QString(otvet) +QString("|")+ ugol);
        ui->text->setText(otvet);
        qDebug() << ugol;
        qDebug() << otvet;
    }
    if (txt == "task2")
    {
        QString ugol;
        ugol = ui->lineEdit->text();
        otvet = SingClient::getInstance()->send_To_server(QString("checktask2") + QString("|") +QString("email")+ QString("|") + QString(otvet) +QString("|")+ ugol);
        ui->text->setText(otvet);
        qDebug() << ugol;
        qDebug() << otvet;
    }
    if (txt == "task3")
    {
        QString ugol;
        ugol = ui->lineEdit->text();
        otvet = SingClient::getInstance()->send_To_server(QString("checktask3") + QString("|") +QString("email")+ QString("|") + QString(otvet) +QString("|")+ ugol);
        ui->text->setText(otvet);
        qDebug() << ugol;
        qDebug() << otvet;
    }
    if (txt == "task4")
    {
        QString ugol;
        ugol = ui->lineEdit->text();
        otvet = SingClient::getInstance()->send_To_server(QString("checktask4") + QString("|") +QString("email")+ QString("|") + "123" +QString("|")+ ugol);
        ui->text->setText(otvet);
        qDebug() << ugol;
        qDebug() << otvet;
    }
    //this->close();
}


void Task_solution::on_back_Button_clicked()
{
    emit back("*");
    ui->lineEdit->clear();
    ui->text->clear();
    this->close();
    qDebug("pushed back");
}

void Task_solution::on_message_task(QString msg)
{
    ui->text->setText(msg);
}

