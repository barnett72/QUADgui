#include "updatedisplay.h"

using namespace std;

UpdateDisplay::UpdateDisplay(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<std::string>("std::string");
}


void UpdateDisplay::run()
{

    length = 0;
    i = 0;
    const char * directory = "/receive";
    string file;
    bool isValidFile = false;

    fd = inotify_init();
    if(fd < 0)
    {
        onMsgCenterChanged("inotify_init error");
    }

    wd = inotify_add_watch(fd, directory, IN_CREATE);


    while(1)
    {
        length = read(fd, buffer, BUF_LEN);
        if(length < 0)
        {
            onMsgCenterChanged("read error");
        }
        i=0;

        while(i < length)
        {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            if(event->len)
            {
                if(event->mask & IN_CREATE)
                {
                    if(!(event->mask & IN_ISDIR))
                    {
                        file = event->name;
                        isValidFile = true;
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }

        if(isValidFile)
        {
            usleep(100000); // i really didn't wan't to do this :(
            string filePath = string(directory) + "/" + file;

            string line;
            ifstream myFile(filePath.c_str());
            bool isReadingMsg = false;
            int messageLength = 0;
            int messageLineIndex = 0;

            if(myFile.is_open())
            {
                while ( getline (myFile, line) )
                {
                    if(!isReadingMsg)
                    {
                        istringstream iss(line);
                        vector<string> strings;
                        copy(std::istream_iterator<std::string>(iss),
                             std::istream_iterator<std::string>(),
                             std::back_inserter(strings));

                        bool isValidLine = false;

                        int size = strings.size();
                        if(size > 0)
                            isValidLine = true;

                        if(isValidLine)
                        {
                            string s = strings.at(0);
                            if(s == "end") { /* Do nothing, just catch */ }
                            else if(s == "msg")
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
                            }
                            else if(s == "lcv")
                            {
                                emit onLowCellVoltageChanged(strings.at(1));
                            }
                            else if(s == "thr")
                            {
                                emit onThrottleChanged(strings.at(1));
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
                            else if(s == "lat")
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
                                onMsgCenterChanged("UI: Err Prsng Line");
                            }
                        }
                    }
                    else
                    {
                        messageLineIndex++;
                        onMsgCenterChanged(line);
                        if(messageLineIndex>=messageLength)
                        {
                            messageLineIndex = 0;
                            isReadingMsg = false;
                        }
                    }
                }
                myFile.close();
                if(remove(filePath.c_str()) != 0 )
                   onMsgCenterChanged("UI: cldnt dlt fil");
                else
                    isValidFile = false;
            }
            else
            {
                onMsgCenterChanged("UI: Err open file");
            }
        }
    }
    (void) inotify_rm_watch(fd, wd);
    (void) close(fd);
}
