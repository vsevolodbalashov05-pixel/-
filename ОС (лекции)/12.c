#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/stat.h>

// Глобальные переменные конфигурации
int daemon_delay = 5;
int daemon_verbose = 0;

void signal_handler(int sig) {
    switch(sig) {
        case SIGTERM:
            syslog(LOG_INFO, "Получен сигнал SIGTERM, завершение работы");
            closelog();
            exit(EXIT_SUCCESS);
            break;
        case SIGHUP:
            syslog(LOG_INFO, "Получен сигнал SIGHUP, перечитываем конфигурацию");
            // Здесь можно добавить перечитывание конфигурации
            break;
    }
}

void daemonize() {
    pid_t pid;
    
    // 1. Форкаем процесс
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) {
        // Родительский процесс завершается
        exit(EXIT_SUCCESS);
    }
    
    // 2. Создаем новую сессию
    if (setsid() < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }
    
    // 3. Устанавливаем маску прав на создаваемые файлы
    umask(0);
    
    // 4. Меняем рабочую директорию
    if (chdir("/") < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }
    
    // 5. Закрываем стандартные дескрипторы
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[]) {
    int opt;
    
    // Разбор аргументов командной строки
    while ((opt = getopt(argc, argv, "d:vh")) != -1) {
        switch (opt) {
            case 'd':
                daemon_delay = atoi(optarg);
                break;
            case 'v':
                daemon_verbose = 1;
                break;
            case 'h':
                printf("Использование: %s [-d delay] [-v]\n", argv[0]);
                printf("  -d delay   Задержка в секундах (по умолчанию: 5)\n");
                printf("  -v         Подробный вывод\n");
                printf("  -h         Эта справка\n");
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "Используйте -h для справки\n");
                exit(EXIT_FAILURE);
        }
    }
    
    // Демонизация
    if (!daemon_verbose) {
        daemonize();
    }
    
    // Настройка syslog
    openlog("MyDaemon", LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Демон запущен с задержкой %d секунд", daemon_delay);
    
    // Настройка обработчиков сигналов
    signal(SIGTERM, signal_handler);
    signal(SIGHUP, signal_handler);
    
    // Основной цикл демона
    syslog(LOG_INFO, "Демон начал работу");
    
    while (1) {
        syslog(LOG_INFO, "Демон работает...");
        sleep(daemon_delay);
    }
    
    closelog();
    return EXIT_SUCCESS;
}
