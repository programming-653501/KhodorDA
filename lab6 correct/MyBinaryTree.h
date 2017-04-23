//---------------------------------------------------------------------------

#ifndef MyBinaryTreeH
#define MyBinaryTreeH



#include "BinTree.h"
#include <vcl.h>
#include <iostream>
#include "Stack.h"
#include "MyFunctions.h"
using namespace std;


class MyBinaryTree: public BinaryTree0
{
	public:
	MyBinaryTree():BinaryTree0() {};

	void ToStack( Stack<AnsiString>* stack );



	private:

	void ToStack( Stack<AnsiString>* stack, Node* root );



};
//---------------------------------------------------------------------------
#endif
