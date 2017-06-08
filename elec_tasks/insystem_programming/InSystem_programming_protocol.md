# Insystem Programming 

In-System Programming allows programming and reprogramming of any AVR microcontroller without connecting it with a PC. Using a simple Three-wire SPI interface, the In-System Programmer communicates serially with the AVR microcontroller, reprogramming all non-volatile memories on the chip. 

We will see below how to design the system to support In-System Programming.

## The Programming Interface

For In-System Programming, the programmer is connected to the target using as few wires as possible. To program any AVR microcontroller in any target system, a simple Six-wire interface is used to connect the programmer to the target PCB. The figure below shows the connections needed.

![six_wire_interface.png](https://github.com/sabSAThai/Advitiya/blob/master/images/six_wire_interface.png)

The SPI consists of three wires: SCK, MISO, MOSI.
**Note** : When programming the AVR, the In-System Programmer always operate as the Master, and the target system always operate as the Slave. 

The In-System Programmer (Master) provides the clock for the communication on the SCK Line. Each pulse on the SCK Line transfers one bit from the Programmer (Master) to the Target (Slave) on the MOSI line. Simultaneously, each pulse on the SCK Line transfers one bit from the target (Slave) to the Programmer (Master) on the MISO line.
</br>

To enter and stay in Serial Programming mode, the AVR microcontroller reset line has to be kept active (low).
Also, to perform a Chip Erase, the Reset has to be pulsed to end the Chip Erase cycle.
</br>
To ease the programming task, it is preferred to let the Insystem programmer take control of the target microcontroller reset line to automate this process using a fourth control line (Reset).

![Insystem_programmer_layout.png](https://github.com/sabSAThai/Advitiya/blob/master/images/Insystem_programmer_layout.png)

## Hardware Design Considerations
To allow In-System Programming of the AVR microcontroller, the In-System Programmer must be able to
override the pin functionality during programming. 
</br>
Now we will discuss the details of each pin used for the programming operation.

### GND
The In-System Programmer and target system need to operate with the same reference voltage.

### RESET
The target AVR microcontroller will enter the Serial Programming mode only when its reset line is active (low).
When erasing the chip, the reset line has to be toggled to end the erase cycle.

</br>

Immediately after Reset has gone active, the In-System Programmer will start to communicate on the
three dedicated SPI wires; SCK, MISO, and MOSI. To avoid driver contention, a series resistor should be
placed on each of the three dedicated lines if there is a possibility that external circuitry could be driving
these lines. The value of the resistors should be chosen depending on the circuitry connected to the SPI
bus.

![SPI_Connections.png](https://github.com/sabSAThai/Advitiya/blob/master/images/SPI_Connections.png)


**Note** : The AVR microcontroller will automatically set all its I/O pins to inputs, with pull ups disabled,
when Reset is active. 

### Serial Clock (SCK )
When programming the AVR in Serial mode, the In-System Programmer supplies clock information on the
SCK pin. Immediately after the Reset goes active, this pin will be driven to zero by the programmer.
</br>
During this first phase of the programming cycle, keeping the SCK Line free from pulses is critical, as pulses will cause the target AVR to lose synchronization with the programmer.
</br>
The target AVR microcontroller will always set up its SCK pin to be an input with no pull-up whenever
Reset is active. See also the description of the Reset wire.

### Master Out – Slave In (MOSI)
When programming the AVR in Serial mode, the In-System Programmer supplies data to the target on
the MOSI pin. This pin is always driven by the programmer, and the target system should never attempt
to drive this wire when target reset is active.
The target AVR microcontroller will always set up its MOSI pin to be an input with no pull-up whenever
Reset is active.


### Master In – Slave Out (MISO)
Communication line from the target AVR (Slave) to the In-System Programmer (Master). 
When Reset is applied to the target AVR microcontroller, the MISO pin is set up to be an input with no
pull-up. Only after the “Programming Enable” command has been correctly transmitted to the target, the
target AVR microcontroller will set its MISO pin to become an output. During this first time, the In-System
programmer will apply its pull-up to keep the MISO line stable until it is driven by the target
microcontroller.

### Vcc (Target Power)
To allow simple programming of targets operating at any voltage, the In-System Programmer can draw power from the
target. Alternatively, the target can have power supplied through the In-System Programming connector for the duration of the programming cycle.

**NOTE** : To avoid problems, the In-System Programmer should be able to keep the entire Target System Reset for
the duration of the programming cycle. The target system should never attempt to drive the three SPI
lines while Reset is active.



## Algorithm

1. Power-up sequence:
Apply power between VCC and GND while RESET and SCK are set to “0”. In some systems, the programmer can not guarantee that SCK is held low during power-up. In this case, RESET must be given a positive pulse of at least two CPU clock cycles duration after SCK has been set to “0”.

2. Wait for at least 20 ms and enable SPI Serial Programming by sending the Programming Enable serial instruction to pin MOSI.

3. The SPI Serial Programming instructions will not work if the communication is out of synchronization. When in sync. the second byte ($53), will echo back when issuing the third byte of the Programming Enable instruction. If the
$53 did not echo back, give RESET a positive pulse and issue a new Programming Enable command.

### Command Format
All commands have a common format consisting of four bytes. The first byte contains the command code,
selecting operation and target memory. The second and third byte contain the address of the selected
memory area. The fourth byte contains the data, going in either direction. 
</br>
The data returned from the target is usually the data sent in the previous byte. Data is always sent on MOSI and MISO lines with the most significant bit (MSB) first.

### Enable Memory Access
When the Reset pin is first pulled active, the only instruction accepted by the SPI interface is “Programming Enable”.
</br>
Only this command will open for access to the Flash and EEPROM memories, and without this access, any other command issued will be ignored.
</br>
After a “Programming Enable” command has been sent to the target, access is given to the nonvolatile
memories of the chip according to the current setting of the protecting Lock bits.
The target AVR microcontroller will not respond with an acknowledge to the “Programming Enable”
command. To check if the command has been accepted by the target AVR microcontroller, the device
code could be read. The device code is also known as the signature bytes.

### Device Code
After the “Programming Enable” command has been successfully read by the SPI interface, the
programmer can read the device code. The device code will identify the chip vendor (Atmel), the part
family (AVR), Flash size in kilobytes, and family member (i.e., AT90S1200). The “Read Device Code”
command format is found in the Serial Programming section of the datasheet.
</br>
Device Code will sometimes read as $FF. If this happens, the part device
code has not been programmed into the device. This does not indicate an error, but the part has to be
manually identified to the programmer.
Device code $FF might also occur if there is no target ready or if the MISO line is constantly pulled high.
The programmer can detect this situation by detecting that also a command sent to the target is returned
as $FF.
</br>
If the target reports Vendor Code $00, Part Family $01, and Part Number $02, both Lock bits have been
set. This prevents the memory blocks from responding, and the value returned will be the byte just
received from the programmer, which just happens to be the current address. To erase the Lock bits, it is
necessary to perform a valid “Chip Erase”.

### Flash Program Memory Access

When the part has been identified, it is time to start accessing the Flash memory. 
</br>
A Chip Erase should be performed before programming the Flash memory. Depending on the target device the Flash is programmed using “Byte” or “Page” mode.
</br>
In Page Programming mode, a temporary Page buffer is first filled, and then programmed in one single write
cycle. This mode reduces the total Flash programming time.
</br>

**Note** : A device with Byte Programming mode do not have the Page Programming option. A device with Page Programming mode of the Flash will, however, use byte programming for the EEPROM memory.  

</br>

Regardless if the device uses Byte Programming mode or Page Programming mode the Flash will be
read one byte at the time using the “Read Flash Program Memory” command. The command sends a
memory address ($aa bb) to select a 16-bit word, and selects low or high byte with the H bit in the
command byte (0 is low, 1 is high byte). The byte stored at this address is then returned from the target
AVR microcontroller in byte 4.

</br>

Usually, each 16-bit word in Flash contains one AVR instruction. Assuming the instruction stored at
address $104 is “add r16,r17”, the op-code for this instruction would be stored as $0F01. Reading
address $104 serially, the expected result returned in byte 4 will be $0F from the high byte, and $01 from
the low byte.

</br>

For devices using Page Programming mode the Flash is programmed in two steps. First, a temporary
Page buffer is filled using the “Load Program Memory Page” command. Each byte in this buffer can be
directly accessed. Once the entire Page buffer is filled, it can be written to the Flash Memory using the
“Write Program Memory Page” command.
