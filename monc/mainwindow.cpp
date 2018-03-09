#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->stackedWidget->setCurrentIndex(0);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

    QWidget::showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//MainWindow buttons



void MainWindow::on_btnBack_pressed()

{

    switch(ui->stackedWidget->currentIndex()){

        case 4:

            ui->stackedWidget->setCurrentIndex(3);

            ui->btnBack->setVisible(false);

            break;

        case 5:

            ui->stackedWidget->setCurrentIndex(3);

            ui->btnBack->setVisible(false);

            break;

        case 7:

            ui->stackedWidget->setCurrentIndex(5);

            break;

    }

}



void MainWindow::on_btnStop_pressed()

{

    ui->stackedWidget->setCurrentIndex(0);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

}





//Start screen buttons



void MainWindow::on_btnStart_pressed()

{

    ui->stackedWidget->setCurrentIndex(1);

    ui->btnStop->setVisible(true);

}





//Pincode screen buttons



void MainWindow::on_btnPinCorrection_pressed()

{



}



void MainWindow::on_btnPinConfirm_pressed()

{

    ui->stackedWidget->setCurrentIndex(3);

}





//Menu screen buttons



void MainWindow::on_btnSaldo_pressed()

{

    ui->stackedWidget->setCurrentIndex(4);

    ui->btnBack->setVisible(true);

}



void MainWindow::on_btnOpnemen_pressed()

{

    ui->stackedWidget->setCurrentIndex(5);

    ui->btnBack->setVisible(true);

}



void MainWindow::on_btnSnel_pressed()

{

    ui->stackedWidget->setCurrentIndex(6);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

}





//Opnemen screen buttons



void MainWindow::on_btn20_pressed()

{

    ui->stackedWidget->setCurrentIndex(6);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

}



void MainWindow::on_btn100_pressed()

{

    ui->stackedWidget->setCurrentIndex(6);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

}



void MainWindow::on_btn500_pressed()

{

    ui->stackedWidget->setCurrentIndex(6);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

}



void MainWindow::on_btnAnders_pressed()

{

    ui->stackedWidget->setCurrentIndex(7);

}



//Anders screen buttons



void MainWindow::on_btnBedragCorrectie_pressed()

{



}



void MainWindow::on_btnBedragConfirm_pressed()

{

    ui->stackedWidget->setCurrentIndex(6);

    ui->btnBack->setVisible(false);

    ui->btnStop->setVisible(false);

}





//Bon screen buttons



void MainWindow::on_btnBonYes_pressed()

{

    ui->stackedWidget->setCurrentIndex(8);

}



void MainWindow::on_btnBonNo_pressed()

{

    ui->stackedWidget->setCurrentIndex(8);

}





//DEBUG BUTTONS



void MainWindow::on_btnSkipDebug_pressed()

{

    ui->stackedWidget->setCurrentIndex(2);

}



void MainWindow::on_btnRestartDebug_pressed()

{

    ui->stackedWidget->setCurrentIndex(0);

}
