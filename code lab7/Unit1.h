//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *CarStringGrid;
	TStringGrid *ClientStringGrid;
	TLabel *Label1;
	TLabel *Label2;
	TButton *CloseButton;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *FilterEditLabel;
	TLabel *FilterChangeLabel;
	TComboBox *ClientChangeComboBox;
	TEdit *FeatureChangeEdit;
	TEdit *FeatureFindEdit;
	TLabel *SortLabel;
	TComboBox *SortComboBox;
	TButton *SortButton;
	TButton *DeleteCarButton;
	TButton *ChangeButton;
	TButton *FindButton;
	TButton *FullCarsListButton;
	TButton *FullClientsListButton;
	TButton *DeleteClientButton;
	TButton *AddButton;
	TEdit *YearEdit;
	TEdit *EngineCapacityEdit;
	TEdit *BrandEdit;
	TEdit *ConditionEdit;
	TComboBox *CarFindComboBox;
	TComboBox *ClientFindComboBox;
	TEdit *SurnameEdit;
	TEdit *NameEdit;
	TEdit *PhoneNumberEdit;
	TEdit *MaxPriceEdit;
	TButton *AppropriateCarsButton;
	TLabel *SurnameLabel;
	TLabel *NameLabel;
	TLabel *PhoneNumberLabel;
	TLabel *MaxPriceLabel;
	TLabel *YearLabel;
	TLabel *BrandLabel;
	TLabel *EngineCapacityLabel;
	TLabel *ConditionLabel;
	TLabel *Label5;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CarStringGridOnSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall ClientStringGridOnSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall FullCarsListButtonClick(TObject *Sender);
	void __fastcall FullClientsListButtonClick(TObject *Sender);
	void __fastcall DeleteCarButtonClick(TObject *Sender);
	void __fastcall ChangeButtonClick(TObject *Sender);
	void __fastcall DeleteClientButtonClick(TObject *Sender);
	void __fastcall SortButtonClick(TObject *Sender);
	void __fastcall FindButtonClick(TObject *Sender);
	void __fastcall AppropriateCarsButtonClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall CloseButtonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
