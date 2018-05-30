 #ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QByteArray>

class dbconnection
{
private:
    static QSqlDatabase db;
    static QByteArray nuid;
    static QByteArray iban;
    static QByteArray transactie;
public:
    dbconnection();
    static bool card(QByteArray nuid);
    static bool getIban();
    static int checkPin(QString pin);
    static bool blocked();
    static float getSaldo();
    static bool withdraw(float amount);
    static void log(QByteArray message);
    static void stop();
    static void close();
};

#endif // DBCONNECTION_H
