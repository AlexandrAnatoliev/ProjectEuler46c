﻿// ProjectEuler46c - Другая проблема Гольдбаха

// Кристиан Гольдбах показал, что любое нечетное составное число можно записать в виде суммы простого числа 
// и удвоенного квадрата.

// 9 = 7 + 2×1^2
// 15 = 7 + 2×2^2
// 21 = 3 + 2×3^2
// 25 = 7 + 2×3^2
// 27 = 19 + 2×2^2
// 33 = 31 + 2×1^2

// Оказалось, что данная гипотеза неверна.// 5777

// Каково наименьшее нечетное составное число, которое нельзя записать в виде суммы простого числа и удвоенного квадрата?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>			// для работы функции sqrt()
#include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>			// русский язык в printf()
#include <stdlib.h>			// для calloc()

enum bit_nums               // числа в виде битовых флагов
{
	one = 0x1,              // 00000001
	three = 0x1 << 1,		// 00000010
	five = 0x1 << 2,		// 00000100
	seven = 0x1 << 3,		// 00001000
	nine = 0x1 << 4			// 00010000
} bit_t;

enum check_sign				// праметр для функции check()
{
	more,					// больше
	less					// меньше
}sign_t;

typedef struct list
{
	int len;                // длина массива
	char* arr;              // указатель на массив
}list_t;

list_t list_сalloc(int len);
bool push_num(list_t* prime_arr, int num);
bool is_prime(list_t prime_arr, int num);
int get_next_prime(list_t prime_arr, int num);
bool is_goldbach(list_t prime_arr, int two_sqrt_arr[], int num);

inline static bool check(char* name_func, char* name_param, int param, int sign, char* name_limit, int limit)
// Встраиваемая (!) функция для проверки невыхода параметров за пределы
{
	if (sign == more && param >= limit) // отрабатываем превышение параметром предела
	{
		printf("%s: %s = %d превышает значение %s = %d\n", name_func, name_param, param, name_limit, limit);
		return true;
	}

	else if (sign == less && param <= limit) // отрабатываем недостижение параметром предела
	{
		printf("%s: %s = %d меньше значения %s = %d\n", name_func, name_param, param, name_limit, limit);
		return true;
	}
	return false;
}

int main(void)
{
	setlocale(LC_ALL, "Rus"); // русский язык в printf()

	int max_num;

	printf("Введите максимальное число, до которого будет осуществляться поиск: ");
	scanf_s("%d", &max_num);

	double time_spent = 0.0; // для хранения времени выполнения кода
	clock_t begin = clock(); // СТАРТ таймера

	int* two_sqrt_arr = calloc(sizeof(int), (int)sqrt(max_num / 2) + 2);

	list_t prime_list = { .len = 0 };
	prime_list = list_сalloc(max_num / 10);
	
	int prime = 2;
	int answ = 9;                                       // первое составное нечетное число
	int indx = 0;
	int num = 0;

	while (prime && prime < max_num)// дойдя до конца массива prime == false т.е. 0
	{
		while (prime && prime < answ)
		{
			prime = get_next_prime(prime_list, prime); // определяем следующее простое число
			push_num(&prime_list, prime); // и заносим число в массив
		}

		while ((two_sqrt_arr[num] = 2 * num * num) < answ)
			num++;

		if (is_prime(prime_list, answ) == false && is_goldbach(prime_list, two_sqrt_arr, answ) == false)
			break;

		answ += 2;
	}

	free(prime_list.arr);										// освобождаем память
	free(two_sqrt_arr);

	clock_t end = clock();								  // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

	if (answ > max_num)
		printf("В диапазоне чисел до %d ответ не найден", max_num);
	else
		printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы

	return 0;
}

list_t list_сalloc(int len)
// Функция для выделения памяти структуре
// Не забывать free()!!!
{
	list_t ptr = {.arr = NULL, .len = 0};
	if ((ptr.arr = calloc(1, len)) == NULL)					// не выделена память
		return ptr;
	ptr.len = len;

	return ptr;										// память успешно выделена
}

bool push_num(list_t* prime_list, int num)
// Функция для внесения числа в массив
{
	if (check("push_num()", "num / 10", num / 10, more, "prime_list.len", prime_list->len))
		return false;

	char past_num[10] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };
	prime_list->arr[num / 10] |= past_num[num % 10]; // 123 => arr[12] = 00000010
	return true;
}

bool is_prime(list_t prime_list, int num)
// Функция для определения простого числа - проверки его наличия в массиве простых чисел
{
	if (check("is_prime()", "num / 10", num / 10, more, "prime_list.len", prime_list.len))
		return false;

	char prime_flag[] = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
	if (num < 10)
		return prime_flag[num];

	char mask[10] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };

	return prime_list.arr[num / 10] & mask[num % 10];
}

int get_next_prime(list_t prime_list, int num)
// Функция для получения следующего простого числа после num
{
	num += (num % 2) ? 2 : 1;	// перебор нечетных чисел += 2
	bool prime_fl = false;

	while (prime_fl == false)	// пока не нашли простое число
	{
		if (check("get_next_prime()", "num / 10", num / 10, more, "prime_list.len", prime_list.len))
			return false;

		int max_div = sqrt(num) + 1;
		int div;
		for (div = 2; div < max_div; div++)
		{
			if (is_prime(prime_list, div) == false)// проверяем только простые делители
				continue;

			if (num % div == 0)						// число составное
			{
				prime_fl = false;
				break;
			}
		}

		if (div == max_div) // перебрали все делители до конца
			prime_fl = true;
		else
			num += 2;
	}
	return num;
}

bool is_goldbach(list_t prime_list, int two_sqrt_arr[], int num)
// Функция проверяет удовлетворяет ли число условия Гольдбаха 
{
	if (num % 2 == 0)
	{
		printf("is_goldbach(): число %d - четное\n", num);
		return true;
	}

	if (is_prime(prime_list, num))
	{
		printf("is_goldbach(): число %d - простое\n", num);
		return true;
	}

	int number = 0;
	while (two_sqrt_arr[number] < num)
	{
		if (is_prime(prime_list, num - two_sqrt_arr[number]))
			return true;
		number++;
	}
	return false;
}