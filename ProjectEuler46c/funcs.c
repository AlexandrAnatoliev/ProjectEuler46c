#include <stdio.h>
#include <stdbool.h>
#include <math.h>			// для работы функции sqrt()
#include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>			// русский язык в printf()
#include <stdlib.h>			// для calloc()
#include "header.h"

inline const bool check(char* name_func, char* name_param, int param, int sign, char* name_limit, int limit)
// Встраиваемая (inline) функция для проверки невыхода параметров за пределы
// функция скрыта с помощью const т.к. функция является частью реализации, а не интерфейса
// Параметры:	name_func	- название функции
//				name_param	- навание параметра
//				param		- значение параметра
//				sign		- знак сравнения между параметром и пределом 
//				name_limit	- название предела
//				limit		- занчение предела
// return:		true		- параметр выходит за переделы
{
	if (sign == more && param >= limit)			// отрабатываем превышение параметром предела
	{
		printf("%s: %s = %d превышает значение %s = %d\n", name_func, name_param, param, name_limit, limit);
		return true;
	}

	else if (sign == less && param <= limit)	// отрабатываем недостижение параметром предела
	{
		printf("%s: %s = %d меньше значения %s = %d\n", name_func, name_param, param, name_limit, limit);
		return true;
	}

	return false;
}


list_t list_сalloc(int len)
// Функция для создания структуры и выделения ей памяти
// Не забывать free()!!!
// Параметры:	len	- длина массива
// return:			- структуру list_t
{
	list_t list = { .arr = NULL, .len = 0 };
	if ((list.arr = calloc(1, len)) == NULL)	// не выделена память
		return list;

	list.len = len;

	return list;								// память успешно выделена
}

bool push_num(list_t* prime_hash, int num)
// Функция для внесения числа в хеш-массив структуры
// Параметры:	prime_hash	- структура
//				num			- вносимое число
// return:		true		- число успешно внесено
{
	if (check("push_num()", "num / 10", num / 10, more, "prime_hash.len", prime_hash->len))
		return false;

	char mask_num[] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };
	prime_hash->arr[num / 10] |= mask_num[num % 10];			// 123 => arr[12] = 00000010

	return true;
}

bool is_prime(const list_t *prime_hash, int num)
// Функция для определения простого числа (проверки его наличия в хеш-массиве простых чисел)
// Параметры:	prime_hash	- структура
//				num			- проверяемое число
// return:		true		- число простое
{
	if (check("is_prime()", "num / 10", num / 10, more, "prime_hash.len", prime_hash->len))
		return false;

	char prime_flag[] = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
	if (num < 10)
		return prime_flag[num];

	char mask_num[] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };

	return prime_hash->arr[num / 10] & mask_num[num % 10];
}

int get_next_prime(const list_t *prime_hash, int num)
// Функция для получения следующего простого числа после num
// Параметры:	prime_hash	- структура
//				num			- проверяемое число
// return:		0			- выход за пределы массива
{
	num += (num % 2) ? 2 : 1;						// перебор нечетных чисел += 2
	bool prime_fl = false;

	while (prime_fl == false)						// пока не нашли простое число
	{
		if (check("get_next_prime()", "num / 10", num / 10, more, "prime_hash.len", prime_hash->len))
			return false;

		int max_div = sqrt(num) + 1;
		int div;

		for (div = 2; div < max_div; div++)			// проверяем только простые делители
		{
			if (is_prime(prime_hash, div) == false)
				continue;

			if (num % div == 0)						// число составное
			{
				prime_fl = false;
				break;
			}
		}

		if (div == max_div)							// перебрали все делители до конца
			prime_fl = true;						// число простое
		else
			num += 2;								// перебираем числа
	}

	return num;
}

bool is_goldbach(const list_t *prime_hash, int two_sqrt_arr[], int num)
// Функция проверяет удовлетворяет ли число условия Гольдбаха 
// Параметры:	prime_hash		- структура
//				two_sqrt_arr	- массив двойных квадратов натуральных чисел
//				num				- проверяемое число
// return:		false			- число не удовлетворяет условию Гольдбаха
{
	if (num % 2 == 0)
	{
		printf("is_goldbach(): число %d - четное\n", num);
		return true;
	}

	if (is_prime(prime_hash, num))
	{
		printf("is_goldbach(): число %d - простое\n", num);
		return true;
	}

	int number = 0;
	while (two_sqrt_arr[number] < num)
	{
		if (is_prime(prime_hash, num - two_sqrt_arr[number]))
			return true;
		number++;
	}
	return false;
}