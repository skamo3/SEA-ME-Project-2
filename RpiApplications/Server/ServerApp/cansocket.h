#ifndef CANSOCKET_H
#define CANSOCKET_H

#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <QString>

# define CAN_FRAME_MAX_LEN 8

class CANSocket
{
public:
        CANSocket();
        CANSocket(CANSocket const &origin);
        CANSocket &operator=(CANSocket const &origin);
        ~CANSocket();

        void initSocket(const QString &ifname);
        int readData(struct Data &dataFrame);

        int getSocketFD() const;
        struct can_frame getCanFrame() const;

private:
    int socketFD;
    struct can_frame canFrame;
};

#endif // CANSOCKET_H
