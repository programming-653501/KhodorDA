//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop

#include <tchar.h>
//---------------------------------------------------------------------------
#include "stdio.h"
#include <conio.h>
#pragma argsused
#include "stdlib.h"
#include <malloc.h>
#include <string.h>
#include <ctype.h>


int input_validated()
{
   int number;
   char* char_number;
   _Bool isCorrect;

   do{


		int i = 0;

		isCorrect = 1;
		char_number = (char*)malloc(20 * sizeof(char) );
		gets( char_number );

		while(isCorrect && char_number[i] != '\0')
		{
			if ( ! isdigit( char_number[i] ) )
			{
				isCorrect = 0;
			}
			i++;
		}

		if(isCorrect == 1)
		{
			number = atoi(char_number);
		}
		else
		{
			printf("wrong input,try again\n");
		}

		free( char_number );
		char_number = NULL;

   }while( isCorrect == 0 );

   return number;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a, b, length;
	int* arr[2];
	int i, temp;
	int amount;
	int step;
	int temp1;
	_Bool correct;

	do{
		printf("enter the first number of the interval\n");
		a = input_validated();
		printf("enter the last number of the interval\n");
		b = input_validated();
		correct = a>=0 && b>0 && a<b;
		if(!correct)
		{
			printf("wrong input,try again\n");
		}
	}while(!correct);

	length = b - a + 1;

	arr[0] =(int*) malloc( length * sizeof( int ) );
	arr[1] =(int*) malloc( length * sizeof( int ) );



	for(i = 0; i < length; i++)
	{
		*(arr[0]+i) = 0;
		*(arr[1]+i) = a + i;
		temp = arr [1][i];
		while( temp > 0)
		{
			if( temp % 2 == 1)
			{
				arr[0][i]++;
			}

			temp /= 2;
		}

	}




	for(step = length / 2 ; step > 0 ; step /= 2)
	{
		int i;
		for(i = step; i < length; i++)
		{
			int j = i - step;
			int x = arr[0][i];
			int y = arr[1][i];
			while( x > arr[0][j] && j >= 0)
			{
				arr[0][j+step] = arr[0][j];
				arr[1][j+step] = arr[1][j];
				j = j-step;
			}

			arr[0][j + step] = x;
			arr[1][j + step] = y;

        }
    }

	amount = 0;


	do{
	   char binary[50] = {0};
	   int binary_digits = 1;

	   amount ++;
	   printf("%d \t", arr[1][amount - 1]);
	   temp1 = arr[1][amount - 1] ;

	   while(temp1 > 0)
	   {
		  binary[ binary_digits - 1 ] = ( char )( temp1 % 2 + 48 );
		  temp1 /= 2;
		  binary_digits ++;
       }
	   binary[ binary_digits ] = '\0';
	   strrev ( binary );
	   printf( "%s \n", binary);
	} while( arr [0][amount - 1] == arr [0][amount]);





	free ( arr[0] );
	free ( arr[1] );
	getch();
	return 0;
}
//---------------------------------------------------------------------------
