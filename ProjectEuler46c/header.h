// header.h

#include <stdio.h>
#include <stdbool.h>
#include <math.h>			// ��� ������ ������� sqrt()
#include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>			// ������� ���� � printf()
#include <stdlib.h>			// ��� calloc()

enum bit_nums               // ����� � ���� ������� ������
{
	one = 0x1,              // 00000001
	three = 0x1 << 1,		// 00000010
	five = 0x1 << 2,		// 00000100
	seven = 0x1 << 3,		// 00001000
	nine = 0x1 << 4			// 00010000
} bit_t;

enum check_sign				// ������� ��� ������� check()
{
	more,					// ������
	less					// ������
}sign_t;

typedef struct list			// ��������� ��� �������� ������� �����
{
	int len;                // ����� �������
	char* arr;              // ��������� �� ������
}list_t;

list_t list_�alloc(int len);
bool push_num(list_t* prime_arr, int num);
bool is_prime(list_t prime_arr, int num);
int get_next_prime(list_t prime_arr, int num);
bool is_goldbach(list_t prime_arr, int two_sqrt_arr[], int num);
