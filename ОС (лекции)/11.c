#include <stdio.h>
#include <stdlib.h>

int validate_config_file(const char *config_filename) {
    FILE *config_file = NULL;
    int ret = -1;
    int delay = 0;

    config_file = fopen(config_filename, "r");
    
    if (config_file == NULL) {
        fprintf(stderr, "Ошибка: Не удалось прочитать конфигурационный файл %s\n", 
                config_filename);
        return EXIT_FAILURE;
    }
    
    ret = fscanf(config_file, "%d", &delay);
    
    if (ret <= 0) {
        fprintf(stderr, "Ошибка: Неверный формат конфигурационного файла %s\n", 
                config_filename);
        fclose(config_file);
        return EXIT_FAILURE;
    }
    
    fclose(config_file);
    
    if (delay <= 0) {
        fprintf(stderr, "Ошибка: Задержка должна быть положительным числом\n");
        return EXIT_FAILURE;
    }
    
    printf("Конфигурационный файл '%s' валиден\n", config_filename);
    printf("Задержка: %d секунд\n", delay);
    
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <config_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    return validate_config_file(argv[1]);
}
