#include "cm7_main.h"

UART_HandleTypeDef huart2;

/******************** HISTORY BUFFER ************************/

static char hokku_history[HOKKU_HISTORY][HOKKU_MAX_SIZE];
static uint32_t history_index = 0;
static char current_hokku[HOKKU_MAX_SIZE];
static uint32_t current_pos = 0;
static uint8_t dma_rx_byte;

static void uart2_init(void) {
    huart2.Instance = USART2;

    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT;
    huart2.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        error_handler();
    }
}

/************************************************************/

void error_handler(void) {
    while (1) {
        led_toggle(ERR_LED);
        HAL_Delay(100);
    }
}

/************************************************************/

static void save_current_hokku(void) {
    if (current_pos == 0) { return; }

    strcpy(hokku_history[history_index], current_hokku);
    history_index++;
    history_index %= HOKKU_HISTORY;
}

/************************************************************/

static void print_hokku_reversed(const char *hokku) {
    const char *parts[10];
    int part_count = 0;
    
    // Копируем строку для токенизации
    char temp[HOKKU_MAX_SIZE];
    strncpy(temp, hokku, HOKKU_MAX_SIZE - 1);
    temp[HOKKU_MAX_SIZE - 1] = '\0';
    
    // Разбиваем по '|'
    char *saveptr;
    char *token = strtok_r(temp, "|", &saveptr);
    while (token != NULL && part_count < 10) {
        parts[part_count++] = token;
        token = strtok_r(NULL, "|", &saveptr);
    }
    
    // Выводим в обратном порядке (пропуская номер - parts[0])
    // part_count-1 это последняя строка, part_count-2 предпоследняя и т.д.
    for (int i = part_count - 1; i >= 1; i--) {
        printf("%s", parts[i]);
        if (i > 1) {
            printf("\r\n");
        }
    }
    printf("\r\n\r\n");
}

static void print_last_3_hokku(void) {

    for (int i = 0; i < HOKKU_HISTORY; i++) {

        int idx = (history_index + i) % HOKKU_HISTORY;

        if (strlen(hokku_history[idx]) == 0) { continue; }
        print_hokku_reversed(hokku_history[idx]);
    }
}

int main(void)
{
    HAL_Init();
    vterm_init(115200);
    
    led_enable(RX_LED);
    led_enable(ERR_LED);
    
    uart2_init();
    
    puts(u8"\r\nНажмите любую клавишу для запуска...");
    getchar();
    
    HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);
    puts(u8"\r\nDMA хоккуанализатор запущен\r\n");

    __HAL_DMA_DISABLE_IT(huart2.hdmarx, DMA_IT_HT);

    while (1) {
        if (vterm_keypressed() > 0) {
            if (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, dma_buf, DMA_BUF_SIZE) != HAL_OK) {
                // Ошибка перезапуска → очищаем флаг DMA и пробуем снова
                __HAL_DMA_DISABLE(huart2.hdmarx);
                __HAL_DMA_CLEAR_FLAG(huart2.hdmarx, DMA_FLAG_TCIF0_4);
                HAL_UARTEx_ReceiveToIdle_DMA(&huart2, dma_buf, DMA_BUF_SIZE);
            }
            getchar();

            print_last_3_hokku();
        }
    }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance != USART2) return;

    for (uint16_t i = 0; i < Size; i++) {
        uint8_t ch = dma_buf[i];
        led_toggle(RX_LED);

        if (ch == '#') {
            save_current_hokku();
            current_pos = 0;
        }

        if (current_pos < (HOKKU_MAX_SIZE - 1)) {
            current_hokku[current_pos++] = ch;
            current_hokku[current_pos] = '\0';
        }
    }
}

/************************************************************/

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    printf("\r\nUART ERROR\r\n");
    printf("State: %d\r\n", HAL_UART_GetState(huart));
    printf("Error: %lu\r\n", HAL_UART_GetError(huart));
    error_handler();
}