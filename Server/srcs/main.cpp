#include "../includes/CANSocket.hpp"
#include "../includes/utils.h"

int main()
{
	CANSocket CANSock;

	CANSock.initSocket("can0");

	while (1)
	{
		int rd_byte = CANSock.readData();
	}

	return 0;
}