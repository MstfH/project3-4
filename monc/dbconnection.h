#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QByteArray>

class dbconnection
{
private:
    static QSqlDatabase db;
    static QByteArray Pasnummer;
    static QByteArray Rekeningnummer;
    static QByteArray transactie;
public:
    dbconnection();
    static bool card(QByteArray nuid);
    static bool getIban();
    static int checkPin(QString pin);
    static bool blocked();
    static bool createTransaction();
    static bool updateTransaction(float amount);
    static float getSaldo();
    static bool newAction(QByteArray action, float amount);
    static bool withdraw(float amount);
    static void stop();
    static void close();
};

#endif // DBCONNECTION_H
