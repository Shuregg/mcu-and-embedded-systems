#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Активное ожидание с индикацией светодиодами, пока кнопка пользователя не будет отпущена
 * @note Вызов конфигурирует ресурсы GPIO для чтения состояния кнопки без обратного 
 */
void wait_for_blue_button_release();

#ifdef __cplusplus
}
#endif