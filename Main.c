/********************************************************
 *                                                      *
 * M Y  R E A L  T I M E  O P R A T I N G  S Y S T E M  *
 *                                                      *
 *                                                      *
 *                J U N E  2 0 1 3                      *
 *                                                      *
 ********************************************************/

#include "Config.h"
#include "TaskManagement.h"
#include "USER TASKS.h"

// Declare your global variables here

extern void selectTask(void);
extern pTcb CreateNullTask(void);

void InitHardware()
{
    PORTB=0x06;
    DDRB=0xFF;

    PORTC=0x00;
    DDRC=0x00;

    PORTD=0x00;
    DDRD=0x00;


    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    MCUCR=0x00;


    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: 0.977 kHz
    // Mode: CTC top=OCR1A
    // OC1A output: Discon.
    // OC1B output: Discon.
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer 1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A=0x00;
    TCCR1B=0x0D;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x10;
    OCR1BH=0x00;
    OCR1BL=0x00;
    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK=0x10;

    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud Rate: 9600
    //UCSRA=0x00;
    //UCSRB=0x18;
    //UCSRC=0x86;
    //UBRRH=0x00;
    //UBRRL=0x06;

    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud Rate: 4800
    UCSRA=0x00;
    UCSRB=0x18;
    UCSRC=0x86;
    UBRRH=0x00;
    UBRRL=0x0C;
}

void main(void)
{
    // Declare your local variables here

    IncreaseResetCounter();

    CreateNullTask();
    CreateTask1();
    CreateTask2();
    
    InitHardware();

    // Start Task
    // Simulating context switching
    selectTask();
    RESTORE_CONTEXT();
    #asm("    RETI")

    while (1)
    {
        // Place your code here
        #asm("NOP");
    };
}
