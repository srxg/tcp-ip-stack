#ifndef ARP_H
#define ARP_H

#include <stdint.h>

struct arp_hdr {
    uint16_t hwtype; // determines the (data) link layer type used - this is
                     // ethernet in our case, and the value is 0x0001
    uint16_t protype; // protocol type - ipv4 in our case - 0x0800
    
    unsigned char hwsize; // sizes of hardware
    unsigned char prosize; // and protocol fields
                           // in our case - 6 bytes for MAC addrs
                           // 4 bytes for IP addrs
    
    uint16_t opcode; // declares TYPE of ARP message.
                     // can be : arp request  (1)
                     //          arp reply    (2)
                     //          RARP request (3)
                     //          RARP reply   (4)

    unsigned char data[];
}__attribute__((packed));

struct arp_ipv4 {
    unsigned char smac[6];
    uint32_t sip;

    unsigned char dmac[6];
    uint32_t dip;
}__attribute__((packed));

#endif