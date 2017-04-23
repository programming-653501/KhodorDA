//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "MyBinaryTree.h"
#include "MyStack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

MyBinaryTree* tree = NULL;
MyStack* stack = NULL;

typedef enum { in_order, pre_order, post_order } PrintType;

PrintType selected_print_type = in_order;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	tree = new MyBinaryTree();
	stack = new MyStack();
	Memo -> Clear();
	StackMemo -> Clear();
	StringGrid -> ColWidths[0] = 120;
	StringGrid -> ColWidths[1] = 120;
	StringGrid -> Cells[0][0] = "String";
	StringGrid -> Cells[1][0] = "Key";
	PrintComboBox -> Items -> Add("InOrder");
	PrintComboBox -> Items -> Add("PreOrder");
	PrintComboBox -> Items -> Add("PostOrder");


}
//---------------------------------------------------------------------------


void __fastcall TForm1::PlusButtonClick(TObject *Sender)
{
	StringGrid -> RowCount++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MinusButtonClick(TObject *Sender)
{
	StringGrid -> RowCount--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	if( StringGrid -> RowCount == 1 )
	{
		ShowMessage("Fill in at least one row");
		return;
    }
	for( int i = 1; i < StringGrid -> RowCount; i++ )
	{
		int value = 0;
		if( StringGrid -> Cells[0][i] == "" || StringGrid -> Cells[1][i] == "" )
		{
			ShowMessage("Fill in all the rows");
			return;
		}

		if( !TryStrToInt( StringGrid -> Cells[1][i], value ) || value < 0 )
		{
			ShowMessage("Only positive integer numbers in the second column are allowed");
			return;
		}
	}

	try
	{
		tree -> Add(StringGrid);
		PrintAllClick(Sender);

		PrintButton -> Enabled = true;
		DeleteButton -> Enabled = true;
		FindButton -> Enabled = true;
		BalanceButton -> Enabled = true;
		Add1Button -> Enabled = true;

		AddButton -> Enabled = false;
	}
	catch(std::invalid_argument& e)
	{
		tree -> ClearAll();
		ShowMessage("The table contains more than one element with the same key");
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::StringGridOnSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	if( ARow != 0 )
	{
		StringGrid -> Options << goEditing;
	}
	else
	{
		StringGrid -> Options >> goEditing;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PrintAllClick(TObject *Sender)
{
	PrintButtonClick(Sender);
	tree -> ToStack( stack );
	stack -> Print( StackMemo );
	tree -> Show (TreeView);
	TreeView -> FullExpand();

	KeyEditFindDelete -> Clear();
	InfoFindPanel -> Caption = "";




}
//---------------------------------------------------------------------------



void __fastcall TForm1::PrintButtonClick(TObject *Sender)
{
	switch( selected_print_type )
	{
		case in_order:
		{
			tree -> PrintInOrder(Memo);
			break;
		}
		case pre_order:
		{
			tree -> PrintPreOrder(Memo);
			break;
		}
		case post_order:
		{
			tree -> PrintPostOrder(Memo);
			break;
        }

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PrintComboBoxOnChange(TObject *Sender)
{
	selected_print_type = (PrintType) PrintComboBox -> ItemIndex;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
{
	if( KeyEditFindDelete -> Text != ""	)
	{
		try
		{
			tree -> Delete( StrToInt (KeyEditFindDelete -> Text) );
			PrintAllClick(Sender);
		}
		catch( std::invalid_argument& e )
		{
			ShowMessage( e.what() );
        }

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindButtonClick(TObject *Sender)
{
	AnsiString result = "";
	if( KeyEditFindDelete -> Text != ""	)
	{
		try
		{
			result = tree -> Find( StrToInt (KeyEditFindDelete -> Text) );
			InfoFindPanel -> Caption = result;
		}
		catch( std::invalid_argument& e )
		{
			ShowMessage( e.what() );
        }

	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BalanceButtonClick(TObject *Sender)
{
		tree -> Balance();
		tree -> Show(TreeView);
		PrintButtonClick(Sender);
		TreeView -> FullExpand();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CloseButtonClick(TObject *Sender)
{
	delete tree;
	delete stack;
	Form1 -> Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Add1ButtonClick(TObject *Sender)
{
	try
	{
		tree -> Add( AddStringEdit->Text, StrToInt( AddKeyEdit->Text ) );
		PrintAllClick(Sender);
	}
	catch(std::invalid_argument& e)
	{
        ShowMessage(e.what());
    }
	catch(...)
	{
		ShowMessage("wrong input");
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::PushButtonClick(TObject *Sender)
{
	try
	{
		if( stack -> Push( StackAddEdit -> Text ) )
		{
			stack -> Print( StackMemo );
		}
		else
		{
			ShowMessage( "The string doesn't have an even sum of codes" );
        }
	}
	catch( std::invalid_argument& e )
	{
		ShowMessage(e.what());
	}
}


//---------------------------------------------------------------------------

void __fastcall TForm1::PopButtonClick(TObject *Sender)
{
	try
	{
		stack -> Pop();
		stack -> Print(StackMemo);
	}
	catch(std::logic_error& e)
	{
		ShowMessage(e.what());
	}
}
//---------------------------------------------------------------------------

