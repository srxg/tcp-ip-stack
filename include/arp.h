#ifndef ARP_H
#define ARP_H

#include <stdint.h>

struct arp_hdr {
    uint16_t hwtype;
    uint16_t protype;
    
    unsigned char hwsize;
    unsigned char prosize;
    
    uint16_t opcode;

    unsigned char data[];
}__attribute__((packed));

#endif