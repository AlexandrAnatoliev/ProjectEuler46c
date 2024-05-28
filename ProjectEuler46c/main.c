// euler46c - ������ �������� ���������

// �������� �������� �������, ��� ����� �������� ��������� ����� ����� �������� � ���� ����� �������� ����� 
// � ���������� ��������.

// 9 = 7 + 2?1^2
// 15 = 7 + 2?2^2
// 21 = 3 + 2?3^2
// 25 = 7 + 2?3^2
// 27 = 19 + 2?2^2
// 33 = 31 + 2?1^2

// ���������, ��� ������ �������� �������.

// ������ ���������� �������� ��������� �����, ������� ������ �������� � ���� ����� �������� ����� � ���������� ��������?

#include <stdio.h>
#include <stdbool.h>
#include <math.h>								        // ��� ������ ������� sqrt()
#include <time.h>	 // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>	 // ������� ���� � printf()

bool is_simple(char prime_ar[], int num)
// ������� ��������� ����� � ���������� true - ���� ����� �������
// ���������:	prime_ar[]  - ������ � ����� ������������ �������� �������
//              num         - ����������� �����    
// return:      true        - ���� ����� �������
{
    int div_max = sqrt(num) + 1;                        // ������� ���������� ����������� ����� �� ����� for

    for (int div = 2; div < div_max; div++)             // ����� �� �� ���������� ������ �������� �����
    {
        if (prime_ar[div] && !(num % div))              // ���������� ��������� �������� � ����������� ��� num % i == 0
            return false;
    }
    return true;
}

bool is_goldbach(char prime_ar[], int num)
// ������� ��������� ����� � ���������� true - ���� ��� ����� ���������
// ���������:	prime_ar[]  - ������ � ����� ������������ �������� �������
//              num         - ����������� �����    
// return:      true        - ���� ��� ����� ���������
{
    bool answ_fl = false;
    int sq_num_max = (sqrt(num / 2 + 1) + 1);           // ������� ���������� ����������� ����� �� ����� for
    for (int sq_num = 1; sq_num < sq_num_max; sq_num++) // ����� �� �� ���������� ������ �������� �����
        if (prime_ar[num - (2 * sq_num * sq_num)])
        {
            answ_fl = true;
            break;
        }
    return answ_fl;
}

int add_primes(char prime_ar[], int len, int value)
// ������� ��������� ������ ����� "�������/���������" � ���������� � ������
// ���������:	prime_ar[]  - ������ � ����� ������������ �������� �������
//              len         - ���������� ����� � ������� ��� ������� ��� ��������� �����: �������/���������
//              value       - ���������� �����, ������ ������� ������ ������������� ����������    
{
    for (int i = len + 1; i < (len + 1 + value); i++)    // ��� ���� � �������
        prime_ar[i] = is_simple(prime_ar, i);
    return 0;
}

int main(void)
{
    setlocale(LC_ALL, "Rus"); // ������� ���� � printf()

    double time_spent = 0.0; // ��� �������� ������� ���������� ����
    clock_t begin = clock(); // ����� �������
    
    int answ = 9;                                       // ������ ��������� �������� �����
    bool goldbach_fl = true;

    static char prime_arr[10000] = { 0 };		        // ������[������� �����] = 1 - static ������ �����������!

    prime_arr[1] = 1;                                   // ���������� ������ ������ 10 ����� � �������
    prime_arr[2] = 1;
    add_primes(prime_arr, 2, 8);

    while (goldbach_fl)                                  // ���� �� ������ �����  
    {
        add_primes(prime_arr, answ, 100);               // ���������� ������ ��� 100 �����
        int finish = answ + 100;
        while (goldbach_fl && answ < finish)            // ��������� ����� � ����������� ��������� (+100)
        {
            answ += 2;
            if (!prime_arr[answ])                        // ��������� ������ ���� �� �������� ������� ������
                goldbach_fl = is_goldbach(prime_arr, answ);
        }
    }

    //printf("%d\n", answ);					            // 5777
    clock_t end = clock();								  // ���� �������
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // ����� ������ � ��������

    printf("����� = %d ����� = %f\n", answ, time_spent); // ������� ��������� � ����� ������ ���������

    return 0;
}
