// Knapsack Problem.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "time.h"

#define QUANTITY 10
#define V 20

using namespace std;

struct obj //structure of object
{
	int S; //value, Price
	int Vk; //size
	//char Name[10];
};

struct path
{
	int S;
	int t;
	//char Name[10];
	int Xk; //кол-во предмета
};

int main()
{
	srand(time(NULL));
	setlocale(0, "Rus");

	int i, v;
	obj a[QUANTITY];
	path b[QUANTITY][V];

	for (i = 0; i < QUANTITY; i++)
	{
		/*
		cout << "Введите название предмета: " << endl;
		cin >> a[i].Name;
		cout << "Введите массу предмета: " << endl;
		scanf_s("%d", &a[i].Vk);
		cout << "Введите стоимость предмета: " << endl;
		scanf_s("%d", &a[i].S);
		cout << endl << endl;
		*/
		a[i].S = rand() % 30 + 1;
		a[i].Vk = rand() % 10 + 1;
		cout << i << endl;
		cout << "Цена: " << a[i].S << endl;
		cout << "Вес" << a[i].Vk << endl << endl;
	}

	int max = 0;
	int temp;
	int xk; //количество k-го предмета
	//int vk;		//объем k-го предмета
	for (i = 0, v = 0; i < QUANTITY; i++)
	{
		b[i][v].S = 0;
	}

	for (i = 0, v = 0; v < V; v++)	//v=1
	{
		for (xk = 0; xk * a[i].Vk <= v; xk++)
		{
			b[i][v].S = a[i].S * xk;
			b[i][v].t = xk * a[i].Vk;
			b[i][v].Xk = xk;
			//strcpy_s(b[i][v].Name, a[i].Name);
		}
	}

	int t;
	//char name[10];
	int mxk;
	for (i = 1; i < QUANTITY; i++)
	{
		for (v = 0; v < V; v++)
		{
			max = 0;
			for (xk = 0; xk * a[i].Vk <= v; xk++)
			{
				temp = b[i - 1][v - xk * a[i].Vk].S + a[i].S * xk;
				if (temp >= max)
				{
					max = temp;
					t = xk * a[i].Vk;
					//strcpy_s(name, a[i].Name);
					mxk = xk;
				}
			}
			b[i][v].S = max;
			b[i][v].t = t;
			b[i][v].Xk = mxk;
			//strcpy_s(b[i][v].Name, name);
		}
	}

	for (v = 0; v < V; v++)
	{

		for (i = 0; i < QUANTITY; i++)
		{
			printf("%d/%d(%d)  \t", b[i][v].S, b[i][v].t, b[i][v].Xk);
		}
		printf("\n");
	}printf("\n");

	int u = V - 1;
	for (int i = QUANTITY - 1; i >= 0; i--)
	{
		//printf("Кладем %s, %d штук(a) \n", b[i][u].Name, b[i][u].Xk);
		printf("Кладем %d-й предмет, %d штук(a) \n", i, b[i][u].Xk);
		u = u - b[i][u].t;
	}

	return 0;
}