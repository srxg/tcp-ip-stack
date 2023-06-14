#ifndef ETHER_H
#define ETHER_H
#include <linux/if_ether.h>
#include <stdint.h>
#include <netinet/in.h>
// if_ether.h provides a mapping between ethertypes and their hexadecimal values
#define ETH_HDR_LEN sizeof(struct eth_hdr)



/**
 * Defining the Ethernet frame header as a C struct.
 * 
 * non-urgent TODO: implement the full suite of different tags
 *                  include the frame check sequence field at the end
 *                      for CRC (cyclic redundancy check) to check integrity
 *                      of the frame
 * 
 * non-urgent TODO: serialisation method?
 * 
 * ethertype >= 1536: type of payload e.g. ipv4 or ARP
 * < 1536 : contains length of payload
*/
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