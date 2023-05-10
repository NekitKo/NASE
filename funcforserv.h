#include <QByteArray>
#include <QString>
#include <QStringList>
#include "database.h"

QByteArray parse(QString str);

QByteArray rege(const QString& email, const QString& role, const QString& password,const QString& verifypass);

QByteArray auth(const QString& email,const QString& password);

QString stat(const QString& email);

QByteArray task1(const QString& email);

QByteArray task2(const QString& email);

QByteArray task3(const QString& email);

QByteArray task4(const QString& email);
