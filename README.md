# tcp-ip-stack
This is a Userspace TCP/IP stack (built from Layer 2 up) for Linux made purely for educational purposes.
I want to learn more about networking at a deeper level and following saminiir's tutorial seemed
liked a good way to do that.

## TUN/TAP devices
A Linux TAP device will be used to intercept low-level (data link) network traffic from the (Linux) kernel.

### What's a TUN/TAP Device?
They're just "kernel virtual network devices". They're supported entirely in software.
Used by *userspace applications* to manipulate L3/L2 traffic, respectively (network and data layers).
For example - tunneling (wrapping a packing inside the payload of another packet).

### Advantages
- We can set them up easily in userspace
- Already used in a large variety of programs, e.g. OpenVPN.

### TUN and TAP in the Network Stack
TUN and TAP can't be used together - they work (transmit and receive) at diferent layers of the network stack.
- **TUN**nel, simulates a device on the network layer. So, it carries IP packets in layer 3.
    - **TUN** is used with *routing*.
- **TAP** (network TAP) simulates a device on the data link layer. So, it carries Ethernet frames on Layer 2.
    - **TAP** can be used to create a network bridge in userspace.
    - A *network tap* is typically a *dedicated pice of hardware* which provides a way to access the data
      flowing across a network. It montiors events on a local network.
    - A *network tap* has >= 3 ports: Port A, B and a Monitor Port. A tap inserted between A and B passes
      all traffic (send and receive streams) through unimpeded in real time, but also copies the traffic
      to the monitor port. VoIP recording, Packet Sniffers, Network Intrusion Detection Systems, etc.

```
(3) Network Layer    <------ TUN ------>  Network Layer
(2) Data Link Layer  <------ TAP ------>  Data Link Layer
```

So, a TUN/TAP device is used by the OS to *send packets*.
These packets are delivered to a *program* in *userspace* which attaches itself to the device.
Such a program in userspace could also *pass packets* **into** a TUN/TAP device - in which case,
the TUN/TAP device delivers ("injects") these packets to the OS network stack
(i.e. emulating their reception from an external source).

Use cases : VPNs, Virtual-Machine Networking
---
Recap:
- **TUN** devices:
  - work at the **IP level** (this is on layer 3)
  - forwarding packets from the network layer (layer 3).
  - they appear to the system as if they were a **network interface card** (e.g. ethernet card or wifi nic)
    - **BUT** instead of sending packets to the physical network, they pass them to a **USERSPACE PROGRAM**.

- **TAP** Devices:
  - Work at the **ethernet level** (layer 2 - datalink layer).
  - They forward frames from the data link layer.
  - Useful for creating virtual network bridges.
    - E.g., you could connect a TAP device with a physical network device (like `eth0`) in a bridge, and then all traffic that comes over the physical device could be read by the program that has the **TAP** device open.
  
  - So, a Userspace program can then hence read packets from the TAP device just like it would read from a regular network 


### What's tunneling?
"the idea of carrying lower-layer traffic in higher-layer (or equal-layer) packets."
"For example, IPv4 can be carried in an IPv4 or IPv6 packet; Ethernet can be carried in a UDP or IPv4 or IPv6 packet, and so on."
So - to achieve this, we inject packets into the payload of other packets.

### Tunneling Protocols?
- Generic Routing Encapsulation (GRE)
- Point-to-Point Tunneling Protocol (PPTP)
- Layer 2 Tunneling Protocol (L2TP)

### The result of tunneling?
Virtual links between computers in different networks can be set up!
E.g. an company's private network can be accessed from the outside, public network via tunneling

**Tunneling *itself* does not guarantee secure communications**.
