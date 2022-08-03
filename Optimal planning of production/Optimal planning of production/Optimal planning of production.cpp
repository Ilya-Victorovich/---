// ASU(optimal planning)2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define NUMB 6//4 b 0
#define Y 11

struct Benefit
{
	int S;
	int t;//из какой вершины пришли
};

int main()
{
	Benefit b[SIZE][Y];
	int max; int temp;
	int y;

	setlocale(0, "Rus");

	//int f[SIZE][NUMB] = { {0,150,300,400,500,500},{0,130,250,360,500,500},{0,150,300,450,600,600},{0,160,330,480,650,800} };	//доход от реализации ...продукции... (номер продукции, кол-во ресов)


	//создание таблицы доходов от реализации x продукций
	int f[SIZE][NUMB];
	for (int i = 0, x = 0; i < SIZE; i++)	//доход от 0 продукций равен 0
		f[i][x] = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int x = 1; x < NUMB; x++)
		{
			//printf("Доход от реализации %d продукции от %d ресурсов: \n", i+1, x);
			//scanf_s("%d", &f[i][x]);
			f[i][x] = rand() % 100;
			//if(f[i][x]<f[i-1][x])
				//f[i][x] = rand() % 100;
		}
	}


	//Вывод таблицы доходов
	printf("f(i)/x");
	for (int x = 0; x < NUMB; x++)
		printf("\t%d", x);
	printf("\n");

	for (int i = 0; i < SIZE; i++)
	{
		printf("f%d", i + 1);
		for (int x = 0; x < NUMB; x++)
		{
			printf("\t%d", f[i][x]);
		}
		printf("\n");
	}




	//доход от 0 = 0
	for (int i = 0, y = 0; i < SIZE; i++)
	{
		b[i][y].S = 0;
		b[i][y].t = 0;
	}

	int k = 0;
	//для первого года
	for (int i = 0, y = 1; y < Y; y++)
	{
		max = 0;
		for (int x = 0; x <= y & x < NUMB; x++)
		{
			temp = f[i][x];
			if (temp > max)
			{
				max = temp;
				k = x;
			}

		}
		b[i][y].S = temp;
		b[i][y].t = k;
	}

	//далее
	for (int i = 1; i < SIZE; i++)
	{
		printf("\n");
		for (y = 1; y < Y; y++)
		{
			max = 0;
			for (int x = 0; x <= y & x < NUMB; x++)
			{
				temp = b[i - 1][y - x].S + f[i][x];
				if (temp > max)
				{
					max = temp;
					k = x;
				}
			}
			b[i][y].S = max;
			b[i][y].t = k;
		}
	}

	//вывод S
	printf("\ny/S");
	for (int i = 0; i < SIZE; i++)
	{
		printf("\tS%d[y]", i + 1);
	}
	printf("\n");
	for (y = 0; y < Y; y++)
	{
		printf("%d", y);
		for (int i = 0; i < SIZE; i++)
		{
			printf("\t%d/%d", b[i][y].S, b[i][y].t);
		}
		printf("\n");
	}

	int u = 0; max = 0;
	for (int i = SIZE - 1, y = 0; y < Y; y++)
	{
		if (b[i][y].S > max)
		{
			u = y;
		}
	}
	printf("\n%d\n", u);

	//Вывод пути:

	int a[SIZE];
	for (int i = SIZE - 1; i >= 0; i--)
	{
		a[i] = b[i][u].t;
		u = u - b[i][u].t;
	}

	for (int i = 0; i < SIZE; i++)
	{
		printf("\t%d", a[i]);
	}

	return 0;
}