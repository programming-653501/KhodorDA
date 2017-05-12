//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Client.h"
#include "Car.h"
#include "ElementDatabase.h"
#include "CarDatabase.h"


TForm1 *Form1;
CarDatabase* main_car_list;
CarDatabase* current_car_list;
ElementDatabase<Client>* main_client_list;
ElementDatabase<Client>* current_client_list;
Car* current_car;
Client* current_client;
GetterSetter* current_element;
int current_row;
bool work_with_cars;
TEdit* client_edits[8];
TEdit* car_edits[4];

void ToCarDatabaseState();
void ToClientDatabaseState();
void LoadFromFile(AnsiString car_path, AnsiString client_path);
template <class U>
void Delete( ElementDatabase<U>* main_list, ElementDatabase<U>* current_list, U* current_element, TStringGrid* StringGrid );


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	main_car_list = new CarDatabase();

	main_client_list = new ElementDatabase<Client>();


	current_car = NULL;
	current_client = NULL;

	try
	{
		LoadFromFile("car_database.txt", "client_database.txt");
	}
	catch(...)
	{
		ShowMessage("The file is damaged or does not contain database");
    }

	FullCarsListButtonClick(Sender);
	FullClientsListButtonClick(Sender);

	ToCarDatabaseState();

	client_edits[0] = SurnameEdit;
	client_edits[1] = NameEdit;
	client_edits[2] = PhoneNumberEdit;
	client_edits[3] = BrandEdit;
	client_edits[4] = YearEdit;
	client_edits[5] = EngineCapacityEdit;
	client_edits[6] = ConditionEdit;
	client_edits[7] = MaxPriceEdit;

	car_edits[0] = YearEdit;
	car_edits[1] = EngineCapacityEdit;
	car_edits[2] = BrandEdit;
	car_edits[3] = ConditionEdit;






	CarStringGrid -> Cells[1][0] = "Year";
	CarStringGrid -> Cells[2][0] = "Engine capacity";
	CarStringGrid -> Cells[3][0] = "Brand";
	CarStringGrid -> Cells[4][0] = "Condition";
	CarStringGrid -> Cells[5][0] = "Price";
	CarStringGrid -> Cells[6][0] = "Profit";

	ClientStringGrid -> Cells[1][0] = "Surname";
	ClientStringGrid -> Cells[2][0] = "Name";
	ClientStringGrid -> Cells[3][0] = "Phone number";
	ClientStringGrid -> Cells[4][0] = "Pref. brand";
	ClientStringGrid -> Cells[5][0] = "Pref. min.year";
	ClientStringGrid -> Cells[6][0] = "Pref. min.engine capacity";
	ClientStringGrid -> Cells[7][0] = "Pref. condition";
	ClientStringGrid -> Cells[8][0] = "Pref. max.price";

	for(int i = 0; i < 7 ; i++ )
	{
		CarStringGrid -> ColWidths[i] = 150;
	}

	for(int i = 0; i < 9; i++)
	{
		ClientStringGrid -> ColWidths[i] = 150;
	}

	ClientChangeComboBox -> Items -> Add ("Surname");
	ClientChangeComboBox -> Items -> Add ("Name");
	ClientChangeComboBox -> Items -> Add ("Phone number");
	ClientChangeComboBox -> Items -> Add ("Pref. brand");
	ClientChangeComboBox -> Items -> Add ("Pref. min.year");
	ClientChangeComboBox -> Items -> Add ("Pref. min.engine capacity");
	ClientChangeComboBox -> Items -> Add ("Pref. condition");
	ClientChangeComboBox -> Items -> Add ("Pref. max.price");

	SortComboBox -> Items -> Add("Year");
	SortComboBox -> Items -> Add("Engine capacity");
	SortComboBox -> Items -> Add("Price");

	ClientFindComboBox -> Items -> Add ("Surname");
	ClientFindComboBox -> Items -> Add ("Name");
	ClientFindComboBox -> Items -> Add ("Phone number");
	ClientFindComboBox -> Items -> Add ("Pref. brand");
	ClientFindComboBox -> Items -> Add ("Pref. min.year");
	ClientFindComboBox -> Items -> Add ("Pref. min.engine capacity");
	ClientFindComboBox -> Items -> Add ("Pref. condition");
	ClientFindComboBox -> Items -> Add ("Pref. max.price");

	CarFindComboBox -> Items -> Add("Year");
	CarFindComboBox -> Items -> Add("Engine capacity");
	CarFindComboBox -> Items -> Add("Brand");
	CarFindComboBox -> Items -> Add("Condition");
	CarFindComboBox -> Items -> Add("Price");
	CarFindComboBox -> Items -> Add("Profit");


}


//---------------------------------------------------------------------------

void __fastcall TForm1::CarStringGridOnSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	current_row = ARow;
	if( ARow != 0 )
	{
		current_car = current_car_list -> GetElement( current_row - 1);
	}
	else
	{
		current_car = NULL;
	}
	ToCarDatabaseState();

}
//---------------------------------------------------------------------------



void __fastcall TForm1::ClientStringGridOnSelectCell(TObject *Sender, int ACol, int ARow,
		  bool &CanSelect)
{
	current_row = ARow;
	if(ARow != 0)
	{
		current_client = current_client_list -> GetElement( ARow - 1);
	}
	else
	{
		current_client = NULL;
	}
	ToClientDatabaseState();

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FullCarsListButtonClick(TObject *Sender)
{
	if(current_car_list != main_car_list)
	{
		delete current_car_list;
	}

	current_car_list = main_car_list;
	current_car_list -> Print(CarStringGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FullClientsListButtonClick(TObject *Sender)
{
	if(current_car_list != main_car_list)
	{
		delete current_client_list;
	}
	current_client_list = main_client_list;
	current_client_list -> Print(ClientStringGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteCarButtonClick(TObject *Sender)
{
	Delete(main_car_list, current_car_list, current_car, CarStringGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteClientButtonClick(TObject *Sender)
{
	Delete(main_client_list, current_client_list, current_client, ClientStringGrid);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChangeButtonClick(TObject *Sender)
{
	try
	{
		int filter = ClientChangeComboBox -> ItemIndex;
		current_client -> Change( FeatureChangeEdit -> Text, filter );
		current_client_list -> Print(ClientStringGrid);
	}
	catch(...)
	{
		ShowMessage("Wrong format of input.");
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SortButtonClick(TObject *Sender)
{
	try
	{
		CarDatabase* temp = new CarDatabase();
		current_car_list -> Sort(temp, SortComboBox -> ItemIndex);
		if(current_car_list != main_car_list)
		{
			delete current_car_list;
        }

		current_car_list = temp;
		current_car_list -> Print(CarStringGrid);
	}
	catch(...)
	{
		ShowMessage("The list is empty or a filter of sorting is not choosen");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindButtonClick(TObject *Sender)
{
	try
	{
		if(work_with_cars)
		{
			CarDatabase* temp = new CarDatabase();
			current_car_list -> SeekFeature(FeatureFindEdit -> Text, CarFindComboBox -> ItemIndex, temp);
			if(current_car_list != main_car_list)
			{
				delete current_car_list;
			}
			current_car_list = temp;
			current_car_list -> Print(CarStringGrid);
		}
		else
		{
			ElementDatabase<Client>* temp = new ElementDatabase<Client>();
			current_client_list -> SeekFeature(FeatureFindEdit -> Text, ClientFindComboBox -> ItemIndex, temp);
			if(current_client_list != main_client_list)
			{
				delete current_client_list;
			}
			current_client_list = temp;
			current_client_list -> Print(ClientStringGrid);
		}
	}
	catch(...)
	{
		ShowMessage("A filter is not chosen or the input is wrong.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AppropriateCarsButtonClick(TObject *Sender)
{
	if(current_client != NULL)
	{
		if( current_car_list != main_car_list )
		{
			delete current_car_list;
		}
		current_car_list = current_client -> AppropriateCars(main_car_list);
		current_car_list ->Print( CarStringGrid );
	}
	else
	{
		ShowMessage("Select a client from the client grid.");
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	try
	{
		if(work_with_cars)
		{
			Car* new_car = new Car(car_edits);
			main_car_list -> Add(new_car);
			if(main_car_list != current_car_list)
			{
				current_car_list -> Add(new_car);
			}
			current_car_list -> Print(CarStringGrid);
		}
		else
		{
			Client* new_client = new Client(client_edits);
			main_client_list -> Add(new_client);
			if(main_client_list != current_client_list)
			{
				current_client_list -> Add(new_client);
			}
			current_client_list -> Print(ClientStringGrid);
		}

	}
	catch(...)
	{
		ShowMessage("Wrong input");
	}
}

void __fastcall TForm1::CloseButtonClick(TObject *Sender)
{
	delete current_car_list;
	delete current_client_list;

	main_car_list -> ClearAll();
	main_client_list -> ClearAll();

	delete main_car_list;
	delete main_client_list;

	this -> Close();


}
//---------------------------------------------------------------------------



void ToCarDatabaseState()
{
	current_client = NULL;
	work_with_cars = true;
	Form1 -> CarFindComboBox -> Visible = true;
	Form1 -> ClientFindComboBox -> Visible = false;
	Form1 -> SortComboBox -> Visible = true;
	Form1 -> SortButton -> Visible = true;
	Form1 -> ClientChangeComboBox -> Visible = false;
	Form1 -> FeatureChangeEdit -> Visible = false;
	Form1 -> ChangeButton -> Visible = false;
	Form1 -> FullClientsListButton -> Visible = false;
	Form1 -> DeleteClientButton -> Visible = false;
	Form1 -> DeleteCarButton -> Visible = true;
	Form1 -> FullCarsListButton -> Visible = true;
	Form1 -> SortLabel -> Visible = true;
	Form1 -> FilterChangeLabel -> Visible = false;
	Form1 -> FeatureChangeEdit -> Visible = false;

	Form1 -> SurnameEdit -> Visible = false;
	Form1 -> SurnameLabel -> Visible = false;
	Form1 -> NameEdit -> Visible = false;
	Form1 -> NameLabel -> Visible = false;
	Form1 -> PhoneNumberEdit -> Visible = false;
	Form1 -> PhoneNumberLabel -> Visible = false;
	Form1 -> MaxPriceEdit -> Visible = false;
	Form1 -> MaxPriceLabel -> Visible = false;

	Form1 -> AppropriateCarsButton -> Visible = false;

	Form1 -> AddButton -> Caption = "Add a car";
}

void ToClientDatabaseState()
{
	current_car = NULL;
	work_with_cars = false;
	Form1 -> CarFindComboBox -> Visible = false;
	Form1 -> ClientFindComboBox -> Visible = true;
	Form1 -> SortComboBox -> Visible = false;
	Form1 -> SortButton -> Visible = false;
	Form1 -> ClientChangeComboBox -> Visible = true;
	Form1 -> FeatureChangeEdit -> Visible = true;
	Form1 -> ChangeButton -> Visible = true;
	Form1 -> FullClientsListButton -> Visible = true;
	Form1 -> DeleteClientButton -> Visible = true;
	Form1 -> DeleteCarButton -> Visible = false;
	Form1 -> FullCarsListButton -> Visible = false;
	Form1 -> SortLabel -> Visible = false;
	Form1 -> FilterChangeLabel -> Visible = true;
	Form1 -> FeatureChangeEdit -> Visible = true;

	Form1 -> SurnameEdit -> Visible = true;
	Form1 -> SurnameLabel -> Visible = true;
	Form1 -> NameEdit -> Visible = true;
	Form1 -> NameLabel -> Visible = true;
	Form1 -> PhoneNumberEdit -> Visible = true;
	Form1 -> PhoneNumberLabel -> Visible = true;
	Form1 -> MaxPriceEdit -> Visible = true;
	Form1 -> MaxPriceLabel -> Visible = true;

	Form1 -> AppropriateCarsButton -> Visible = true;

	Form1 -> AddButton -> Caption = "Add an application";
}

void LoadFromFile(AnsiString car_path, AnsiString client_path)
{
	TStringList* each_car_info = new TStringList();
	each_car_info -> LoadFromFile(car_path);
	main_car_list -> SetFromFile( each_car_info );

	TStringList* each_client_info = new TStringList();
	each_client_info -> LoadFromFile(client_path);
	main_client_list -> SetFromFile( each_client_info );
}

template <class U>
void Delete( ElementDatabase<U>* main_list, ElementDatabase<U>* current_list, U* current_element, TStringGrid* StringGrid )
{
	try
	{
		if( current_row == 0 )
		{
			throw std::logic_error("");
		}

		main_list -> Erase(current_element);
		if(main_list != current_list)
		{
			current_list -> Delete(current_row - 1);
		}
		current_list -> Print( StringGrid );
	}
	catch(...)
	{
		ShowMessage("Select an element");
	}
}











//---------------------------------------------------------------------------



