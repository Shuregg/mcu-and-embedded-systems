/**
 * @file bootloader.c
 * @author S.B. Simonov
 * @date 20.04.2026
 *  Автозагрузчик приложения из AXI-SRAM с перехватом HardFault и опцией запуска ядра СM4  */

#include <stdbool.h>
#include <stdio.h>
#include <stm32h7xx.h>
#include <vterm.h>

#define AXI_SRAM_BEGIN_ADDR 0x24000000
#define AXI_SRAM_END_ADDR 0x24080000
#define APP_BEGIN_ADDR 0x24000000
#define APP_STACK_ADDR 0x24080000
#define AUTOSTART_TIMEOUT_COUNTER 5000000
#define NO_KEYPRESSED UINT8_MAX
#define NUM_COMMANDS 3
#define IN_BOUNDS(BOTTOM, VAL, TOP) ((VAL) >= (BOTTOM) && (VAL) <= (TOP))

volatile uint32_t bootloader_SP = 0;
void HardFault_Handler();
bool check_app_is_valid(uint32_t iv_address, uint32_t sp_address, uint32_t ram_begin, uint32_t ram_end);
void do_BootSRAM();
void do_RunCM4();

/***************************** Boot Menu ************************************/

const char* menu_title =
    u8"\n\r Welcome to bootloader"
    u8"\n\r┌─────────────┬─────────────┬────────────┐"
    u8"\n\r│ 1:Boot SRAM │ 2: Run CM4  │ 3: Reset   │"
    u8"\n\r└─────────────┴─────────────┴────────────┘"
    u8"\n\r Выбор [1-3] > ";

void (*handlers[NUM_COMMANDS])() = {do_BootSRAM, do_RunCM4, NVIC_SystemReset};

uint8_t read_index() {
    uint8_t ch = vterm_keypressed();
    if (ch > 0) {
        putchar(ch);  // echo
        return ch - '1';
    }
    return NO_KEYPRESSED;
}

/***************************** Main Loop ************************************/
int main() {
    vterm_init(115200);
    bool ready_for_autoboot =
        check_app_is_valid(APP_BEGIN_ADDR, APP_STACK_ADDR, AXI_SRAM_BEGIN_ADDR, AXI_SRAM_END_ADDR);
    int autoboot_counter = 0;
    int autoboot_div10_counter = 0;
    printf("\n\n\r\n Welcome to bootloader! %s", menu_title);
    for (uint8_t menu_index = NO_KEYPRESSED; true; menu_index = read_index()) {
        if (menu_index == NO_KEYPRESSED) {
            if (ready_for_autoboot) {
                // Обработка до первого нажатия клавиши
                if (++autoboot_counter == AUTOSTART_TIMEOUT_COUNTER) {
                    do_BootSRAM();
                } else if (autoboot_counter > AUTOSTART_TIMEOUT_COUNTER / 10 * autoboot_div10_counter) {
                    autoboot_div10_counter += 1;
                    printf(u8"\rНажмите любую клавишу чтобы прервать автозагрузку AXI-SRAM  %d",
                           10 - autoboot_div10_counter);
                }
            }
        } else {
            // Обработка нажатия клавиши
            ready_for_autoboot = false;  // stop auto boot
            if (menu_index < NUM_COMMANDS && handlers[menu_index]) {
                handlers[menu_index]();
            }
            printf("\r\n Welcome to bootloader! %s", menu_title);
        }
    }  // for
    return 0;
}

/****************************************************************************************/
bool check_app_is_valid(uint32_t iv_address, uint32_t sp_address, uint32_t ram_begin, uint32_t ram_end) {
    const uint32_t* app_IV = (uint32_t*)(iv_address);
    return (app_IV[0] == sp_address) && IN_BOUNDS(ram_begin, sp_address, ram_end) &&
           IN_BOUNDS(ram_begin, app_IV[1], ram_end);
}

void do_RunCM4() {
    SET_BIT(RCC->GCR, RCC_GCR_BOOT_C2);
}

void do_BootSRAM() {
    if (check_app_is_valid(APP_BEGIN_ADDR, APP_STACK_ADDR, AXI_SRAM_BEGIN_ADDR, AXI_SRAM_END_ADDR)) {
        printf("\n No valid application in AXI-SRAM at 0x%08x found!\n", APP_BEGIN_ADDR);
        return;
    }
    const uint32_t* app_IV = (uint32_t*)APP_BEGIN_ADDR;
    uint32_t app_end_stack = app_IV[0];
    void* app_entry = (void*)app_IV[1];
    printf("\r\n Jumping to AXI-SRAM application Reset Handeler at %p...\n", app_entry);
    bootloader_SP = __get_MSP();
    __disable_irq();
    __set_MSP(app_end_stack);
    SCB->VTOR = (uint32_t)app_IV;
    NVIC_SetVector(HardFault_IRQn, (uint32_t)HardFault_Handler);
    __DSB();
    __ISB();
    __ASM volatile("bx %0" ::"r"(app_entry));
    while (1)
        ;
}

/***************************** HardFault_Handler() ************************************/
void HardFault_Handler() {
    if (bootloader_SP) {
        __set_MSP(bootloader_SP);
        vterm_init(115200);
        printf("\r\nApplication HardFault exception; SCB->VTOR=%p\r\n", (void*)SCB->VTOR);
    } else {
        puts("\r\nBootloader HardFault exception\r\n");
    }
    NVIC_SystemReset();
}