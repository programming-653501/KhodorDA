//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop
#include <stdlib.h>
#include <conio.h>

#include <tchar.h>
//---------------------------------------------------------------------------

#pragma argsused


void SwapColumns(int**, int, int, int);
void SwapRows(int**, int, int, int);
void PrintMatrix(int**, int);
void RandomizeMatrix(int**, int);
void CountColumnZeros(int**, int*, int);
void CountRowZeros(int**, int*, int);
void swap(int*, int*);
void SortByColumns(int**, int*, int);
void SortByRows(int**, int*, int);


int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	int** a = NULL;
	int i;
	int* b;
	int* c;


	printf("please enter the number of columns and rows in your square matrix \n");
	scanf("%d",&n);

	randomize();




	a = (int**)malloc( n * sizeof(int*) );
	for(i = 0; i < n; i++)
	{
		int j;

		a[i] = (int*)malloc( n * sizeof(int) );
		for(j = 0; j < n; j++)
		{
			if(i <= j)
			{
				a[i][j] = rand()%100 + 1;
			}
			else
			{
				a[i][j] = 0;
            }
		}
	}



	PrintMatrix(a, n);

	RandomizeMatrix(a, n);
	printf("\nrandomized matrix is \n\n");
	PrintMatrix(a, n);

	b = (int*)malloc(n * sizeof(int) );
	c = (int*)malloc(n * sizeof(int) );

	CountColumnZeros(a,b,n);
	SortByColumns(a,b,n);
	CountRowZeros(a,c,n);
	SortByRows(a,c,n);

	printf("\nfixed matrix is\n\n");
	PrintMatrix(a, n);

	getch();

	free(b);
	free(c);
	for(i = 0; i < n;i++)
	{
		free(a[i]);
	}

	free(a);

	return 0;
}
//---------------------------------------------------------------------------

void SwapColumns(int** a, int n, int x, int y)
{

	int i;
	for(i = 0; i < n; i++)
	{
	   swap(*(a+i) + x, *(a+i) +y);
	}

}

void SwapRows(int **a, int n, int x, int y)
{

	int j;
	for(j = 0; j < n; j++)
	{
		swap(*(a+x) + j, *(a+y)+j);
	}

}


void PrintMatrix(int** a, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		int j;
		for(j = 0; j < n; j++)
		{
			printf("%5d", a[i][j] );
		}

		printf("\n");
	}

	printf("\n\n");
}

void RandomizeMatrix(int** a, int n)
{
	int SwapsNumber;
	int ColumnsOrRows;
	int SwapsCounter = 0;
	randomize();

	SwapsNumber = rand() + 1;

	while(SwapsCounter < SwapsNumber)
	{
		int x = rand()%n;
		int y = rand()%n;
		ColumnsOrRows = rand()%2;
		switch(ColumnsOrRows)
		{
			case 0:
			{

				SwapColumns(a, n, x, y);
				break;
			}
			case 1:
			{
				SwapRows(a,n,x,y);
				break;
			}

		}

		SwapsCounter++;

	}
}

void CountColumnZeros(int** a, int* b, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		int j;
		for(j = 0; j < n; j++)
		{
			if(a[i][j] == 0)
			{
				b[j]++;
			}
		}
	}
}

void CountRowZeros(int** a, int* c, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		int j;
		for(j = 0; j < n; j++)
		{
			if(a[i][j] == 0)
			{
				c[i]++;
			}
		}
	}
}

void SortByColumns(int** a, int* b, int n )
{
	int i;
	for(i = 0; i < n; i++)
	{
		int j;
		for(j = 0; j < n - i - 1; j++)
		{
			if(b[j] < b[j+1])
			{
				swap(b+j, b+j+1);
				SwapColumns(a,n,j,j+1);
            }
        }
    }
}

void SortByRows(int** a, int* c, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		int j;
		for(j = 0; j < n - i - 1; j++)
		{
			if( c[j] > c[j+1] )
			{
				swap(c+j,c+j+1);
				SwapRows(a,n,j,j+1);
            }
        }
    }
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}



