#ifndef MYTCPSERVER_H //аналог pragma once
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer> ///tcp сервер (прослушивание канала, сигнал о подключении - все, что уже готово)
#include <QTcpSocket>
#include <QtNetwork> //указание порта, хоста
#include <QByteArray> //передаются биты
#include <QDebug> //вывод в консоль
#include <QMap>
#include <QCoreApplication>
#include <funcforserv.h>
class MyTcpServer : public QObject
{
    Q_OBJECT //где-то в аду есть define, по которому понятно, что это такое, и с чем это едят
public:
//explicit - командное слово, которое говорит что конструктор
//не приемлет неявное преобразование типов
//распростараняется на всю функцию, а не только ее параметры
//по аналогии с const

//в нашем проекте можно без expicit

    explicit MyTcpServer(QObject *parent = nullptr); //конструктор
    ~MyTcpServer(); //деструктор
    void function1(QTcpSocket*);
    void function2(QTcpSocket*);
public slots: //вызывается в случае срабатывания какого-либо сигнала
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();
    //void slotReadClient();
private:
    QTcpServer * mTcpServer;
    QMap<int, QTcpSocket *> mTcpSocket;
    int server_status;
};
#endif // MYTCPSERVER_H //аналог pragma once

