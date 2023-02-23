//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Help.h"
#include "GradeBook.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TInfoForm *InfoForm;

//---------------------------------------------------------------------------

__fastcall TInfoForm::TInfoForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TInfoForm::CloseButtonClick(TObject *Sender)
{
    InfoForm->Free();
}

//---------------------------------------------------------------------------

void __fastcall TInfoForm::Memo1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)

{
    Handled = true;
}

//---------------------------------------------------------------------------

