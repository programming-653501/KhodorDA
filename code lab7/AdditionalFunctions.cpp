//---------------------------------------------------------------------------


#pragma hdrstop

#include "AdditionalFunctions.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void SplitString(AnsiString string_to_split, vector<AnsiString>& destination)
{
	int last_space_index = 0;
	string_to_split = string_to_split + " ";
	for(int i = 1; i <= string_to_split.Length(); i++)
	{
		if( string_to_split.IsDelimiter(" ", i) )
		{
			if(i == last_space_index + 1)
			{
				last_space_index++;
				continue;
            }
			AnsiString temp = string_to_split.SubString(last_space_index + 1, i - last_space_index - 1);
			destination.push_back(temp);
			last_space_index = i;
		}
	}
}

bool CheckForNumber(AnsiString string)
{
	char* my_string = string.c_str();
	char current;
	for(int i = 0; i < string.Length(); i++)
	{
		current = my_string[i];
		if( !isdigit(current) )
		{
			return false;
		}
	}
	return true;
}
