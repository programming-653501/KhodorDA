//---------------------------------------------------------------------------

#ifndef CarH
#define CarH
//---------------------------------------------------------------------------


#define CURRENT_YEAR 2017
#define MIN_YEAR 1900
#define MIN_ENGINE_CAPACITY 900
#define MAX_ENGINE_CAPACITY 5000
#define COST_PRICE 250
#define PROFIT_PERCENTAGE 0.15


#include <vector>
#include <vcl.h>
#include <iostream>
#include <system.hpp>
#include <Grids.hpp>
#include <stdexcept>
#include "ElementDatabase.h"


using namespace std;
class Car : public GetterSetter
{

	private:


	int _year;
	int _engine_capacity;
	AnsiString _brand;
	AnsiString _condition;
	int _age;
	double _price;
	double _profit;


	public:

	Car( vector <AnsiString> features );
	Car( TEdit** edits );

	void SetSetters();
	void SetGetters();

	void SetClassInfo();


	int CompareYear( Car* car );
	int CompareEngineCapacity( Car* car );
	int ComparePrices( Car* car );


	Car() {}


	void SetYear(AnsiString year);
	void SetEngineCapacity(AnsiString capacity);
	void SetBrand(AnsiString brand);
	void SetCondition(AnsiString condition);


	AnsiString GetYear();
	AnsiString GetEngineCapacity();
	AnsiString GetBrand();
	AnsiString GetCondition();
	AnsiString GetPrice();
	AnsiString GetProfit();

   //	bool operator == (Car* car);

	void CalculatePrice();
};



#endif
