/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 */

/* $Id: twitest.c,v 1.6 2005/11/05 22:32:46 joerg_wunsch Exp $ */

/*
 * Simple demo program that talks to a 24Cxx I²C EEPROM using the
 * builtin TWI interface of an ATmega device.
 */

/**
 * @file eeprom.c
 * @brief Interface with the EEPROM Device
 */

#include "common.h"
#include <util/twi.h>		/* Note [1] */
#include <util/delay.h>
#include "eeprom.h"

/**
 * Note [3]
 * TWI address for 24Cxx EEPROM:
 *
 * 1 0 1 0 E2 E1 E0 R/~W	24C01/24C02
 * 1 0 1 0 E2 E1 A8 R/~W	24C04
 * 1 0 1 0 E2 A9 A8 R/~W	24C08
 * 1 0 1 0 A10 A9 A8 R/~W	24C16
 */
static uint8_t eeprom_addr = 0b10100110;	/* E2 E1 E0 = 0 0 0 */

void ioinit(void)
{

  /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
#if defined(TWPS0)
  /* has prescaler (mega128 & newer) */
  TWSR = 0;					//initialising all pins to zero//status register//prescaler req=1 pg 216
#endif

#if F_CPU < 3600000UL
  TWBR = 10;			/* smallest TWBR value, see note [5] *///baud rate register
#else
  TWBR = (F_CPU / 100000UL - 16) / 2;
#endif
}

int eeprom_read_bytes(uint32_t eeaddr, int len, uint8_t *buf)			//reading starting at eeaddr into buf
{
  if((eeaddr < HALF_ADDR) && ((eeaddr + len) > HALF_ADDR))			//can only write till half the address at once- ref datasheet
  {
    int first = HALF_ADDR - eeaddr;
    eeprom_read_bytes_part(eeaddr, first, buf);
    return eeprom_read_bytes_part(HALF_ADDR, len - first , buf + first);
  }
  
  return eeprom_read_bytes_part(eeaddr, len, buf);
}

int eeprom_read_bytes_part(uint32_t eeaddr, int len, uint8_t *buf)
{
  uint8_t sla, twcr, n = 0;
  int rv = 0;
  
  ///* Added code for handling the two halves of the EEPROM
  if(eeaddr >= HALF_ADDR)
  {
    eeaddr -= HALF_ADDR;			//first half and second half differentiated on the basis of slave address
    eeprom_addr |= 0x08;			//will get in datasheet- what slave address should be if data exceeds half address
  }
  else
  {
    eeprom_addr &= ~0x08;				//what slave address should be if not greater than half address
  }
  
  /* patch high bits of EEPROM address into SLA */						//sla+w is slave address + write req
  sla = eeprom_addr;

  /*
   * Note [8]
   * First cycle: master transmitter mode
   */
 restart:
  if (n++ >= MAX_ITER)				//max times we could repeatedly instruct a device to do a particular operation- it might have been busy with some other operation
    return -1;
 begin:

  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); /* send start condition */			//_BV is 1<<TWINT
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))			//twst stores the error condition//assigned the value and checked//assigned value is the output value
    {
    case TW_REP_START:		/* OK, but should not happen */			//send repeat start condn- for both repeat start and start -break applicable
    case TW_START:					//send start condn
      break;

    case TW_MT_ARB_LOST:	/* Note [9] */				//arbitration bit lost
      goto begin;     

    default:
      return -1;		/* error: not in start condition */
      /* NB: do /not/ send stop condition */
    }

  /* Note [10] */
  /* send SLA+W */
  TWDR = sla | TW_WRITE;				//pg 208//transmitting the slave addr and write bit- to enter master transmitter mode//assumed last bit is zero so doesnt affect "or"
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */		//taken the i/o pins in hand so that we can start the transmission
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */		//implies TWINT zero so transmission stopped
  switch ((twst = TW_STATUS))
    {
    case TW_MT_SLA_ACK:
      break;

    case TW_MT_SLA_NACK:	/* nack during select: device busy writing */
      /* Note [11] */
      goto restart;     //knows that mistake is due to the wrong instructions given to it and not due to its own mistake

    case TW_MT_ARB_LOST:	/* re-arbitrate */
      goto begin;         //knows that it committed some mistake - so it will try again

    default:
      goto error;		/* must send stop condition */
    }

  TWDR = (eeaddr>>8);		/* high 8 bits of addr */				//loading the data register with the data//65536 is 10^16 and eeaddr is 16 bits so will give highest 8 bits
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission *///eeaddr can't be greater than 16 bits
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_MT_DATA_ACK:
      break;

    case TW_MT_DATA_NACK:				

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      goto error;		/* must send stop condition */
    }

  TWDR = eeaddr;		/* low 8 bits of addr */
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_MT_DATA_ACK:
      break;

    case TW_MT_DATA_NACK:
      goto quit;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      goto error;		/* must send stop condition */
    }

  /*
   * Note [12]
   * Next cycle(s): master receiver mode
   */
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); /* send (rep.) start condition *///in order to enter master mode start condition needs to be sent//twsta=start condition bit
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_START:		/* OK, but should not happen */
    case TW_REP_START:
      break;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      goto error;
    }

  /* send SLA+R */
  TWDR = sla | TW_READ;				//master receiver mode pg 216
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_MR_SLA_ACK:
      break;

    case TW_MR_SLA_NACK:
      goto quit;

    case TW_MR_ARB_LOST:
      goto begin;

    default:
      goto error;
    }

  for (twcr = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);	len > 0;len--)		//twea=twi enable ack bit//for receiving the data it should send an ack bit even though it is master receiver//this also instructs the slave to start loading data on the bus
    {
      if (len == 1)
	twcr = _BV(TWINT) | _BV(TWEN); /* send NAK this time */			//pg 216
      TWCR = twcr;		/* clear int to start transmission */   //whichever of the two is right copy it to TWCR
      while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
      switch ((twst = TW_STATUS))		
	{
	case TW_MR_DATA_NACK:
	  len = 0;		/* force end of loop *///for loop ends automatically
				/* FALLTHROUGH */
	case TW_MR_DATA_ACK:
	  *buf++ = TWDR;			//reading from TWDR to buffer       //twdr contains the last byte received
	  rv++;				//counting the bits received
	  break;				//exits the nearby switch condition

	default:
	  goto error;    
	}
    }
 quit:
  /* Note [14] */
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); /* send stop condition */

  return rv;

 error:
  rv = -1;
  goto quit;
}

int eeprom_write_page(uint32_t eeaddr, int len, uint8_t *buf)
{
  uint8_t sla, n = 0;
  int rv = 0;
  uint16_t endaddr;
  
  ///* Added code for handling the two halves of the EEPROM
  if(eeaddr >= HALF_ADDR)
  {
    eeaddr -= HALF_ADDR;
    eeprom_addr |= 0x08;			
  }
  else
    eeprom_addr &= ~0x08;

  if (eeaddr + len < (eeaddr | (PAGE_SIZE - 1)))			//continuity in writing 
    endaddr = eeaddr + len;                   //if it doesnt pass
  else
    endaddr = (eeaddr | (PAGE_SIZE - 1)) + 1;         //if it does pass
  len = endaddr - eeaddr;              

  /* patch high bits of EEPROM address into SLA */
  sla = eeprom_addr;			

 restart:
  if (n++ >= MAX_ITER)				
    return -1;
 begin:

  /* Note [15] */
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); /* send start condition */
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_REP_START:		/* OK, but should not happen */
    case TW_START:
      break;
    case TW_MT_ARB_LOST:
      goto begin;
    default:
      return -1;		/* error: not in start condition */
      /* NB: do /not/ send stop condition */
    }

  /* send SLA+W */
  TWDR = sla | TW_WRITE;			//making master transmitter and slave receiver
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_MT_SLA_ACK:
      break;

    case TW_MT_SLA_NACK:	/* nack during select: device busy writing */
      goto restart;

    case TW_MT_ARB_LOST:	/* re-arbitrate */
      goto begin;

    default:
      goto error;		/* must send stop condition */
    }
	
	
  TWDR = (eeaddr>>8);		/* high 8 bits of addr */
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_MT_DATA_ACK:
      break;

    case TW_MT_DATA_NACK:
      goto quit;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      goto error;		/* must send stop condition */
    }


  TWDR = eeaddr;		/* low 8 bits of addr */
  TWCR = _BV(TWINT) | _BV(TWEN); /* clear interrupt to start transmission */
  while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */
  switch ((twst = TW_STATUS))
    {
    case TW_MT_DATA_ACK:
      break;

    case TW_MT_DATA_NACK:
      goto quit;

    case TW_MT_ARB_LOST:
      goto begin;

    default:
      goto error;		/* must send stop condition */
    }

  for (; len > 0; len--)
    {
      TWDR = *buf++;            //reading from buffer and writing the value into twdr- write and send 
      TWCR = _BV(TWINT) | _BV(TWEN); /* start transmission */         //master transmitter mode-twdr contains next byte to be transmitted-207- reading from buffer and storing it into twdr to get transmitted
      while ((TWCR & _BV(TWINT)) == 0) ; /* wait for transmission */     
      switch ((twst = TW_STATUS))
	{
	case TW_MT_DATA_NACK:
	  goto error;		/* device write protected -- Note [16] */

	case TW_MT_DATA_ACK:
	  rv++;
	  break;

	default:
	  goto error;
	}
    }
 quit:
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); /* send stop condition */

  return rv;

 error:
  rv = -1;
  goto quit;
}

int eeprom_write_bytes(uint32_t eeaddr, int len, uint8_t *buf)
{
  int rv, total;

  total = 0;
  do
    {
      rv = eeprom_write_page(eeaddr, len, buf);         //length for that particular function changes
      if (rv == -1)
        return -1;
      eeaddr += rv;             //rv number of bytes 
      len -= rv;
      buf += rv;
      total += rv;
    }
  while (len > 0);

  return total;
}

void error(void)
{

  exit(0);
}

