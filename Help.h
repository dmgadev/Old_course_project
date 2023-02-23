//---------------------------------------------------------------------------

#ifndef HelpH
#define HelpH

//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Buttons.hpp>

//---------------------------------------------------------------------------

class TInfoForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *CBPanel;
	TButton *CloseButton;
	TPanel *AppName;
	TMemo *Memo1;
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall Memo1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);

private:	// User declarations
public:		// User declarations
	__fastcall TInfoForm(TComponent* Owner);
};

//---------------------------------------------------------------------------

extern PACKAGE TInfoForm *InfoForm;

//---------------------------------------------------------------------------

#endif
