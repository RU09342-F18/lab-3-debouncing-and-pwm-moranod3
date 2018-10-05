# How to Use the Code

To use the code simply program it onto the correct microcontroller and then power the microcontoller.

# MSP430G2553

This code shows how PWM can be used to control the power that is output from a microprocessor. In this example the power is then used to determine the dimness or brightness of the output led. The dimness or brightness is controlled by the duty cycle which is controlled by the PWM. This code is relatively similiar to the software PWM. The main difference is that this code utilizes OUTMOD. This code also doesn't need to use a switch case for the states like the software PWM. Essentially the software code utilized timers to control the PWM while this code utilizes onboard hardware to control the PWM. The idea is still very similiar though, however instead of using a variable to control the value of the PWM, instead the CCRO and CCR1 registers were controlled directly. This means the duty cycle was being directly manipulated. The duty cycle was controlled by changng CCR1. The higher CCR1's value was the higher higher the duty cycle and the brighter the light. The brightness was controlled by the speed of the LED blinking similiar to how it was controlled in the software PWM.

# MSP430FR2311 

These codes are very similiar, the main difference is that the FR2311 uses TIMER_B, while the G2553 uses TIMER_A. The FR2311 also has the line "PM5CTL0 &= ~LOCKLPM5;" in it's code that enables the GPIO for this microprocessor. The final set of differences is mostly syntax anything that isn't clock specific in the MSP430 has to have it's clock specified for the FR2311. For example, CCR0 for the MSP430 has to be TB0CCR0 for the FR2311.
