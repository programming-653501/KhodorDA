//---------------------------------------------------------------------------


#pragma hdrstop

#include "MyStack.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void MyStack::Print(TMemo* Memo)
{
	Node* slider = _end;
	Memo -> Lines -> Clear();

	for( int i = 0; i < _length; i++ )
	{
		Memo -> Lines -> Add( slider -> info);
		slider = slider -> previous;
    }
}

bool MyStack::Push(AnsiString new_string)
{
	if( new_string == "" )
	{
        throw std::invalid_argument("You are trying to push an empty string");
	}

	int sum = GetSumOfCodes ( new_string );
	if(sum % 2 == 0)
	{
		Stack<AnsiString>::Push( new_string + " " + IntToStr( sum ) );
		return true;
	}

	return false;

}
