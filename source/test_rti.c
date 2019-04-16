#include "rti.h"
#include "test_rti.h"
#include "test_sci.h"

void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    if (notification == rtiNOTIFICATION_COMPARE0)
    {
        sciTest();
    }

}

void rtiTest(){
    rtiInit();                                                      // Initialize RTI module
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);                // Enable RTI Compare 0 interrupt notification
    _enable_interrupt_();                                           // Enable IRQ - Clear Interrupt flag in CPS register
    rtiStartCounter(rtiCOUNTER_BLOCK0);                             // Start RTI Counter Block 0

    while(1);                                                       // Infinite loop
}
