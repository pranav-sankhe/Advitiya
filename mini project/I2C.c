#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU/(16UL*BAUD)-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char address = 0xEF;
unsigned char data = 0b00000000;

//------------------------------------------------------------------------
void USART_Init(unsigned int ubrr);
void USARTWriteChar(char c);
void ERROR(); //for error signal
void I2C_start(void); // Start send
void I2C_rep_start(void);
void I2C_init_master(void);//enter in master mode
void I2C_write_address(unsigned char); //send address
void I2C_write_data(unsigned char);//sends the data byte
void I2C_stop(void);// Sends STOP
void  I2C_read_address(unsigned char); // reads the address
unsigned char I2C_read_data(void);//  reads the data from ST
//-------------------------------------------------------------------------

void ERROR(void)
{
	PORTA = 0B11111111;
}
void I2C_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//Send START condition
	while (!(TWCR &	(1<<TWINT)));//Wait for TWINT flag set
	while((TWSR & 0xF8) != 0x08);
	PORTA =0b00000010;// step 2

	
}

void I2C_init_master(void)
{
	TWBR=0b00100000;//set bit rate ton 100kHZ
	TWSR=(0<<TWPS1)|(0<<TWPS0);//set prescalar to 1
	PORTA =0b00000001;//step 1
	
}

void I2C_write_address(unsigned char add1)
{
	TWDR=add1; //set address in TWDR Register
	TWCR = (1<<TWINT) |	(1<<TWEN);//clears TWI interrupts, enable TWI
	while (!(TWCR &	(1<<TWINT)));
	while((TWSR & 0xF8) !=0x18);
	PORTA =0b00000011;// step 3
	//USARTWriteChar('a');
}

void I2C_write_data(unsigned char data_1)
{
	TWDR=data_1;
	TWCR=(1<<TWINT) | (1<<TWEN);
	while (!(TWCR &	(1<<TWINT)));
	while((TWSR & 0xF8) !=0x28);
	PORTA =0b00000100;//step 4
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(!(TWCR & (1<<TWSTO)));
	PORTA =0b00000101;// step 5
	
}

void I2C_read_address(unsigned char add_1)
{
	TWDR=add_1;
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)));
	if ((TWSR & 0xF8)!=0x40)
		ERROR();
}

unsigned char I2C_read_data(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	if((TWSR & 0xF8) != 0x58) // Check for the acknowledgment
		ERROR();
	unsigned char recv_data=TWDR;
	return recv_data;
}


void USART_Init(unsigned int ubrr)
{
    
    UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;
    //UCSRB = (1<<RXEN)|(1<<TXEN);
    
    UCSRB = (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL) | (1<<USBS) | (1<<UCSZ1)|(1<<UCSZ0);
}


void USARTWriteChar(char c)
{

    while(!(UCSRA & (1<<UDRE)))
    {
        
    }

    UDR=c;
}

//-----------------------------------------------------------------

int main(void)
{
    DDRA=0xFF;
	PORTA = 0x00;
	I2C_init_master();
	USART_Init(95);
	unsigned char a;

    while (1)
    {
		I2C_start();
		
		// I2C_write_address(address);
		I2C_read_address(address);
		
		a = I2C_read_data();
		I2C_stop();

	    USARTWriteChar(a);
		PORTA=0x00;
		_delay_ms(50);
		// data = data + 0b00000001;
    }
}
