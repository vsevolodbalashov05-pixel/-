#include <stdlib.h>
#include <stdio.h>

int main(){
    int *array = NULL;
    unsigned length, i;

    printf("Enter length of array: ");
    scanf("%d", &length);

    if (length > 0){
        if ((array = (int*)malloc(length * sizeof(int))) != NULL){
            for (i = 0; i < length; i++){
                array[i] = i * i;
                printf("%d ", array[i]);
            }
            printf("\n");
        }
        else{
            printf("Error: can't allocate memory\n");
        }
    }
    if (array != NULL){
        free(array);
    }

    //ждем любой ввод
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Очищаем буфер ввода
    getchar(); // Ждем Enter

    return 0;
}
