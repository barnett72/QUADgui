#ifndef UPDATEDISPLAY_H
#define UPDATEDISPLAY_H

#include <QThread>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <cmath>

#include "receiver.h"
#include "flighttime.h"

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))
#define LINE_LEN 256
#define SUM_ARRAY_LEN 10

class UpdateDisplay : public QThread
{
    Q_OBJECT
public:
    explicit UpdateDisplay(QObject *parent = 0);
    void run();
    bool Stop;
    flighttime *ft;
signals:
    void onTotalVoltageChanged(std::string voltage);
    void onLowCellVoltageChanged(std::string voltage);
    void onLongitudeChanged(std::string longitude);
    void onLatitdueChanged(std::string latitude);
    void onSpeedChanged(std::string speed);
    void onDirectionChanged(std::string direction);
    void onRemainingTimeChanged(std::string time);
    void onFlightTimeChanged(std::string time);
    void onBatteryRemainingChanged(int percent);
    void onThrottleChanged(std::string val);
    void onDistanceChanged(std::string distance);
    void onHeightChanged(std::string height);
    void onLed1Changed(bool onOff);
    void onLed2Changed(bool onOff);
    void onSrv1Changed(std::string val);
    void onSrv2Changed(std::string val);
    void onPanChanged(std::string val);
    void onTiltChanged(std::string val);
    void onMsgCenterChanged(std::string msg);
    void onBatteryColorGreen(void);
    void onBatteryColorYellow(void);
    void onBatteryColorRed(void);
public slots:
    void SetFlightTime(uint32_t time);
private:
    int length, i, fd, wd;
    char buffer[BUF_LEN];
    double lowCellV, totalV, startVoltage;
    int startTime, throttle, totalTime;
    bool isFlying;
    int timeLeft, remaining;
    double vAvg[SUM_ARRAY_LEN];
    std::string formatTime(int seconds);
};

#endif // UPDATEDISPLAY_H
