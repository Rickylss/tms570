#include "sci.h"
#include "test_sci.h"

#define  TSIZE1 10
uint8  TEXT1[TSIZE1]= {'H','E','R','C','U','L','E','S',' ',' '};
#define  TSIZE2 18
uint8  TEXT2[TSIZE2]= {'M','I','C','R','O','C','O','N','T','R','O','L','L','E','R','S',' ',' '};
#define  TSIZE3 19
uint8  TEXT3[TSIZE3]= {'H','E','L','L','O',' ',' '};

static unsigned char command;    // A variable declared to store received character

static void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length){
    while(length--)
    {
        while ((sciREG->FLR & 0x4) == 4); /* wait until busy */
        sciSendByte(sciREG,*text++);      /* send out text   */
    };
}

void sciNotification(sciBASE_t *sci, uint32 flags)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (29) */
    if ((flags & (uint32)SCI_RX_INT) == (uint32)SCI_RX_INT) {                   // sci Interrupt Notification called when RI occurs
        sciSend(sci, 1, (unsigned char *)&command);                          // Echo received character back to user
        sciReceive(sci, 1,(unsigned char *)&command);                           // Await furter character
    }
/* USER CODE END */
}

static void sciTX(void){
    while(1){
    sciDisplayText(sciREG,&TEXT1[0],TSIZE1);
    sciDisplayText(sciREG,&TEXT2[0],TSIZE2);   /* send text code 2 */
    sciDisplayText(sciREG,&TEXT3[0],TSIZE3);   /* send text code 3 */
}

static void sciRX(void){
    _enable_interrupt_();                                                  // Enable the IRQ & FIQ
    sciInit();                                                              // Initialize the SCI driver
    sciSend(sciREG, 21, (unsigned char *)"Please press a key!\r\n");       // Send user prompt
    sciReceive(sciREG, 1,(unsigned char *)&command);                       // Await user character
    while(1);                                                               // Infinite loop
}

void sciTest(void){

    sciTX();

    //sciRX();
}

