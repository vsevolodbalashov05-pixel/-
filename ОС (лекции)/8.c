#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>

// Раскомментировать для включения отладочных сообщений:
#define DEBUG

int main() {
    int i = 0;
    
    // Открываем лог с PID и для пользователя
    openlog("MyTestApp", LOG_PID, LOG_USER);
    
    #ifdef DEBUG
    syslog(LOG_DEBUG, "Начало отправки 10 сообщений");
    #endif
    
    for (i = 0; i < 10; i++) {
        syslog(LOG_INFO, "Информационное сообщение [i = %d]", i);
    }
    
    #ifdef DEBUG
    syslog(LOG_DEBUG, "Переключаемся на stderr");
    #endif
    
    closelog();
    
    // Открываем с флагом LOG_PERROR для вывода в stderr
    openlog("MyTestApp", LOG_PERROR | LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Это сообщение также выведется в stderr");
    
    closelog();
    return 0;
}
