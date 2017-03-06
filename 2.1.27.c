//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop

#include <tchar.h>
//---------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>

#define CEMENT_PRICE 230
#define CEMENT_COST_PRICE 160
#define GRAVEL_PRICE 142
#define GRAVEL_COST_PRICE 96
#define CONCRETE_PRICE 260
#define CONCRETE_COST_PRICE 205
#define CARRIAGE_CAPACITY 50
#define BELARUS 200
#define RUSSIA 320
#define UKRAINE 320
#define MOLDAVIA 360
#define CROSS_LINE 25000

#pragma argsused

typedef enum {Belarus, Russia, Ukraine, Moldavia} Country;

void ConcreteQuantity (float *quantity)
{
	float a;
	printf(" please, enter in tons the quantity of concrete you would like to order \n");
	scanf("%f", &a);
	*quantity += a;
}

void CementQuantity (float *quantity)
{
	float a;
	printf(" please, enter in tons the quantity of cement you would like to order \n");
	scanf("%f", &a);
	*quantity += a;
}

void GravelQuantity (float *quantity)
{
	float a;
	printf(" please, enter in tons the quantity of gravel you would like to order \n");
	scanf("%f", &a);
	*quantity += a;
}

void ShowParameters(float concrete_quantity, float cement_quantity,float gravel_quantity, Country chosen_country)
{
	 int carriages = 0;
	 float carriages1 = (concrete_quantity + cement_quantity + gravel_quantity)/CARRIAGE_CAPACITY;

	 float concrete_cost = concrete_quantity * CONCRETE_PRICE;
	 float cement_cost = cement_quantity * CEMENT_PRICE;
	 float gravel_cost = gravel_quantity * GRAVEL_PRICE;
	 float full_cost = concrete_cost + cement_cost + gravel_cost;

	 float profit;

	 int transport_price;
	 switch(chosen_country)
	 {
		 case Belarus:
		 {
			 transport_price = BELARUS;
			 break;
		 }
		 case Russia:
		 {
			 transport_price = RUSSIA;
			 break;
		 }
		 case Ukraine:
		 {
			 transport_price = UKRAINE;
			 break;
		 }
		 case Moldavia:
		 {
			 transport_price = MOLDAVIA;
			 break;
         }
     }



	 printf("a ton of CONCRETE costs %d\n", CONCRETE_PRICE);
	 printf("a ton of CEMENT costs %d\n",CEMENT_PRICE);
	 printf("a ton of GRAVEL costs %d\n",GRAVEL_PRICE);
	 carriages = (int)carriages1;
	 if(carriages1 > (int)carriages)
	 {
		 carriages++;
	 }

	 if(concrete_cost != 0)
	 {
		printf("the amount of CONCRETE you've chosen costs %2.f\n",concrete_cost);
	 }
	 if(cement_cost != 0)
	 {
		printf("the amount of CEMENT you've chosen costs %2.f\n",cement_cost);
	 }
	 if(gravel_cost != 0)
	 {
		printf("the amount of GRAVEL you've chosen costs %2.f\n",gravel_cost);
	 }

	 printf("the amount of required carriages is %d \n the price of transportation for one carriage is %d\n full cost of transportation is %d\n", carriages, transport_price, carriages * transport_price);


	 full_cost += carriages * transport_price;



	 profit = (CEMENT_PRICE - CEMENT_COST_PRICE) * cement_quantity + (CONCRETE_PRICE - CONCRETE_COST_PRICE) * concrete_quantity + (GRAVEL_PRICE - GRAVEL_COST_PRICE) * gravel_quantity;

	 if(profit <= CROSS_LINE)
	 {
		 printf("\n sorry, we cannot accept your order\n");
	 }
	 else
	 {
		 printf(" we accept your order\n the full cost of order is %2.f \n the profit is %2.f \n", full_cost, profit );
	 }


}

int _tmain(int argc, _TCHAR* argv[])
{
	int CheckMaterial;
	float concrete_amount = 0, cement_amount = 0, gravel_amount = 0;
	int CheckCountry;
	Country chosen_country;

	do
	{

		printf(" if you would like to order CONCRETE enter 1 \n if you would like to order CEMENT enter 2 \n ");
		printf("if you would like to order GRAVEL enter 3 \n if your order is complete enter 0 \n\n");
		scanf("%d",&CheckMaterial);

		switch(CheckMaterial)
		{
			case 1:
			{
			   ConcreteQuantity(&concrete_amount);
			   break;
			}
			case 2:
			{
				CementQuantity(&cement_amount);
				break;
			}
			case 3:
			{
				GravelQuantity(&gravel_amount);
				break;
			}
			case 0: break;
			default:
			{
			   printf("\n wrong input, try again, please \n\n ");
            }
		}
	} while(CheckMaterial != 0);


	do
	{
		printf(" please choose the destination of transportation \n\n");
		printf(" enter 1- for Belarus\n 2-for Russia \n 3-for Ukraine \n 4-for Moldavia \n\n");
		scanf("%d", &CheckCountry);
		switch(CheckCountry)
		{
			case 1:
			{
				chosen_country = Belarus;
				break;
			}
			case 2:
			{
				chosen_country =  Russia;
				break;
			}
			case 3:
			{
				chosen_country = Ukraine;
				break;
			}
			case 4:
			{
			   chosen_country = Moldavia;
			   break;
			}
			default:
			{
				CheckCountry = 0;
				printf("wrong input, try again\n\n");
            }
        }
	} while(CheckCountry == 0);

	ShowParameters(concrete_amount,cement_amount,gravel_amount,chosen_country);

	_getch();




	return 0;
}
//---------------------------------------------------------------------------
