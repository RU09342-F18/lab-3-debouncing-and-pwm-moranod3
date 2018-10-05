# How to Use the Code

To use the code simply program it onto the correct microcontroller and then power the microcontoller.

# MSP430G2553

The point of this code was to show how to prevent a button from bouncing by means of software. This is done by essentially turning the watchdog timer on at certain points (when the button is pressed), which in essence force resets the board and prevents the LED from reacting to button bouncing. Normally button bounce can be prevented through a time delay line. The issue with this is that normally a time delay lineis implemented by the compiler by filling in that area in the code with "gibberish" code that simply waste time. This means that no other task can be completed at this time by the processor. The way the debounce prevention was implemented in my code allows for the processor to complete task during prevention. 

# MSP432

This code was implemented by using interrupts like the MSP430 code. The main difference is that this code did not utilize the watchdog timer to put the processor in a psuedo sleep state. Instead the code simple used a for loop that delays all other processes that are non-interrupts. This means that while other task can't be completed during the debounce prevention delay, interrupts can be processed. Since this code has nothing else going on but interrupts this process does thejob.

