#include <stm32h7xx.h>
#include <assert.h>
#include <stdio.h>
#include <vterm.h>
#include <stdint.h>

#define APP_SRAM_OFFSET 0x24000000
#define APP_SRAM_ESTACK 0x24080000
#define APP_FLASH1_OFFSET 0x08080000
#define APP_FLASH1_END 0x080FFFFF

#define NO_KEYPRESSED UINT8_MAX
#define AUTOSTART_TIMEOUT_COUNTER 5000000

#define NUM_COMMANDS 6
#if NUM_COMMANDS > 9
#error NUM_COMMANDS must be less then 10 or change read_handler_index()
#endif
extern void HardFault_Handler();
uint32_t bootloader_SP = 0;

static const char *gc_help_msg =
    u8"\n\r┌────────────┬──────────────┬────────────┬────────────┬────────────┬─────────────┐"
    u8"\n\r│ 1:BootSRAM │ 2:UsageFault │ 3:BusFault │ 4:MemFault │ 5:assert() │ 6:BootFlash │"
    u8"\n\r└────────────┴──────────────┴────────────┴────────────┴────────────┴─────────────┘"
    u8"\n\r Выбор [1-6] > ";

static void do_BootSRAM();
static void do_UsageFault();
static void do_MemFault();
static void do_BusFault();
static void do_Assert();
static void do_User();
static void do_BootFlash();

int check_sram_app_valid();
int check_flash_app_valid();

typedef void (*handler_func_t)();

handler_func_t handlers[NUM_COMMANDS] = {
    do_BootSRAM,
    do_UsageFault,
    do_BusFault,
    do_MemFault,
    do_Assert,
    /*do_User*/ do_BootFlash
};
// uint8_t read_handler_index() {
//     while (vterm_keypressed() != 0);
//     char str[2];
//     int sz = vterm_gets(str, sizeof(str), 1);
//     if (sz < 1)
//     return UINT8_MAX;
//     return str[0] >= '1' ? str[0] - '1' : UINT8_MAX;
// }

uint8_t read_index() {
    uint8_t ch = vterm_keypressed();
    if (ch > 0) {
        putchar(ch);  // echo
        uint8_t idx = ch - '1';
        return idx;
    }
    return NO_KEYPRESSED;
}

void enable_fault_handlers() {
    // Включить генерацию исключений для UsageFault; cм. PM0253, п. 4.3.7 на стр. 200
    // SCB->CCR ...
    SCB->CCR |= (1UL << 3);
    
    // Разрешить генерацию исключений; см. PM0253, п. 4.3.9 на
    // стр. 204 SCB->SHCSR ...
    SCB->SHCSR |= (7UL << 16);
    // [18] USGFAULTENA UsageFault enable bit, set to 1 to enable(1)
    // [17] BUSFAULTENA BusFault enable bit, set to 1 to enable(1)
    // [16] MEMFAULTENA MemManage enable bit, set to 1 to enable(1)

}

__attribute__((optimize("-O0"))) static void delay(int ms) {
    volatile int counter = SystemCoreClock / 1000 / 6 * ms ;
    while (counter > 0) counter -= 1;
}

int main() {
    vterm_init(115200);
    int autostart_counter = 0;
    int autostart_div10_counter = 0;
    int app_is_valid = check_sram_app_valid();
    enable_fault_handlers();

    printf("\r\n System clock is %ld MHz.", SystemCoreClock / 1000000);
    printf("\n\n\r\n Welcome to bootloader! %s", gc_help_msg);
    for (uint8_t handler_index = NO_KEYPRESSED; ; handler_index = read_index()) {
        if (handler_index == NO_KEYPRESSED) {
            if(app_is_valid) {
                // Обработка до первого нажатия клавиши
                if(++autostart_counter == AUTOSTART_TIMEOUT_COUNTER) {
                    do_BootSRAM();
                } else if(autostart_counter > AUTOSTART_TIMEOUT_COUNTER / 10 * autostart_div10_counter) {
                    autostart_div10_counter += 1;
                    printf(u8"\rНажмите любую клавишу чтобы прервать автозагрузку AXI-SRAM  %d",
                        10 - autostart_div10_counter);
                }
            }
        } else {
            // Stop auto boot
            app_is_valid = 0;
            if(handler_index < NUM_COMMANDS && handlers[handler_index]) {
                handlers[handler_index]();
            }
            printf("\n\n\r\n Welcome to bootloader! %s", gc_help_msg);
        }
    }
    return 0;
}

/***************************** Обработчики команд ************************************/
void do_BootSRAM() {
    if(!check_sram_app_valid) {
        printf("\nNo valid app in AXI-SRAM at 0x%08x...\n", APP_SRAM_OFFSET);
    } else {
        printf("\nJumping to AXI-SRAM app at 0x%08lx...\n", APP_SRAM_OFFSET);

        // 1) Определить ТВП приложения, адреса начала стека и точки входа приложения
        const uint32_t* app_IV = (uint32_t*)(APP_SRAM_OFFSET);
        uint32_t* app_sp = app_IV[0];
        uint32_t* app_pc = app_IV[1];

        printf("\n1 (0x%x)\n", app_sp);
        printf("\n2 (0x%x)\n", app_pc);
        printf("\n3\n");
        bootloader_SP = __get_MSP();
        
        // Доп.1.) Признак того, что был запуск приложения bootloader_SP != 0
        printf("\n4\n");

        // 2) Отключить все прерывания
        __disable_irq();
        printf("\n5\n");
            
        // 3) заменить текущий адрес стека на начальный адрес стека приложения
        __set_MSP(app_sp);
        // printf("\n6\n");

        // 4) задать новый адрес таблицы векторов прерываний
        SCB->VTOR = app_IV;
        // printf("\n7\n");
        
        // Доп.2) Заменили обработчика HardFault в ТВП на собственный
        NVIC_SetVector(HardFault_IRQn, (uint32_t)HardFault_Handler);

        // Инвалидация кеша инстуркций у ядра Cortex-M7
        SCB_InvalidateICache();
        
        // 5) Безусловный переход на точку входу
        __ASM volatile("bx %0" ::"r"(app_pc));
        
        while(1);
    }
    return;
}

void do_UsageFault() {
    // Отслеживаемые ошибки задаются в SCB->UFSR (PM0253.rev5 стр. 209 )
    // Например, деление на ноль, Доступ к невыровненным данным
    int a = 4;
    int b = a / 0;
    printf("b = a / 0 = %d", b);
}

void do_MemFault() {
    // Нарушение аттрибутов памяти
    // например, попытка выполнения кода из области памяти для переферийных устройств
    void *ptr = (void *)0x40000000;
    goto *ptr;
}

void do_BusFault() {
    // Ошибка доступа к памяти по шине
    // Например, попытка чтения из отсутствующей внешней памяти (0х60000000)
    uint32_t a = (*(uint32_t*)((void*)0x60000000));
    printf("Try to read from 0x60000000: 0x%lx", a);
}

void do_Assert() { assert(!"Assertion example"); }
void do_User() { puts(u8"\r\nВнезапно выпал снег\n"); }

// Task 2 - Check and Autorun
int check_sram_app_valid() {
    const uint32_t* app_IV = (uint32_t*)(APP_SRAM_OFFSET);
    return (app_IV[0] == APP_SRAM_ESTACK && app_IV[1] < APP_SRAM_ESTACK && app_IV[1] > APP_SRAM_OFFSET);
}

// Task 3 - Boot Load from FLASH
int check_flash_app_valid() {
    const uint32_t* app_IV = (uint32_t*)(APP_FLASH1_OFFSET);
    return (app_IV[0] == APP_FLASH1_OFFSET && app_IV[1] < APP_FLASH1_END && app_IV[1] > APP_FLASH1_OFFSET);
}

void do_BootFlash() {
    printf("\nJumping to FLASH1 app at %08lx....\n", APP_FLASH1_OFFSET);

    // 1) Определить ТВП приложения, адреса начала стека и точки входа приложения
    const uint32_t* app_IV = (uint32_t*)(APP_FLASH1_OFFSET);
    uint32_t app_end_stack = (*((uint32_t *)(app_IV)));
    void* app_entry = (void *)(*((uint32_t *)(APP_FLASH1_OFFSET + 4)));

    // Доп.1.) Признак того, что был запуск приложения bootloader_SP != 0
    bootloader_SP = __get_MSP();

    // 2) Отключить все прерывания
    __disable_irq();

    // 3) заменить текущий адрес стека на начальный адрес стека приложения
    __set_MSP(app_end_stack);

    // 4) задать новый адрес таблицы векторов прерываний
    SCB->VTOR = app_IV;

    // Доп.2) Заменили обработчика HardFault в ТВП на собственный
    NVIC_SetVector(HardFault_IRQn, (uint32_t)HardFault_Handler);

    // Инвалидация кеша инстуркций у ядра Cortex-M7
    SCB_InvalidateICache();

    // 5) Безусловный переходapp_IV на точку входу
    __ASM volatile("bx %0" ::"r"(app_entry));
}