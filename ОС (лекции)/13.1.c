#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Структура для передачи данных в поток
typedef struct {
    int thread_id;
    char *message;
} thread_data_t;

// Функция, выполняемая в потоке
void *thread_function(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    
    printf("Поток %d: %s\n", data->thread_id, data->message);
    printf("Поток %d: Засыпаю на %d секунд\n", data->thread_id, data->thread_id);
    
    sleep(data->thread_id);
    
    printf("Поток %d: Завершил работу\n", data->thread_id);
    
    // Возвращаем результат
    int *result = malloc(sizeof(int));
    *result = data->thread_id * 100;
    pthread_exit(result);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    void *thread_result;
    int rc;
    
    printf("Основной поток: Создаю %d потоков\n", NUM_THREADS);
    
    // Создаем потоки
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i + 1;
        thread_data[i].message = "Привет из потока!";
        
        rc = pthread_create(&threads[i], NULL, thread_function, (void *)&thread_data[i]);
        
        if (rc) {
            printf("Ошибка: невозможно создать поток %d, код: %d\n", i, rc);
            exit(EXIT_FAILURE);
        }
    }
    
    // Ожидаем завершения потоков и собираем результаты
    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], &thread_result);
        
        if (rc) {
            printf("Ошибка: невозможно присоединиться к потоку %d, код: %d\n", i, rc);
        } else {
            printf("Основной поток: Поток %d завершился с результатом: %d\n", 
                   i + 1, *((int *)thread_result));
            free(thread_result);
        }
    }
    
    printf("Основной поток: Все потоки завершили работу\n");
    pthread_exit(NULL);
}
