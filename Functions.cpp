//---------------------------------------------------------------------------

#pragma hdrstop

#include "Functions.h"
#include "GradeBook.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define Set_File_Sign L"GradeBookApplication|.gbtfile"

//---------------------------------------------------------------------------

int SaveTable(wchar_t* file_name, bool mode)
{
    // returt for testing
	//return 1;  // если функция прервана (возникла ошибка выделения памяти/что-то другое)
	fstream F;
	if (mode)
	{
		F.open(file_name, ios::out | ios::binary);
		if (!F)
		{
			return 1;
		}
		F.write ((char *) Set_File_Sign, 29*sizeof(wchar_t));

		int row = MainForm->InfoTable->RowCount,
			col = MainForm->InfoTable->ColCount;

		F.write ((char *)&col, sizeof(int));
		F.write ((char *)&row, sizeof(int));

		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
				{
					int length = MainForm->InfoTable->Cells[i][j].Length();
					F.write ((char *) &length, sizeof(int));
					if (length != 0)
					{
						F.write ((char *) (MainForm->InfoTable->Cells[i][j].w_str()),
							 length*sizeof(wchar_t));
					}
				}
		}
	}
	else
	{
		F.open(file_name, ios::out);
        if (!F)
		{
			return 1;
		}
        // запись таблицы результатов
        //
	}
	F.close();
	return 0;
}

//---------------------------------------------------------------------------

int LoadTable(wchar_t* file_name)
{
	fstream F;
	F.open(file_name, ios::in | ios::binary);
	if (!F)
	{
		;
	}
	wchar_t File_Sign[30];
	F.read ((char*) File_Sign, 29*sizeof(wchar_t));	//////
	//MainForm->EditRow->Text = File_Sign;
	if (File_Sign == Set_File_Sign)
	{
		;//MainForm->EditColumn->Text = L"wow, it works!";
	}
	int k, m;
	F.read ((char *) &k, sizeof(int));
	F.read ((char *) &m, sizeof(int));
	MainForm->InfoTable->ColCount = k;
	MainForm->InfoTable->RowCount = m;
	int length;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < m; j++)
		{
			F.read ((char *) &length, sizeof(int));
			if (length != 0)
			{
				wchar_t* buffer = (wchar_t*) calloc ((length+1), sizeof(wchar_t));
				if (buffer == NULL)
				{
					return 1;
				}
				F.read ((char *) buffer, length*sizeof(wchar_t));
				MainForm->InfoTable->Cells[i][j] = buffer;
				free(buffer);
                buffer = NULL;
			}
		}
	}
	F.close();
	return 0;
}

//---------------------------------------------------------------------------

void MyBubbleSort(int Column, int Row, TStringGrid *pntr, UnicodeString sort_type)   // pointer
{
	int MovesCount;
	if ((Row == 0)&&(Column == 0))
	{
		if (sort_type == L"horz") // means "true"  = horizontal
		{
			pntr->ColCount++;
			do
			{
				MovesCount = 0;
				for(int i = 1; i < (pntr->ColCount-2); i++)
				{
					if ((wcscmpi(pntr->Cells[i][Row].w_str(),
							pntr->Cells[i+1][Row].w_str()) < 0))
					{
						MovesCount++;
						pntr->Cols[pntr->ColCount] = pntr->Cols[i];
						pntr->Cols[i] = pntr->Cols[i+1];
						pntr->Cols[i+1] = pntr->Cols[pntr->ColCount];
					}
				}
			} while (MovesCount != 0);
            int i;
			for (i = 1; i < (pntr->ColCount); i++)
			{
				if (pntr->Cells[i][Row] == L"")
				{
					break;
				}
			}
			int j = 1;
			i--;
			//int k = i-j;
			//while (k > 0)
			while ((i-j) > 0)
			{
				//MainForm->SearchEdit->Text = k;
				pntr->Cols[pntr->ColCount] = pntr->Cols[i];
				pntr->Cols[i] = pntr->Cols[j];
				pntr->Cols[j] = pntr->Cols[pntr->ColCount];
				j++;
				i--;
				//k = i-j;
			}
			pntr->Cols[pntr->ColCount]->Clear();
			//
			pntr->ColCount--;
		}
		else
		{
			pntr->RowCount++;
			do
			{
				MovesCount = 0;
				for(int i = 1; i < (pntr->RowCount-2); i++)
				{
					if ((wcscmpi(pntr->Cells[Column][i].w_str(),
							pntr->Cells[Column][i+1].w_str()) < 0))
					{
						MovesCount++;
						pntr->Rows[pntr->RowCount] = pntr->Rows[i];
						pntr->Rows[i] = pntr->Rows[i+1];
						pntr->Rows[i+1] = pntr->Rows[pntr->RowCount];
					}
				}
			} while (MovesCount != 0);
			int i;
			for (i = 1; i < (pntr->RowCount); i++)
			{
				if (pntr->Cells[Column][i] == L"")
				{
					break;
				}
			}
			int j = 1;
			i--;
			//int k = i-j;
			//while (k > 0)
			while ((i-j) > 0)
			{
				//MainForm->SearchEdit->Text = k;
				pntr->Rows[pntr->RowCount] = pntr->Rows[i];
				pntr->Rows[i] = pntr->Rows[j];
				pntr->Rows[j] = pntr->Rows[pntr->RowCount];
				j++;
				i--;
				//k = i-j;
			}
			pntr->Rows[pntr->RowCount]->Clear();
			pntr->RowCount--;
		}
	}
	if ((Row == 0) && (Column != 0))
	{
		pntr->RowCount++;
		do
		{
			MovesCount = 0;
			for(int i = 1; i < (pntr->RowCount-2); i++)
			{
				if (wcscmpi(pntr->Cells[Column][i].w_str(),
						pntr->Cells[Column][i+1].w_str()) < 0)
				{
					MovesCount++;
					pntr->Rows[pntr->RowCount] = pntr->Rows[i];
					pntr->Rows[i] = pntr->Rows[i+1];
					pntr->Rows[i+1] = pntr->Rows[pntr->RowCount];
				}
			}
		} while (MovesCount != 0);
		pntr->Rows[pntr->RowCount]->Clear();
		pntr->RowCount--;
	}
	if ((Column == 0) && (Row != 0))
	{
		pntr->ColCount++;
		do
		{
			MovesCount = 0;
			for (int i = 1; i < (pntr->ColCount-2); i++)
			{
				if (wcscmpi(pntr->Cells[i][Row].w_str(),
						pntr->Cells[i+1][Row].w_str()) < 0)
				{
					MovesCount++;
					pntr->Cols[pntr->ColCount] = pntr->Cols[i];
					pntr->Cols[i] = pntr->Cols[i+1];
					pntr->Cols[i+1] = pntr->Cols[pntr->ColCount];
				}
			}
		} while (MovesCount != 0);
		pntr->Cols[pntr->ColCount]->Clear();
		pntr->ColCount--;
	}
}

//---------------------------------------------------------------------------

void MyReverseSort(int Column, int Row, TStringGrid *pntr, UnicodeString sort_type)
{

}
//void one(void)
//{
//	fstream F;
//	F.open("G:\\123\\testing_of_saves.txt", ios::out);
//	if (F)
//	{
//		MainForm->SearchEdit->Text = "ok";
//	}
//	UnicodeString asd = L"lol";
//	wchar_t *mass;
//	mass = (wchar_t*) calloc (3, sizeof(wchar_t));
//	mass = asd.c_str();
//	F.write ((char *) mass, (3*sizeof(wchar_t)));
//	F.close();
//}
//void two(void)
//{
//	fstream F;
//	F.open("G:\\123\\testing_of_saves.txt", ios::in);
//	if (F)
//	{
//		//MainForm->SearchEdit->Text = "ok - two";
//	}
//	//UnicodeString asd = L"lol";
//	wchar_t *mass;
//	mass = (wchar_t*) calloc (3, sizeof(wchar_t));
//	//mass = asd.c_str();
//	F.read ((char *) mass, (3*sizeof(wchar_t)));
//	MainForm->EditRow->Text = "allright!";
//	MainForm->SearchEdit->Text = mass;
//	F.close();
//}


