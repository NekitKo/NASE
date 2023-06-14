#include "auth.h"
#include "ui_auth.h"
#include <QDebug>
#include "consoleclient.h"
#include <QMessageBox>
auth::auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auth)
{
    flag=false;
    ui->setupUi(this);
    ui->log_Edit->setVisible(false);
    ui->log_lable->setVisible(false);
    ui->pass_Edit->setVisible(false);
    ui->pass_label->setVisible(false);
    ui->pass_acses_Edit->setVisible(false);
    ui->pass_acses_label->setVisible(false);
    ui->back_Button->setVisible(false);
    connect(SingClient::getInstance(), &SingClient::msg_reg, this, &auth::on_message_reg);
    connect(SingClient::getInstance(), &SingClient::msg_auth, this, &auth::on_message_auth);

}
void auth::change_mode (int mode){
   if (mode==1){
       flag=false;

       ui->label->setText("Добро пожаловать");
       ui->log_Edit->setVisible(false);
       ui->log_lable->setVisible(false);
       ui->pass_Edit->setVisible(false);
       ui->pass_label->setVisible(false);
       ui->pass_acses_Edit->setVisible(false);
       ui->pass_acses_label->setVisible(false);
       ui->back_Button->setVisible(false);
       ui->reg_Button->setVisible(true);
       ui->auth_Button->setVisible(true);
   }

    if (mode==2){
       flag=true;
       ui->label->setText("Авторизация");
       ui->log_Edit->setVisible(true);
       ui->log_lable->setVisible(true);
       ui->pass_Edit->setVisible(true);
       ui->pass_label->setVisible(true);
       ui->back_Button->setVisible(true);
       ui->reg_Button->setVisible(false);
     }
    if (mode==3){
       flag=true;
       ui->label->setText("Регистрация");
       ui->log_Edit->setVisible(true);
       ui->log_lable->setVisible(true);
       ui->pass_Edit->setVisible(true);
       ui->pass_label->setVisible(true);
       ui->back_Button->setVisible(true);
       ui->pass_acses_Edit->setVisible(true);
       ui->pass_acses_label->setVisible(true);
       ui->auth_Button->setVisible(false);
     }
}
auth::~auth()
{
    delete ui;
}

void auth::on_auth_Button_clicked()
{
   if(flag==false){

    this->change_mode(2);
    qDebug("auth");

   }
   else{
       SingClient::getInstance()->send_To_server("auth"+ QString("|")+ui->log_Edit->text()+QString("|")+ui->pass_Edit->text()+QString("|")+""+QString("|")+"");// отправка на сервер
       qDebug()<<"auth"+ QString("|")+ui->log_Edit->text()+QString("|")+ui->pass_Edit->text();
       //*
       //qDebug("auth");
       //emit closed(ui->log_Edit->text());
       //ui->log_Edit->clear();
       //ui->pass_Edit->clear();
       //this->close();

   }

}


void auth::on_reg_Button_clicked()
{
   if(flag==false){
       this->change_mode(3);
    }
   else{
       if(ui->log_Edit->text() !=""  && ui->pass_Edit->text() !="" && ui->pass_acses_Edit->text() !=""){
           if (ui->pass_Edit->text() != ui->pass_acses_Edit->text()){
               QMessageBox::warning(this,"Несовпадение","Пароли должны совпадать!");
           }
           else{
              SingClient::getInstance()->send_To_server("rege"+QString("|")+ui->log_Edit->text()+QString("|")+ui->pass_Edit->text()+QString("|")+ui->pass_acses_Edit->text());
              //*
              //ui->log_Edit->clear();
              //ui->pass_Edit->clear();
              //ui->pass_acses_Edit->clear();
              //this->change_mode(1);
              //qDebug("reg");
           }
       }
       else{
           QMessageBox::warning(this,"Не все данные","Сначала заполните все поля!");
       }

   }


}


void auth::on_back_Button_clicked()
{
    ui->log_Edit->clear();
    ui->pass_Edit->clear();
    ui->pass_acses_Edit->clear();
    this->change_mode(1);
    qDebug("begin");
}

void auth::on_message_reg(QString msg)
{
    if (msg.left(5) == "rege+"){
        QMessageBox::information(this,"Успешно","Вы зарегестрированы");
        ui->log_Edit->clear();
        ui->pass_Edit->clear();
        ui->pass_acses_Edit->clear();
        this->change_mode(1);
        qDebug("reg");
    }
    else if (msg.left(5) == "rege-"){
        QMessageBox::warning(this, "Неуспешно", "Аккаунт уже зарегистрирован");
    }

}

void auth::on_message_auth(QString msg)
{
    if (msg.left(5) == "auth+"){
        QMessageBox::information(this, "Успешно", "Вы прошли авторизацию");
        qDebug("auth");
        emit closed(ui->log_Edit->text());
        ui->log_Edit->clear();
        ui->pass_Edit->clear();
        this->close();
    }
    else if (msg.left(5) == "auth-"){
        QMessageBox::warning(this, "Неуспешно", "Неверный логин или пароль");}
}

