#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Voltage
    ui->lcdNumber_volts->display(12.34);
    // Battery remaining
    ui->progressBar_battery->setValue(98);
    // Time in flight
    ui->label_time->setText("11:23");

    // Throttle progress bar
    ui->progressBar_throttle->setValue(98);
    // Throttle label value
    ui->label_throttleValue->setText("98%");

    // Distance value
    ui->label_distance->setText("199.9'");
    // Height above ground
    ui->label_height->setText("19.9'");

    // Set LED1 on
    ui->radioButton_led1->setChecked(true);
    // Set LED2 off
    ui->radioButton_led2->setChecked(false);

    // Servo 1 progress bar
    ui->progressBar_srv1->setValue(50);
    // Servo 2 progress bar
    ui->progressBar_srv2->setValue(50);

    // longitude
    ui->label_longitude->setText("N 99° 99' 99.99");
    // latitude
    ui->label_latitude->setText("W 99° 99' 9.999");
    // speed
    ui->label_speed->setText("99.99 kn @ 999.9°");

}

MainWindow::~MainWindow()
{
    delete ui;
}
