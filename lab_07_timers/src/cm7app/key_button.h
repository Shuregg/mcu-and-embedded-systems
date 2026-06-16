#pragma once
/* Обработа кнопки KeyButton по внешнему прерыванию
Для того чтобы использовать этот драйвер необходимо
1) Опредлеить параметры кнопки с помощью макропооредлений в этом файле
2) В обработчике соответсвующей линии EXTI и вызвать
HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
3) Переопредлеить weak-функцию void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) и вызвать в
ней обработчик нажатия на кнопку */
#define KEY_BUTTON_PIN GPIO_PIN_13
#define KEY_BUTTON_PORT GPIOC
#define KEY_BUTTON_CLK_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE
#define KEY_BUTTON_IRQn EXTI15_10_IRQn
void Key_Button_EXTI_Init();