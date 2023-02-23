//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH

//---------------------------------------------------------------------------

#include <fstream>
#include <string.h>
#include "GradeBook.h"

//---------------------------------------------------------------------------

int SaveTable(wchar_t* file_name, bool mode);		// ���������� � ����
int LoadTable(wchar_t* file_name);  				// �������� �� �����

//---------------------------------------------------------------------------

void SearchInTable(wchar_t* request_name);
void Otlichniki(void);

//---------------------------------------------------------------------------

void MyBubbleSort	(int Column, int Row, TStringGrid *pntr, UnicodeString sort_type);	// ���������� �������
void MyReverseSort	(int Column, int Row, TStringGrid *pntr, UnicodeString sort_type);	// �������� ���������� �������

//---------------------------------------------------------------------------

//void one(void);
//void two(void);

#endif
