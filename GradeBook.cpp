//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GradeBook.h"
#include "Functions.h"
#include "Help.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;
using namespace std;

#define MIN_COL_WIDTH 16
#define DEFAULT_ROW_HEIGHT 18
#define DEFAULT_COL_WIDTH 104
#define DEFAULT_FIXED_COL_WIDTH 132
#define WRONG_TYPE  L" В данном поле разрешено вводить только числовые значения от 0 до 5"
#define APPLICATION_NAME L" Журнал успеваемости"
#define ZERO_CELL_CONTENT L"● Студент \\ Предмет ●"
#define SAVE_ERROR L" Произошла ошибка, попробуйте сохранить файл заново."
#define OPEN_ERROR L" Произошла ошибка, попробуйте открыть файл заново."
#define SAVE_SUCCESSFUL L" Таблица успешно сохранена в файл."
#define OPEN_SUCCESSFUL L" Выбранный файл успешно загружен."
#define SAVED_ALREADY L" Таблица уже сохранена под именем: "

//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) //+
{
//	wchar_t zerocolrow[22] = L"● Студент \\ Предмет ●";
//	SearchEdit->Text = zerocolrow;
	search_for_matches = false;
	Language = L"RU";
	ToHidePanel->Hide();
	int sorted_index[2][3] = {-1};  // 2 колонки
	saved = true;

	InfoTable	->Cells[0][0] 	= ZERO_CELL_CONTENT;
	InfoTable->ColWidths[0] = DEFAULT_FIXED_COL_WIDTH;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NewSession()
{
	saved = true;
	SaveDialog1->FileName = L"";
	SaveDialog2->FileName = L"";
    OpenDialog1->FileName = L"";
	ClearTables();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::AddExtension(TSaveDialog *Sender)
{
//	UnicodeString File_Name, Extension;
//	File_Name = Sender->FileName;
//	//SearchEdit->Text = File_Name.Length();
//	if (Sender->Filter == L"*.gbtfile")
//	{
//		if (true)
//		{
//
//			//wstrstr
//		}
//	}
}

//---------------------------------------------------------------------------
int __fastcall TMainForm::SavingProcess(TObject *Sender, bool binary_save)
{
	if (saved == false)
	{
		//SearchEdit->Text = SaveDialog1->FileName;   // если до этого производилось сохранение, то имя будет непустым
		if (!(SaveDialog1->Execute())) // подумать, может ли имя, заданное до этого шага остаться тем же после этого шага // да, если его захотели перезаписать
		{
			return 1;
		}
		//if (SaveDialog1->FileName != NULL)  // нельзя сохранить пустой, поэтому эта строк будет означать нажатие "Отмена"
		//{

		//}
	}
	else
	{
		if (Sender == SaveAs)
		{
			//UnicodeString buffer_name = SaveDialog1->FileName;
			//SaveDialog1->FileName = L"";
			//EditRow->Text = L"true - save as";
			if (!(SaveDialog1->Execute()))
			{
                //SaveDialog1->FileName = buffer_name;
				return 1;
			}
		}
		else
		{
			if (SaveDialog1->FileName != L"")
				StatusBar->Panels->Items[0]->Text = SAVED_ALREADY + SaveDialog1->FileName;
			Timer2->Enabled = true;
			return 1;
        }
	}
	if (SaveDialog1->FilterIndex != 2)  // gbtfile
	{
		UnicodeString name_check = SaveDialog1->FileName;
		if (name_check.SubString(name_check.Length() - 7, 8) != L".gbtfile")
			(name_check) = (name_check)+ L".gbtfile";

		//EditColumn->Text = L"What???";
//		UnicodeString name_check = SaveDialog1->FileName, file_ext = L".gbtfile";
//		EditRow->Text = name_check;
//
//		//if (name_check.SubString(name_check.Length() - 7, 8) != file_ext)

		SaveDialog1->FileName = name_check;
		//SearchEdit->Text = SaveDialog1->FileName;
	}
	if (SaveTable((SaveDialog1->FileName).w_str(), binary_save)) // если функция сохранения вернет 1(код ошибки выделения или другой ошибки)
	{
		Application->NormalizeTopMosts();
		Application->MessageBox(SAVE_ERROR, APPLICATION_NAME, MB_OK | MB_ICONWARNING);
		Application->RestoreTopMosts();
		StatusBar->Panels->Items[0]->Text = SAVE_ERROR;
		Timer2->Enabled = true;
		return 1;
	}
	else    // если она выполнится до конца
	{
		saved = true;
		UnicodeString app_name = APPLICATION_NAME;
		MainForm->Caption = (app_name) + (L" - ") + (SaveDialog1->FileName);
		StatusBar->Panels->Items[0]->Text = SAVE_SUCCESSFUL;
		Timer2->Enabled = true;
	}
	return 0;
}
int __fastcall TMainForm::SaveCheck()
{
	if (saved == false)
	{
		UnicodeString Message = L" Сохранить изменения в файле ", Sign = L"?";
		Message = Message + (SaveDialog1->FileName) + Sign;
		Application->NormalizeTopMosts();
		int answer_id = Application->MessageBox(Message.w_str(), APPLICATION_NAME, MB_YESNOCANCEL | MB_ICONQUESTION);
		Application->RestoreTopMosts();
		switch (answer_id)
		{
			case IDCANCEL:
			{
				return 1;   // need to Abort closing
				//break;
				//return 1;
			}
			case IDNO:
			{
				break;
				//return 1;
			}
			case IDYES:
			{
				//SaveAsClick(SaveAs);
				if (SavingProcess(SaveAs, true))
				//if (!(SaveDialog1->Execute()))
					return 1;
				//break;
			}
		}
	}
	return 0;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ChangeLanguage(UnicodeString Language)   // перевод всех компонентов на разные языки //+
{
	if (Language == L"RU")
	{
		MainForm->StatusBar->Panels->Items[1]->Text = L" RU";
		// добавить компоненты
	}
	if (Language == L"ENG")
	{
		MainForm->StatusBar->Panels->Items[1]->Text = L" ENG";
		// добавить компоненты
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearTables()
{
	TStringGrid *point[3] = {InfoTable, ResultTable, TableWithAverage};
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < point[0]->RowCount; i++) // tabsheet 0
		{
			point[j]->Rows[i]->Clear();
		}
		point[j]->ColCount = 2;
		point[j]->RowCount = 2;
	}
	InfoTable->Cells[0][0] = ZERO_CELL_CONTENT;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ClearResultTables()
{
	TStringGrid *point[2] = {ResultTable, TableWithAverage};
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < point[0]->RowCount; i++) // tabsheet 0
		{
			point[j]->Rows[i]->Clear();
		}
		point[j]->ColCount = 2;
		point[j]->RowCount = 2;
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::TableDoubleClick(TStringGrid *Sender)
{
	TPoint p;
	p = Mouse->CursorPos;
	p = ((TStringGrid*)Sender)->ScreenToClient(p);
	if (GetCursor() == Screen->Cursors[crHSplit])
	{
		TGridCoord gc = ((TStringGrid*)Sender)->MouseCoord(p.X-4,p.Y);
		//int current_col = Col;
		//int current_row = Row;
		int w = DEFAULT_COL_WIDTH; //Canvas->TextWidth(InfoTable->Cells[current_col][current_row]);//CalcGridColWidth((TStringGrid*)Sender, gc.X);
		if (((TStringGrid*)Sender)->ColWidths[gc.X] != w)
		{
			((TStringGrid*)Sender)->ColWidths[gc.X] = w;
		}
		else
		{
			((TStringGrid*)Sender)->ColWidths[gc.X] = MIN_COL_WIDTH;
		}
	}
	else
	{
		TGridCoord gc = ((TStringGrid*)Sender)->MouseCoord(p.X,p.Y);
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenFileClick(TObject *Sender)
{
    // спросить нужно ли сохранение текущего - MessageBox
	if (saved == false)
	{
		if (SavingProcess(SaveAs, true))
		//if (!(SaveDialog1->Execute()))
			Abort();
	}
	if (OpenDialog1->Execute())
	{
		/*
		wchar_t* wchar_t_array_file_name = (wchar_t*) calloc ((OpenDialog1->FileName).Length(), sizeof(wchar_t));
		if (wchar_t_array_file_name)
		{
			wchar_t_array_file_name = (OpenDialog1->FileName).c_str();
			SearchEdit->Text = wchar_t_array_file_name;
			LoadTable(wchar_t_array_file_name);
			free (wchar_t_array_file_name);
			MainForm->Caption = "Журнал успеваемости - " + OpenDialog1->FileName;
			OpenDialog1->FileName = "";
			OpenDialog1->Tag = 1;
		}
		else
		{
			SearchEdit->Text = L"Ошибка выделения памяти.";
		}
		*/
		if (LoadTable((OpenDialog1->FileName).w_str()))
		{
			Application->NormalizeTopMosts();
			Application->MessageBox(OPEN_ERROR, APPLICATION_NAME, MB_OK | MB_ICONWARNING);
			Application->RestoreTopMosts();
			StatusBar->Panels->Items[0]->Text = OPEN_ERROR;
			Timer2->Enabled = true;
			Abort();
		}
		SaveDialog1->FileName = OpenDialog1->FileName;
		UnicodeString app_name = APPLICATION_NAME;
		MainForm->Caption = (app_name) + (L" - ") + (SaveDialog1->FileName);
		StatusBar->Panels->Items[0]->Text = SAVE_SUCCESSFUL;
		Timer2->Enabled = true;
		//OpenDialog1->FileName = NULL;
		//OpenDialog1->Tag = 1;
		InfoTableClick(InfoTable);  // при загрузке будет обображать названия столбца 1 и строки 1
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveClick(TObject *Sender)
{
	// if != "";
    bool binary_save = true;
	if (SaveDialog1->FileName != L"")
	{
		if (SaveTable((SaveDialog1->FileName).w_str(), binary_save)) // если функция сохранения вернет 1(код ошибки выделения или другой ошибки)
		{
			Application->NormalizeTopMosts();
			Application->MessageBox(SAVE_ERROR, APPLICATION_NAME, MB_OK | MB_ICONWARNING);
			Application->RestoreTopMosts();
			StatusBar->Panels->Items[0]->Text = SAVE_ERROR;
			Timer2->Enabled = true;
		}
		else    // если она выполнится до конца
		{
			saved = true;
			UnicodeString app_name = APPLICATION_NAME;
			MainForm->Caption = (app_name) + (L" - ") + (SaveDialog1->FileName);
			StatusBar->Panels->Items[0]->Text = SAVE_SUCCESSFUL;
			Timer2->Enabled = true;
		}
	}
	else
	{
		SavingProcess(Sender, binary_save);
	}
//	if (saved == false)
//	{
//		if (SaveDialog1->FileName != NULL)
//		{
//            SearchEdit->Text = L"false";
//			SaveAsClick(SaveAs);
//		}
//		else
//		{
//			bool binary_save = true;
//			SaveTable((SaveDialog1->FileName).w_str(), binary_save);
//            saved = true;
//        }
//	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveAsClick(TObject *Sender)
{
	bool binary_save = true;
	SavingProcess(Sender, binary_save);
	//ShowMessage("it was aborted");
//	if (Sender == Save)
//	{
//		SearchEdit->Text = L"save";
//	}
//	else
//	{
//		SearchEdit->Text = L"saveas";
//    }
//	if (saved == false)
//	{
//		SaveDialog1->Execute();
//		//UnicodeString file_name = SaveDialog1->FileName;
//		//wchar_t* wchar_t_array_file_name = new (nothrow) wchar_t [file_name.Length()];
//		//wchar_t_array_file_name = file_name.c_str();
//		//EditRow->Text = wchar_t_array_file_name;
//		//wchar_t* wchar_t_array_file_name;
//		//wchar_t_array_file_name = (wchar_t*) calloc ((file_name.Length()+1), sizeof(wchar_t));
//		//wchar_t_array_file_name = file_name.c_str();
//		//SaveTable(wchar_t_array_file_name);
//		//EditColumn->Text = (SaveDialog1->FileName).w_str();
//		if (SaveDialog1->FileName != NULL)
//		{
//			bool binary_save = true;
//			SaveTable((SaveDialog1->FileName).w_str(), binary_save);
//			saved = true;
//		}
		//delete [] wchar_t_array_file_name;
		//free (wchar_t_array_file_name);
		//SaveDialog1->FileName = L"";

		//int wcscmp(const wchar_t *s1, const wchar_t *s2);
	//}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::AddRecordClick(TObject *Sender)  //+
{
	if (Student->Checked == true)
	{
		InfoTable->RowCount++;
	}
	else
	{
		InfoTable->ColCount++;
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::PasteRecordClick(TObject *Sender) //+
{
	TStringGrid *point = InfoTable;
	if (Student->Checked == true)
	{
		int buffer = point->Row;
		point->RowCount++;
		for (int i = 1; i < ((point->RowCount)-buffer); i++)
		{
			point->Rows[point->RowCount-i+1] = point->Rows[point->RowCount-i];
		}
		point->Row = buffer++;
		point->Rows[buffer]->Clear();
	}
	if (Subject->Checked == true)
	{
		int buffer = point->Col;
		point->ColCount++;
		for (int i = 1; i < ((point->ColCount)-buffer); i++)
		{
			point->Cols[point->ColCount-i+1] = point->Cols[point->ColCount-i];
		}
		point->Col = buffer++;
		point->Cols[buffer]->Clear();
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteRecordClick(TObject *Sender) //+
{
	TStringGrid *point = InfoTable;
		if ((Student->Checked == true) && (point->RowCount != 2))
		{
			point->Rows[point->Row]->Clear();
			for (int i = (point->Row); i < (point->RowCount); i++)
			{
				point->Rows[i] = point->Rows[i+1];
			}
			point->RowCount--;
		}
		if ((Subject->Checked == true) && (point->ColCount != 2))
		{
			point->Cols[point->Col]->Clear();
			for (int i = (point->Col); i < (point->ColCount); i++)
			{
				point->Cols[i] = point->Cols[i+1];
			}
			point->ColCount--;

		}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InfoTableClick(TObject *Sender) //+
{
 	EditRow		->Text = InfoTable->Cells[0][InfoTable->Row];
	EditColumn	->Text = InfoTable->Cells[InfoTable->Col][0];
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchButtonClick(TObject *Sender)
{
	search_for_matches = true;
	// malloc, but if colored_cells free
//	InfoTable->Canvas->Brush->Color = clYellow;
//	InfoTable->Canvas->FillRect(Rect(200,200,300,300));
//
//	if (SearchEdit->Text != L"")
//	{
//		for (int i = 0; i < (InfoTable->ColCount); i++)
//		{
//			for (int j = 0; j < (InfoTable->RowCount); j++)
//			{
//				if (SearchEdit->Text == InfoTable->Cells[i][j])
//				{
//                    ;
//				}
//			}
//		}
//	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitOptionClick(TObject *Sender)
{
	if (SaveCheck())    // эта функция возвращает 1, если нужно отменить закрытие
	{
		Abort();
	}
	Application->Terminate();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::LockTableClick(TObject *Sender) //+
{
	if (LockTable->Checked == true)
	{
		LockEditing->Checked = true;
		InfoTable	->Options << goEditing;
		EditRow		->Enabled = true;
		EditColumn	->Enabled = true;
	}
	else
	{
        LockEditing->Checked = false;
		InfoTable	->Options >> goEditing;
		EditRow		->Enabled = false;
		EditColumn	->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::InfoTableKeyPress(TObject *Sender, System::WideChar &Key) // когда срабатывает. узнать. если до != после => FALSE

{
	if (LockTable->Checked == true)
	{
		int rowN, colN;
		colN = InfoTable->Col;
		rowN = InfoTable->Row;
		if (((InfoTable->Cells[colN][rowN].Length()) == 0)||((InfoTable->Cells[colN][rowN].Length() == 1)))
		{
			if ((Key >= '0') && (Key <= '5'))
			{
				InfoTable->Cells[colN][rowN] = Key;
				saved = false;
				//StatusBar->Panels->Items[0]->Text = L"";
			}
			else
			{
				if ((Key != VK_RETURN) && (Key != VK_BACK))
				{
					Key = VK_BACK;
					InfoTable->Cells[colN][rowN] = VK_BACK;
					StatusBar->Panels->Items[0]->Text = WRONG_TYPE;
					Timer2->Enabled = true;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::EditRowChange(TObject *Sender) //+
{
    saved = false;
	InfoTable->Cells[0][InfoTable->Row] = EditRow->Text;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::EditColumnChange(TObject *Sender) //+
{
    saved = false;
	InfoTable->Cells[InfoTable->Col][0] = EditColumn->Text;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InfoTableDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
		if (InfoTable->ColWidths[ACol] < MIN_COL_WIDTH)
		{
			InfoTable->ColWidths[ACol] = MIN_COL_WIDTH;
        }
		//EditRow->Text = Canvas->TextWidth(InfoTable->Cells[1][0]);         // [stolb][strok]
		//InfoTable->Canvas->Brush->Color = clRed;
		/*
		if (InfoTable->Tag != 0)
		{
			InfoTable->Canvas->Brush->Color = clRed;
			InfoTable->Canvas->FillRect(Rect);
		}
		*/
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InfoTableSetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
	saved = false;

/*
int i;
AnsiString buffer = (InfoTable->Cells[ARow][ACol]).c_str();
TryStrToInt(buffer, i);
EditRow->Text = i;
if (TryStrToInt(buffer, i))
{
	InfoTable->Cells[ARow][ACol] = i;
}
else
{
	InfoTable->Cells[ARow][ACol] = L"";
	EditRow->SetFocus();
	InfoTable->SetFocus();
	StatusBar->Panels->Items[0]->Text = WRONG_TYPE;
	Timer2->Enabled = true;
}
*/

			/*
			float number;
				if (!(TryStrToFloat((InfoTable->Cells[ARow][ACol]), number)))
				{
					InfoTable->Cells[ARow][ACol] = L"";
					StatusBar->Panels->Items[0]->Text = WRONG_TYPE;
				}
				else
				{
					int number_to_int = (int *)(InfoTable->Cells[ARow][ACol]);
					InfoTable->Cells[ARow][ACol] = number_to_int;
				}
			*/
			//changed = true;
/*		if ((InfoTable->Col != 0) && (InfoTable->Row != 0))
    	{
    		if (!(0<= (InfoTable->Cells[ARow][ACol]) <= 5))
    		{
    			InfoTable->Cells[ARow][ACol] = L"";
			}
		}
*/
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ShowResultButtonClick(TObject *Sender) //+
{
    DeleteRecord->Enabled = false;
	PasteRecord->Enabled = false;
	AddRecord->Enabled = false;
	TabSheet1			->Enabled			= true;
	TabSheet1			->Visible			= true;
	TabSheet1			->TabVisible		= true;
	ResultTable			->Visible			= true;
	ResultTable			->Enabled 			= true;
	PageControl1		->ActivePage 		= TabSheet1;
	TabSheet2			->Enabled			= true;
	TabSheet2			->Visible			= true;
	TabSheet2			->TabVisible		= true;
	TableWithAverage	->Visible			= true;
	TableWithAverage	->Enabled 			= true;
	//EditButtonsPanel->Hide();
	AdditionalButtonsPanel->Hide();
	ToHidePanel	->Show();
	//ToHidePanel	->Visible 			= true;
	//ToHidePanel	->Enabled 			= true;
	//AdditionalButtonsPanel->Enabled = false;
	//AdditionalButtonsPanel->Visible = false;
	//ShowResultButton->Enabled 	= false;
	//ShowResultButton->Visible 	= false;
	//LockTable	->Enabled 		= false;
	//LockTable	->Visible 		= false;
	//EditRow		->Enabled 		= false;
	//EditColumn	->Enabled 		= false;
	//EditRow		->Visible 		= false;
	//EditColumn	->Visible 		= false;
	//SaveResults	->Enabled 		= true;
	//SaveResults	->Visible		= true;
	//one();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::OpenOptionClick(TObject *Sender)
{
	OpenFileClick(OpenFile);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveOptionClick(TObject *Sender)
{
	SaveClick(Save);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveAsOptionClick(TObject *Sender)
{
	SaveAsClick(SaveAs);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SortAllClick(TObject *Sender)
{
    ShowResultButtonClick(ShowResultButton);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InfoTableDblClick(TObject *Sender) //+ // ??? изменить текущее на ширину текста
{
	TStringGrid *point = (TStringGrid*) Sender;
	TableDoubleClick(point);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::LockEditingClick(TObject *Sender) //+
{
	if (LockTable->Checked == true)
	{
		LockTable->Checked = false;
	}
	else
	{
		LockTable->Checked = true;
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender) //+
{
	StatusBar->Panels->Items[2]->Text = Now();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ResetSelectionClick(TObject *Sender)
{
	search_for_matches = false;
	if (!colored_cells)
	{
		for (int i = 0; i < 1; i++)
		{
			;
		}
	}

//	SearchEdit->Text = wcscmp(EditRow->Text.w_str(), EditColumn->Text.w_str());
//    SearchEdit->Text = SaveDialog1->FileName;
	//float f;
	//MainForm->SearchEdit->Text = (TryStrToFloat(InfoTable->Cells[1][1], f)? L"true":L"false");
	//MainForm->SearchEdit->Text = StrToInt(InfoTable->Cells[1][1]);
	//if (changed == false)
	//{
		; // очистить таблицу
	//}
	/*
	wchar_t* first, *second;
	first = InfoTable->Cells[1][0].w_str();
	second= InfoTable->Cells[2][0].w_str();
	SearchEdit->Text = wcscmp(first, second);
	*/
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender) //+
{
	StatusBar->Panels->Items[0]->Width = (MainForm->Width - 175);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer2Timer(TObject *Sender) //+
{
	StatusBar->Panels->Items[0]->Text = L"";
    Timer2->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveResultsClick(TObject *Sender)    // ???????????????????????????????????????/ check this
{
	// сделать зависимость от актив пэджа + ввести переменные(или еще 1 SaveDialog),
		//отвечающие за сохранение каждой из таблиц с результатом
//	SaveDialog2->Execute();
//	if (SaveDialog2->FileName != L"")
//	{
//		bool binary_save = false;
//		SaveTable((SaveDialog1->FileName).w_str(), binary_save);
//		SaveDialog2->FileName = L"";
//		SaveDialog2->Tag = 1;
//
//		//int wcscmp(const wchar_t *s1, const wchar_t *s2);
//	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::PageControl1Change(TObject *Sender) //+
{
	if (PageControl1->ActivePage == TabSheet0)
	{
		ToHidePanel	->Hide();
		AdditionalButtonsPanel->Show();
		DeleteRecord->Enabled = true;
		PasteRecord->Enabled = true;
		AddRecord->Enabled = true;
	}
	else
	{
		DeleteRecord->Enabled = false;
		PasteRecord->Enabled = false;
		AddRecord->Enabled = false;
		AdditionalButtonsPanel->Hide();
		ToHidePanel	->Show();
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutClick(TObject *Sender)
{
	Application->CreateForm(__classid(TInfoForm), &InfoForm); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::InfoTableMouseActivate(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)

{
	TStringGrid *point = (TStringGrid*)Sender;
	int Column, Row;
	UnicodeString Horizontal_Sort = L"vert";    // по умолчанию при попадании в ячейку [0][0] сортировка по вертикали
	InfoTable->MouseToCell(X, Y, Column, Row);
	if (!(Column || Row))
	{
		double k = DEFAULT_ROW_HEIGHT*1.0/(point->ColWidths[0]);
		//SearchEdit->Text = k;
		if ((X*k) > Y)
		{
			Horizontal_Sort = L"horz";    // то курсор попал ниже диагонали |\|
		}
		//EditRow->Text = X;
		//EditColumn->Text = Y;
	}
	MyBubbleSort(Column, Row, point, Horizontal_Sort);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::CreateOptionClick(TObject *Sender)
{
	if (SaveCheck())
	{
        Abort();
    }
	NewSession();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RUClick(TObject *Sender)
{
	if (Language != L"RU")
	{
		Language = L"RU";
		ChangeLanguage(Language); // +
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ENGClick(TObject *Sender)
{
    if (Language != L"ENG")
	{
		Language = L"ENG";
		ChangeLanguage(Language); // +
	}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::EditRowContextPopup(TObject *Sender, TPoint &MousePos,
          bool &Handled)
{
	Handled = true; // +
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::EditColumnContextPopup(TObject *Sender, TPoint &MousePos,
		  bool &Handled)
{
	Handled = true; // +
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchEditContextPopup(TObject *Sender, TPoint &MousePos,
		  bool &Handled)
{
	Handled = true; // +
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	ExitOptionClick(ExitOption);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Add0Click(TObject *Sender)
{
	AddRecordClick(AddRecord); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Add1Click(TObject *Sender)
{
	AddRecordClick(AddRecord); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Paste0Click(TObject *Sender)
{
	PasteRecordClick(PasteRecord); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Paste1Click(TObject *Sender)
{
	PasteRecordClick(PasteRecord); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Delete0Click(TObject *Sender)
{
	DeleteRecordClick(DeleteRecord); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Delete1Click(TObject *Sender)
{
	DeleteRecordClick(DeleteRecord); //+
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SearchEditKeyPress(TObject *Sender, System::WideChar &Key) //+

{
	if (Key == VK_RETURN)
	{
        SearchButtonClick(SearchButton);
	}
}

//---------------------------------------------------------------------------



