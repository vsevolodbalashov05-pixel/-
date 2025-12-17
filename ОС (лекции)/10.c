#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "data.txt";
    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL) {
        fprintf(stderr, "Ошибка: fopen() не удалось открыть файл %s\n", filename);
        fprintf(stderr, "Ошибка в файле %s на строке %d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    printf("Файл '%s' успешно открыт\n", filename);
    
    // Чтение содержимого файла
    char buffer[256];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        line_count++;
        printf("Строка %d: %s", line_count, buffer);
    }
    
    fclose(fp);
    printf("Программа завершена успешно\n");

    return EXIT_SUCCESS;
}
