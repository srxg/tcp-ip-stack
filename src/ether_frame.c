#include <linux/if_ether.h>
#include <stdint.h>


// Here we're defining the Ethernet frame header
// as a C struct.
struct eth_hdr {
    unsigned char dmac[6]; // destination mac address
    unsigned char smac[6]; // source mac address
    uint16_t ethertype; // todo
    unsigned char payload[];
}__attribute__((packed));

