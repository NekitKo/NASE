#include "funcforserv.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSqlDatabase>
QByteArray parse(QString str){
    QStringList params = str.split("|");   //формат msg: function|params0|params1...
    qDebug()<<params[0];
    QString mail=params[1];           //разделяем данные для функций
    QString pass= params[2];
    QString verpass=params[3];
    QString role = params[4];
    if (params[0] =="auth"){
        if (params.count()!=3){
            qDebug();
             return "Invalid data for auth";
         }
         else{
            return auth(mail,pass);
         }
    }
    else if (params[0] =="rege"){
        if (params.count()!=5)
            return "Invalid data for registration";
        else{
            return rege(mail,role,pass,verpass);
        }
   }
   else if (params[0] == "stat"){
     if (params.count()!=2)
            return "Invalid data for statistics";
        else{
             stat(mail);
        }
   }
   else if (params[0] == "task1"){
      if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task1(mail);
        }
   }
   else if (params[0] == "task2"){
        if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task2(mail);
        }
   }
   else if (params[0] == "task3"){
        if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task3(mail);
        }
   }
   else if (params[0] == "task4"){
        if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task4(mail);
        }
   }
   else{
             return "Invalid function name";
   }
   return "parse";
}

QByteArray rege(const QString& email, const QString& role, const QString& password,const QString& verifypass){
    if(password!=verifypass)                           // надо ли?
    {
        return "passwords are not same";
    }
    QString query = QString("INSERT INTO users (mail, pass, role) VALUES(\"%1\", \"%2\", \"%3\")").arg(email, password ,role);
    //Database::getInstance()->execQuery(query).size()>0
    Database::getInstance()->execQuery(query);  
    QString s = Database::getInstance()->execQuery("SELECT * from users where mail = \"" + email+"\"");
    if (s.size()>0) {
        return "User successfully inserted";
    } else {
        return "User not successfully inserted because user already exists";
    }
}

QByteArray auth(const QString& email,const QString& password){
    QString query = QString("SELECT * FROM users WHERE mail = \"" + email+"\"");
    qDebug()<<query;
    if (Database::getInstance()->execQuery(query).size()>0){  // Если найдено больше нуля записей с заданным именем пользователя,
        return "User exists in database.";
        Database::getInstance()->execQuery("UPDATE users SET in_sys = 1 WHERE mail = \"" + email+"\"");
    }
    else                                                                     // Иначе пользователь с заданным именем не найден в базе данных.
        return "Incorrect password or email ";
}

QString stat(const QString& email){
   QString query = ("SELECT task1, task2, task3, task4 FROM users WHERE mail = \"" + email+"\"");
   qDebug()<<query;
   QString response = "";
    if (Database::getInstance()->execQuery(query).size()>0){  
        response = Database::getInstance()->execQuery(query);
        return response;
    }
    else                                                               
        return "Error";
}

QByteArray task1(const QString& email){
     return "task1";
};

QByteArray task2(const QString& email){
     return "task2";
};

QByteArray task3(const QString& email){
     return "task3";
};

QByteArray task4(const QString& email){
     return "task4";
};
