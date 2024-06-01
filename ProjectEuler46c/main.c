// euler46c - Другая проблема Гольдбаха

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
#include <math.h>								        // для работы функции sqrt()
#include <time.h>	 // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>	 // русский язык в printf()
#include <stdlib.h>		// для malloc()

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

typedef struct arr			// TODO переименовать в list
{
	int len;                // длина массива
	char* arr;              // указатель на массив
}arr_t;

arr_t arr_сalloc(arr_t arr, int len);
bool check(char* name_func, char* name_param, int param, int sign, char* name_limit, int limit);
bool push_num(arr_t* prime_arr, int num);
bool is_prime(arr_t prime_arr, int num);
int get_next_prime(arr_t prime_arr, int num);
bool is_goldbach(arr_t prime_arr, int two_sqrt_arr[], int num);


int main(void)
{
	setlocale(LC_ALL, "Rus"); // русский язык в printf()

	int max_num = 10000;

	printf("Введите до какого числа будет осуществляться поиск: ");
	scanf_s("%d", &max_num);
	
	double time_spent = 0.0; // для хранения времени выполнения кода
	clock_t begin = clock(); // СТАРТ таймера

	arr_t prime_list = { .len = 0 };
	
	prime_list = arr_сalloc(prime_list, max_num / 10); // TODO убрать (arr) из функции, заменить временными структурами (NULL, 0)
	// вычислять длину массива как max_num / 10

	// TODO выделить память через структуру
	int two_sqrt[500] = {0}; // вычислять длину массива как sqrt(max_num) / 2

	int prime = 2;
	int answ = 9;                                       // первое составное нечетное число
	int indx = 0;
	int num = 0;

	while (prime < max_num)
	{
		while (prime < answ)
		{
			prime = get_next_prime(prime_list, prime); // определяем следующее простое число TODO обработать выход за пределы массива
			push_num(&prime_list, prime); // и заносим число в массив
		}

		while ((two_sqrt[num] = 2 * num * num) < answ)
			num++;

		if (is_prime(prime_list, answ) == false && is_goldbach(prime_list, two_sqrt, answ) == false)
			break;

		answ += 2;
	}

	free(prime_list.arr);										// освобождаем память

	clock_t end = clock();								  // СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

	printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы

	return 0;
}

arr_t arr_сalloc(arr_t arr, int len)
// Функция для выделения памяти структуре
// Не забывать free()!!!
{
	arr_t ptr;
	if ((ptr.arr = calloc(1, len)) == NULL)					// не выделена память
		return arr;
	ptr.len = len;

	return ptr;										// память успешно выделена
}

bool check(char* name_func, char* name_param, int param, int sign, char* name_limit, int limit)
// Функция для проверки невыхода параметров за пределы
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

bool push_num(arr_t* prime_arr, int num)
// Функция для внесения числа в массив
{
	if (check("push_num()", "num / 10", num / 10, more, "prime_arr.len", prime_arr->len))
		return false;

	char past_num[10] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };
	prime_arr->arr[num / 10] |= past_num[num % 10]; // 123 => arr[12] = 00000010
	return true;
}

bool is_prime(arr_t prime_arr, int num)
// Функция для определения простого числа - проверки его наличия в массиве простых чисел
{
	if (check("is_prime()", "num / 10", num / 10, more, "prime_arr.len", prime_arr.len))
		return false;

	char prime[] = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
	if (num < 10)
		return prime[num];

	char mask[10] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };

	return prime_arr.arr[num / 10] & mask[num % 10];
}

int get_next_prime(arr_t prime_arr, int num)
// Функция для получения следующего простого числа после num
{
	num += (num % 2) ? 2 : 1;	// перебор нечетных чисел += 2
	bool prime_fl = false;

	while (prime_fl == false)	// пока не нашли простое число
	{
		if (check("get_next_prime()", "num / 10", num / 10, more, "prime_arr.len", prime_arr.len))
			return false;

		int max_div = sqrt(num) + 1;
		int div;
		for (div = 2; div < max_div; div++)
		{
			if (is_prime(prime_arr, div) == false)// проверяем только простые делители
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

bool is_goldbach(arr_t prime_arr, int two_sqrt_arr[], int num)
// Функция проверяет удовлетворяет ли число условия Гольдбаха 
{
	if (num % 2 == 0)
	{
		printf("is_goldbach(): число %d - четное\n", num);
		return true;
	}

	if (is_prime(prime_arr, num))
	{
		printf("is_goldbach(): число %d - простое\n", num);
		return true;
	}

	int number = 0;
	while (two_sqrt_arr[number] < num)
	{
		if (is_prime(prime_arr, num - two_sqrt_arr[number]))
			return true;
		number++;
	}
	return false;
}