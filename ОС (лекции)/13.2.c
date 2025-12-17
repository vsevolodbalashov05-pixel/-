#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_ITERATIONS 5

// Глобальные разделяемые данные
int shared_counter = 0;
pthread_mutex_t counter_mutex;

void *increment_counter(void *thread_id) {
    long tid = (long)thread_id;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Захватываем мьютекс перед доступом к разделяемым данным
        pthread_mutex_lock(&counter_mutex);
        
        // Критическая секция
        int temp = shared_counter;
        printf("Поток %ld: читаю значение %d\n", tid, temp);
        usleep(1000); // Имитация работы
        shared_counter = temp + 1;
        printf("Поток %ld: увеличиваю счетчик до %d\n", tid, shared_counter);
        
        // Освобождаем мьютекс
        pthread_mutex_unlock(&counter_mutex);
        
        usleep(50000); // Некоторая работа вне критической секции
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    
    // Инициализация мьютекса
    pthread_mutex_init(&counter_mutex, NULL);
    
    printf("Основной поток: Создаю %d потоков для увеличения счетчика\n", NUM_THREADS);
    printf("Начальное значение счетчика: %d\n", shared_counter);
    
    // Создаем потоки
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        if (rc) {
            printf("Ошибка создания потока %ld, код: %d\n", t, rc);
            exit(EXIT_FAILURE);
        }
    }
    
    // Ожидаем завершения потоков
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    
    printf("Основной поток: Все потоки завершили работу\n");
    printf("Финальное значение счетчика: %d (ожидалось: %d)\n", 
           shared_counter, NUM_THREADS * NUM_ITERATIONS);
    
    // Уничтожаем мьютекс
    pthread_mutex_destroy(&counter_mutex);
    
    return 0;
}
