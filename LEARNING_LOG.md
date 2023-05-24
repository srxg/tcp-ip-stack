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