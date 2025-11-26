#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define NAMEDPIPE_NAME "/tmp/my_named_pipe" // имя файла канала
#define BUFSIZE 50

int fd; // глобальная переменная для дескриптора канала

// Обработчик сигнала для корректного завершения
void handle_signal(int sig) {
    printf("\nЗавершение работы...\n");
    if (fd > 0) {
        close(fd);
    }
    remove(NAMEDPIPE_NAME);
    exit(0);
}

int main(int argc, char ** argv) {
    int len;
    char buf[BUFSIZE];

    // Устанавливаем обработчики сигналов
    signal(SIGINT, handle_signal);  // Ctrl+C
    signal(SIGTERM, handle_signal); // сигнал завершения

    // Удаляем канал если он существует
    remove(NAMEDPIPE_NAME);

    if (mkfifo(NAMEDPIPE_NAME, 0777)) { // создать канал с правами доступа для всех
        perror("mkfifo");
        return 1;
    }

    printf("%s создан\n", NAMEDPIPE_NAME);

    if ((fd = open(NAMEDPIPE_NAME, O_RDONLY)) <= 0) {
        perror("ошибка открытия:");
        remove(NAMEDPIPE_NAME);
        return 1;
    }

    printf("%s открыт\n", NAMEDPIPE_NAME);
    printf("Для завершения нажмите Ctrl+C\n");

    do {
        memset(buf, '\0', BUFSIZE);
        if ((len = read(fd, buf, BUFSIZE - 1)) <= 0) {
            perror("ошибка чтения");
            break;
        }
        printf("Входящее сообщение (%d): %s\n", len, buf);
    } while (1);

    // Закрытие и удаление при нормальном завершении
    close(fd);
    remove(NAMEDPIPE_NAME);
    printf("Канал удален\n");

    return 0;
}
