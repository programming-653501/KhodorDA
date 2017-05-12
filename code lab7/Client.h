//---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH
//---------------------------------------------------------------------------
#include <vector>
#include <vcl.h>
#include <iostream>
#include <system.hpp>
#include <Grids.hpp>
#include <stdexcept>


#include "Car.h"
#include "ElementDatabase.h"
#include "CarDatabase.h"




class Client:public GetterSetter
{
	private:
	AnsiString _surname;
	AnsiString _name;
	AnsiString _phone_number;
	int _min_year;
	int _min_engine_capacity;
	AnsiString _brand;
	AnsiString _condition;
	double _max_price;



	public:


	Client( TEdit** edits );
	Client( vector <AnsiString> features);



	void SetSetters();
	void SetGetters();

	void SetClassInfo();

	void SetSurname(AnsiString surname);
	void SetName(AnsiString name);
	void SetPhoneNumber(AnsiString phone_number);
	void SetBrand(AnsiString brand);
	void SetMinYear(AnsiString year);
	void SetMinEngineCapacity(AnsiString engine_capacity);
	void SetCondition(AnsiString condition);
	void SetMaxPrice(AnsiString max_price);

	AnsiString GetSurname();
	AnsiString GetName();
	AnsiString GetPhoneNumber();
	AnsiString GetBrand();
	AnsiString GetMinYear();
	AnsiString GetMinEngineCapacity();
	AnsiString GetCondition();
	AnsiString GetMaxPrice();

	CarDatabase* AppropriateCars( CarDatabase* full_list );
	bool IsAppropriate( Car* car );
};

#endif
