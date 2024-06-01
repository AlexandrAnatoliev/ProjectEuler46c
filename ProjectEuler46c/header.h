// header.h

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

typedef struct list			// структура для хранения массива чисел
{
	int len;                // длина массива
	char* arr;              // указатель на массив
}list_t;

list_t list_сalloc(int len);
bool push_num(list_t* prime_arr, int num);
bool is_prime(list_t prime_arr, int num);
int get_next_prime(list_t prime_arr, int num);
bool is_goldbach(list_t prime_arr, int two_sqrt_arr[], int num);
