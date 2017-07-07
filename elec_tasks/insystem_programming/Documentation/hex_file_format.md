INTERPRETING INTEL HEX FORMAT
 
Intel HEX format traditionally looks something like this: :107800000C94343C0C94513C0C94513C0C94513CE1
 
Understanding the bytes can be done by breaking each line of HEX code into groups like this:
 
:10 7800 00 0C94343C0C94513C0C94513C0C94513C E1
 
Each line in this bootloader example begins with a : representing the start of a new line.
 
The next two chars 0x10 from the example shows how many data bytes are in the line of text.
 
The next four bytes 0x7800 show the starting address where the code will be written to Flash
with 0x78 as MSB or SEGMENT and 0x00 as LSB or OFFSET for the address.
 
The next two chars 0x00 show that the next 16 bytes in the line are plain uint8 data.
This will be written low byte first then high byte in that order until end of file.
 
Following the data type is a group of 16 bytes beginning with 0x0C ending with 0x3C
0x0C will be written as the low byte using ISP command 0x40 at address 0x7800
0x94 will be written as the high byte using ISP command 0x48 at address 0x7800
 
Then these bytes are locked into place inside the Flash using ISP command
4C 78 00 00 reflecting the address of the bytes that were issued to the buffer.
 
0x3C will be written as the high byte using ISP command 0x48 at address 0x7807
This is because the ATmega328(p) holds two bytes per address in Flash unlike
the hex file shows.
 
The last two chars 0xE1 are the checksum digits for the entire line which can be discarded.
 
The last two lines in the hex file can be ignored as they will not be written to Flash in any shape, way or form.
The last two lines of code look something like this:
:040000030000780081
:00000001FF
 
They are not used for AVR, but used for storing instruction and stack pointer addresses in Intel x86  CPU's.
The last line marks the end of file which can be ignored completely.
 
** Write the low byte, then write the high byte and then lock the bytes into place before writing any bytes to any other address **
** The only address we are interested in is the very first address listed in the hex file, 7800 in this case for bootloader **
** No other address should ever be used as the other addresses do not line up to how the data needs to be written to MCU Flash! **
