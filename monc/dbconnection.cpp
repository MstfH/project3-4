#include "dbconnection.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <string>

QSqlDatabase dbconnection::db;
QByteArray dbconnection::Pasnummer;
QByteArray dbconnection::Rekeningnummer;
QByteArray dbconnection::transactie;

dbconnection::dbconnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "monc");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("monc");
    db.setUserName("atm");
    db.setPassword("password");
    db.setPort(3306);
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
    query.exec("SELECT Pasnummer FROM monc.debitcard WHERE Pasnummer = '" + data + "';");
    if(query.next())
    {
        Pasnummer = query.value(0).toByteArray();
        return true;
    }
    else
    {
        qDebug("No result");
    }
    return false;
}

bool dbconnection::blocked()
{
    QSqlQuery query(db);
    query.exec("SELECT Kansen FROM monc.debitcard WHERE Pasnummer = '" + Pasnummer + "';");
    if(query.next())
    {
        if(query.value(0).toInt()>=3)
        {
            return true;
        }
    }
    else
    {
        qDebug("No result");
    }
    return false;
}

bool dbconnection::getIban()
{
    QSqlQuery query(db);
    query.exec("SELECT Rekeningnummer FROM monc.debitcard WHERE Rekeningnummer='"+Pasnummer+"' LIMIT 1;");
    if(query.next())
    {
        Rekeningnummer = query.value(0).toByteArray();
        return true;
    }
    else
    {
        qDebug("No result");
    }
    return false;
}

int dbconnection::checkPin(QString pin)
{
    QSqlQuery query(db);
    query.exec("SELECT Pasnummer, Pincode, Kansen FROM monc.debitcard WHERE Pasnummer='"+Pasnummer+"';");
    if(query.next() && query.value(1).toString() == pin)
    {
        query.exec("UPDATE `monc`.`debitcard` SET `Kansen`='0' WHERE `Pasnummer`='"+Pasnummer+"';");
        return 0;
    }
    else
    {
        int Kansen = query.value(2).toInt();
        query.exec("UPDATE `monc`.`debitcard` SET `Kansen`='"+QByteArray::number(Kansen+1)+"' WHERE `Pasnummer`='"+Pasnummer+"';");
        return Kansen+1;
    }
}

bool dbconnection::createTransaction()
{
    QSqlQuery query(db);
    query.exec("INSERT INTO `monc`.`transacties` (`Rekeningnummer`) VALUES ('"+Rekeningnummer+"');");
    query.exec("SELECT max(transactieID) FROM `monc`.`transacties`;");
    if(query.next()){
        transactie = query.value(0).toByteArray();
        return true;
    }
    return false;
}

bool dbconnection::updateTransaction(float amount)
{
    QSqlQuery query(db);
    QByteArray stringAmount = QByteArray::number(amount);
    query.exec("UPDATE `monc`.`transacties` SET `HoeveelGeld`='"+stringAmount+"', `Datum`=current_timestamp() WHERE `transactieID`='"+transactie+"';");
    return true;
}

float dbconnection::getSaldo()
{
    QSqlQuery query(db);
    query.exec("SELECT Saldo FROM monc.accounts WHERE Rekeningnummer='"+Rekeningnummer+"';");
    if(query.next())
    {
        return query.value(0).toFloat();
    }
    else
    {
        qDebug("No result");
    }
    return -9999.9;
}

bool dbconnection::newAction(QByteArray action, float amount)
{
    QSqlQuery query(db);
    query.exec("INSERT INTO `monc`.`transacties` (`transactieID`, `Beschrijving`, `HoeveelGeld`) VALUES ('"+transactie+"', '"+action+"','"+QByteArray::number(amount)+"');");
    return true;
}

bool dbconnection::withdraw(float amount)
{
    QSqlQuery query(db);
    float newAmount = getSaldo() - amount;
    if(newAmount >= 0){
        query.exec("UPDATE `monc`.`accounts` SET `Saldo`='"+QByteArray::number(newAmount)+"' WHERE `Rekeningnummer`='"+Rekeningnummer+"';");
        return true;
    }
    return false;
}

void dbconnection::stop()
{
    Pasnummer = nullptr;
    transactie = nullptr;
    Rekeningnummer = nullptr;
}

void dbconnection::close()
{
    db.close();
    qDebug("Db connection closed");
}

