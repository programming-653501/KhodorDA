//---------------------------------------------------------------------------

#ifndef BinTreeH
#define BinTreeH

#include <vcl.h>
#include <Grids.hpp>
#include <system.hpp>
#include <iostream>

using namespace std;



struct Node
{

	public:
	AnsiString info;
	int key;
	Node* left_child;
	Node* right_child;

	AnsiString ToString()
	{
		return info + " " + IntToStr( key );
	}

	Node(AnsiString info1, int key1)
	{
		info = info1;
		key = key1;
		left_child = NULL;
		right_child = NULL;
	}


};

struct element
{
	AnsiString info;
	int key;

	element(Node* node)
	{
		if( node )
		{
			info = node -> info;
			key = node -> key;
		}
		else
		{
			info = "";
			key = 0;
		}
	}

};

class BinaryTree0
{
	protected:
	Node* _root;
	int _amount;

	Node** GetNode(Node** root_pointer, int key);
	void Add(Node** root, AnsiString info, int key);
	void ClearAll(Node** root);

	void PrintInOrder( Node* root, TMemo* Memo);
	void PrintPreOrder( Node* root, TMemo* Memo);
	void PrintPostOrder( Node* root, TMemo* Memo);

	void FillInArray( Node* root, element** element_array, int* current_index );
	void BalancedAdding(element** element_array, int n);

	void BinaryTree0::Show(TTreeView* TreeView, TTreeNode* Root, Node* root);

	void Delete(int key, Node** subroot);


	public:
	BinaryTree0();

	void Add(TStringGrid* StringGrid);
	void Add(AnsiString info, int key);
    void Delete(int key);
	AnsiString Find(int key);
	void PrintInOrder(TMemo* Memo);  //симметричный
	void PrintPreOrder(TMemo* Memo);//прямой
	void PrintPostOrder(TMemo* Memo);//обратный
	void Balance();
	void Show(TTreeView* TreeView);
	void ClearAll();

	~BinaryTree0();



};
//---------------------------------------------------------------------------
#endif
