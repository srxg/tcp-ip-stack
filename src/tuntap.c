
// See kernel.org/doc/Documentation/networking/tuntap.txt
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int tun_alloc(char *dev) {
    struct ifreq ifr;
    int fd, err;

    if((fd = open("/dev/net/tap", O_RDWR)) < 0)
    {
        print_error("Can't open TUN/TAP dev");
        exit(1);
    }

    CLEAR(ifr);


}