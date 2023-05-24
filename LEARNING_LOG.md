# Learning Log
Answering questions I've left myself in comments
I'll probably end up explaining things I haven't asked myself about (need to
gain a comprehensive understanding of things, no gaps!)

- What is "```ifreq```"?
    - A structure used in Linux to configure network interfaces.
      It's defined in ```<net/if.h>```.
    - Used to hold the **settings** of a network interface
        - Used to change such settings via ```ioctl``` calls.
    
    - Why are we using it?
        - Because we're creating and configuring a TUN/TAP Device, which
          is a type of network interface (a virtual network interface)!

---

- What is ```err```?
    - You already know it just holds the return value of ```ioctl()```.
    So, if ```ioctl()``` fails, it returns a negative value. Hence,
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
Testy