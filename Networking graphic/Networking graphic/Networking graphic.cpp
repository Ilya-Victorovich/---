// ASU_6(networking graphic).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "stdio.h"
#include "iostream"
#include "time.h"

#define SIZE 5

using namespace std;

struct graph {
	int next[SIZE]; //следующие вершины
	int pred[SIZE];
	int v; //показатель посещенности вершины
	int np;
	int nm;
	int index = -1;//метка, из какой вершины мы приходим, чтобы до нее был максимальный путь из 0-ой вершины
	int tie;// максимальная длина пути через num вершину, наиболее ранний момент наступления события
	int max;
	int tjl;//наиболее поздний момент наступления события
	int Rj;//резерв времени события
};

int main()
{
	srand(time(NULL));
	int i, j, temp;
	setlocale(0, "Rus");
	graph G[SIZE]; int L[SIZE][SIZE];
	int rFull[SIZE][SIZE];//полный резерв времени
	int rFree[SIZE][SIZE];
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			L[i][j] = -1;
			G[i].next[j] = -1;
			G[i].pred[j] = -1;
			G[i].tie = 0;
			G[i].v = -1;
			G[i].np = 0;
			G[i].nm = 0;
			G[i].max = 0;
			rFree[i][j] = -1;
			rFull[i][j] = -1;
		}
	}
	//заполнение графа
	for (i = 0; i < SIZE - 1; i++)
	{
		for (j = i + 1; j < SIZE; j++)
		{
			if (i != j)
			{
				temp = rand() % 4; //printf("i=%d j=%d temp=%d\n", i, j, temp);
				if (temp != 0) // && L[j][i] == -1
				{
					L[i][j] = rand() % 25;
				}
			}
		}

	}
	int k = 0;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (L[i][j] != -1)
			{
				G[i].next[k] = j;
				k++;
			}
		}
		k = 0;
	}
	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			if (L[i][j] != -1)
			{
				G[j].pred[k] = i;
				k++;
			}
		}
		k = 0;
	}
	//вывод
	for (i = 0; i < SIZE; i++)
	{
		cout << "Вершина номер: " << i << endl;
		cout << "Выходящие вершины: ";
		for (j = 0; j < SIZE; j++)
		{
			if (G[i].next[j] != -1)
				printf("%d, ", G[i].next[j]);
		}
		cout << endl << "Предшествующие вершины: ";
		for (j = 0; j < SIZE; j++)
		{
			if (G[i].pred[j] != -1)
				printf("%d, ", G[i].pred[j]);
		}
		cout << endl;
		cout << endl;
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			if (L[i][j] != -1)
				printf("Дуга из %d в %d: %d\n", i, j, L[i][j]);
	}

	//пошло поехало
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (L[i][j] != -1)
			{
				G[i].nm++;
				G[j].np++;
			}
		}
	}

	for (i = 1; i < SIZE - 1; i++)
	{
		if (G[i].nm == 0 || G[i].np == 0)
		{
			printf("%d - нетранзитная вершина\n", i);
			//system("pause");
		}
	}

	//начинаем обход
	//ищем tie
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (G[i].next[j] != -1)
			{
				if (G[G[i].next[j]].tie < (G[i].tie + L[i][G[i].next[j]]))
				{
					G[G[i].next[j]].tie = G[i].tie + L[i][G[i].next[j]];
					G[G[i].next[j]].index = i;
				}
			}
		}
	}
	int Tcr = G[SIZE - 1].tie;

	//ищем tjl
	for (i = 0; i < SIZE; i++)
	{
		for (k = i; k < SIZE; k++)
		{
			for (j = 0; j < SIZE; j++)
			{
				if (G[k].next[j] != -1)
				{
					if (G[G[k].next[j]].max < (G[k].max + L[k][G[k].next[j]]))
					{
						G[G[k].next[j]].max = G[k].max + L[k][G[k].next[j]];
					}
				}
			}
		}
		G[i].tjl = Tcr - G[SIZE - 1].max;
		for (temp = 0; temp < SIZE; temp++)
		{
			G[temp].max = 0;
		}
	}

	//ищем rFull
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (L[i][j] != -1)
			{
				rFull[i][j] = G[j].tjl - G[i].tie - L[i][j];
			}
		}
	}

	//ищем rFree
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (L[i][j] != -1)
			{
				rFree[i][j] = G[j].tie - G[i].tie - L[i][j];
			}
		}
	}

	for (i = 0; i < SIZE; i++)
	{
		printf("\nНаиболее ранний срок наступления события %d = %d", i, G[i].tie);
	} cout << endl;
	printf("Tcr=%d\n", Tcr);

	for (i = 0; i < SIZE; i++)
	{
		G[i].Rj = G[i].tjl - G[i].tie;
		printf("\nНаиболее поздний срок наступления события %d = %d", i, G[i].tjl);
	}cout << endl; cout << endl;
	for (i = 0; i < SIZE; i++)
	{
		printf("Резерв времени события %d = %d\n", i, G[i].Rj);
	}cout << endl;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (rFull[i][j] != -1)
				printf("Полный резерв времени работы %d-%d = %d\n", i, j, rFull[i][j]);
		}
	}cout << endl;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (rFree[i][j] != -1)
				printf("Свободный резерв времени работы %d-%d = %d\n", i, j, rFree[i][j]);
		}
	}cout << endl;

	return 0;
}