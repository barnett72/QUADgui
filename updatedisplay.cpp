#include "updatedisplay.h"

UpdateDisplay::UpdateDisplay(QObject *parent) :
    QThread(parent)
{
    qRegisterMetaType<std::string>("std::string");
}


void UpdateDisplay::run()
{
    emit onMsgCenterChanged("This is a message");
    sleep(1);
    emit onMsgCenterChanged("And another");
    sleep(1);
    emit onMsgCenterChanged("Msg 3");
    sleep(1);
    emit onMsgCenterChanged("Msg 4");
    sleep(1);
    emit onMsgCenterChanged("Msg 5");
}
