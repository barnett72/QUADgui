#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "updatedisplay.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    speed = "0.0";
    direction = "---";

    updateDisplay = new UpdateDisplay(this);

    connect(updateDisplay, SIGNAL(onTotalVoltageChanged(std::string)), this, SLOT(SetTotalVoltage(std::string)));
    connect(updateDisplay, SIGNAL(onLowCellVoltageChanged(std::string)), this, SLOT(SetLowCellVoltage(std::string)));
    connect(updateDisplay, SIGNAL(onLongitudeChanged(std::string)), this, SLOT(SetLongitude(std::string)));
    connect(updateDisplay, SIGNAL(onLatitdueChanged(std::string)), this, SLOT(SetLatitude(std::string)));
    connect(updateDisplay, SIGNAL(onSpeedChanged(std::string)), this, SLOT(SetSpeed(std::string)));
    connect(updateDisplay, SIGNAL(onDirectionChanged(std::string)), this, SLOT(SetDirection(std::string)));
    connect(updateDisplay, SIGNAL(onRemainingTimeChanged(std::string)), this, SLOT(SetRemainingTime(std::string)));
    connect(updateDisplay, SIGNAL(onFlightTimeChanged(std::string)), this, SLOT(SetFlightTime(std::string)));
    connect(updateDisplay, SIGNAL(onBatteryRemainingChanged(int)), this, SLOT(SetBatteryRemaining(int)));
    connect(updateDisplay, SIGNAL(onThrottleChanged(std::string)), this, SLOT(SetThrottle(std::string)));
    connect(updateDisplay, SIGNAL(onDistanceChanged(std::string)), this, SLOT(SetDistance(std::string)));
    connect(updateDisplay, SIGNAL(onHeightChanged(std::string)), this, SLOT(SetHeight(std::string)));
    connect(updateDisplay, SIGNAL(onLed1Changed(bool)), this, SLOT(SetLed1(bool)));
    connect(updateDisplay, SIGNAL(onLed2Changed(bool)), this, SLOT(SetLed2(bool)));
    connect(updateDisplay, SIGNAL(onSrv1Changed(std::string)), this, SLOT(SetSrv1(std::string)));
    connect(updateDisplay, SIGNAL(onSrv2Changed(std::string)), this, SLOT(SetSrv2(std::string)));
    connect(updateDisplay, SIGNAL(onPanChanged(std::string)), this, SLOT(SetPan(std::string)));
    connect(updateDisplay, SIGNAL(onTiltChanged(std::string)), this, SLOT(SetTilt(std::string)));
    connect(updateDisplay, SIGNAL(onMsgCenterChanged(std::string)), this, SLOT(AddStringToMsgCenter(std::string)));
    connect(updateDisplay, SIGNAL(onBatteryColorGreen()), this, SLOT(SetBatteryColorsGreen()));
    connect(updateDisplay, SIGNAL(onBatteryColorYellow()), this, SLOT(SetBatteryColorsYellow()));
    connect(updateDisplay, SIGNAL(onBatteryColorRed()), this, SLOT(SetBatteryColorsRed()));

    updateDisplay->start();

    vectorIndex = 0;

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
    double cellVoltage = atof(voltage.c_str());
    if(cellVoltage > 3.6)
    {
        SetBatteryColorsGreen();
    }
    else if(cellVoltage > 3.4)
    {
        SetBatteryColorsYellow();
    }
    else
    {
        SetBatteryColorsRed();
    }
    ui->label_batteryLowCell->setText(QString::fromStdString(voltage));
}

void MainWindow::SetLongitude(std::string longitude)
{
    ui->label_longitude->setText(QString::fromUtf8(longitude.c_str()));
}

void MainWindow::SetLatitude(std::string latitude)
{
    ui->label_latitude->setText(QString::fromUtf8(latitude.c_str()));
}

void MainWindow::SetSpeed(std::string speed)
{
    this->speed = speed;
    ui->label_speed->setText(QString::fromUtf8(getSpeedDirText(speed, direction).c_str()));
}

void MainWindow::SetDirection(std::string direction)
{
    this->direction = direction;
    ui->label_speed->setText(QString::fromUtf8(getSpeedDirText(speed, direction).c_str()));
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

void MainWindow::SetThrottle(std::string val)
{
    ui->label_throttleValue->setText(QString::fromStdString(val) + "%");
    ui->progressBar_throttle->setValue(atoi(val.c_str()));
}

void MainWindow::SetDistance(std::string distance)
{
    ui->label_distance->setText(QString::fromStdString(distance) + "'");
}

void MainWindow::SetHeight(std::string height)
{
     ui->label_height->setText(QString::fromStdString(height) + "'");
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
    ui->label_srv1->setText(QString::fromStdString(val) + "%");
}

void MainWindow::SetSrv2(std::string val)
{
    ui->label_srv2->setText(QString::fromStdString(val) + "%");
}

void MainWindow::SetPan(std::string val)
{
    ui->label_srvPan->setText(QString::fromStdString(val) + "%");
}

void MainWindow::SetTilt(std::string val)
{
    ui->label_srvTilt->setText(QString::fromStdString(val) + "%");
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
    if(vectorIndex == (NUM_ROWS*100))
        vectorIndex = 0;
}

std::string MainWindow::getSpeedDirText(std::string speed, std::string direction)
{
    std::string str = speed + "kn @ " + direction + "°";
    return str;
}

void MainWindow::SetBatteryColorsGreen()
{
    ui->label_batteryTotal->setStyleSheet("QLabel { background-color : darkGreen; color : white; }");
    ui->label_batteryTotalLabel->setStyleSheet("QLabel { background-color : darkGreen; color : white; }");

    ui->label_batteryLowCell->setStyleSheet("QLabel { background-color : green; color : white; }");
    ui->label_batteryLowCellLabel->setStyleSheet("QLabel { background-color : green; color : white; }");

    ui->label_timeRemaining->setStyleSheet("QLabel { background-color : green; color : white; }");
    ui->label_timeRemainingLabel->setStyleSheet("QLabel { background-color : green; color : white; }");
}

void MainWindow::SetBatteryColorsYellow()
{
    ui->label_batteryTotal->setStyleSheet("QLabel { background-color : #D0D000; color : black; }");
    ui->label_batteryTotalLabel->setStyleSheet("QLabel { background-color : #D0D000; color : black; }");

    ui->label_batteryLowCell->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    ui->label_batteryLowCellLabel->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    ui->label_timeRemaining->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    ui->label_timeRemainingLabel->setStyleSheet("QLabel { background-color : yellow; color : black; }");
}

void MainWindow::SetBatteryColorsRed()
{
    ui->label_batteryTotal->setStyleSheet("QLabel { background-color : darkRed; color : white; }");
    ui->label_batteryTotalLabel->setStyleSheet("QLabel { background-color : darkRed; color : white; }");

    ui->label_batteryLowCell->setStyleSheet("QLabel { background-color : red; color : white; }");
    ui->label_batteryLowCellLabel->setStyleSheet("QLabel { background-color : red; color : white; }");

    ui->label_timeRemaining->setStyleSheet("QLabel { background-color : red; color : white; }");
    ui->label_timeRemainingLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
}
