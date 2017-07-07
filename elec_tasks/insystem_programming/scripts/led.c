#include <avr/io.h>; 

int main(){

    DDRB = 0b00000001; //Pin B0 becomes output pin 
    PORTB = 0b00000000; //set B0 to Low 
    TCCR1B |= 1<<CS10 | 1<<CS11; //set Prescaler 
    while(1){
        if(TCNT1>2232){ //2232=65536/7 
            TCNT1=0; //reset counter 
            PORTB ^= 1<<PINB0; //toggle LED 
        }
    }
}