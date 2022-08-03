// ASU-5(shortest_way(rangs with difficult)).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include "stdio.h"
#define SIZE 4

using namespace std;

/*struct rang {
	int i;
	int j;
	int njp;
	int njm;
};*/
/*struct arc {
	int i;
	int j;
	int w;
};*/
struct rang {
	int i[3];//предшествующие вершины
	int r;
	int v;
	int np;
	int nm;
	int Um[12][12];//вес дуги
};

int main()
{
	int i, j, temp, t;
	setlocale(0, "Rus");
	rang R[SIZE]; 
	int u[12][12];
	//инициализация
	/*for (i = 0; i < 3; i++)
		R[0].i[i] = 0;*/

	for (i = 0; i < 12; i++)
		for (j = 0; j < 12; j++)
			u[i][j] = -1;

	for (j = 0; j < SIZE; j++)//было 1?
	{
		cout << "Вершина номер " << j << endl;
		for (i = 0; i < 3; i++)
		{
			cout << "Введите номер предшествующей вершины (если нет, то -1): ";
			scanf_s("%d", &temp);
			if (temp != -1)
			{
				R[j].i[i] = temp;
				cout << "Введите вес дуги ";
				scanf_s("%d", &u[R[j].i[i]][j]);
			}
			else
			{
				for (t = i; t < 3; t++)
					R[j].i[t] = -1;
				break;
			}
		}
		cout << endl;
	}

	//вывод
	for (j = 0; j < SIZE; j++)
	{
		cout << "Вершина номер: " << j << endl;
		for (i = 0; i < 3; i++)
		{
			if (R[j].i[i] != -1)
				cout << "Предшествующая вершина " << R[j].i[i] << endl;
		}
		cout << endl;
	}
	for (j = 0; j < 12; j++)
	{
		for (i = 0; i < 12; i++)
			if (u[i][j] != -1)
				printf("Дуга из %d в %d: %d\n", i, j, u[i][j]);
	}

	//пошло поехало
	for (j = 0; j < SIZE; j++)
	{
		R[j].np = R[j].nm = 0;
		R[j].v = -1;
		//
		R[j].r = -1;
	}

	for (j = 0; j < 12; j++)
	{
		for (i = 0; i < 12; i++)
		{
			if (u[i][j] != -1)
			{
				R[i].nm++;
				R[j].np++;
				//memcpy(R[i].Um, R[i].Um, sizeof(R[j].Um));
				R[i].Um[i][j] = u[i][j];
			}
		}
	}

	for (j = 1; j < SIZE - 1; j++)//было 1? size-1
	{
		if (R[j].nm == 0 || R[j].np == 0)
		{
			printf("%d - нетранзитная вершина\n", j);
			system("pause");
		}
	}

	//Act two
	int v[SIZE];
	//R[0].v = R[0].i[0];	
	int k1 = 0;
	int k = 0;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (u[i][j] != -1)
			{
				if (i < j)
				{
					v[k] = i;
				}
				else
				{
					v[k] = -1;
					break;
				}
			}
		}
		k += 1;
	}

	for (k = 0; k < SIZE; k++)
	{
		i = v[k];
		if (i == -1)
		{
			printf("Цикл!\n");
			system("pause");
		}
	}

	R[0].r = 0;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (u[i][j] != -1)
			{
				if (R[j].r == -1)
				{
					R[j].r = R[i].r + 1;
				}
			}
		}

	}

	for (j = 0; j < SIZE; j++)
	{
		printf("\nВершина %d %d-го ранга\n", j, R[j].r);
	}

	return 0;
}