//---------------------------------------------------------------------------


#pragma hdrstop

#include "MyFunctions.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int GetSumOfCodes(AnsiString some_string)
{
	if(some_string == "")
	{
		return -1;
	}
	int sum = 0;
	for(int i = 1; i <= some_string.Length(); i++)
	{
		sum += (int)some_string[i];
	}

	return (int)sum;
}

/*bool EvenSum(AnsiString some_string)
{

		if(GetSumOfCodes(some_string) % 2 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}

}*/
