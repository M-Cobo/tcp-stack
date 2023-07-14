#include <iostream>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <fcntl.h>

int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

    if((fd = open("/dev/net/tap", O_RDWR)) < 0)
    {
        std::cerr << "Cannot open TUN/TAP dev" << std::endl;
        exit(1);
    }

    memset(&(ifr), 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if( *dev ) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
        print_error("ERR: Could not ioctl tun: %s\n", strerror(errno));
        close(fd);
        return err;
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}
