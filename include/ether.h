#ifndef ETHER_H
#define ETHER_H
#include <linux/if_ether.h>
#include <stdint.h>
#include <netinet/in.h>


#define ETH_HDR_LEN sizeof(struct eth_hdr)

struct eth_hdr {
    unsigned char dmac[6]; // destination mac address
    unsigned char smac[6]; // source mac address
    
    uint16_t ethertype; // overloaded - not the oo type of overloaded.

    unsigned char payload[]; // pointer to payload - in our case, this will
                             // contain an arp or ipv4 packet.
                             // if payload length < min required 48 bytes (without tags)
                             // pad bytes are appended to the end of the payload to meet
                             // the requirement
}__attribute__((packed));


#endif