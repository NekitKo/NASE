#ifndef CONSOLECLIENT_H
#define CONSOLECLIENT_H

#include <QtNetwork> //указание порта, хоста
#include <QByteArray> //передаются биты
#include <QDebug> //вывод в консоль
#include <QObject>
#include <QTcpSocket>


class SingClient;

class SingletonDestroyer
{
    private:
        SingClient * p_instance;
    public:
        ~SingletonDestroyer() { delete p_instance;}
        void initialize(SingClient * p){p_instance = p;}

};


class SingClient:public QObject
{
    Q_OBJECT//вносим кюобджект для того чтоб работал коннект
    private:
        static SingClient * p_instance;
        static SingletonDestroyer destroyer;
        QTcpSocket* socket;
        QString answer;
    protected:
        SingClient(QObject*parent=nullptr):QObject(parent)
        {
            socket = new QTcpSocket;   //задаем сокет
            socket->connectToHost("127.0.0.1",33333); //подключаем его к серверу
            connect(socket,&QTcpSocket::readyRead,this,&SingClient::slotReadyRead); // сокет готов к приему информации и отправлению
            connect(socket,&QTcpSocket::disconnected,this,&SingClient::slotClientDisconnected);
        }//connectToHost, connect from server
        ~SingClient() {
            if(socket!=nullptr) socket->close();
        }

        SingClient(const SingClient& )=delete;
        SingClient& operator = (SingClient& )=delete;
        friend class SingletonDestroyer;
    public:
        static SingClient* getInstance()
        {
            if (!p_instance)
            {
                p_instance = new SingClient();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }
        QString send_To_server (QString msg)
        {
            try {
                    socket->write(msg.toUtf8());

                    socket->waitForReadyRead(-1);
                    return answer;
                } catch (const std::exception & e)
                {
                    return "Error";
                }
        }

      protected slots:
        void slotReadyRead() {
            QByteArray array;
            QString msg ;

            while (socket->bytesAvailable()>0)
            {
                array = socket->readAll();
                msg.append(array);
                //send_To_server(msg);
            }
            array.clear();
            qDebug()<< msg;
            // проверяем какой ответ с сервера нам пришел и запускаем нужный сигнал
            if(msg.left(4) == "rege")
                emit msg_reg(msg);
            if(msg.left(4) == "auth")
                emit msg_auth(msg);
            if(msg.left(4) == "stat")
                emit msg_stat(msg);
            if(msg.left(4) == "task")
                emit msg_task(msg);
            answer = msg;
        }
       public slots:
       void slotClientDisconnected(){
            socket->close();
       }
signals:
    void msg_auth(QString msg);
    void msg_reg(QString msg);
    void msg_task(QString msg);
    void msg_stat(QString msg);
};


#endif // CONSOLECLIENT_H
