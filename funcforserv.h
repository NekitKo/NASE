#include <QByteArray>
#include <QString>
#include <QStringList>
#include "database.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>
#include <QSqlDatabase>

QByteArray parse(QString str);

QByteArray rege(const QString& email, const QString& password,const QString& verifypass);

QByteArray auth(const QString& email,const QString& password);

QString stat(const QString& email);

QByteArray task1(const QString& email);

QByteArray task2(const QString& email);

QByteArray checktask3(const QString& email, const QString& variant, const QString& answer);

QByteArray task4(const QString& email);

QByteArray checktask1(const QString& email,const QString& variant,const QString& answer);

QByteArray get_task3();

QByteArray checktask2(const QString& email,const QString& variant,const QString& answer);
QByteArray checktask4(const QString& email, const QString& variant, const QString& answer);
