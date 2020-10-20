#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start_clock, end_clock;

void compute(void)
{
	int x = 0;
	for (int i = 0; i < 1000000; i++)
	{
		x = x + 1;
	}
}

void average_of_10_times()
{
	double time_sum = 0;
	double time_ave = 0;
	for (int i = 0; i < 10; i++)
	{
		start_clock = clock();
		compute();
		end_clock = clock();
		time_sum = (double)(end_clock - start_clock) + time_sum;
	}
	time_ave = time_sum / 10;
	printf("１回の繰り返しにかかる平均時間は%fです。\n", time_ave / CLOCKS_PER_SEC);
}

int main(void)
{
	average_of_10_times();

	return 0;
}