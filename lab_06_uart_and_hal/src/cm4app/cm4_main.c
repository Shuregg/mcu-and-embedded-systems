#include "cm4_main.h"
#include <stm32h7xx_hal.h>
#include <stm32h7xx_ll_utils.h>
#include <assert.h>

UART_HandleTypeDef huart;

char hokkus[] = u8"#01|Старый пруд.|Прыгнула в воду лягушка.|Всплеск в тишине."
                "#02|Хорошо по воде брести|Через тихий летний ручей|C сандалиями в руке."
                "#03|О, с какой тоской|Птица из клетки глядит|На полет мотылька!"
                "#04|Вода так холодна!|Уснуть не может чайка,|Качаясь на волне."
                "#05|Сочла кукушка|Мгновения летних дней|И улетела."
                "#06|Тишина кругом.|Проникают в сердце скал|Голоса цикад."
                "#07|Убил паука,|И так одиноко стало|В холоде ночи."
                "#08|Чужих меж нами нет!|Мы все друг другу братья|Под вишнями в цвету."
                "#09|Отсечь слова.|Ненужное отбросить.|Радостно вздохнуть."
                "#10|На полпути.|Не остановится|Цветков паденье!"
                "#11|Снег все сыплет|И сыплет,|Если на него смотреть."
                "#12|Зимняя ночь.|Закипает уха|Из озерной рыбы."
                "#13|Лист сакуры...|Такой же формы вырезаю|Из листка бумаги.";

void error_handler() {
    while (1)
        led_on(SIGNAL_LED);
}

void assert_failed(uint8_t *file, uint32_t line) {
    led_on(SIGNAL_LED);
    __assert_func((const char *)file, line, "assert_failed", "");
};

static void uart_init() {
    huart.Instance = UART5;
    huart.Init.BaudRate = 9600;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.Mode = UART_MODE_TX;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK) { // calls HAL_UART_MspInit()
        error_handler();
    }
}

int main() {
    HAL_Init(); // it calls HAL_MspInit()
    uart_init();
    if (HAL_UART_Transmit_DMA(&huart, (uint8_t *)hokkus, (uint16_t)(sizeof(hokkus)) - 1) != HAL_OK) {
        error_handler();
    }
    led_toggle(led_yellow);
    while(1);
}
// ******************* CallBacks ***********************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    (void)(huart);
    led_on(SIGNAL_LED);
    LL_mDelay(100);
    led_off(SIGNAL_LED);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    (void)(huart);
    error_handler();
}