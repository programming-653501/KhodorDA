//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeView;
	TStringGrid *StringGrid;
	TComboBox *PrintComboBox;
	TMemo *Memo;
	TButton *AddButton;
	TButton *PrintButton;
	TEdit *KeyEditFindDelete;
	TLabel *Label3;
	TPanel *InfoFindPanel;
	TButton *FindButton;
	TButton *DeleteButton;
	TButton *BalanceButton;
	TButton *CloseButton;
	TButton *MinusButton;
	TButton *PlusButton;
	TButton *PrintAll;
	TEdit *AddKeyEdit;
	TButton *Add1Button;
	TEdit *AddStringEdit;
	TLabel *Label1;
	TLabel *Label2;
	TMemo *StackMemo;
	TLabel *Label4;
	TEdit *StackAddEdit;
	TButton *PushButton;
	TButton *PopButton;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall PlusButtonClick(TObject *Sender);
	void __fastcall MinusButtonClick(TObject *Sender);

	void __fastcall StringGridOnSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall PrintAllClick(TObject *Sender);
	void __fastcall PrintButtonClick(TObject *Sender);
	void __fastcall PrintComboBoxOnChange(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
	void __fastcall FindButtonClick(TObject *Sender);
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall BalanceButtonClick(TObject *Sender);
	void __fastcall Add1ButtonClick(TObject *Sender);
	void __fastcall PushButtonClick(TObject *Sender);
	void __fastcall PopButtonClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
