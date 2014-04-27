#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vectorIndex = 0;

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

    ui->messageCenter->viewport()->setAutoFillBackground(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetTotalVoltage(std::string voltage)
{
    ui->label_batteryTotal->setText(QString::fromStdString(voltage));
}

void MainWindow::SetLowCellVoltage(std::string voltage)
{
    ui->label_batteryLowCell->setText(QString::fromStdString(voltage));
}

void MainWindow::SetLongitude(std::string longitude)
{
    ui->label_longitude->setText(QString::fromStdString(longitude));
}

void MainWindow::SetLatitude(std::string latitude)
{
    ui->label_latitude->setText(QString::fromStdString(latitude));
}

void MainWindow::SetSpeed(std::string speed)
{
    this->speed = speed;
    ui->label_speed->setText(QString::fromStdString(speed + "kn @ " + direction + "°"));
}

void MainWindow::SetDirection(std::string direction)
{
    this->direction = direction;
    ui->label_speed->setText(QString::fromStdString(speed + "kn @ " + direction + "°"));
}

void MainWindow::SetRemainingTime(std::string time)
{
    ui->label_timeRemaining->setText(QString::fromStdString(time));
}

void MainWindow::SetFlightTime(std::string time)
{
    ui->label_timeFlight->setText(QString::fromStdString(time));
}

void MainWindow::SetBatteryRemaining(int percent)
{
    ui->progressBar_battery->setValue(percent);
}

void MainWindow::SetThrottleLabel(std::string val)
{
    ui->label_throttleValue->setText(QString::fromStdString(val));
}

void MainWindow::SetThrottleBarValue(int val)
{
    ui->progressBar_throttle->setValue(val);
}

void MainWindow::SetDistance(std::string distance)
{
    ui->label_distance->setText(QString::fromStdString(distance));
}

void MainWindow::SetHeight(std::string height)
{
     ui->label_height->setText(QString::fromStdString(height));
}

void MainWindow::SetLed1(bool onOff)
{
    ui->radioButton_led1->setChecked(onOff);
}

void MainWindow::SetLed2(bool onOff)
{
    ui->radioButton_led2->setChecked(onOff);
}

void MainWindow::SetSrv1(std::string val)
{
    ui->label_srv1->setText(QString::fromStdString(val));
}

void MainWindow::SetSrv2(std::string val)
{
    ui->label_srv2->setText(QString::fromStdString(val));
}

void MainWindow::SetPan(std::string val)
{
    ui->label_srvPan->setText(QString::fromStdString(val));
}

void MainWindow::SetTilt(std::string val)
{
    ui->label_srvTilt->setText(QString::fromStdString(val));
}

void MainWindow::AddStringToMsgCenter(std::string msg)
{
    ui->messageCenter->clear();
    if(msgCenterText.size() < NUM_ROWS)
    {
        msgCenterText.append(QString::fromStdString(msg));
        for(int i=vectorIndex; i>=0; i--)
        {
            ui->messageCenter->insertPlainText(msgCenterText.at(i) + "\n");
        }
    }
    else
    {
        msgCenterText.replace((vectorIndex%NUM_ROWS), QString::fromStdString(msg));
        for(int i=0; i<NUM_ROWS; i++)
        {
            ui->messageCenter->insertPlainText(msgCenterText.at((vectorIndex-i)%NUM_ROWS) + "\n");
        }
    }
    vectorIndex++;
}
