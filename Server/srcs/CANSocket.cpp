#include "../includes/CANSocket.hpp"
#include "../includes/utils.h"

CANSocket::CANSocket()
: socketFD(-1), canFrame()
{

}

CANSocket::CANSocket(CANSocket const &origin)
: socketFD(origin.socketFD), canFrame(origin.canFrame)
{

}

CANSocket &CANSocket::operator=(CANSocket const &origin)
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

}

void CANSocket::initSocket(std::string const &ifname)
{
    socketFD = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (socketFD < 0)
    {
		PrintErrorText("Failed to socket create", socketFD);
        exit(socketFD);
    }
	PrintSuccessText("Success to socket create");

	struct ifreq ifr;
	strcpy(ifr.ifr_name, ifname.c_str());
	int ret = ioctl(socketFD, SIOCGIFINDEX, &ifr);
	if (ret < 0)
    {
		PrintErrorText("Failed to get CAN interface index", ret);
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
		PrintErrorText("Failed to socket bind", ret);
        exit(ret);
    }
	PrintSuccessText("Success to socket bind");
}

int CANSocket::readData()
{
    int rd_byte = read(socketFD, &canFrame, sizeof(canFrame));
    if (rd_byte < 0)
		return PrintErrorText("Failed to recieve CAN frame", rd_byte);
	else if (rd_byte < (int)sizeof(struct can_frame))
		return PrintErrorText("Incomplete CAN frame is received", rd_byte, rd_byte);
	else if (canFrame.can_dlc > CAN_MAX_DLEN)
		return PrintErrorText("Invalid dlc", -1, canFrame.can_dlc);
	
	std::cout << "ID =>[" << canFrame.can_id << "] | size{" << canFrame.can_dlc << "}" << std::endl;

	for (int i = 0; i < canFrame.can_dlc; i++)
		std::cout << std::setprecision(3) << canFrame.data[i] << " ";
	std::cout << std::endl;

	return rd_byte;
}

int CANSocket::getSocketFD() const
{
    return socketFD;
}

struct can_frame CANSocket::getCanFrame() const
{
	return canFrame;
}