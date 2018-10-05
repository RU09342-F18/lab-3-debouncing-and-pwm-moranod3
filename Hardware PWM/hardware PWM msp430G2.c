#include <msp430.h> 


/**
 * main.c
 */
void init (void);
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;            //Watchdog disabled 
    init();
    for (;;){
}
}

#pragma vector = PORT1_VECTOR //Button press interrupt
__interrupt void Port_1(void)
{
    if((P1IN & BIT3) == 0) //Checks if button is still pressed
    {
        P1OUT ^= BIT1; //Toggles LED on PIN 1.0

        if(CCR1 < CCR0)
            CCR1 += 100; //increments duty cycle by 10%
        else
            CCR1 = 0;
    }
    P1IFG &= ~BIT3; //Resets interrupt flag initially triggered
}

void init(void){
    BCSCTL3 = LFXT1S_2;                  //Enables crystal
    P1DIR |= 0X41;                       //PIN 1.6 (GREEN LED) and PIN 1.0 (RED LED) is output
    P1SEL |= 0X40;                       //Pin 1.6 selected for PWM
    P1OUT |= BIT3;                       //Pull down resistor
    P1REN |= BIT3;                       //Sets BIT3 to be enabled
    P1IE |= BIT3;                        //Enables interrupt on Pin 1.3 (Button)
    P1IES |= BIT3;                       //Enables high - to - low behavior on interrupt (Button press)

    CCR0 = 1000; //PWM Period (1KHZ)
    CCTL1 = OUTMOD_7;
    CCR1 = 0; //This code will initially start at 0% Duty Cycle
    TACTL = TASSEL_2 + MC_1; //SMCLK, Up Mode
    __enable_interrupt();
}
