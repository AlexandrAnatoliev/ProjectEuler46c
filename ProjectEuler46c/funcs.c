#include <stdio.h>
#include <stdbool.h>
#include <math.h>			// ��� ������ ������� sqrt()
#include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>			// ������� ���� � printf()
#include <stdlib.h>			// ��� calloc()
#include "header.h"

inline const bool check(char* name_func, char* name_param, int param, int sign, char* name_limit, int limit)
// ������������ (inline) ������� ��� �������� �������� ���������� �� �������
// ������� ������ � ������� const �.�. ������� �������� ������ ����������, � �� ����������
// ���������:	name_func	- �������� �������
//				name_param	- ������� ���������
//				param		- �������� ���������
//				sign		- ���� ��������� ����� ���������� � �������� 
//				name_limit	- �������� �������
//				limit		- �������� �������
// return:		true		- �������� ������� �� ��������
{
	if (sign == more && param >= limit)			// ������������ ���������� ���������� �������
	{
		printf("%s: %s = %d ��������� �������� %s = %d\n", name_func, name_param, param, name_limit, limit);
		return true;
	}

	else if (sign == less && param <= limit)	// ������������ ������������ ���������� �������
	{
		printf("%s: %s = %d ������ �������� %s = %d\n", name_func, name_param, param, name_limit, limit);
		return true;
	}

	return false;
}


list_t list_�alloc(int len)
// ������� ��� �������� ��������� � ��������� �� ������
// �� �������� free()!!!
// ���������:	len	- ����� �������
// return:			- ��������� list_t
{
	list_t list = { .arr = NULL, .len = 0 };
	if ((list.arr = calloc(1, len)) == NULL)	// �� �������� ������
		return list;

	list.len = len;

	return list;								// ������ ������� ��������
}

bool push_num(list_t* prime_hash, int num)
// ������� ��� �������� ����� � ���-������ ���������
// ���������:	prime_hash	- ���������
//				num			- �������� �����
// return:		true		- ����� ������� �������
{
	if (check("push_num()", "num / 10", num / 10, more, "prime_hash.len", prime_hash->len))
		return false;

	char mask_num[] = { 0, one, 0, three, 0, five, 0, seven, 0, nine };
	prime_hash->arr[num / 10] |= mask_num[num % 10];			// 123 => arr[12] = 00000010

	return true;
}

bool is_prime(const list_t *prime_hash, int num)
// ������� ��� ����������� �������� ����� (�������� ��� ������� � ���-������� ������� �����)
// ���������:	prime_hash	- ���������
//				num			- ����������� �����
// return:		true		- ����� �������
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
// ������� ��� ��������� ���������� �������� ����� ����� num
// ���������:	prime_hash	- ���������
//				num			- ����������� �����
// return:		0			- ����� �� ������� �������
{
	num += (num % 2) ? 2 : 1;						// ������� �������� ����� += 2
	bool prime_fl = false;

	while (prime_fl == false)						// ���� �� ����� ������� �����
	{
		if (check("get_next_prime()", "num / 10", num / 10, more, "prime_hash.len", prime_hash->len))
			return false;

		int max_div = sqrt(num) + 1;
		int div;

		for (div = 2; div < max_div; div++)			// ��������� ������ ������� ��������
		{
			if (is_prime(prime_hash, div) == false)
				continue;

			if (num % div == 0)						// ����� ���������
			{
				prime_fl = false;
				break;
			}
		}

		if (div == max_div)							// ��������� ��� �������� �� �����
			prime_fl = true;						// ����� �������
		else
			num += 2;								// ���������� �����
	}

	return num;
}

bool is_goldbach(const list_t *prime_hash, int two_sqrt_arr[], int num)
// ������� ��������� ������������� �� ����� ������� ��������� 
// ���������:	prime_hash		- ���������
//				two_sqrt_arr	- ������ ������� ��������� ����������� �����
//				num				- ����������� �����
// return:		false			- ����� �� ������������� ������� ���������
{
	if (num % 2 == 0)
	{
		printf("is_goldbach(): ����� %d - ������\n", num);
		return true;
	}

	if (is_prime(prime_hash, num))
	{
		printf("is_goldbach(): ����� %d - �������\n", num);
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