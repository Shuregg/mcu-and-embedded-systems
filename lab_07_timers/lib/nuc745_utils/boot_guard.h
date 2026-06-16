#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Активное ожидание с индикацией светодиодами, пока кнопка пользователя не будет отпущена
 * @note Вызов конфигурирует ресурсы GPIO для чтения состояния кнопки без обратного 
 */
void boot_guard();

#ifdef __cplusplus
}
#endif