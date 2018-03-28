#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialread.h"
#include "dbconnection.h"
#include <QTime>

QString MainWindow::pincode;
QString MainWindow::anderBedrag;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->buttonBack->setVisible(false);
    ui->buttonStop->setVisible(false);
    ui->buttonSkipDebug->setVisible(false);
    ui->buttonRestartDebug->setVisible(false);

    QWidget::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//MainWindow buttons
void MainWindow::on_buttonBack_pressed()
{
    switch(ui->stackedWidget->currentIndex())
    {
    case 4:
        ui->stackedWidget->setCurrentIndex(3);
        ui->buttonBack->setVisible(false);
        break;
    case 5:
        ui->stackedWidget->setCurrentIndex(3);
        ui->buttonBack->setVisible(false);
        break;
    case 7:
        ui->stackedWidget->setCurrentIndex(5);
        break;
    }
    ui->labelScanError->setText("");
    ui->labelPinError->setText("");
    ui->labelMenuError->setText("");
    ui->labelOpnemenError->setText("");
    ui->labelAndersError->setText("");
    ui->labelErrorMessage->setText("");
    ui->txtBedrag->setText("");
    anderBedrag = "";
}

void MainWindow::on_buttonStop_pressed()
{
    ui->labelScanError->setText("");
    ui->labelPinError->setText("");
    ui->labelMenuError->setText("");
    ui->labelOpnemenError->setText("");
    ui->labelAndersError->setText("");
    ui->labelErrorMessage->setText("");
    ui->stackedWidget->setCurrentIndex(0);
    ui->buttonBack->setVisible(false);
    ui->buttonStop->setVisible(false);
    pincode = "";
    ui->pwPincode->setText("");
}

//Start screen buttons
void MainWindow::on_buttonStart_pressed()
{  
    ui->stackedWidget->setCurrentIndex(1);
    ui->buttonStop->setVisible(true);
}

//Pincode screen buttons
void MainWindow::on_buttonPinCorrection_pressed()
{}

void MainWindow::on_buttonPinConfirm_pressed()
{
    pincode = ui->pwPincode->text();
    if(pincode.length() == 4)
    {
        int attempts = dbconnection::checkPin(pincode);
        if(attempts == 0)
        {
            if(dbconnection::getIban())
            {
                ui->labelPinError->setText("");
                ui->stackedWidget->setCurrentIndex(3);
            }
            else
            {
                ui->labelPinError->setText("Er is iets fout gegaan. Neem contact op met uw bank.");
            }
        }
        else
        {
            if(!dbconnection::blocked())
            {
                ui->labelPinError->setText("Pincode onjuist. U heeft nog "+QByteArray::number(3-attempts)+" pogingen over");
            }
            else
            {
                ui->buttonStop->setVisible(false);
                ui->labelErrorMessage->setText("Pincode 3x onjuist ingevoerd. Uw pas is geblokkeerd.");
                ui->stackedWidget->setCurrentIndex(9);
                QTime dieTime= QTime::currentTime().addSecs(5);
                while (QTime::currentTime() < dieTime) {
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                }
                on_buttonStop_pressed();
            }
        }
        pincode = "";
        ui->pwPincode->setText("");
    }
}

//Menu screen buttons
void MainWindow::on_buttonSaldo_pressed()
{
    float saldo = dbconnection::getSaldo();
    dbconnection::updateTransaction(0);
    dbconnection::newAction("Saldo retrieved", 0);
    ui->labelSaldo->setText(QLocale().toCurrencyString(saldo));
    ui->stackedWidget->setCurrentIndex(4);
    ui->buttonBack->setVisible(true);
}

void MainWindow::on_buttonOpnemen_pressed()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->buttonBack->setVisible(true);
}

void MainWindow::on_buttonSnel_pressed()
{
    if(dbconnection::withdraw(70)){
        dbconnection::updateTransaction(70);
        dbconnection::newAction("Money withdrawn", 70);
        ui->stackedWidget->setCurrentIndex(8);
        ui->buttonBack->setVisible(false);
        ui->buttonStop->setVisible(false);
        QTime dieTime= QTime::currentTime().addSecs(5);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        on_buttonStop_pressed();
    } else {
        ui->labelMenuError->setText("Onvoldoende saldo");
    }
}

//Opnemen screen buttons
void MainWindow::on_button100_pressed()
{
    if(dbconnection::withdraw(100)){
        dbconnection::updateTransaction(100);
        dbconnection::newAction("Money withdrawn", 100);
        ui->stackedWidget->setCurrentIndex(6);
        ui->buttonBack->setVisible(false);
        ui->buttonStop->setVisible(false);
    } else {
        ui->labelOpnemenError->setText("Onvoldoende saldo");
    }
}

void MainWindow::on_button20_pressed()
{
    if(dbconnection::withdraw(20)){
        dbconnection::updateTransaction(20);
        dbconnection::newAction("Money withdrawn", 20);
        ui->stackedWidget->setCurrentIndex(6);
        ui->buttonBack->setVisible(false);
        ui->buttonStop->setVisible(false);
    } else {
        ui->labelOpnemenError->setText("Onvoldoende saldo");
    }
}

void MainWindow::on_button200_pressed()
{
    if(dbconnection::withdraw(200)){
        dbconnection::updateTransaction(200);
        dbconnection::newAction("Money withdrawn", 200);
        ui->stackedWidget->setCurrentIndex(6);
        ui->buttonBack->setVisible(false);
        ui->buttonStop->setVisible(false);
    } else {
        ui->labelOpnemenError->setText("Onvoldoende saldo");
    }
}

void MainWindow::on_button50_pressed()
{
    if(dbconnection::withdraw(50)){
        dbconnection::updateTransaction(50);
        dbconnection::newAction("Money withdrawn", 50);
        ui->stackedWidget->setCurrentIndex(6);
        ui->buttonBack->setVisible(false);
        ui->buttonStop->setVisible(false);
    } else {
        ui->labelOpnemenError->setText("Onvoldoende saldo");
    }
}

void MainWindow::on_button500_pressed()
{
    if(dbconnection::withdraw(500)){
        dbconnection::updateTransaction(500);
        dbconnection::newAction("Money withdrawn", 500);
        ui->stackedWidget->setCurrentIndex(6);
        ui->buttonBack->setVisible(false);
        ui->buttonStop->setVisible(false);
    } else {
        ui->labelOpnemenError->setText("Onvoldoende saldo");
    }
}

void MainWindow::on_buttonAnders_pressed()
{
    ui->stackedWidget->setCurrentIndex(7);
}

//Anders screen buttons
void MainWindow::on_buttonBedragCorrectie_pressed()
{}

void MainWindow::on_buttonBedragConfirm_pressed()
{
    anderBedrag = ui->txtBedrag->text();
    if(anderBedrag.toInt() % 10 == 0){
        if(anderBedrag.toInt() > 9 && anderBedrag.toInt() < 501){
            qDebug(QByteArray::number(anderBedrag.toFloat()));
            if(dbconnection::withdraw(anderBedrag.toFloat())){
                dbconnection::updateTransaction(anderBedrag.toFloat());
                dbconnection::newAction("Money withdrawn", anderBedrag.toFloat());
                ui->stackedWidget->setCurrentIndex(6);
                ui->buttonBack->setVisible(false);
                ui->buttonStop->setVisible(false);
            } else {
                ui->labelAndersError->setText("Onvoldoende saldo");
            }
        } else {
            ui->labelAndersError->setText("Bedrag moet tussen de 10 en 500 liggen");
        }
    } else {
        ui->labelAndersError->setText("Bedrag moet een veelvoud zijn van 10");
    }
    anderBedrag = "";
    ui->txtBedrag->setText("");
}

//Bon screen buttons
void MainWindow::on_buttonBonYes_pressed()
{
    ui->stackedWidget->setCurrentIndex(8);
    QTime dieTime= QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    on_buttonStop_pressed();
}

void MainWindow::on_buttonBonNo_pressed()
{
    ui->stackedWidget->setCurrentIndex(8);
    QTime dieTime= QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    on_buttonStop_pressed();
}

//DEBUG BUTTONS
void MainWindow::on_buttonSkipDebug_pressed()
{ 
    if(dbconnection::card("505B8A7C")){
        dbconnection::createTransaction();
        if(!dbconnection::blocked()){
            dbconnection::newAction("Card scan succesful", 0);
            ui->labelScanError->setText("");
            ui->stackedWidget->setCurrentIndex(2);
        } else {
            dbconnection::newAction("Card scan failed. Blocked", 0);
            ui->labelScanError->setText("Kaart geblokkeerd. Neem contact op met uw bank.");
        }
    }
}

void MainWindow::on_buttonSkipDebug_pressed(QByteArray nuid)
{
    if(dbconnection::card(nuid)){
        dbconnection::createTransaction();
        if(!dbconnection::blocked()){
            dbconnection::newAction("Card scan succesful", 0);
            ui->stackedWidget->setCurrentIndex(2);
        } else {
            dbconnection::newAction("Card scan failed. Blocked", 0);
            ui->labelScanError->setText("Kaart geblokkeerd. Neem contact op met uw bank");
        }
    }
}

void MainWindow::on_buttonRestartDebug_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//Get current window
int MainWindow::getIndex()
{
    return ui->stackedWidget->currentIndex();
}

//Inserting stuff
void MainWindow::insertPincode(QByteArray key){
    if(key == "A"){
        if(pincode.length()>0){
            pincode.remove(pincode.length() -1, 1);
        }
    }
    else {
        if(pincode.length()<4){
            pincode.append(key);
        }
    }
    ui->pwPincode->setText(pincode);
}

void MainWindow::insertAnderBedrag(QByteArray key){
    if(key == "A"){
        if(anderBedrag.length()>0){
            anderBedrag.remove(anderBedrag.length() -1, 1);
        }
    }
    else {
        if(anderBedrag.length()<3){
            anderBedrag.append(key);
        }
    }
    ui->txtBedrag->setText(anderBedrag);
}

//Close window
void MainWindow::closeEvent(QCloseEvent *event)
{
    SerialRead::closePort();
    dbconnection::close();
    event->accept();
}
