#include <msp430.h>

void init(void);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stops watchdog timer
    init();
    for(;;);
}

//button interrupt
#pragma vector=PORT1_VECTOR         //Interrupt when Button is pressed
__interrupt void Port_1(void)
{
    P1IE &= ~BIT1;                          //Disable interrupt on Pin 1.1 (BUTTON)
    if((P1IN & BIT1)==0){
            if (TB1CCR1<1000)              //Checks to see if below max PWM
                TB1CCR1+=100;               //increment duty cycle by 10%
             else
                TB1CCR1 = 0;                //Reset duty cycle to 0
    }
           P1OUT ^= BIT0;                   //Toggle PIN 1.0
          __delay_cycles(5000);             //Delay cycles to prevent button bouncing
           P1IE |= BIT1;                     //Enable interrupt on Pin 1.1 (BUTTON)
           P1IFG &= ~BIT1;                  //clear flags
}
void init(void){
    PM5CTL0 &= ~LOCKLPM5;         //Enable GPIO

    P1DIR |= BIT0;              // Set PIN 1.0 direction to output
    P2DIR |= BIT0;              // Set PIN 2.0 direction to output
    P2SEL0 |= (BIT0);              //sets PIN 2.0 as output
    P2SEL1 &= ~BIT0;
    P1DIR &= ~BIT1;                      //set PIN 1.3 direction to input
    P1REN |= BIT1;                       //enable resistor on PIN 1.1 (BUTTON)
    P1OUT |= BIT1;                       //set resistor to pull up
    P1IE |= BIT1;                       //enable interrupt on PIN 1.1 (BUTTON)
    P1IES |= BIT1;                      //Set interrupt from high -> low on button press
    P1IFG &= ~BIT1;                     //Clear interrupt flags

       //timer B1 for PWM
    TB1CTL = TBSSEL_2 + MC_1;          // SMCLK, Up Mode
    TB1CCR0 = 1000;                         // set max PWM to 1000 clock cycles. So when TB1CCR1 = 1000 the DutyCycle = 100%.
    TB1CCR1 = 0;                         // set duty cycle to 0%
    TB1CCTL1 = OUTMOD_7;                   // set timer to Set/Reset mode


    __enable_interrupt(); // enable interrupts
}
