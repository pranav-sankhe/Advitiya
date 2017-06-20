# AVR Memory Organization

The AVR microcontroller's memory is divided into: 
- Program Memory
	Program Memory (ROM) is used for permanent saving program being executed. 

- Data Memory
	 Data Memory (RAM) is used for temporarily storing and keeping intermediate results and variables.



## Program Memory (ROM)
Program Memory (ROM) is used for permanent saving program (CODE) being executed, and it is divided into two sections :
- Boot Program section
- Application Program section

The Flash memory is divided into two sections, one Application section and one Boot Loader section. The Application section contains the main code for the application, while the Boot Loader section contains the code for the actual Self-programming. The SPM instruction can only be executed from the Boot Loader section.
</br>
The size of the Boot Loader section can be selected using the two BOOTSZx Fuses. The fuses select one of four predefined sizes. The BOOTSZx Fuses can be changed using Serial or Parallel Programming.
</br>
The Flash memory is divided into pages containing 32, 64, or 128 words each. The usage of pages is explained later. The entire memory span, both Application and Boot Loader sections, is divided into pages. For instance, a device with 8 KB of Flash and page size of 32 words (64 bytes) will therefore have a total of 128 pages.

![program_memory.png](https://github.com/sabSAThai/Advitiya/blob/master/images/program_memory.png)


### Read-While-Write Capabilities
In addition to the selectable division between the application and Boot Loader sections, the Flash is also divided into two fixed-size sections. The first section is the Read-While- Write (RWW) section. The second is the No-Read-While-Write (NRWW) section.
The NRWW section size always equals the largest selectable Boot Loader section size, thus
the Boot Loader section occupies all or part of the NRWW section.
</br>
The difference between the sections is that the NRWW section is accessible while
updating the RWW section. It is not possible to access the RWW section when it’s being
updated. When the NRWW is updated (e.g., updating the Boot Loader code itself), the
CPU is halted during the whole operation. In other words, No-Read-While-Writing to the
NRWW section, but possible to Read-While-Writing to the RWW section.
This functionality makes it possible to continue execution of critical code while updating
the RWW section. Note that this critical code must be contained within the NRWW sec-
tion (not necessarily in the Boot Loader section).
![RWsections.png](https://github.com/sabSAThai/Advitiya/blob/master/images/RWsections.png)

## Data Memory (RAM)

Data memory consists of :

- Rx space
	Rx space consists of 32 general purpose working 8-bit registers (R0-R31). These registers have the shortest (fastest) access time, which allows single-cycle Arithmetic Logic Unit (ALU) operation.

- I/O Memory
	I/O Memory space contains addresses for CPU peripheral function, such as Control registers, SPI, and other I/O functions. 

- Extended I/O Memory (MCU dependent)
	Due to the complexity, some AVR microcontrollers with more peripherals have Extended I/O memory, which occupies part of the internal SRAM. Extended I/O memory is MCU dependent. 
	Storing data in I/O and Extended I/O memory is handled by the compiler only. Users can not use this memory space for storing their data. 

- Internal SRAM
	Internal SRAM (Data Memory) is used for temporarily storing and keeping intermediate results and variables (static link and dynamic link). 

![data_memory.png](https://github.com/sabSAThai/Advitiya/blob/master/images/data_memory.png)
