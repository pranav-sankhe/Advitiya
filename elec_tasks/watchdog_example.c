#include "mbed.h"
// LEDs used to indicate code activity and reset source
DigitalOut myled1(LED1); //in main loop part 1
DigitalOut myled2(LED2); //in main loop part 2 (where fault occurs)
DigitalOut myled3(LED3); //The pushbutton or power on caused a reset
DigitalOut myled4(LED4); //The watchdog timer caused a reset
 

class Watchdog {
public:
// Load timeout value in watchdog timer and enable
    void kick(float s) {
        LPC_WDT->WDCLKSEL = 0x1;                // Set CLK src to PCLK
        uint32_t clk = SystemCoreClock / 16;    // WD has a fixed /4 prescaler, PCLK default is /4
        LPC_WDT->WDTC = s * (float)clk;
        LPC_WDT->WDMOD = 0x3;                   // Enabled and Reset
        kick();
    }
// "kick" or "feed" the dog - reset the watchdog timer
// by writing this required bit pattern
    void kick() {
        LPC_WDT->WDFEED = 0xAA;
        LPC_WDT->WDFEED = 0x55;
    }
};
 
// Setup the watchdog timer
Watchdog wdt;
 
int main() {
    int count = 0;
// On reset, indicate a watchdog reset or a pushbutton reset on LED 4 or 3
    if ((LPC_WDT->WDMOD >> 2) & 1)
        myled4 = 1; else myled3 = 1;
        
// setup a 10 second timeout on watchdog timer hardware
// needs to be longer than worst case main loop exection time
    wdt.kick(10.0);  
 
// Main program loop - resets watchdog once each loop iteration
// Would typically have a lot of code in loop with many calls
    while (1) {
        myled1 = 1; //Flash LEDs 1 & 2 to indicate normal loop activity
        wait(.05);
        myled1 = 0;
        myled2 = 1;
        wait(.05);
// Simulate a fault lock up with an infinite while loop, but only after 25 loop iterations
        if (count == 25) while (1) {};
// LED 2 will stay on during the fault
        myled2 = 0;
        count ++;
// End of main loop so "kick" to reset watchdog timer and avoid a reset
        wdt.kick();
    }
}
