# C Functions for Reading and Writing to Flash Memory

The Atmel AVR devices have a feature called Self programming Program memory. This feature enables an AVR device to reprogram the Flash memory while executing the program. Such a feature is helpful for applications that must self-update firmware or store parameters in Flash.

We will discuss the details about the C functions for accessing the Flash memory.

## Theory of Operation 

We will go through some basic theory around using the Self programming Program memory feature in AVR.

### Using SPM Instructions

The Flash memory may be programmed using the Store Program Memory (SPM) instruction. During Flash write to the Boot section the CPU is always halted. However, most devices may execute
code (read) from the Boot section while writing to the Application section.

### Writing Procedure
The Flash memory is written in a page-by-page fashion. The write function is performed by storing data
for an entire page into a temporary page buffer prior to writing the Flash. Which Flash address to write to is decided by the content of the Z-register and RAMPZ-register. A Flash page must be erased before it can be programmed with the data stored in the temporary buffer. 
</br>
The functions describe below use the following procedure when writing a Flash page:

- Fill temporary page buffer
- Erase Flash page
- Write Flash page

**Note** : As it is evident in this sequence there is a possibility for loss of data, if a reset or power failure should occur immediately after a page erase. Loss of data can be avoided by taking necessary precautions in software, involving buffering in non-volatile memory. The write functions contained in this application note provide optional buffering when writing.

### Addressing 
The Flash memory in AVR is divided into 16-bit words. This means that each Flash address location can store two bytes of data.
</br>
In some cases the Flash memory is referred to by using word addressing and in other cases
by using byte addressing, which can be confusing. All functions discussed below use byte addressing. The relation between byte address and word address is as follows:

              **Byte address = word address • 2**

</br>

A Flash page is addressed by using the byte address for the first byte in the page. The relation between
page number (ranging 0, 1, 2...) and byte address for the page is as follows:

              **Byte address = page number • page size (in bytes)**


##### Example on byte addressing:

A Flash page in an ATmega128 is 256 bytes long.
Byte address 0x200 (512) will point to:
• Flash byte 0x200 (512), equal to byte 0 on page 2
• Flash page 2

When addressing a page in ATmega128, the lower byte of the address is always zero. When addressing
a word, the LSB of the address is always zero


### Page Size
The constant PAGESIZE must be defined to be equal to the Flash page size (in bytes) of the device being
used.

### Defining Flash Memory For Writing
The memory range in which the functions are allowed to write is defined by the constants
ADR_LIMIT_LOW and ADR_LIMIT_HIGH. The write functions can write to addresses higher or equal to
ADR_LIMIT_LOW and lower than ADR_LIMIT_HIGH.

### Placing Selected Functions Inside the Boot Section

