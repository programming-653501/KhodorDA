//---------------------------------------------------------------------------

#ifndef MyStackH
#define MyStackH

#include "Stack.h"
#include "MyFunctions.h"
#include <vcl.h>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------

class MyStack : public Stack<AnsiString>
{
	public:
	MyStack():Stack<AnsiString>() {};
	void Print(TMemo* Memo);
	bool Push(AnsiString new_string);
};
#endif
