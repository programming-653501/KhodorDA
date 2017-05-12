//---------------------------------------------------------------------------

#ifndef ElementDatabaseH
#define ElementDatabaseH
//---------------------------------------------------------------------------

#include <vector>
#include <vcl.h>
#include <iostream>
#include <system.hpp>
#include <Grids.hpp>
#include <stdexcept>

#include "AdditionalFunctions.h"
using namespace std;



class GetterSetter
{
	protected:

	typedef void(GetterSetter::*Setter)(AnsiString);
	typedef AnsiString(GetterSetter::*Getter)();

	int cnt_set_methods;
	Setter *element_set_methods;

	int cnt_get_methods;
	Getter *element_get_methods;


	virtual void SetSetters() = 0;
	virtual void SetGetters() = 0;

	void virtual SetClassInfo()
	{
		SetSetters();
		SetGetters();
	}

	public:
	void SetFeatures( vector <AnsiString> features )
	{
		if( features.size() == (unsigned)cnt_set_methods )
		{
			for(int i = 0; i < cnt_set_methods; i++)
			{
				(this->*(element_set_methods[i]))( features[i] );
			}
		}
		else
		{
			throw std::invalid_argument("Not all information is given.");
        }
	}

	void SetFeatures( TEdit** Edits )
	{
		for(int i = 0; i < cnt_set_methods; i++)
		{
			(this->*(element_set_methods[i]))( Edits[i] -> Text );
		}
	}

	void SaveToString(TStringList* StringList)
	{
		AnsiString element_info = "";

		for(int i = 0; i < cnt_get_methods; i++)
		{
			element_info = element_info + (this->*(element_get_methods[i]))() + " ";
		}
		StringList -> Add(element_info);
	}

	void Print( int row, TStringGrid* StringGrid)
	{
		if(StringGrid -> RowCount - 1 < row)
		{
			StringGrid -> RowCount++;
		}
		StringGrid->Cells[0][row] = row;
		for( int i = 1; i <= cnt_get_methods; i++)
		{
		   StringGrid -> Cells[i][row] = (this->*(element_get_methods[i-1]))();
		}
	}

	bool Equal(AnsiString feature, int filter)
	{
		if( filter >= cnt_get_methods || filter < 0 )
		{
			throw std::invalid_argument("Wrong filter number");
		}

		AnsiString element_feature = (this->*(element_get_methods[filter]))();
		if(element_feature == feature)
		{
			return true;
		}
		return false;
	}

	void Change(AnsiString new_feature, int filter)
	{
		if( filter >= cnt_set_methods || filter < 0 )
		{
			throw std::invalid_argument("Wrong filter number");
		}

		(this->*(element_set_methods[filter]))(new_feature);
    }
};


template <class U>
class ElementDatabase
{
	protected:

	vector < U* > _list;

	public:

	void SetFromFile(TStringList* StringList)
	{

		unsigned int number_of_elements = StringList -> Count;
		vector <AnsiString> element_info;
		for(unsigned int i = 0; i < number_of_elements; i++)
		{
			if(StringList -> Strings[i] != "")
			{
				vector <AnsiString> & pointer = element_info;
				SplitString(StringList -> Strings[i], pointer);
				_list.push_back( new U(element_info));
				element_info.clear();
			}
		}


	}

	int Size()
	{
		return _list.size();
	}

	void SaveToFile(TStringList* StringList)
	{
		for(unsigned int i = 0; i < _list.size(); i++)
		{
			_list[i] -> SaveToString(StringList, i);
		}
	}

	void Add(U* element_to_add)
	{
		_list.push_back(element_to_add);
	}


	bool IsEmpty()
	{
		if(_list.size() == 0)
		{
			return true;
		}
		return false;
	}


	void SeekFeature(AnsiString feature, int filter, ElementDatabase<U>* destination)
	{
        if(!destination -> IsEmpty() && destination != this)
		{
			delete destination;
			destination = new ElementDatabase<U>();
		}
		for(unsigned int i = 0; i < _list.size(); i++)
		{
			if( _list[i] -> Equal( feature, filter ) )
			{
				destination -> Add( _list[i] );
			}
		}
	}


	void CopyAll(ElementDatabase<U> *destination)
	{
		for(unsigned int i = 0; i < _list.size(); i++)
		{
			destination -> Add( _list[i] );
		}
	}

	void Erase(U* element_to_delete)
	{
		for(unsigned int j = 0; j < _list.size(); j++)
		{
			if( element_to_delete == _list[j] )
			{
				_list.erase(_list.begin() + j);
			}
		}
	}

	void Delete(int index)
	{
		delete _list[index];
		_list.erase(_list.begin() + index);
	}

	void ClearAll()
	{
		int size = Size();
		for(int i = 0; i < size; i++)
		{
            Delete(i);
        }
    }



	U* GetElement(unsigned int index)
	{
		if( index < _list.size() )
		{
			return _list[index];
		}
		else
		{
			throw std::invalid_argument("Index out of range");
		}
	}


	void Print(TStringGrid* StringGrid)
	{
		StringGrid -> RowCount = StringGrid -> FixedRows;
		if( this -> IsEmpty() )
		{
			return;
		}
		for(unsigned int i = 0; i < _list.size(); i++)
		{
			_list[i] -> Print( i + 1, StringGrid);
		}
	}
};
#endif
