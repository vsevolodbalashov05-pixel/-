#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rez = 0;
    // opterr = 0; // Раскомментировать, чтобы отключить автоматические сообщения об ошибках
    
    while ((rez = getopt(argc, argv, "ab:C::d")) != -1) {
        switch (rez) {
            case 'a': 
                printf("Найден аргумент \"a\".\n"); 
                break;
            case 'b': 
                printf("Найден аргумент \"b = %s\".\n", optarg); 
                break;
            case 'C': 
                printf("Найден аргумент \"C = %s\".\n", optarg ? optarg : "(null)"); 
                break;
            case 'd': 
                printf("Найден аргумент \"d\".\n"); 
                break;
            case '?': 
                printf("Обнаружена ошибка в аргументах!\n"); 
                break;
        }
    }
    
    return 0;
}
