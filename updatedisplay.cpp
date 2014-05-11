#include "updatedisplay.h"

using namespace std;

UpdateDisplay::UpdateDisplay(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<uint32_t>("uint32_t");

    lowCellV = 0.0;
    totalV = 0.0;
    startVoltage = 0.0;
    startTime = 0;
    throttle = 0;
    totalTime = 0;

    isFlying = false;

    ft = new flighttime(this);
    connect(ft, SIGNAL(onUpdateFlightTime(uint32_t)), this, SLOT(SetFlightTime(uint32_t)));
    ft->start();
}


void UpdateDisplay::run()
{
    Receiver* receiver = new Receiver();

    bool isReadingMsg = false;
    int messageLength = 0;
    int messageLineIndex = 0;    

    bool isValidLine;
    int size;

    while(1)
    {
        //cout << "attempting to get line" << endl;
        string line = receiver->getLine();
        //cout << "got line '" << line << "'" << endl;


        if(!isReadingMsg)
        {
            istringstream iss(line);
            vector<string> strings;
            copy(std::istream_iterator<std::string>(iss),
                 std::istream_iterator<std::string>(),
                 std::back_inserter(strings));

            isValidLine = false;

            size = strings.size();
            if(size > 0)
                isValidLine = true;

            //cout << "is valid line? " << isValidLine << endl;
            if(isValidLine)
            {
                string s = strings.at(0);
                //cout << "s value: '" << s << "'" << endl;
                if(size == 2)
                {
                    if(s == "msg")
                    {
                        messageLength = atoi(strings.at(1).c_str());
                        isReadingMsg = true;
                    }
                    else if(s == "hgt")
                    {
                        emit onHeightChanged(strings.at(1));
                    }
                    else if(s == "tot")
                    {
                        emit onTotalVoltageChanged(strings.at(1));
                        totalV = atof(strings.at(1).c_str());
                    }
                    else if(s == "lcv")
                    {
                        emit onLowCellVoltageChanged(strings.at(1));
                        lowCellV = atof(strings.at(1).c_str());
                    }
                    else if(s == "thr")
                    {
                        emit onThrottleChanged(strings.at(1));
                        throttle = atoi(strings.at(1).c_str());
                    }
                    else if(s == "spd")
                    {
                        emit onSpeedChanged(strings.at(1));
                    }
                    else if(s == "dir")
                    {
                        emit onDirectionChanged(strings.at(1));
                    }
                    else if(s == "ld1")
                    {
                        string s = strings.at(1);
                        if(s=="1")
                            onLed1Changed(true);
                        else
                            onLed1Changed(false);
                    }
                    else if(s == "ld2")
                    {
                        string s = strings.at(1);
                        if(s=="1")
                            onLed2Changed(true);
                        else
                            onLed2Changed(false);
                    }
                    else if(s == "sv1")
                    {
                        onSrv1Changed(strings.at(1));
                    }
                    else if(s == "sv2")
                    {
                        onSrv2Changed(strings.at(1));
                    }
                    else if(s == "pan")
                    {
                        onPanChanged(strings.at(1));
                    }
                    else if(s == "tlt")
                    {
                        onTiltChanged(strings.at(1));
                    }
                    else
                    {
                        onMsgCenterChanged(line);
                        onMsgCenterChanged("Err Parsing Line:");
                    }
                }
                else if((size >= 2) && (size <= 6))
                {
                    if(s == "lat")
                    {
                        int stringsSize = strings.size();
                        string lat;
                        for(int i=1; i<stringsSize; i++)
                        {
                            lat += strings.at(i);
                            if(i < (stringsSize-2))
                                lat += " ";
                        }
                        onLatitdueChanged(lat);
                    }
                    else if(s == "lon")
                    {
                        int stringsSize = strings.size();
                        string lon;
                        for(int i=1; i<stringsSize; i++)
                        {
                            lon += strings.at(i);
                            if(i < (stringsSize-2))
                                lon += " ";
                        }
                        onLongitudeChanged(lon);
                    }
                    else
                    {
                        onMsgCenterChanged(line);
                        onMsgCenterChanged("Err Parsing Line:");
                    }
                }
                else
                {
                    onMsgCenterChanged(line);
                    onMsgCenterChanged("Err Parsing Line:");
                }
            }
        }
        else
        {
            //cout << "got message chunk: '" << line << "'" << endl;
            messageLineIndex++;
            onMsgCenterChanged(line);
            if(messageLineIndex>=messageLength)
            {
                messageLineIndex = 0;
                isReadingMsg = false;
            }
        }
    }
}


void UpdateDisplay::SetFlightTime(uint32_t time)
{
    if(!isFlying && (throttle > 40))
    {
       startTime = time;
       totalTime++;
       startVoltage = totalV;
       isFlying = true;
    }
    if(isFlying)
    {
        emit onFlightTimeChanged(formatTime(totalTime++));
        int diff = time - startTime;
        if(diff > 10)
        {
            int timeLeft = (int)(diff/(abs(startVoltage - totalV)))*(totalV - 13.8);
            emit onRemainingTimeChanged(formatTime(timeLeft));
            int remaining = (int)(timeLeft / (timeLeft + totalTime))*100;
            emit onBatteryRemainingChanged(remaining);
        }

    }
    if(throttle < 20)
    {
        isFlying = false;
    }
}

std::string UpdateDisplay::formatTime(int seconds)
{
    int hours = (int)(seconds / 3600);
    int minutes = (int)((seconds % 3600) / 60);
    int secs = (int)(seconds % 60);
    QTime time(hours, minutes, secs);
    return time.toString("mm:ss").toUtf8().constData();
}
