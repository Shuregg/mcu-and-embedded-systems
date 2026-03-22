#include "stm32h7xx.h"
#include <stdio.h>
#include <vterm.h>

extern uint32_t bootloader_SP;

void MemManage_Handler() {
    puts("\r\nMemory Management Fault exception!");

    uint32_t mmfsr = (SCB->CFSR) & SCB_CFSR_MEMFAULTSR_Msk;
    printf("MMFSR = 0x%02lx\n\r", mmfsr);

    if (mmfsr & 0x01) {
        puts("The processor attempted an instruction fetch from a location that "
            "does not permit execution");
    }
    if (mmfsr & 0x80)
    printf("MMFAR = 0x%lx\n\r", (SCB->MMFAR));
    NVIC_SystemReset();
}

void HardFault_Handler() {
    if (bootloader_SP) {
        __set_MSP(bootloader_SP);
        bootloader_SP = 0;
        vterm_init(115200);
        puts("\r\nApplication HardFault exception\r\n");
    } else {
        puts("\r\nBootloader HardFault exception\r\n");
    }
    NVIC_SystemReset();
}

void UsageFault_Handler() {
    uint32_t ufsr = SCB->UFSR;
    puts("\r\nUsage Fault exception!");
    printf("\r\n UFSR = 0x%x", ufsr);
    if(ufsr & 1)
        printf("\r\nUNDEFINSTR");
    if(ufsr & 2)
        printf("\r\nINVSTATE");
    if(ufsr & 4)
        printf("\r\nINVPC");
    if(ufsr & 8)
        printf("\r\nNOCP");
    if(ufsr & 256)
        printf("\r\nUNALIGNED");
    if(ufsr & 512)
        printf("\r\nDIVBYZERO");

    NVIC_SystemReset();
}

void BusFault_Handler() {
    uint32_t bfsr = SCB->BFSR;
    puts("\r\nBus Fault exception!");
    printf("\r\n UFSR = 0x%x", bfsr);

    NVIC_SystemReset();
}