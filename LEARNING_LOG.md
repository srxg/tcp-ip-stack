# Learning Log
Answering questions I've left myself in comments
I'll probably end up explaining things I haven't asked myself about (need to
gain a comprehensive understanding of things, no gaps!)

- What is "`ifreq`"?
    - A structure used in Linux to configure network interfaces.
      It's defined in `<net/if.h>`.
    - Used to hold the **settings** of a network interface
        - Used to change such settings via `ioctl` calls.
    
    - Why are we using it?
        - Because we're creating and configuring a TUN/TAP Device, which
          is a type of network interface (a virtual network interface)!

---

- What is `err`?
    - You already know it just holds the return value of `ioctl()`.
    So, if `ioctl()` fails, it returns a negative value. Hence,
    we can use this to understand the type of error that occured.

- What is `O_RDWR`?
    - It's just a flag we can use when opening a file in Linux.
    - It stands for "Open for Reading and Writing"
    
    - So why is it used?
      - Because we're writing and reading to and from the device.

- What is `ifr_flags`?
  - Member of ifreq structure, obviously.
  - It's used to change the flags of the network interface.
  - Flags indicate how the interface operates/should operate.
  - In this case, `IFF_TAP` is setting up the device to be a TAP device.
    - **Remember:**
      - a *TAP* device operates at the data link layer.
      - a *TUN* device operates at the network layer.
  - The `IFF_NO_PI` is setting the device to NOT prepend the packet information
    to the packet content.
  - SO `IFF_TAP | IFF_NO_PI` sets the device up as a TAP device which doesn't
    prepend the packet information to the packet content.
---
## Overview of the `tun_alloc` function
1. Open the file `/dev/net/tap`. This is a special device file - it's the entry point to the kernel's TUN/TAP functionality. The returned file descriptor `fd` is used in further operations on the TUN/TAP device.
2. `ifreq` structure is cleared, and then set up for the creation of the TUN/TAP device.
3. The `ioctl()` function is used to send a command to the kernel, specifically `TUNSETIFF`, which tells the kernel to create a new TUN/TAP device with the given parameters.
4. If `ioctl()` fails, it closes the file descriptor and returns the error code. If it succeeds, it writes the name of the newly created TUN/TAP device back into the provided buffer and returns the file descriptor for the TUN/TAP device.
  **Remember:**:
    - a buffer is just a region of memory storage used to temporarily store data while it is being moved from one place to another.
    - Buffers are usually used when there is a difference between the rate at which data is received and the rate at which it can be processed, or in the case where data can be created and used at different points in time.
    - In our context, `char *dev` can be seen as a buffer because it's used to store the name of the network device that's being created. The function `tun_alloc()` is writing to this buffer when it calls `strcpy(dev, interface_request.ifr_name);` copying the name of the TUN/TAP device that was created into the buffer so that it can be used by the calling function.
---
## Why are we talking about 'TUN/TAP' devices if tun_alloc just creates a TAP device?
The (Linux) kernel provides a combined TUN and TAP device driver. The actual type of device that gets created (TUN or TAP) is determined by the flags you set when you call `ioctl()`.

The same function and the same `/dev/net/tap` device file are used for setting up either type of device, apparently, and the actual device type is determined by the flags you provide.
---
## Ethernet Frames!
`ethertype` either indicates the length of the payload, or the type of the payload - this depends on its value.
If `ethertype` >= 1536, then it contains the type of payload (e.g. `IPv4`, `ARP`).
If the value is `< 1536` then it contains the length of the payload.


`__attribute__((packed));` is an IMPLEMENTATION DETAIL
It instructs gcc *NOT to optimise the struct memory layout for data alignment*
*with padding bytes.*
This stems from how we parse the protocol buffer (atm), see below:
`struct eth_hdr *hdr = (struct eth_hdr*) buf;`
  - `buf` would be the data buffer with the proper protocol struct
     (block of data, formatted according to a specific protocol
     (the protocol's struct)).
  - here, we're assuming that `buf` contains an ethernet frame, and that frame
    is being interpreted as an eth_hdr structure.

*Parsing* : analysing a block of data (usually binary data received over a 
network or read from a file or a device) and *extracting the information it*
*contains into a structured format* that the software can use.

When you do something like struct eth_hdr *hdr = (struct eth_hdr*) buf;
you're interpreting the block of data in buf as an eth_hdr structure,
which involves parsing the data.

A portable, albeit slightly more laborious approach, would be to serialize the
protocol data manually. This way, the compiler is free to add padding bytes to
conform better to different processor’s data alignment requirements.

## Parsing and Handling Ethernet frames:
Overall process is straightforward:
```
if (tun_read(buf, BUFLEN) < 0) {
    print_error("ERR: Read from tun_fd: %s\n", strerror(errno));
}

struct eth_hdr *hdr = init_eth_hdr(buf);

handle_frame(&netdev, hdr);
```

- `handle_frame`: looks at the ethertype field and decides what to do
                  based on the value
