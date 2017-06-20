#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


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
  DDRD |= 0x01;                       //PD0 as Output
  PORTD = 0x00;                       // RESET Pin low

// Wait at least t PWRUP . and drive SS high.
    _delay_ms(1);

  DDRA |= 0x01;                       //PA0 as Output
  PORTA = 1<<PA0;                       // SS Pin HIGH

 // Wait at least t POR for the internal Power-on Reset to complete. The value of t POR will depend on the current settings of the target device.
 
 // Start programming session.  
}