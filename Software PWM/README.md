# How to Use the Code

To use the code simply program it onto the correct microcontroller and then power the microcontoller.

# MSP430G2553

This code shows how PWM can be used to control the power that is output from a microprocessor. In this example the power is then used to determine the dimness or brightness of the output led. The dimness or brightness is controlled by the duty cycle which is controlled by the PWM. The PWM is controlled by a variable of type int that is 16 bits long. This variable is used as the value of a clock. This clock then determines how fast the LED blinks, which correlates to how dim or bright the LED is. So the higher the pwm variable is the faster the LED blinks, which makes it look brighter. When the button is pressed and interrupt is triggered that increments the pmw by 100 and therefore makes the LED appear brighter. Once the pwm variable overflows or is incremented over 1000 the variable is reset to 0. So everytime the button is pressed the duty cycle is increased by 10% and therfore the LED becomes 10% brighter.

# MSP430F5529

These codes are identical other than the ports that are used for the inputs and outputs, since the layout of the boards are different.



