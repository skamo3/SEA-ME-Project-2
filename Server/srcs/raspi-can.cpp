#include "../includes/raspi-can.h"
#include "../includes/utils.h"

int InitSocket(const char *ifname)
{
	int sock_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (sock_fd < 0)
		return PrintErrorText("Failed to socket create", sock_fd);
	PrintSuccessText("Success to socket create");

	struct ifreq ifr;
	strcpy(ifr.ifr_name, ifname);
	int ret = ioctl(sock_fd, SIOCGIFINDEX, &ifr);
	if (ret < 0)
		return PrintErrorText("Failed to get CAN interface index", ret);
	printf("%sSuccess to get CAN interface index : %d%s\n", 
					COLOR_BGREEN, ret, COLOR_RESET);

	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	ret = bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
		PrintErrorText("Failed to socket bind", ret);
	PrintSuccessText("Success to socket bind");
	
	return sock_fd;
}

// struct can_frame {
//     canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
//     __u8    can_dlc; /* frame payload length in byte (0 .. 8) */
//     __u8    __pad;   /* padding */
//     __u8    __res0;  /* reserved / padding */
//     __u8    __res1;  /* reserved / padding */
//     __u8    data[8] __attribute__((aligned(8)));
// };
int main()
{
	int can_fd = InitSocket("can0");
	if (can_fd < 0)
		return can_fd;
	
	struct can_frame frame;
	while (1)
	{
		int rd_byte = read(can_fd, &frame, sizeof(frame));
		if (rd_byte < 0)
			return PrintErrorText("Failed to recieve CAN frame", rd_byte);
		else if (rd_byte < (int)sizeof(struct can_frame))
			return PrintErrorText("Incomplete CAN frame is received", rd_byte, rd_byte);
		else if (frame.can_dlc > CAN_MAX_DLEN)
			return PrintErrorText("Invalid dlc", -1, frame.can_dlc);

		
		printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);

		for (int i = 0; i < frame.can_dlc; i++)
			printf("%02X ",frame.data[i]);
		printf("\n");
		printf("RPM : %d : %d \n", frame.data[0], frame.data[1]);
		
	}

	return 0;
}