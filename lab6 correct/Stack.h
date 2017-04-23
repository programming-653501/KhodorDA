//---------------------------------------------------------------------------

#ifndef StackH
#define StackH

#include <vcl.h>
#include <iostream>
using namespace std;





template <typename T>
class Stack
{
	protected:
	struct Node
	{
		T info;
		Node* previous;
		Node* next;

	};

	Node* _end;
	int _length;

	public:
	Stack()
	{
		_end = NULL;
		_length = 0;
	}

	bool virtual Push(T new_symbol)
	{
		if (_length == 0)
		{

			_end = new Node();
			_end -> info = new_symbol;
			_length++;
		}
		else
		{
			Node* new_node = new Node();
			new_node -> info = new_symbol;
			new_node -> previous = _end;
			_end -> next = new_node;
			_end = new_node;

			_length++;
		}
		return true;
	}

	void virtual Print(TMemo* Memo) = 0;

	/*T OutLastElement()
	{
		if(_length == 0 )
		{
			throw std::logic_error("Invalid expression input");
		}
		T temp = _end -> info;
		Pop();
		return temp;
	} */

	void Pop()
	{
		if(_length != 0)
		{
			Node* temp = _end;

			if(_length != 1)
			{
				_end -> previous -> next = NULL;
				_end = _end -> previous;
			}
			_length --;

			delete temp;
		}
		else
		{
			throw std::logic_error("You are trying to delete an element from empty stack");
		}
	}

   /*	T LastElement()
	{
		if(_length == 0 )
		{
			throw std::logic_error("Invalid expression input");
		}
		return _end -> info;
	} */

	bool IsEmpty()
	{
		if(_length == 0)
		{
			return true;
		}

		return false;
	}

	void ClearAll()
	{
		while(!IsEmpty())
		{
			Pop();
		}
    }

	~Stack()
	{
    	ClearAll();
	}
};



//---------------------------------------------------------------------------
#endif
