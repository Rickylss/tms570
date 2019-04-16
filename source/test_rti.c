#include "test_sci.h"

void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    gioSetPort(gioPORTB, gioGetPort(gioPORTB) ^ 0x000000C0);        // Toggle GIOB6, GIOB7 (USER LEDs on the board)
}

void rtiTest(){
    rtiInit();                                                      // Initialize RTI module
    gioREG->GCR0 = 1U;                                              // Set the Global Control Register
    gioSetDirection(gioPORTB, 0xFF);                                // Set GIO port pin direction to all output
    rtiEnableNotification(rtiREG1,rtiNOTIFICATION_COMPARE0);        // Enable RTI Compare 0 interrupt notification
    _enable_interrupt_();                                           // Enable IRQ - Clear Interrupt flag in CPS register
    rtiStartCounter(rtiREG1,rtiCOUNTER_BLOCK0);                     // Start RTI Counter Block 0

    while(1);                                                       // Infinite loop
}
