// euler46c - Другая проблема Гольдбаха

// Кристиан Гольдбах показал, что любое нечетное составное число можно записать в виде суммы простого числа 
// и удвоенного квадрата.

// 9 = 7 + 2?1^2
// 15 = 7 + 2?2^2
// 21 = 3 + 2?3^2
// 25 = 7 + 2?3^2
// 27 = 19 + 2?2^2
// 33 = 31 + 2?1^2

// Оказалось, что данная гипотеза неверна.

// Каково наименьшее нечетное составное число, которое нельзя записать в виде суммы простого числа и удвоенного квадрата?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>								        // для работы функции sqrt()
#include <time.h>	 // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>	 // русский язык в printf()

bool is_simple(char prime_ar[], int num)
// функция принимает число и возвращает true - если число простое
// параметры:	prime_ar[]  - массив с ранее вычисленными простыми числами
//              num         - проверяемое число    
// return:      true        - если число простое
{
    int div_max = sqrt(num) + 1;                        // выносим вычисление квадратного корня из цикла for

    for (int div = 2; div < div_max; div++)             // чтобы он не вычислялся каждую итерацию цикла
    {
        if (prime_ar[div] && !(num % div))              // пропускаем составные делители и срабатываем при num % i == 0
            return false;
    }
    return true;
}

bool is_goldbach(char prime_ar[], int num)
// функция принимает число и возвращает true - если это число Гольдбаха
// параметры:	prime_ar[]  - массив с ранее вычисленными простыми числами
//              num         - проверяемое число    
// return:      true        - если это число Гольдбаха
{
    bool answ_fl = false;
    int sq_num_max = (sqrt(num / 2 + 1) + 1);           // выносим вычисление квадратного корня из цикла for
    for (int sq_num = 1; sq_num < sq_num_max; sq_num++) // чтобы он не вычислялся каждую итерацию цикла
        if (prime_ar[num - (2 * sq_num * sq_num)])
        {
            answ_fl = true;
            break;
        }
    return answ_fl;
}

int add_primes(char prime_ar[], int len, int value)
// функция проверяет статус чисел "простое/составное" и записывает в массив
// параметры:	prime_ar[]  - массив с ранее вычисленными простыми числами
//              len         - количество чисел в массиве для которых уже определен сатус: простое/составное
//              value       - количество чисел, статус которых нуэжно дополнительно определить    
{
    for (int i = len + 1; i < (len + 1 + value); i++)    // еще ноль в массиве
        prime_ar[i] = is_simple(prime_ar, i);
    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Rus"); // русский язык в printf()

    double time_spent = 0.0; // для хранения времени выполнения кода
    clock_t begin = clock(); // СТАРТ таймера
    
    int answ = 9;                                       // первое составное нечетное число
    bool goldbach_fl = true;

    static char prime_arr[10000] = { 0 };		        // массив[простое число] = 1 - static писать обязательно!

    prime_arr[1] = 1;                                   // определяем статус первых 10 чисел в массиве
    prime_arr[2] = 1;
    add_primes(prime_arr, 2, 8);

    while (goldbach_fl)                                  // пока не найден ответ  
    {
        add_primes(prime_arr, answ, 100);               // определяем статус еще 100 чисел
        int finish = answ + 100;
        while (goldbach_fl && answ < finish)            // проверяем числа в добавленном диапазоне (+100)
        {
            answ += 2;
            if (!prime_arr[answ])                        // проверяем только если не является простым числом
                goldbach_fl = is_goldbach(prime_arr, answ);
        }
    }

    //printf("%d\n", answ);					            // 5777
    clock_t end = clock();								  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

    printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы

    return 0;
}
