/******************************************************************************
 *                                                                            *
 *  FileName            : Context.h			                                  *
 *  Date                : June 2013                                           *
 *  Description         : Context switching and 	                          *
 *						  critical section macros.	                          *
 *                                                                            *
 ******************************************************************************/
           
#ifndef CONTEXT_H_
#define CONTEXT_H_
      
// Critical section
// Enter to critical section simply disable global interrupt.
#define ENTER_CRITICAL	#asm("cli")

// Critical section
// Exit from critical section simply enable again globl interupt.
#define EXIT_CRITICAL	#asm("sei")

// Save context of task
#define SAVE_CONTEXT()	#asm("\
    PUSH R0\
    IN R0,SREG\
    PUSH R0\
    PUSH R1\
    PUSH R2\
    PUSH R3\
    PUSH R4\
    PUSH R5\
    PUSH R6\
    PUSH R7\
    PUSH R8\
    PUSH R9\
    PUSH R10\
    PUSH R11\
    PUSH R12\
    PUSH R13\
    PUSH R14\
    PUSH R15\
    PUSH R16\
    PUSH R17\
    PUSH R18\
    PUSH R19\
    PUSH R20\
    PUSH R21\
    PUSH R22\
    PUSH R23\
    PUSH R24\
    PUSH R25\
    PUSH R26\
    PUSH R27\
    PUSH R30\
    PUSH R31\
    LDS R30,_CurrentTask	\
    LDS R31,_CurrentTask+1	\
    STD Z+0,R28\
    STD Z+1,R29\
    IN  R26,SPL\
    IN  R27,SPH\
    STD Z+2,R26\
    STD Z+3,R27")

// Restore context of task
#define RESTORE_CONTEXT()	#asm("\
    LDS R30,_CurrentTask	\
    LDS R31,_CurrentTask+1	\
    LDD R26,Z+2\
    LDD R27,Z+3\
    OUT SPL,R26\
    OUT SPH,R27\
    LDD R28,Z+0\
    LDD R29,Z+1\
    POP R31\
    POP R30\
    POP R27\
    POP R26\
    POP R25\
    POP R24\
    POP R23\
    POP R22\
    POP R21\
    POP R20\
    POP R19\
    POP R18\
    POP R17\
    POP R16\
    POP R15\
    POP R14\
    POP R13\
    POP R12\
    POP R11\
    POP R10\
    POP R9\
    POP R8\
    POP R7\
    POP R6\
    POP R5\
    POP R4\
    POP R3\
    POP R2\
    POP R1\
    POP R0\
    OUT SREG,R0\
    POP R0")

#endif

