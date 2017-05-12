//---------------------------------------------------------------------------

#ifndef AdditionalFunctionsH
#define AdditionalFunctionsH

#include <vector>
#include <vcl.h>
#include <iostream>
#include <system.hpp>
#include <Grids.hpp>
#include <stdexcept>
#include <cctype>

using namespace std;
//---------------------------------------------------------------------------
void SplitString(AnsiString string_to_split, vector<AnsiString>& destination);
bool CheckForNumber(AnsiString string);
#endif
