#ifndef UPDATEDISPLAY_H
#define UPDATEDISPLAY_H

#include <QThread>
#include <QtCore>

class UpdateDisplay : public QThread
{
    Q_OBJECT
public:
    explicit UpdateDisplay(QObject *parent = 0);
    void run();
    bool Stop;
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
public slots:

};

#endif // UPDATEDISPLAY_H
