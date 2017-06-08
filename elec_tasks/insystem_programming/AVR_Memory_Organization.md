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

The size of these sections is configured by the BOOTSZ fuse.

![program_memory.png](https://github.com/sabSAThai/Advitiya/blob/master/images/program_memory.png)

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
