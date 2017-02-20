// numeric_sequence.cpp: определяет точку входа для консольного приложения.
// Program finds the kth digit of the sequence,
// made up of squares of natural numbers

#include "stdafx.h"
#include <conio.h>

int count_digits(int); // returns the amount of digits in a number
int find_digit(int number, int position); // returns a digit with a specified position 

int main()
{
	int i, k, current_member, counter, k_digit, current_length, exit;

	printf("I'll find the nth digit of the consequence 14916253649...\n");
	for (exit = 0; !exit; )
	{
		printf("\nEnter the position of a sought-for digit (1, 2, 3, etc.): k=");
		scanf_s("%d", &k);

		for (i = 1, counter = 0; ; i++)
		{
			current_member = i*i;
			current_length = count_digits(current_member);

			if (counter + current_length >= k)
			{
				k_digit = find_digit(current_member, k - counter);
				break;
			}
			counter += count_digits(current_member); // counter, counts digits in the sequence 
		}

		printf("The %d-th digit is %d\n", k, k_digit);
		printf("\nPress the key (1 - exit, 0 - continue)\t");
		scanf_s("%d", &exit);
	}
	_getch();
	return 0;
}

int count_digits(int number)
{
	int counter = 1;
	if (number)  // in case it's not a zero
	{
		for (counter = 0; number > 0; counter++)
			number /= 10;
	}
	return counter;
}

int find_digit(int number, int position)
{
	int length, digit, i;
	length = count_digits(number);
	if (position<1 || position>length) // parameter check
	{
		printf("sorry nonexistent position\t");
		return -1;
	}
	for (i = length - position; i > 0; i--)
		number /= 10;
	digit = number % 10;
	return digit;
}

