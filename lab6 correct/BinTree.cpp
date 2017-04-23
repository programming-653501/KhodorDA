//---------------------------------------------------------------------------


#pragma hdrstop

#include "BinTree.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

BinaryTree0::BinaryTree0()
{
	_root = NULL;
	_amount = 0;

}

void BinaryTree0::ClearAll()
{
	ClearAll(&_root);
	_amount = 0;
}

void BinaryTree0::Add(TStringGrid* StringGrid)
{
	int length = StringGrid -> RowCount;

	for(int i = 1; i < length; i++)
	{
		AnsiString info = StringGrid -> Cells[0][i];
		int key = StrToInt( StringGrid -> Cells[1][i] );
		Add( info, key );
	}
}

void BinaryTree0::Add(Node** root, AnsiString info, int key)
{
	if( !(*root) )
	{
		(*root) = new Node( info, key );
		return;
    }

	if(key < (*root) -> key )
	{
		if ( ! (*root) -> left_child )
		{
			(*root) -> left_child = new Node(info, key);

		}
		else
		{
			Add( &( (*root) -> left_child ), info, key);
		}
	}
	else
	{
		if( key > (*root) -> key )
		{
			if ( ! (*root) -> right_child )
			{
				(*root) -> right_child = new Node(info, key);

			}
			else
			{
				Add( &( (*root) -> right_child ), info, key);
			}
		}
		else
		{
			//UnicodeString error_message =  + IntToStr(key);
			throw std::invalid_argument("You are trying to add an element with the key already used in the tree");
		}
	}


}

void BinaryTree0::Add(AnsiString info, int key)
{
	Add(&_root, info, key);
	_amount++;
}

Node** BinaryTree0::GetNode(Node** root_pointer, int key)//, Node** destination)
{

	if ( *root_pointer )
	{
		if ( (*root_pointer) -> key == key)
		{
			return root_pointer;
		}
		else
		{
			if ( key < (*root_pointer) -> key)
			{
				return GetNode( & ((*root_pointer) -> left_child), key);
			}
			else
			{
				if ( key > (*root_pointer) -> key )
				{
					return GetNode( & ((*root_pointer) -> right_child), key);
				}
			}
		}
	}

	return NULL;

}



AnsiString BinaryTree0::Find(int key)
{
	Node** needed_node = GetNode( &_root, key );

	if( needed_node )
	{
		return (*needed_node) -> info;
	}
	else
	{
		throw std::invalid_argument("There is no element with such key");
    }
}

void BinaryTree0::Delete( int key )
{
	Delete( key, &_root );
}

void BinaryTree0::Delete( int key, Node** subroot )
{
	if( !(*subroot) )
	{
		throw std::invalid_argument("There is no element with such key");
	}

	Node** needed_node = GetNode( subroot, key );


	if( !needed_node )
	{
		throw std::invalid_argument("There is no element with such key");
	}

	if( !(*needed_node) -> left_child && !(*needed_node) -> right_child )
	{

		delete *needed_node;
		*needed_node = NULL;
		_amount--;
		return;
	}

	Node** change_to;

	if( (*needed_node) -> left_child )   //ищем наибольший в левом поддереве...
	{
		change_to = & ((*needed_node) -> left_child) ;
		while( (*change_to) -> right_child )
		{
			change_to =  & ((*change_to) -> right_child) ;
		}
	}
	else //...или наименьший в правом
	{
		change_to = & ((*needed_node) -> right_child) ;
		while( (*change_to) -> left_child )
		{
			change_to =  & ((*change_to) -> left_child) ;
		}
	}

	AnsiString new_info = (*change_to) -> info;
	int new_key = (*change_to) -> key;

	(*change_to) -> info = (*needed_node) -> info;
	(*change_to) -> key = (*needed_node) -> key;
	(*needed_node) -> info = new_info;
	(*needed_node) -> key = new_key;


	Delete( (*change_to) -> key, change_to );


}

void BinaryTree0::PrintInOrder( Node* root, TMemo* Memo )
{
	if( !root )
	{
		return;
	}

	PrintInOrder( root -> left_child, Memo );
	Memo -> Lines -> Add( root -> ToString() );
	PrintInOrder( root -> right_child, Memo );
}

void BinaryTree0::PrintInOrder( TMemo* Memo )
{
	Memo -> Clear();
	PrintInOrder( _root, Memo );
}

void BinaryTree0::PrintPreOrder( Node* root, TMemo* Memo )
{
	if( !root )
	{
		return;
	}

	Memo -> Lines -> Add( root -> ToString() );
	PrintPreOrder( root -> left_child, Memo);
	PrintPreOrder( root -> right_child, Memo );
}

void BinaryTree0::PrintPreOrder(TMemo* Memo)
{
	Memo -> Clear();
	PrintPreOrder(_root, Memo);
}


void BinaryTree0::PrintPostOrder( Node* root, TMemo* Memo )
{
	if( !root )
	{
		return;
	}

	PrintPostOrder( root -> left_child, Memo );
	PrintPostOrder( root -> right_child, Memo );
	Memo -> Lines -> Add( root -> ToString() );
}

void BinaryTree0::PrintPostOrder( TMemo* Memo )
{
	Memo -> Clear();
	PrintPostOrder(_root, Memo);
}

void BinaryTree0::ClearAll( Node** root )
{
	if( !(*root) )
	{
		return;
	}


	ClearAll( & ((*root) -> left_child) );
	ClearAll( & ((*root) -> right_child) );
	delete *root;
	*root = NULL;
}

void BinaryTree0::Balance()
{
	if( _amount < 3 )
	{
		return;
    }
	element **element_array = new element* [_amount];
	int* index = new int(0);
	FillInArray( _root, element_array, index );
	ClearAll( &_root );
	int n = _amount;
	_amount = 0;
	BalancedAdding( element_array, n );

	for(int i = 0; i < _amount; i++)
	{
		delete element_array[i];
	}
	delete []element_array;
	delete index;

}

void BinaryTree0::BalancedAdding(element** element_array, int n)
{
	if( n == 0 )
	{
		return;
	}

	AnsiString info_to_add = ( *(element_array + n/2) ) -> info;
	int key_to_add = ( *(element_array + n/2) ) -> key;

	Add( info_to_add, key_to_add );
	if( n == 1 )
	{
		return;
	}
	else
	{
		BalancedAdding( element_array, n/2 );
		if( n%2 == 1 )
		{
			BalancedAdding( element_array + n/2 + 1, n/2 );
		}
		else
		{
			BalancedAdding( element_array + n/2 + 1, n/2 - 1 );
        }
    }
}

void BinaryTree0::FillInArray( Node* root, element** element_array, int* current_index ) //массив указателей на элементы
{
	if( !root )
	{
		return;
	}

   //	static int current_index = 0;

	FillInArray( root -> left_child, element_array, current_index);
	element_array[ *current_index ] = new element(root);
	(*current_index)++;
	FillInArray( root-> right_child, element_array, current_index );

	//current_index = 0;

}

void BinaryTree0::Show(TTreeView* TreeView, TTreeNode* Root, Node* root)
{
	if( !root )
	{
		return;
	}


	TTreeNode* current_root = Root;
	if( root -> left_child )
	{
			Root = TreeView -> Items -> AddChildFirst( current_root, root -> left_child -> ToString() );
			Show(TreeView, Root, root -> left_child);
	}
	else
	{
		Root = TreeView -> Items -> AddChildFirst( current_root, "NULL" );
    }
	if( root -> right_child )
	{
			Root = TreeView -> Items -> AddChild( current_root, root -> right_child -> ToString() );
			Show(TreeView, Root, root -> right_child);
	}
	else
	{
		Root = TreeView -> Items -> AddChild( current_root, "NULL" );
    }
}

void BinaryTree0::Show(TTreeView* TreeView)
{
	TreeView -> Items -> BeginUpdate();

	TreeView -> Items -> Clear();
	if( _root )
	{
		TTreeNode* Root = TreeView -> Items -> Add( NULL, _root -> ToString() );
		Show( TreeView, Root, _root );
	}

	TreeView -> Items -> EndUpdate();
}

BinaryTree0::~BinaryTree0()
{
	ClearAll( &_root );
	_amount = 0;
}





