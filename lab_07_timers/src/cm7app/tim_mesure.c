#include "tim_mesure.h"
#include "error_handler.h"
TIM_HandleTypeDef hTimMesure;
static volatile int caputure_done = 0;
static uint16_t captures[4]
    __attribute__((aligned(16))); // __attribute__((section(".dma_buffer")));
void Tim_Mesure_Init()
{
    /** Конфигруация в режим Input Compare */
    HAL_StatusTypeDef status = HAL_OK;
    hTimMesure.Instance = TIMm;
    hTimMesure.Init.Period = TIMm_PERIOD;
    hTimMesure.Init.Prescaler = TIMm_PRESCALER;
    hTimMesure.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    hTimMesure.Init.CounterMode = TIM_COUNTERMODE_UP;
    hTimMesure.Init.RepetitionCounter = 0;
    status = HAL_TIM_IC_Init(&hTimMesure);
    assert_hal_status(status);
    /* Конфигурация входного канала */
    TIM_IC_InitTypeDef sICConfig = {0};
    sICConfig.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
    sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sICConfig.ICPrescaler = TIM_ICPSC_DIV1;
    sICConfig.ICFilter = 0;
    status = HAL_TIM_IC_ConfigChannel(&hTimMesure, &sICConfig, TIMm_CHANNEL);
    assert_hal_status(status);
}
void Tim_Mesure_Deinit()
{
    HAL_StatusTypeDef status = HAL_TIM_IC_DeInit(&hTimMesure);
    assert_hal_status(status);
}
void Tim_Mesure_Start()
{
    caputure_done = 0;
    HAL_StatusTypeDef status =
        HAL_TIM_IC_Start_DMA(&hTimMesure, TIMm_CHANNEL, (uint32_t *)captures, 2);
    assert_hal_status(status);
}
void Tim_Mesure_Stop()
{
    HAL_StatusTypeDef status = HAL_TIM_IC_Stop_DMA(&hTimMesure, TIMm_CHANNEL);
    assert_hal_status(status);
}
uint16_t Tim_Mesure_GetDiff()
{
    if (captures[1] >= captures[0])
    {
        return captures[1] - captures[0];
    }
    else
    {
        return TIMm_PERIOD - captures[0] + captures[1];
    }
}
void Tim_Mesure_IC_Callback(TIM_HandleTypeDef *htim)
{
    if (htim == &hTimMesure)
    {
        if (htim->Channel == TIMm_DMA_ACTIVE_CHANNEL)
            caputure_done = 1;
    }
}
int Tim_Mesure_Wait_Once(uint32_t timeout)
{
    uint32_t time_limit = HAL_GetTick() + timeout;
    while (caputure_done == 0 && HAL_GetTick() < time_limit)
        ;
    if (caputure_done)
    {
        caputure_done = 0;
        return 1;
    };
    return 0;
}
/**** Функции обратного вызова библиотеки HAL *****************************************/
/** Переопредленные ниже функцию обрабатывают любые IC-таймеры и обычно помещаются в
отдельный *msp.c
* В нашей программе толко один PWM таймер, поэтому мы поместили эти функции здесь.
*/
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim == &hTimMesure)
    {
        HAL_StatusTypeDef status = HAL_OK;
        TIMm_CLK_ENABLE();
        TIMm_CH_CLK_ENABLE();
        TIMm_DMA_CLK_ENABLE();
        /* Конфигурация вывода на работу с таймером */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = TIMm_CH_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
        GPIO_InitStruct.Alternate = TIMm_CH_GPIO_AF;
        HAL_GPIO_Init(TIMm_CH_PORT, &GPIO_InitStruct);
        /* Инициализация DMA */
        static DMA_HandleTypeDef hdma_tim;
        hdma_tim.Instance = TIMm_DMA_STREAM;
        hdma_tim.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_tim.Init.MemInc = DMA_MINC_ENABLE;
        hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        hdma_tim.Init.Mode = DMA_CIRCULAR;
        hdma_tim.Init.Priority = DMA_PRIORITY_LOW;
        hdma_tim.Init.Request = TIMm_DMA_REQUEST;
        hdma_tim.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        hdma_tim.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
        hdma_tim.Init.MemBurst = DMA_MBURST_SINGLE;
        hdma_tim.Init.PeriphBurst = DMA_PBURST_SINGLE;
        /* Несколько указателей на DMA-дескрипторы в периферии должны указывать на один
        и тот же дескриптор DMA. Существует только один канал для выполнения всех запросов
        к DMA. */
        __HAL_LINKDMA(&hTimMesure, hdma[TIMm_DMA_ID], hdma_tim);
        status = HAL_DMA_Init(hTimMesure.hdma[TIMm_DMA_ID]);
        assert_hal_status(status);
        HAL_NVIC_SetPriority(TIMm_IRQn, 2, 0);
        HAL_NVIC_SetPriority(TIMm_DMA_IRQn, 3, 0);
        HAL_NVIC_EnableIRQ(TIMm_IRQn);
        HAL_NVIC_EnableIRQ(TIMm_DMA_IRQn);
    }
}
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim)
{
    if (htim == &hTimMesure)
    {
        HAL_GPIO_DeInit(TIMm_CH_PORT, TIMm_CH_PIN);
    }
};
