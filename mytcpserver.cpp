#include "mytcpserver.h"

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,this,&MyTcpServer::slotNewConnection);
    if(!mTcpServer->listen(QHostAddress::Any,33333))
    {
       qDebug() << "Servet is Dead";
    }
    else
    {
        server_status=1;
        qDebug()<<"All Good";
    }
}

void MyTcpServer::slotNewConnection()
{
    if(server_status==1)
    {
        QTcpSocket * curr_Socket;
        curr_Socket = mTcpServer->nextPendingConnection();
        curr_Socket->write("rabotaet");
        qDebug()<<"slot creat";
        connect(curr_Socket,&QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(curr_Socket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);

        mTcpSocket.insert(curr_Socket->socketDescriptor(),curr_Socket);
    }
}

void MyTcpServer::slotServerRead()
{
    QByteArray array;
    QString str;
    QTcpSocket* curr_Socket = (QTcpSocket*)sender();
    while(curr_Socket->bytesAvailable()>0)
    {
       array.append(curr_Socket->readAll());
       str+=array;
    }
    array="";
    array.append(str.toUtf8());
    QString task = array.left(str.size());
    qDebug()<<task;
    QByteArray a;
    a = parse(task);
    qDebug()<<a;
    curr_Socket->write(a);
    curr_Socket->write(" ");
    qDebug()<<"frej";
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *curr_Socket = (QTcpSocket*)sender();
    int chet = curr_Socket->socketDescriptor();
    mTcpSocket[chet]->close();
    mTcpSocket.remove(chet);
}
void MyTcpServer::function1(QTcpSocket*curr_Socket)
{
   curr_Socket->write("Добрый день!");
}
void MyTcpServer::function2(QTcpSocket*curr_Socket)
{
   curr_Socket->write("Cервер работает");
}
