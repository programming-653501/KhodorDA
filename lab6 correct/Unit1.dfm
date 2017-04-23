object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 722
  ClientWidth = 1106
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 608
    Top = 527
    Width = 18
    Height = 13
    Caption = 'Key'
  end
  object Label1: TLabel
    Left = 34
    Top = 597
    Width = 28
    Height = 13
    Caption = 'String'
  end
  object Label2: TLabel
    Left = 37
    Top = 645
    Width = 18
    Height = 13
    Caption = 'Key'
  end
  object Label4: TLabel
    Left = 1007
    Top = 29
    Width = 26
    Height = 13
    Caption = 'Stack'
  end
  object TreeView: TTreeView
    Left = 608
    Top = 48
    Width = 265
    Height = 449
    Indent = 19
    ReadOnly = True
    TabOrder = 0
  end
  object StringGrid: TStringGrid
    Left = 32
    Top = 48
    Width = 281
    Height = 449
    ColCount = 2
    FixedCols = 0
    RowCount = 4
    TabOrder = 1
    OnSelectCell = StringGridOnSelectCell
  end
  object AddButton: TButton
    Left = 238
    Top = 520
    Width = 75
    Height = 25
    Caption = 'Create tree'
    TabOrder = 2
    OnClick = AddButtonClick
  end
  object PrintComboBox: TComboBox
    Left = 344
    Top = 522
    Width = 161
    Height = 21
    TabOrder = 3
    OnChange = PrintComboBoxOnChange
  end
  object Memo: TMemo
    Left = 344
    Top = 48
    Width = 225
    Height = 449
    Enabled = False
    Lines.Strings = (
      'Memo')
    ScrollBars = ssVertical
    TabOrder = 4
  end
  object PrintButton: TButton
    Left = 430
    Top = 576
    Width = 75
    Height = 25
    Caption = 'Print'
    Enabled = False
    TabOrder = 5
    OnClick = PrintButtonClick
  end
  object KeyEditFindDelete: TEdit
    Left = 608
    Top = 546
    Width = 121
    Height = 21
    NumbersOnly = True
    TabOrder = 6
  end
  object InfoFindPanel: TPanel
    Left = 752
    Top = 621
    Width = 121
    Height = 25
    TabOrder = 7
  end
  object FindButton: TButton
    Left = 654
    Top = 622
    Width = 75
    Height = 25
    Caption = 'Find'
    Enabled = False
    TabOrder = 8
    OnClick = FindButtonClick
  end
  object DeleteButton: TButton
    Left = 654
    Top = 573
    Width = 75
    Height = 25
    Caption = 'Delete'
    Enabled = False
    TabOrder = 9
    OnClick = DeleteButtonClick
  end
  object BalanceButton: TButton
    Left = 798
    Top = 520
    Width = 75
    Height = 25
    Caption = 'Balance'
    Enabled = False
    TabOrder = 10
    OnClick = BalanceButtonClick
  end
  object CloseButton: TButton
    Left = 926
    Top = 689
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 11
    OnClick = CloseButtonClick
  end
  object MinusButton: TButton
    Left = 32
    Top = 8
    Width = 33
    Height = 25
    Caption = '-'
    TabOrder = 12
    OnClick = MinusButtonClick
  end
  object PlusButton: TButton
    Left = 80
    Top = 8
    Width = 33
    Height = 25
    Caption = '+'
    TabOrder = 13
    OnClick = PlusButtonClick
  end
  object PrintAll: TButton
    Left = 926
    Top = 8
    Width = 75
    Height = 25
    Caption = 'PrintAll'
    TabOrder = 14
    Visible = False
    OnClick = PrintAllClick
  end
  object AddKeyEdit: TEdit
    Left = 32
    Top = 664
    Width = 121
    Height = 21
    NumbersOnly = True
    TabOrder = 15
  end
  object Add1Button: TButton
    Left = 238
    Top = 646
    Width = 75
    Height = 25
    Caption = 'Add'
    Enabled = False
    TabOrder = 16
    OnClick = Add1ButtonClick
  end
  object AddStringEdit: TEdit
    Left = 32
    Top = 616
    Width = 121
    Height = 21
    TabOrder = 17
  end
  object StackMemo: TMemo
    Left = 985
    Top = 48
    Width = 88
    Height = 449
    Enabled = False
    Lines.Strings = (
      'StackMemo')
    TabOrder = 18
  end
  object StackAddEdit: TEdit
    Left = 969
    Top = 522
    Width = 121
    Height = 21
    TabOrder = 19
  end
  object PushButton: TButton
    Left = 998
    Top = 573
    Width = 75
    Height = 25
    Caption = 'Push'
    TabOrder = 20
    OnClick = PushButtonClick
  end
  object PopButton: TButton
    Left = 998
    Top = 614
    Width = 75
    Height = 25
    Caption = 'Pop'
    TabOrder = 21
    OnClick = PopButtonClick
  end
end
