#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnBack_pressed();

    void on_btnStop_pressed();



    void on_btnStart_pressed();



    void on_btnPinCorrection_pressed();

    void on_btnPinConfirm_pressed();



    void on_btnSaldo_pressed();

    void on_btnOpnemen_pressed();

    void on_btnSnel_pressed();



    void on_btn20_pressed();

    void on_btn100_pressed();

    void on_btn500_pressed();

    void on_btnAnders_pressed();



    void on_btnBedragCorrectie_pressed();

    void on_btnBedragConfirm_pressed();



    void on_btnBonYes_pressed();

    void on_btnBonNo_pressed();



    void on_btnSkipDebug_pressed();

    void on_btnRestartDebug_pressed();
	
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
