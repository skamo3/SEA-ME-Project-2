#include "cansocket.h"
#include "printutils.h"
#include "datamanager.h"

CANSocket::CANSocket()
    : socketFD(-1), canFrame{}
{

}

CANSocket::CANSocket(const CANSocket &origin)
{
    if (this != &origin)
    {
        socketFD = origin.socketFD;
        canFrame = origin.canFrame;
    }
}

CANSocket &CANSocket::operator=(const CANSocket &origin)
{
    if (this != &origin)
    {
        socketFD = origin.socketFD;
        canFrame = origin.canFrame;
    }
    return *this;
}

CANSocket::~CANSocket()
{
    if (socketFD > 0)
        close(socketFD);
}

void CANSocket::initSocket(const QString &ifname)
{
    PrintUtils *p = PrintUtils::getInstance();
    socketFD = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socketFD < 0)
    {
        p->PrintErrorText("Failed to socket create", socketFD);
        exit(socketFD);
    }
    p->PrintSuccessText("Success to socket create");

    struct ifreq ifr;
    strcpy(ifr.ifr_name, ifname.toStdString().c_str());
    int ret = ioctl(socketFD, SIOCGIFINDEX, &ifr);
    if (ret < 0)
    {
        p->PrintErrorText("Failed to get CAN interface index", ret);
        exit(ret);
    }
    std::cout << COLOR_BGREEN << "Success to get CAN interface index : "
    << ret << COLOR_RESET << std::endl;

    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(socketFD, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        p->PrintErrorText("Failed to socket bind", ret);
        exit(ret);
    }
    p->PrintSuccessText("Success to socket bind");
}

int CANSocket::readData(struct Data &dataFrame)
{
    PrintUtils *p = PrintUtils::getInstance();
    int rd_byte = read(socketFD, &canFrame, sizeof(canFrame));
    if (rd_byte < 0)
        return p->PrintErrorText("Failed to recieve CAN frame", rd_byte);
    else if (rd_byte < (int)sizeof(struct can_frame))
        return p->PrintErrorText("Incomplete CAN frame is received", rd_byte, rd_byte);
    else if (canFrame.can_dlc > CAN_MAX_DLEN)
        return p->PrintErrorText("Invalid dlc", -1, canFrame.can_dlc);

    std::cout << "ID =>[0x" << std::hex << canFrame.can_id << "] | size{" << int(canFrame.can_dlc) << "}" << std::endl;

    for (int i = 0; i < canFrame.can_dlc; i++)
        std::cout << std::hex << int(canFrame.data[i]) << " : ";
    std::cout << std::endl;

    int rpm = (canFrame.data[0] * 256) + canFrame.data[1];

    std::cout << "RPM : " << std::dec << rpm << std::endl;

    dataFrame.rpm = rpm;
    dataFrame.temp = canFrame.data[2];
    dataFrame.hum = canFrame.data[3];
    dataFrame.battery = canFrame.data[4];

    return rd_byte;
}

int CANSocket::getSocketFD() const
{
    return socketFD;
}

can_frame CANSocket::getCanFrame() const
{
    return canFrame;
}