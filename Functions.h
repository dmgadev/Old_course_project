//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH

//---------------------------------------------------------------------------

#include <fstream>
#include <string.h>
#include "GradeBook.h"

//---------------------------------------------------------------------------

int SaveTable(wchar_t* file_name, bool mode);		// сохранение в файл
int LoadTable(wchar_t* file_name);  				// загрузка из файла

//---------------------------------------------------------------------------

void SearchInTable(wchar_t* request_name);
void Otlichniki(void);

//---------------------------------------------------------------------------

void MyBubbleSort	(int Column, int Row, TStringGrid *pntr, UnicodeString sort_type);	// сортировка таблицы
void MyReverseSort	(int Column, int Row, TStringGrid *pntr, UnicodeString sort_type);	// обратная сортировка таблицы

//---------------------------------------------------------------------------

//void one(void);
//void two(void);

#endif
