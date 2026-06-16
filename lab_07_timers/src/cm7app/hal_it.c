#include "main.h"


void HardFault_Handler(){
    error_state(__FUNCTION__);
}

void SysTick_Handler(){
    HAL_IncTick();
}