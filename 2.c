#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    int sz;
    char *c = (char *)calloc(100, sizeof(char));

    // Открываем файл для чтения
    int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);
    printf("fd = %d\n", fd);

    if (fd == -1) {
        printf("Номер ошибки: %d\n", errno);
        perror("Ошибка открытия файла");
    } else {
        // Читаем данные из файла
        sz = read(fd, c, 20);
        printf("вызван read(%d, c, 20), возвращено %d байт\n", fd, sz);

        if (sz > 0) {
            c[sz] = '\0';
            printf("Прочитанные данные: %s\n", c);
        } else if (sz == 0) {
            printf("Файл пуст\n");
        } else {
            perror("Ошибка чтения");
        }

        // Закрываем файл
        if (close(fd) < 0) {
            perror("Ошибка закрытия файла");
            exit(1);
        }
        printf("Файл закрыт\n");
    }

    free(c);
    return 0;
}
