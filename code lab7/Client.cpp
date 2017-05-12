//---------------------------------------------------------------------------


#pragma hdrstop

#include "Client.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


Client::Client( TEdit** edits )
{
	SetClassInfo();
	SetFeatures(edits);
}

Client::Client( vector <AnsiString> features)
{
	SetClassInfo();
	SetFeatures(features);
}

void Client::SetClassInfo()
{
	cnt_set_methods = 8;
	cnt_get_methods = 8;
	GetterSetter::SetClassInfo();
}

void Client::SetSetters()
{
	element_set_methods = new Setter[8];
	element_set_methods[0] = (Setter)&Client::SetSurname;
	element_set_methods[1] = (Setter)&Client::SetName;
	element_set_methods[2] = (Setter)&Client::SetPhoneNumber;
	element_set_methods[3] = (Setter)&Client::SetBrand;
	element_set_methods[4] = (Setter)&Client::SetMinYear;
	element_set_methods[5] = (Setter)&Client::SetMinEngineCapacity;
	element_set_methods[6] = (Setter)&Client::SetCondition;
	element_set_methods[7] = (Setter)&Client::SetMaxPrice;
}

void Client::SetGetters()
{
	element_get_methods = new Getter[8];
	element_get_methods[0] = (Getter)&Client::GetSurname;
	element_get_methods[1] = (Getter)&Client::GetName;
	element_get_methods[2] = (Getter)&Client::GetPhoneNumber;
	element_get_methods[3] = (Getter)&Client::GetBrand;
	element_get_methods[4] = (Getter)&Client::GetMinYear;
	element_get_methods[5] = (Getter)&Client::GetMinEngineCapacity;
	element_get_methods[6] = (Getter)&Client::GetCondition;
	element_get_methods[7] = (Getter)&Client::GetMaxPrice;
}

void Client::SetSurname(AnsiString surname)
{
	_surname = surname;
}

void Client::SetName(AnsiString name)
{
	_name = name;
}

void Client::SetPhoneNumber(AnsiString phone_number)
{
	if(!CheckForNumber(phone_number) )
	{
		throw std::invalid_argument("Wrong format of phone number.");;
	}
	_phone_number = phone_number;
}

void Client::SetBrand(AnsiString brand)
{
	_brand = brand;
}

void Client::SetMinYear(AnsiString year)
{
	if(!CheckForNumber(year) )
	{
		throw std::invalid_argument("Wrong format of year.");
	}

	if( year.ToInt() <= CURRENT_YEAR && year.ToInt() >= MIN_YEAR )
	{
		_min_year = year.ToInt();
	}
	else
	{
		throw std::invalid_argument("Wrong format of year.");
	}
}

void Client::SetMinEngineCapacity(AnsiString capacity)
{
	if(!CheckForNumber(capacity) )
	{
		throw std::invalid_argument("Wrong format of engine capacity.");
	}

	if(capacity.ToInt() >= MIN_ENGINE_CAPACITY && capacity.ToInt()  <= MAX_ENGINE_CAPACITY)
	{
		_min_engine_capacity = capacity.ToInt();
	}
	else
	{
		throw std::invalid_argument("Wrong format of engine capacity");
	}
}

void Client::SetCondition(AnsiString condition)
{
	if( condition == "NEW" || condition == "BEEN_USED" )
	{
		_condition = condition;
	}
	else
	{
		throw std::invalid_argument("Wrong format of condition. Choose either \"NEW\" or \"BEEN_USED\"");
    }
}

void Client::SetMaxPrice(AnsiString max_price)
{
	if(!CheckForNumber(max_price) )
	{
		throw std::invalid_argument("Wrong format of price.");
	}

	_max_price = max_price.ToInt();
}

AnsiString Client::GetSurname()
{
	return _surname;
}

AnsiString Client::GetName()
{
	return _name;
}

AnsiString Client::GetPhoneNumber()
{
	return _phone_number;
}

AnsiString Client::GetBrand()
{
	return _brand;
}

AnsiString Client::GetMinYear()
{
	return IntToStr(_min_year);
}

AnsiString Client::GetMinEngineCapacity()
{
	return IntToStr(_min_engine_capacity);
}

AnsiString Client::GetCondition()
{
	return _condition;
}

AnsiString Client::GetMaxPrice()
{
    return FloatToStr(_max_price);
}

bool Client::IsAppropriate( Car* car )
{
	bool fits = true;

	fits = fits && car -> GetBrand() == _brand;
	fits = fits && car -> GetCondition() == _condition;
	fits = fits && StrToInt( car -> GetYear() ) >= _min_year;
	fits = fits && StrToInt( car -> GetEngineCapacity() ) >= _min_engine_capacity;
	fits = fits && StrToFloat( car -> GetPrice() ) <= _max_price;

	return fits;
}

CarDatabase* Client::AppropriateCars( CarDatabase* full_list )
{

	CarDatabase* result = new CarDatabase();
	int size = full_list -> Size() ;
	for( int i = 0; i < size; i++ )
	{
		Car* current_car = full_list -> GetElement(i);
		if( IsAppropriate(current_car) )
		{
			result -> Add(current_car);
		}
	}

	return result;
}
