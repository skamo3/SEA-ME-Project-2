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

# define CAN_FRAME_MAX_LEN 8

class CANSocket
{

	public:
		CANSocket();
		CANSocket(CANSocket const &origin);
		CANSocket &operator=(CANSocket const &origin);
		~CANSocket();

		void initSocket(std::string const &ifname);
		int readData();

		int getSocketFD() const; 
		struct can_frame getCanFrame() const;

	private:
		int socketFD;
		struct can_frame canFrame;


};
