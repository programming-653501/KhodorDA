//---------------------------------------------------------------------------

#ifndef CarDatabaseH
#define CarDatabaseH
//---------------------------------------------------------------------------

#include <vector>
#include <vcl.h>
#include <iostream>
#include <system.hpp>
#include <Grids.hpp>
#include <stdexcept>

#include "Car.h"
#include "ElementDatabase.h"
using namespace std;

class CarDatabase: public ElementDatabase<Car>
{
	public:
	typedef int (CarDatabase::*Comparator)( Car* car1, Car* car2 );
	Comparator *comparators;

	CarDatabase():ElementDatabase<Car>()
	{
		SetComparators();
    }

	void SetComparators()
	{
		comparators = new Comparator[3];

		comparators[0] = &CarDatabase::CompareYear;
		comparators[1] = &CarDatabase::CompareEngineCapacity;
		comparators[2] = &CarDatabase::ComparePrices;
	}

	int CompareYear( Car* car1, Car* car2 )
	{
		int car1_year = StrToInt( car1 -> GetYear() );
		int car2_year = StrToInt( car2 -> GetYear() );
		if( car1_year < car2_year )
		{
			return -1;
		}
		else
		{
			if( car1_year > car2_year )
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	int CompareEngineCapacity( Car* car1, Car* car2 )
	{
		int car1_capacity = StrToInt( car1 -> GetEngineCapacity() );
		int car2_capacity = StrToInt( car2 -> GetEngineCapacity() );
		if( car1_capacity < car2_capacity )
		{
			return -1;
		}
		else
		{
			if( car1_capacity > car2_capacity )
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	int ComparePrices( Car* car1, Car* car2 )
	{
		double car1_price = StrToFloat( car1 -> GetPrice() );
		double car2_price = StrToFloat( car2 -> GetPrice() );
		if(car1_price < car2_price)
		{
			return -1;
		}
		else
		{
			if(car1_price > car2_price)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	void Sort(CarDatabase* destination, int filter )
	{
		if( filter >= 3 || filter < 0 )
		{
			throw;
		}

		if( IsEmpty())
		{
			return;
		}
		if(!destination -> IsEmpty())
		{
			delete destination;
			destination = new CarDatabase();
		}

		CopyAll(destination);

		destination -> QuickSort(0, destination -> Size() - 1, filter );
	}


	void QuickSort(int left, int right, int filter)
	{
		int i = left;
		int j = right;
		Car* mid = _list[(left + right)/2];
		Car* temp = NULL;

		do
		{
			temp = _list[i];
			while(  (this->*(comparators[filter]))(_list[i], mid ) == -1 )
			{
				i++;
			}

			while( (this->*(comparators[filter]))(_list[j], mid ) == 1 )
			{
				j--;
			}

			if( i <= j)
			{
				Car* tmp = _list[i];
				_list[i] = _list[j];
				_list[j] = tmp;
				j--;
				i++;
			}
		}
		while(i < j);

		if(j > left)
		{
			QuickSort(left, j, filter);
		}

		if(i<right)
		{
			QuickSort(i, right, filter);
		}

	}


};
#endif
