#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "updatedisplay.h"

#define NUM_ROWS 6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    UpdateDisplay *updateDisplay;
private:
    Ui::MainWindow *ui;
    std::string speed;
    std::string direction;
    QVector<QString> msgCenterText;
    int vectorIndex;
public slots:
    void SetTotalVoltage(std::string voltage);
    void SetLowCellVoltage(std::string voltage);
    void SetLongitude(std::string longitude);
    void SetLatitude(std::string latitude);
    void SetSpeed(std::string speed);
    void SetDirection(std::string direction);
    void SetRemainingTime(std::string time);
    void SetFlightTime(std::string time);
    void SetBatteryRemaining(int percent);
    void SetThrottle(std::string val);
    void SetDistance(std::string distance);
    void SetHeight(std::string height);
    void SetLed1(bool onOff);
    void SetLed2(bool onOff);
    void SetSrv1(std::string val);
    void SetSrv2(std::string val);
    void SetPan(std::string val);
    void SetTilt(std::string val);
    void AddStringToMsgCenter(std::string msg);
};

#endif // MAINWINDOW_H
