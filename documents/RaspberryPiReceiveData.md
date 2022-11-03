# Example of connect and receive CAN data with C library

- CAN communication is also one socket communication and can use the most commonly used socket library in C language

## CAN frame structure

```c
struct can_frame {
    canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    union {
        /* CAN frame payload length in byte (0 .. CAN_MAX_DLEN)
            * was previously named can_dlc so we need to carry that
            * name for legacy support
            */
        __u8 len;
        __u8 can_dlc; /* deprecated */
    };
    __u8    __pad;   /* padding */
    __u8    __res0;  /* reserved / padding */
    __u8    len8_dlc; /* optional DLC for 8 byte payload length (9 .. 15) */
    __u8    data[8] __attribute__((aligned(8)));
};
```

### [Detail of CAN library](kernel.org/doc/html/latest/networking/can.html)

## Example code
- Get CAN data & print it on console.

```c++
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

# define CAN_FRAME_MAX_LEN 8

int main()
{
    /*
        Create socket. Accept three parameter
        PF_CAN - domain/protocol family 
        SOCK_RAW - type of socket (raw or datagram)
        CAN_RAW - socket protocol
    */
    int sock_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW); 
	if (sock_fd < 0)
    {
        std::cout << "Failed to socket create" << std::endl;
        return 1;
    }
    std::cout << "Success to socket create" << std::endl;


    /*
        Retrieve the interface index for the interface name(can0, can1, vcan0 etc).
        Send an I/O control call and pass an ifreq structure containing the interface name.
    */
	struct ifreq ifr;
	strcpy(ifr.ifr_name, "can0");
	int ret = ioctl(sock_fd, SIOCGIFINDEX, &ifr);
	if (ret < 0)
    {
        std::cout << "Failed to get CAN interface index : " << ret << std::endl;
        return 1;
    }
    std::cout << "Success to get CAN interface index : " << ret << std::endl;

	struct sockaddr_can addr;
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	ret = bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
    {
        std::cout << "Failed to socket bind : " << ret << std::endl;
        return 1;
    }
    std::cout << "Success to socket bind : " << ret << std::endl;

    struct can_frame frame;
	while (1)
	{
		int rd_byte = read(can_fd, &frame, sizeof(frame));
		if (rd_byte < 0)
        {
            std::cout << "Failed to recieve CAN frame : " << rd_byte << std::endl;
            return 1;
        }
		else if (rd_byte < (int)sizeof(struct can_frame))
        {
            std::cout << "Incomplete CAN frame is received : " << rd_byte << std::endl;
            return 1;
        }
		else if (frame.can_dlc > CAN_MAX_DLEN)
        {
            std::cout << "Invalid dlc " << frame.can_dlc << std::endl;
            return 1;
        }

		
		printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);

		for (int i = 0; i < frame.can_dlc; i++)
			printf("%02X ",frame.data[i]);
		printf("\n");
	}

    return 0;
}

```

- [I/O control call and pass an ifreq](https://man7.org/linux/man-pages/man7/netdevice.7.html)