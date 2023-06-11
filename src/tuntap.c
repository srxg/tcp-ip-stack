/*
* Device Driver for Universal TUN/TAP
* See the kernel docs on tuntap for more info
*/ 
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <errno.h>

/**
 * dev : the name of the device with a format string
 * (e.g. "tun%d") - apparently this can be any valid network
 * device name though?
 * 
 * Creates and configures a TAP device.
*/
int tun_alloc(char *dev) {
    struct ifreq interface_request; // interface request structure
    int fd, err;

    if((fd = open("/dev/net/tap", O_RDWR)) < 0)
    {
        print_error("Can't open TUN/TAP dev");
        exit(1);
    }

    CLEAR(interface_request);


    // IFF_TUN - TUN Device (no ethernet headers)
    // IFF_TAP - TAP Device
    // IFF_NO_PI - Do not provide packet information
    // IFF_NO_PI is crucial - if we don't use it, we end up with
    // unnecessary packet information prepended to the Eternet frame
    

    interface_request.ifr_flags = IFF_TAP | IFF_NO_PI;

    if(*dev) strncpy(interface_request.ifr_name, dev, IFNAMSIZ);

    if( (err = ioctl(fd, TUNSETIFF, (void *) &interface_request)) < 0 )
    {
        print_error("ERR: COuld not ioctl tun: %s\n", strerror(errno));
        close(fd);
        return err;
    }

    strcpy(dev, interface_request.ifr_name);
    return fd;
}

/**
 * Questions to Myself
 * What is "ifreq"? Why are we using it?
 *      -  ifreq: a data structure used in Linux to configure network interfaces.
 *                It's defined in <net/if.h>.
 *                The structure is used to hold the settings of a network interface
 *                and to change them using ioctl calls.
 * What is O_RDWR?
 * 
*/