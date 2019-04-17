#include "test_vim.h"
#include "sys_vim.h"
#include "rti.h"
#include "sci.h"

//sci中断方式循环输出字符串，rti定时打断循环输出。
void vimTest(void){
    rtiInit();                                                      // Initialize RTI module
    sciInit();
    vimInit();                                                      // Initialize vim module sci interrupt set as irq
    vimEnableInterrupt(2,SYS_FIQ);                                  // set RTI Compare 0 interrupt as fiq
    _enable_interrupt_();

    g_sciTransfer_t[index].mode = (uint32)1 << 8U                   // the data is sent using interrupt mode
    sciSend(sciREG, 21, (unsigned char *)"Please press a key!\r\n");

    rtiStartCounter(rtiCOUNTER_BLOCK0);                             // Start RTI Counter Block 0
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);                // Enable RTI Compare 0 interrupt notification


}
