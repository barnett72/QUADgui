#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define BAUD_RATE_XBEE 57600

class Receiver
{
    public:
        Receiver();
        int8_t readChar();
        std::string getLine();
    private:
        int serialOpen (const char *device, const int baud);
        int handle;
};


#endif // RECEIVER_H
