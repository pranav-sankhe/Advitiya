#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//--------------------------------------------------------------------------------------------------
//Control the RESET pin of the target microcontroller. 
void reset(int mode){  
    if (mode == 0)
    {
        PORTB = 0b00000000;
    }

    if (mode == 1)
    {
        PORTB = 1<<PINB0;
    }
}
//--------------------------------------------------------------------------------------------------
// Control SS pin of the target microcontroller  
void SSPin(int mode)
{
        if (mode == 0)
    {
        PORTB = 0b00000001; //set B0 to Low 
    }

    if (mode == 1)
    {
        PORTB = 0b00000000; //set B0 to High 
    }
    
} 
//--------------------------------------------------------------------------------------------------
// Initialize SPI Master Device (with SPI interrupt)
void spi_init_master (void)
{
    // Set MOSI, SCK as Output
    DDRB=(1<<5)|(1<<3);
 
    // Enable SPI, Set as Master
    // Prescaler: Fosc/16, Enable Interrupts
    //The MOSI, SCK pins are as per ATMega8
    SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);
 
}

// Initialize SPI Slave Device
void spi_init_slave (void)
{
    DDRB = (1<<6);     //MISO as OUTPUT
    SPCR = (1<<SPE);   //Enable SPI
}

//Function to send and receive data for both master and slave
unsigned char spi_tranceiver (unsigned char data)
{
    // Load data into the buffer
    SPDR = data;
 
    //Wait until transmission complete
    while(!(SPSR & (1<<SPIF) ));
 
    // Return received data
    return(SPDR);
}



int main(){
    //Apply power between VCC and GND pins. RST should remain low.
    DDRB = 0b00000001; //Pin B0 becomes output pin 
}