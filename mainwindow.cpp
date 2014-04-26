#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Init for stuffs that isn't values
    ui->label_batteryTotal->setStyleSheet("QLabel { background-color : darkGreen; color : white; }");
    ui->label_batteryTotalLabel->setStyleSheet("QLabel { background-color : darkGreen; color : white; }");

    ui->label_batteryLowCell->setStyleSheet("QLabel { background-color : green; color : white; }");
    ui->label_batteryLowCellLabel->setStyleSheet("QLabel { background-color : green; color : white; }");

    ui->label_timeRemaining->setStyleSheet("QLabel { background-color : green; color : white; }");
    ui->label_timeRemainingLabel->setStyleSheet("QLabel { background-color : green; color : white; }");

    ui->label_distance->setStyleSheet("QLabel { background-color : darkBlue; color : white; }");
    ui->label_distanceText->setStyleSheet("QLabel { background-color : darkBlue; color : white; }");

    ui->label_height->setStyleSheet("QLabel { background-color : darkCyan; color : white; }");
    ui->label_heightText->setStyleSheet("QLabel { background-color : darkCyan; color : white; }");

    //QPalette* palette = new QPalette();
    //palette->setBrush(QPalette::Base, *(new QBrush(*(new QPixmap("quad_textboxLogo.png")))));
    //ui->messageCenter->setPalette(*palette);
    //ui->messageCenter->show();
    //ui->messageCenter->setStyleSheet("background-image : url(:/quad_textboxLogo.png); background-attachment : fixed;");
    //ui->messageCenter->setStyleSheet("background-color : red");
    ui->messageCenter->viewport()->setAutoFillBackground(false);

    // Voltage Total
    ui->label_batteryTotal->setText("15.62");
    // Voltage lowest cell
    ui->label_batteryLowCell->setText("3.87");
    // Battery remaining
    ui->progressBar_battery->setValue(98);
    // Time in flight
    ui->label_timeFlight->setText("11:23");

    // Throttle progress bar
    ui->progressBar_throttle->setValue(98);
    // Throttle label value
    ui->label_throttleValue->setText("98%");

    // Distance value
    ui->label_distance->setText("888.8'");
    // Height above ground
    ui->label_height->setText("18.8'");

    // Set LED1 on
    ui->radioButton_led1->setChecked(true);
    // Set LED2 off
    ui->radioButton_led2->setChecked(false);

    // longitude
    ui->label_longitude->setText(QString::fromUtf8("N 99° 99' 99.99"));
    // latitude
    ui->label_latitude->setText(QString::fromUtf8("W 99° 99' 9.999"));
    // speed
    ui->label_speed->setText(QString::fromUtf8("99.99 kn @ 999.9°"));

    ui->messageCenter->insertPlainText("Line 1\nLine 2\nLine 3\nLine 4\nLine 5\nLine 6");

}

MainWindow::~MainWindow()
{
    delete ui;
}
