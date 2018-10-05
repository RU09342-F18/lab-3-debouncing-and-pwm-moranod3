#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stops watchdog timer
    init();
    for(;;){
    }
}


#pragma vector=PORT1_VECTOR //Button Press Interrupt
__interrupt void Port_1(void) {
        P1IE &= ~BIT3;          //Disables interrupt on Pin 1.3 (BUTTON)
        WDTCTL = WDT_MDLY_32;   //Sets a Watchdog timmer delay to 32ms
        IE1 |= WDTIE;           //Enable WDT interrupt
        P1IFG &=~BIT3;           //clear flag
    }
    
#pragma vector=WDT_VECTOR //Watchdog Timer Interrupt
__interrupt void WDT_ISR (void) 
{
    IE1 &= ~WDTIE;      //Disables WDT interrupt
    IFG1 &= ~WDTIFG;    //clear flag
    WDTCTL = WDTPW | WDTHOLD;   // Disables watchdog timer

    if ((P1IN & BIT3) == 0)//Checks for button press
        P1OUT ^= BIT0; //Toggle PIN 1.0 (LED)
    P1IE |= BIT3;   //enable button interrupt

}
void init (void) {
    P1REN |= BIT3;          //Enables pull up/down on Pin 1.3 (BUTTON)
    P1OUT |= BIT3;          //Sets Pin 1.3 to be pull up
    P1DIR |= BIT0;          //Sets Pin 1.0 to be an output
    P1IE |= BIT3;           // Sets interrupt enable on Pin 1.3 (BUTTON) 
    P1IES |= BIT3;          // Interrupt on high to low on Pin 1.3
    P1IFG &= ~BIT3;          //Clear flags

   __bis_SR_register(LPM0_bits + GIE); //Enables interrupts
