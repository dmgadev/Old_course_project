//---------------------------------------------------------------------------

#ifndef GradeBookH
#define GradeBookH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Data.DB.hpp>
#include <Vcl.Ribbon.hpp>
#include <Vcl.RibbonLunaStyleActnCtrls.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Tabs.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *MainButtons;
	TButton *Save;
	TButton *SaveAs;
	TPanel *EditButtonsPanel;
	TButton *AddRecord;
	TButton *PasteRecord;
	TStatusBar *StatusBar;
	TPanel *AdditionalButtonsPanel;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TCheckBox *LockTable;
	TButton *SearchButton;
	TLabel *LockedCells;
	TEdit *EditRow;
	TEdit *EditColumn;
	TPageControl *PageControl1;
	TTabSheet *TabSheet0;
	TTabSheet *TabSheet1;
	TMainMenu *MainMenu1;
	TMenuItem *Menu;
	TMenuItem *OpenOption;
	TMenuItem *Editing;
	TMenuItem *DataSotring;
	TMenuItem *Help;
	TMenuItem *SaveOption;
	TMenuItem *SaveAsOption;
	TMenuItem *ExitOption;
	TMenuItem *CreateOption;
	TMenuItem *UnDo;
	TMenuItem *ReDo;
	TMenuItem *About;
	TMenuItem *LockEditing;
	TMenuItem *Add0;
	TMenuItem *Paste0;
	TMenuItem *Delete0;
	TMenuItem *Splitter5;
	TMenuItem *SortAll;
	TEdit *SearchEdit;
	TButton *ShowResultButton;
	TStringGrid *InfoTable;
	TStringGrid *ResultTable;
	TMenuItem *Row;
	TMenuItem *Col;
	TMenuItem *Splitter3;
	TMenuItem *Splitter1;
	TMenuItem *Splitter2;
	TButton *UndoButton;
	TButton *RepeatButton;
	TButton *DeleteRecord;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Delete1;
	TMenuItem *Add1;
	TMenuItem *Paste1;
	TMenuItem *N3;
	TMenuItem *CancelSelection;
	TTimer *Timer1;
	TTimer *Timer2;
	TButton *ResetSelection;
	TRadioButton *Student;
	TRadioButton *Subject;
	TButton *OpenFile;
	TSaveDialog *SaveDialog2;
	TMenuItem *N5;
	TMenuItem *RU1;
	TMenuItem *RU;
	TMenuItem *ENG;
	TMenuItem *N4;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TTabSheet *TabSheet2;
	TPanel *ToHidePanel;
	TButton *SaveResults;
	TStringGrid *TableWithAverage;
	void __fastcall OpenFileClick(TObject *Sender);
	void __fastcall SaveAsClick(TObject *Sender);
	void __fastcall AddRecordClick(TObject *Sender);
	void __fastcall InfoTableClick(TObject *Sender);
	void __fastcall SearchButtonClick(TObject *Sender);
	void __fastcall ExitOptionClick(TObject *Sender);
	void __fastcall LockTableClick(TObject *Sender);
	void __fastcall InfoTableKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EditRowChange(TObject *Sender);
	void __fastcall EditColumnChange(TObject *Sender);
	void __fastcall InfoTableDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall SaveClick(TObject *Sender);
	void __fastcall InfoTableSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall ShowResultButtonClick(TObject *Sender);
	void __fastcall OpenOptionClick(TObject *Sender);
	void __fastcall SaveOptionClick(TObject *Sender);
	void __fastcall SaveAsOptionClick(TObject *Sender);
	void __fastcall SortAllClick(TObject *Sender);
	void __fastcall PasteRecordClick(TObject *Sender);
	void __fastcall InfoTableDblClick(TObject *Sender);
	void __fastcall LockEditingClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall DeleteRecordClick(TObject *Sender);
	void __fastcall ResetSelectionClick(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall SaveResultsClick(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall AboutClick(TObject *Sender);
	void __fastcall InfoTableMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y, int HitTest, TMouseActivate &MouseActivate);
	void __fastcall CreateOptionClick(TObject *Sender);
	void __fastcall RUClick(TObject *Sender);
	void __fastcall ENGClick(TObject *Sender);
	void __fastcall EditRowContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall EditColumnContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall SearchEditContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Add0Click(TObject *Sender);
	void __fastcall Add1Click(TObject *Sender);
	void __fastcall Paste0Click(TObject *Sender);
	void __fastcall Paste1Click(TObject *Sender);
	void __fastcall Delete0Click(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall SearchEditKeyPress(TObject *Sender, System::WideChar &Key);


private:	// User declarations
	bool saved;	// при внесении изменений в таблицу устанавливается в false
	int sorted_index[2][3];	// в массиве 3 столбца - (строка - столбец - направление сортировки). 0 - прямое, 1 - обратное
	UnicodeString OpenedFileName;
	UnicodeString **massiv;
	int **colored_cells; bool search_for_matches;
	UnicodeString Language;
	int max_fixed_first_col_width;
	int __fastcall SaveCheck();							// проверка (сохранен ли файл) с помощью MessageBox
	void __fastcall NewSession();							// новый сеанс работы
	void __fastcall ChangeLanguage(UnicodeString Language);	// смена языка rus/eng
	void __fastcall ClearTables();							// очистить все таблицы на форме, чтобы подготовиться к новому сеансу
	void __fastcall ClearResultTables();					// очистить только 2 и 3 таблицы
	void __fastcall TableDoubleClick(TStringGrid *Sender);	// корректировка ширины стоблца любой из таблиц на форме
	int __fastcall SavingProcess(TObject *Sender, bool binary_save);
	void __fastcall AddExtension(TSaveDialog *Sender);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
