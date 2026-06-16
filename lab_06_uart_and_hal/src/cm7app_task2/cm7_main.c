#include "cm7_main.h"
#include "hal_helpers.h"

UART_HandleTypeDef huart2;

static uint8_t rx_byte;
static char hokku_buf[HOKKU_BUF_SIZE];
static volatile uint16_t hokku_pos = 0;
volatile uint16_t hokku_size = 0;
static volatile bool hokku_ready = false;
static char hokku_num[4] = "#00";

/******************************************************************/

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

    HAL_StatusTypeDef status = HAL_UART_Init(&huart2);

    if (status != HAL_OK) {
        printf("HAL_UART_Init failed: %s\r\n",
               HAL_Status_to_string(status));
        error_handler();
    }
}

/******************************************************************/

void error_handler(void) {

    while (1) {
        led_on(ERR_LED);
    }
}

/******************************************************************/

static void uart_receive_start(void) {

    HAL_StatusTypeDef status =
        HAL_UART_Receive_IT(&huart2, &rx_byte, 1);

    if (status != HAL_OK) {

        printf("HAL_UART_Receive_IT failed: %s\r\n",
               HAL_Status_to_string(status));

        error_handler();
    }
}

/******************************************************************/

int main(void) {

    __enable_irq();
    HAL_Init();
    HAL_RCCEx_EnableBootCore(RCC_BOOT_C2);
    vterm_init(115200);
    uart2_init();
    puts(u8"\r\nНажмите любую клавишу для запуска...");
    getchar();

    uart_receive_start();
    while (1) {
        if (hokku_ready) {
            hokku_ready = false;
            printf("\r\n%s Size=%d\r\n", hokku_num, hokku_size);
        }
    }
}

/******************************************************************/
/********************* CALLBACKS **********************************/
/******************************************************************/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance != USART2) return;

    led_toggle(RX_LED);

    // новый пакет начинается с '#'
    if (rx_byte == '#')
    {
        // если уже что-то накопили —
        // предыдущее хокку завершено
        if (hokku_pos > 0) {
            hokku_size = hokku_pos;
            hokku_ready = true;
        }

        // начать новое хокку
        hokku_pos = 0;
    }

    // сохранить символ
    if (hokku_pos < (HOKKU_BUF_SIZE - 1)) {
        hokku_buf[hokku_pos++] = rx_byte;
        hokku_buf[hokku_pos] = '\0';
    }

    // сохранить номер
    if (hokku_pos >= 3 && hokku_buf[0] == '#') {
        hokku_num[0] = hokku_buf[0];
        hokku_num[1] = hokku_buf[1];
        hokku_num[2] = hokku_buf[2];
        hokku_num[3] = '\0';
    }

    // restart RX
    HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
}

/******************************************************************/

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {

    printf("\r\nUART ERROR\r\n");
    printf("State: %s\r\n", HAL_UART_State_to_string (HAL_UART_GetState(huart)));
    printf("Error: %s\r\n", HAL_UART_Error_to_string (HAL_UART_GetError(huart)));

    error_handler();
}