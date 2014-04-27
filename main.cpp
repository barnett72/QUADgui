#include "mainwindow.h"
#include "updatedisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.move(1,8);
    w.show();

//    w.SetTotalVoltage("77.77");
//    w.SetLowCellVoltage("0.00");
//    w.SetLongitude("N 99° 11' 99.99");
//    w.SetLatitude("W 99° 11' 9.999");
//    w.SetSpeed("8.88");
//    w.SetDirection("72");
//    w.SetRemainingTime("99:99");
//    w.SetFlightTime("00:00");
//    w.SetBatteryRemaining(72);
//    w.SetThrottleLabel("73%");
//    w.SetThrottleBarValue(73);
//    w.SetDistance("727.2'");
//    w.SetHeight("72.7'");
//    w.SetLed1(true);
//    w.SetLed2(true);
//    w.SetSrv1("99%");
//    w.SetSrv2("88%");
//    w.SetPan("77%");
//    w.SetTilt("66%");

//    UpdateDisplay updateDisplay;
//    updateDisplay.start();

//    w.AddStringToMsgCenter("Line 1");
//    w.AddStringToMsgCenter("Line 2");
//    w.AddStringToMsgCenter("Line 3");
//    w.AddStringToMsgCenter("Line 4");
//    w.AddStringToMsgCenter("Line 5");
//    w.AddStringToMsgCenter("Line 6");
//    w.AddStringToMsgCenter("Line 7");
//    w.AddStringToMsgCenter("Line 8");
//    w.AddStringToMsgCenter("Line 9");
//    w.AddStringToMsgCenter("Line 10");

    return a.exec();
}
