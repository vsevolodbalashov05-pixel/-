#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Функция ожидания
void wait_thread(void) {
    usleep(100000); // Задержка 100 миллисекунд
}

// Объявление потоковой функции
void* thread_func(void* vptr_args);

int main(int argc, char *argv[], char *envp[]) {
    pthread_t thread; // дескриптор потока
    
    // создание нового потока и вызова потоковой функции
    if (pthread_create(&thread, NULL, thread_func, NULL)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    
    for (unsigned int i = 0; i < 20; i++) {
        puts("a");
        usleep(50000); // Задержка 50 миллисекунд в основном потоке
    }
    
    // ожидание завершения потока
    if (pthread_join(thread, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

// реализация потоковой функции
void* thread_func(void* vptr_args) {
    (void)vptr_args; // Неиспользуемый параметр
    
    for (unsigned int i = 0; i < 20; i++) {
        fputs("b\n", stderr);
        wait_thread(); // Вызов функции ожидания
    }
    
    return NULL;
}
