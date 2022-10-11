#include "../includes/CANSocket.hpp"
#include "../includes/utils.h"
#include "../includes/IPCServer.hpp"

#include <thread>
#include <CommonAPI/CommonAPI.hpp>

int main()
{
	CANSocket canSocket;

	canSocket.initSocket("can0");

	IPCServer ipcServer;
	ipcServer.executeServer();

	while (1)
	{
		int rd_byte = canSocket.readData();
	}

	return 0;
}