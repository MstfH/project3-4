#include "dbconnection.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <string>

QSqlDatabase dbconnection::db;
QByteArray dbconnection::nuid;
QByteArray dbconnection::iban;
QByteArray dbconnection::transactie;

dbconnection::dbconnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "saatbank");
    db.setHostName("145.24.222.155");
    db.setDatabaseName("saatbank");
    db.setUserName("monc");
    db.setPassword("2eAzWh2YqztmMVwq");
    db.setPort(8888);
    bool ok = db.open();
    if(ok) {
        qDebug("Db connection established");
    }
    else {
        qDebug("Could not connect to db");
    }
}

bool dbconnection::card(QByteArray data)
{
    QSqlQuery query(db);
    query.exec("SELECT nuid FROM `card` WHERE nuid = '" + data + "';");
    if(query.next())
    {
        nuid = query.value(0).toByteArray();
        return true;
    }
    else
    {
        qWarning("No result");
    }
    return false;
}

bool dbconnection::blocked()
{
    QSqlQuery query(db);
    query.exec("SELECT attempts FROM `card` WHERE nuid = '" + nuid + "';");
    if(query.next())
    {
        if(query.value(0).toInt()>=3)
        {
            return true;
        }
    }
    else
    {
        qWarning("No result");
    }
    return false;
}

bool dbconnection::getIban()
{
    QSqlQuery query(db);
    query.exec("SELECT iban FROM `cardaccount` WHERE nuid='"+nuid+"' LIMIT 1;");
    if(query.next())
    {
        iban = query.value(0).toByteArray();
        return true;
    }
    else
    {
        qWarning("No result");
    }
    return false;
}

int dbconnection::checkPin(QString pin)
{
    QSqlQuery query(db);
    query.exec("SELECT nuid, pincode, attempts FROM `card` WHERE nuid='"+nuid+"';");
    if(query.next() && query.value(1).toString() == pin)
    {
        query.exec("UPDATE `card` SET `attempts`='0' WHERE `nuid`='"+nuid+"';");
        return 0;
    }
    else
    {
        int attempts = query.value(2).toInt();
        query.exec("UPDATE `card` SET `attempts`='"+QByteArray::number(attempts+1)+"' WHERE `nuid`='"+nuid+"';");
        return attempts+1;
    }
}

float dbconnection::getSaldo()
{
    QSqlQuery query(db);
    query.exec("SELECT balance FROM `account` WHERE iban='"+iban+"';");
    if(query.next())
    {
        return query.value(0).toFloat();
    }
    else
    {
        qWarning("No result");
    }
    return -9999.9;
}

bool dbconnection::withdraw(float amount)
{
    QSqlQuery query(db);
    float newAmount = getSaldo() - amount;
    if(newAmount >= 0){
        query.exec("INSERT INTO `transaction` (`iban`, `amount`, `atm_id`) VALUES ('"+ iban +"', '"+ QByteArray::number(amount*-1) +"', 'MONC');");
        query.exec("UPDATE `account` SET `balance`='"+QByteArray::number(newAmount)+"' WHERE `iban`='"+iban+"';");
        return true;
    }
    return false;
}

void dbconnection::log(QByteArray message)
{
    QSqlQuery query(db);
    query.exec("INSERT INTO `log` (`message`, `atm_id`) VALUES ('"+message+"', 'MONC');");
}

void dbconnection::stop()
{
    nuid = nullptr;
    transactie = nullptr;
    iban = nullptr;
}

void dbconnection::close()
{
    db.close();
    qWarning("Db connection closed");
}
