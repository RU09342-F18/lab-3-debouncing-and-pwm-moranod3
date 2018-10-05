#include <msp430.h>

int pwm = 500; // for PWM
int state = 0; //for debounce
void init(void);
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop WDT
    init();
    for(;;) //inf loop
    {
        if(TA0R <= pwm)
            P1OUT ^= BIT0; 
        else if (TA0R > pwm)
            P1OUT &= ~BIT0;
    }
}
#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
        switch(state)
        {
        case 0: //off -> on
                   TA1CTL = TASSEL_2 + MC_1 + TACLR;       // start timer
                   P1IFG &= ~BIT1;                         // Clear Flag
                   P1IE &= ~BIT1;                          // disable interrupts for button
                   break;
        case 1: //on -> off
                   TA1CTL = TASSEL_2 + MC_1 + TACLR;       //start timer
                   P1IFG &= ~BIT1;                         // Clear Flag
                   P1IE &= ~BIT1;                          // disable interrupts for button
                   break;
        }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A0 (void)
{
        switch(state)
        {
        case 0://on -> on
                    if(pwm < 1000) 
                        pwm += 100;
                    else pwm = 0;              
                    P1IE |= BIT1;               //enable interrupts
                    P1IES &= ~BIT1;              //change interrupt to low -> high
                    TA1CTL &= ~TASSEL_2;        //stop timer
                    TA1CTL |= TACLR;            //clear timer
                    state = 1;                  //go to next case
                    break;
                case 1://off -> off
                    P1IE |= BIT1;               //enable interrupt
                    P1IFG &= ~BIT1;             //clear interrupt flag
                    P1IES |= BIT1;              //change interrupt to high -> low
                    TA1CTL &= ~TASSEL_2;        //stop timer
                    TA1CTL |= TACLR;            //clear timer
                    state = 0;                  //when button pressed again go back to initial case
                    break;

        }
 }
void init (void) {

    /* LED Config */
        P1OUT &= ~BIT0;
        P1DIR |= BIT0;

    /* Timer Config */
        TA0CCR0 = 1000;
        TA0CTL = TASSEL_2 + MC_1 + TACLR; //smclock, up mode, clear timer to zero, enable timer a interrupts

        TA1CCTL0 = CCIE;                    // CCR1 interrupt enabled
        TA1CCR0 = 50000;                    //overflow every 10ms FOR DEBOUNCE

        /* Button Config */
        P1DIR &= ~BIT3;                         //p1.1 input
        P1REN |= BIT3;                          //enable possible pull up or pull down
        P1OUT |= BIT3;                          //pull up
        P1IE |= BIT3;                           //enable interupt
        P1IFG &= ~BIT3;                         //clear interrupt flag
        P1IES |= BIT3;                          //interrupt high -> low

        __enable_interrupt();    //enable interrupt
}
