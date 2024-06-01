// ProjectEuler46c - Другая проблема Гольдбаха

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

#include "header.h"

int main(void)
{
	setlocale(LC_ALL, "Rus");								// русский язык в printf()

	int max_num;
	printf("Введите максимальное число, до которого будет осуществляться поиск: ");
	scanf_s("%d", &max_num);

	double time_spent = 0.0;								// для хранения времени выполнения кода
	clock_t begin = clock();								// СТАРТ таймера

	int* two_sqrt_arr = calloc(sizeof(int), (int)sqrt(max_num / 2) + 2); 
	// массив удвоенных квадратов натуральных чисел arr[5] = 2 * 5^2

	list_t prime_hash;
	prime_hash = list_сalloc(max_num / 10);					// хеш-массив простых чисел
	
	int prime = 2;											// первое простое число
	int answ = 9;											// первое составное нечетное число
	int indx = 0;
	int num = 0;

	while (prime && prime < max_num)						// дойдя до конца массива prime = 0
	{
		while (prime && prime < answ)
		{
			prime = get_next_prime(prime_hash, prime);		// определяем следующее простое число
			push_num(&prime_hash, prime);					// и заносим число в массив
		}

		while ((two_sqrt_arr[num] = 2 * num * num) < answ)	// заполняем массив удвоенных квадратов
			num++;

		if (is_prime(prime_hash, answ) == false && is_goldbach(prime_hash, two_sqrt_arr, answ) == false)
			break;											// найден ответ

		answ += 2;											// перебираем нечетные числа
	}

	free(prime_hash.arr);									// освобождаем память
	free(two_sqrt_arr);
		
	clock_t end = clock();									// СТОП таймера
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;	// время работы в секундах

	if (answ > max_num)
		printf("В диапазоне чисел до %d ответ не найден", max_num);
	else
		printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы

	return 0;
}
