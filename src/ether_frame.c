#include <linux/if_ether.h>
#include <stdint.h>
#include <netinet/in.h>
// if_ether.h provides a mapping between ethertypes and their hexadecimal values

/**
 * Defining the Ethernet frame header as a C struct.
 * non-urgent TODO: implement the full suite of different tags
 *                  include the frame check sequence field at the end
 *                      for CRC (cyclic redundancy check) to check integrity
 *                      of the frame
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

// __attribute__((packed));
// this IMPLEMENTATION DETAIL
// instructs gcc NOT to optimise the struct memory
// layout for data alignment with padding bytes.
// this stems for how we parse the protocol buffer, see below

// struct eth_hdr *hdr = (struct eth_hdr*) buf;
// buf would be the data buffer with the proper protocol struct
// (block of data, containing formatted information - that is,
//  formatted according to a specific protocol (the protocol's struct))
// here, we're assuming that 'uf' contains an ethernet frame, and that frame
// is being interpreted as an eth_hdr structure.

/**
 * 
Parsing : analysing a block of data (usually binary data received over a 
network or read from a file or a device)
          and extracting the information it contains into a structured format
          that the software can use.
          
          When you do something like struct eth_hdr *hdr = (struct eth_hdr*) buf;
          you're interpreting the block of data in buf as an eth_hdr structure,
          which involves parsing the data.

A portable, albeit slightly more laborious approach, would be to serialize the
protocol data manually. This way, the compiler is free to add padding bytes to
conform better to different processor’s data alignment requirements.
 * 
 * 
 * struct eth_hdr serialise_protocol_data(unsigned char* buf) {
    struct eth_hdr hdr;
    int payload_length = 
    memcpy(hdr.dmac, buf, 6);
    buf+=6;
    memcpy(hdr.smac, buf, 6);
    buf+=6;

    hdr.ethertype = ntohs(*(uint16_t*)buf);
    buf+=2;

    if(hdr.ethertype >= ETH_P_802_3_MIN) {
        switch(hdr.ethertype) {
            case ETH_P_IP:
            {

            }
            case ETH_P_ARP:
            {

            }
            default:
            // somehow raise an error to show this is unsupported type?
        }
    } else {
        // contains length of it
    }
}
*/

