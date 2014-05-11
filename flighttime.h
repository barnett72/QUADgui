#ifndef FLIGHTTIME_H
#define FLIGHTTIME_H

#include <QThread>
#include <stdint.h>

class flighttime : public QThread
{
    Q_OBJECT
public:
    explicit flighttime(QObject *parent = 0);
    void run();
    bool Stop;
signals:
    void onUpdateFlightTime(uint32_t seconds);
public slots:

};

#endif // FLIGHTTIME_H
