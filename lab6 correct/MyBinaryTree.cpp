//---------------------------------------------------------------------------


#pragma hdrstop

#include "MyBinaryTree.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void MyBinaryTree::ToStack( Stack<AnsiString>* stack )
{
	stack->ClearAll();
	ToStack( stack, _root);
}

void MyBinaryTree::ToStack( Stack<AnsiString>* stack, Node* root )
{
	if( !root )
	{
		return;
	}


	//int sum = GetSumOfCodes( root -> info );
	//if( sum % 2 == 0 )
	//{
	stack -> Push( root -> info );
	//}

	ToStack( stack, root -> left_child );
	ToStack( stack, root -> right_child );
}
