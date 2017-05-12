//---------------------------------------------------------------------------


#pragma hdrstop

#include "Car.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


Car::Car( vector <AnsiString> features )
{
	SetClassInfo();
	SetFeatures(features);
}

Car::Car( TEdit** edits )
{
	SetClassInfo();
	SetFeatures(edits);
}

void Car::SetClassInfo()
{
	cnt_set_methods = 4;
	cnt_get_methods = 6;

	GetterSetter::SetClassInfo();
}


void Car::SetSetters()
{
	element_set_methods = new Setter[4];
	element_set_methods[0] = (Setter)&Car::SetYear;
	element_set_methods[1] = (Setter)&Car::SetEngineCapacity;
	element_set_methods[2] = (Setter)&Car::SetBrand;
	element_set_methods[3] = (Setter)&Car::SetCondition;
}

void Car::SetGetters()
{

	element_get_methods = new Getter[6];
	element_get_methods[0] = (Getter)&Car::GetYear;
	element_get_methods[1] = (Getter)&Car::GetEngineCapacity;
	element_get_methods[2] = (Getter)&Car::GetBrand;
	element_get_methods[3] = (Getter)&Car::GetCondition;
	element_get_methods[4] = (Getter)&Car::GetPrice;
	element_get_methods[5] = (Getter)&Car::GetProfit;

}

void Car::SetBrand(AnsiString brand)
{
	_brand = brand;
}

void Car::SetYear(AnsiString year)
{
	if(!CheckForNumber(year) )
	{
		throw std::invalid_argument("Wrong format of year.");
	}

	if( year.ToInt() <= CURRENT_YEAR && year.ToInt() >= MIN_YEAR )
	{
		_year = year.ToInt();
		_age = CURRENT_YEAR - _year;
		CalculatePrice();
	}
	else
	{
		throw std::invalid_argument("Wrong format of year.");
	}
}

void Car::SetEngineCapacity(AnsiString capacity)
{
	if(!CheckForNumber(capacity) )
	{
		throw std::invalid_argument("Wrong format of capacity.");
	}

	int check = capacity.ToInt();
	if(capacity.ToInt() >= MIN_ENGINE_CAPACITY && capacity.ToInt()  <= MAX_ENGINE_CAPACITY)
	{
		_engine_capacity = capacity.ToInt();
		CalculatePrice();
	}
	else
	{
		throw std::invalid_argument("Wrong format of engine capacity.");
	}
}

void Car::SetCondition(AnsiString condition)
{
	if( condition == "NEW" || condition == "BEEN_USED" )
	{
		_condition = condition;
	}
	else
	{
		throw std::invalid_argument("Wrong format of condition. Choose either \"NEW\" or \"BEEN_USEd\"");
    }
}

AnsiString Car::GetBrand()
{
	return _brand;
}

AnsiString Car::GetYear()
{
	return IntToStr(_year);
}

AnsiString Car::GetEngineCapacity()
{
	return StrToInt(_engine_capacity);
}

AnsiString Car::GetCondition()
{
	return _condition;
}

AnsiString Car::GetPrice()
{
	return FloatToStr(_price);
}

AnsiString Car::GetProfit()
{
	return FloatToStr(_profit);
}

void Car::CalculatePrice()
{
	_price = COST_PRICE;

	if( _age <= 3 )
	{
		_price += 0.6 * _engine_capacity;
	}
	else
	{
		if( _age <= 10 )
		{
			if( _engine_capacity < 2500 )
			{
				_price += 0.35 * _engine_capacity;
			}
			else
			{
				_price += 0.6 * _engine_capacity;
			}
		}
		else
		{
			if( _age < 14 )
			{
				_price += 0.6 * _engine_capacity;
			}
			else
			{
				_price += 2 * _engine_capacity;
            }
        }
	}

	_price = (double)_price / ( 1 - PROFIT_PERCENTAGE );
	_profit = _price * PROFIT_PERCENTAGE;
}

/*int Car::CompareYear( Car* car )
{
	int car_year = StrToInt( car -> GetYear() );
	if( _year < car_year )
	{
		return -1;
	}
	else
	{
		if( _year > car_year )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int Car::CompareEngineCapacity( Car* car )
{
	int car_capacity = StrToInt( car -> GetEngineCapacity() );
	if( _engine_capacity < car_capacity )
	{
		return -1;
	}
	else
	{
		if( _engine_capacity > car_capacity )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int Car::ComparePrices( Car* car )
{
	int car_price = StrToInt( car -> GetPrice() );
	if(_price < car_price)
	{
		return -1;
	}
	else
	{
		if(_price > car_price)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}  */

/*bool Car::operator == (Car* car)
{
	for(int i = 0; i < 8; i++)
	{
		bool SameFeature = (this->*(patient_get_methods[i]))() == (patient->*(patient_get_methods[i]))();
		if(!SameFeature)
		{
			return false;
		}
	}

	return true;
}  */




