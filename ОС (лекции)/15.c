#include <stdio.h>
/* заголовочный файл для работы с динамическими библиотеками */
#include <dlfcn.h>

int main(int argc, char* argv[])
{
    void *ext_library;    // хандлер внешней библиотеки
    double value = 0;    // значение для теста
    double (*powerfunc)(double x);  // переменная для хранения адреса функции

    //загрузка библиотеки
    ext_library = dlopen("/root/libpowers.so", RTLD_LAZY);
    if (!ext_library)
    {
        //если ошибка, то вывести ее на экран
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        return 1;
    }

    //загружаем из библиотеки требуемую процедуру
    powerfunc = dlsym(ext_library, argv[1]);
    value = 3.0;

    //выводим результат работы процедуры
    printf("%s(%f) = %f\n", argv[1], value, (*powerfunc)(value));

    //закрываем библиотеку
    dlclose(ext_library);

    return 0;
}
