// GraphOptionsZero.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphOptionsZero.h"
#include "GraphOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCalculator *g_Calculator;
extern bool IsEquation(CString equation, char variable);
bool *ChangedEq;

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsZero property page

IMPLEMENT_DYNCREATE(GraphOptionsZero, CPropertyPage)

GraphOptionsZero::GraphOptionsZero() : CPropertyPage(GraphOptionsZero::IDD)
{
	//{{AFX_DATA_INIT(GraphOptionsZero)
	m_Y1 = _T("");
	m_Y10 = _T("");
	m_Y2 = _T("");
	m_Y3 = _T("");
	m_Y4 = _T("");
	m_Y5 = _T("");
	m_Y6 = _T("");
	m_Y7 = _T("");
	m_Y8 = _T("");
	m_Y9 = _T("");
	m_Yon1 = FALSE;
	m_Yon10 = FALSE;
	m_Yon2 = FALSE;
	m_Yon3 = FALSE;
	m_Yon4 = FALSE;
	m_Yon5 = FALSE;
	m_Yon6 = FALSE;
	m_Yon7 = FALSE;
	m_Yon8 = FALSE;
	m_Yon9 = FALSE;
	//}}AFX_DATA_INIT

	m_ColorButton1.SetSelectionMode(CP_MODE_BK);
	m_ColorButton2.SetSelectionMode(CP_MODE_BK);
	m_ColorButton3.SetSelectionMode(CP_MODE_BK);
	m_ColorButton4.SetSelectionMode(CP_MODE_BK);
	m_ColorButton5.SetSelectionMode(CP_MODE_BK);
	m_ColorButton6.SetSelectionMode(CP_MODE_BK);
	m_ColorButton7.SetSelectionMode(CP_MODE_BK);
	m_ColorButton8.SetSelectionMode(CP_MODE_BK);
	m_ColorButton9.SetSelectionMode(CP_MODE_BK);
	m_ColorButton10.SetSelectionMode(CP_MODE_BK);

	m_ColorButton1.SetBkColour(RGB(128,0,0));
	m_ColorButton2.SetBkColour(RGB(0,128,0));
	m_ColorButton3.SetBkColour(RGB(0,0,128));
	m_ColorButton4.SetBkColour(RGB(128,128,0));
	m_ColorButton5.SetBkColour(RGB(0,128,128));
	m_ColorButton6.SetBkColour(RGB(128,0,128));
	m_ColorButton7.SetBkColour(RGB(64,0,0));
	m_ColorButton8.SetBkColour(RGB(0,64,0));
	m_ColorButton9.SetBkColour(RGB(0,0,64));
	m_ColorButton10.SetBkColour(RGB(64,64,0));

	m_fDirty = false;

	ChangedEq = new bool[10];

	for(int i(0); i <= 9; ++i)
		ChangedEq[i] = false;
}

GraphOptionsZero::~GraphOptionsZero()
{
	delete ChangedEq;
}

void AFXAPI DDV_Equation( CDataExchange* pDX, int nIDC, CString& value, int mode, int enabled)
{
	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		int eq(-1);

		switch(nIDC){
		case IDC_EQY1: eq = 0; break;
		case IDC_EQY2: eq = 1; break;
		case IDC_EQY3: eq = 2; break;
		case IDC_EQY4: eq = 3; break;
		case IDC_EQY5: eq = 4; break;
		case IDC_EQY6: eq = 5; break;
		case IDC_EQY7: eq = 6; break;
		case IDC_EQY8: eq = 7; break;
		case IDC_EQY9: eq = 8; break;
		case IDC_EQY10: eq = 9; break;
		default: return;
		}

		if(!ChangedEq[eq])
			return;

		CString Val;				
		pDX->m_pDlgWnd->GetDlgItem(nIDC)->GetWindowText(Val);

		if(Val.IsEmpty()){
			value = Val;
			ChangedEq[eq] = false;
			return;
		}

		if(g_Calculator->IsValid(Val, pDX->m_pDlgWnd->m_hWnd)){
			value = Val;

			if(enabled)
			{
				switch(mode)
				{
				case POLAR:
					{
						if(IsEquation(Val, 'x'))
							{
							pDX->m_pDlgWnd->MessageBox("The variable 'x' can not be used in polar mode.");
							goto Error;
							}
						break;
					}
				case EUCLIDEAN:
					{
						if(IsEquation(Val, 't'))
							{
							pDX->m_pDlgWnd->MessageBox("The variable 't' can not be used in euclidean mode.");
							goto Error;
							}
						break;
					}
				}
			}
			
			ChangedEq[eq] = false;
			return;
		}
		Error:
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
	}	
}

void GraphOptionsZero::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GraphOptionsZero)
	DDX_Control(pDX, IDC_COLOR_Y1, m_ColorButton1);
	DDX_Control(pDX, IDC_COLOR_Y2, m_ColorButton2);
	DDX_Control(pDX, IDC_COLOR_Y3, m_ColorButton3);
	DDX_Control(pDX, IDC_COLOR_Y4, m_ColorButton4);
	DDX_Control(pDX, IDC_COLOR_Y5, m_ColorButton5);
	DDX_Control(pDX, IDC_COLOR_Y6, m_ColorButton6);
	DDX_Control(pDX, IDC_COLOR_Y7, m_ColorButton7);
	DDX_Control(pDX, IDC_COLOR_Y8, m_ColorButton8);
	DDX_Control(pDX, IDC_COLOR_Y9, m_ColorButton9);
	DDX_Control(pDX, IDC_COLOR_Y10, m_ColorButton10);
	DDX_Control(pDX, IDC_EQY1, m_ctrlY1);
	DDX_Control(pDX, IDC_EQY10, m_ctrlY10);
	DDX_Control(pDX, IDC_EQY2, m_ctrlY2);
	DDX_Control(pDX, IDC_EQY3, m_ctrlY3);
	DDX_Control(pDX, IDC_EQY4, m_ctrlY4);
	DDX_Control(pDX, IDC_EQY5, m_ctrlY5);
	DDX_Control(pDX, IDC_EQY6, m_ctrlY6);
	DDX_Control(pDX, IDC_EQY7, m_ctrlY7);
	DDX_Control(pDX, IDC_EQY8, m_ctrlY8);
	DDX_Control(pDX, IDC_EQY9, m_ctrlY9);
	DDX_Check(pDX, IDC_ON_Y1, m_Yon1);
	DDX_Check(pDX, IDC_ON_Y10, m_Yon10);
	DDX_Check(pDX, IDC_ON_Y2, m_Yon2);
	DDX_Check(pDX, IDC_ON_Y3, m_Yon3);
	DDX_Check(pDX, IDC_ON_Y4, m_Yon4);
	DDX_Check(pDX, IDC_ON_Y5, m_Yon5);
	DDX_Check(pDX, IDC_ON_Y6, m_Yon6);
	DDX_Check(pDX, IDC_ON_Y7, m_Yon7);
	DDX_Check(pDX, IDC_ON_Y8, m_Yon8);
	DDX_Check(pDX, IDC_ON_Y9, m_Yon9);
	DDX_Text(pDX, IDC_EQY1, m_Y1);
	DDV_Equation(pDX, IDC_EQY1, m_Y1, m_Mode, m_Yon1);
	DDX_Text(pDX, IDC_EQY10, m_Y10);
	DDV_Equation(pDX, IDC_EQY10, m_Y10, m_Mode, m_Yon10);
	DDX_Text(pDX, IDC_EQY2, m_Y2);
	DDV_Equation(pDX, IDC_EQY2, m_Y2, m_Mode, m_Yon2);
	DDX_Text(pDX, IDC_EQY3, m_Y3);
	DDV_Equation(pDX, IDC_EQY3, m_Y3, m_Mode, m_Yon3);
	DDX_Text(pDX, IDC_EQY4, m_Y4);
	DDV_Equation(pDX, IDC_EQY4, m_Y4, m_Mode, m_Yon4);
	DDX_Text(pDX, IDC_EQY5, m_Y5);
	DDV_Equation(pDX, IDC_EQY5, m_Y5, m_Mode, m_Yon5);
	DDX_Text(pDX, IDC_EQY6, m_Y6);
	DDV_Equation(pDX, IDC_EQY6, m_Y6, m_Mode, m_Yon6);
	DDX_Text(pDX, IDC_EQY7, m_Y7);
	DDV_Equation(pDX, IDC_EQY7, m_Y7, m_Mode, m_Yon7);
	DDX_Text(pDX, IDC_EQY8, m_Y8);
	DDV_Equation(pDX, IDC_EQY8, m_Y8, m_Mode, m_Yon8);
	DDX_Text(pDX, IDC_EQY9, m_Y9);
	DDV_Equation(pDX, IDC_EQY9, m_Y9, m_Mode, m_Yon9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GraphOptionsZero, CPropertyPage)
	//{{AFX_MSG_MAP(GraphOptionsZero)
	ON_BN_CLICKED(IDC_COLOR_Y1, OnColorY1)
	ON_BN_CLICKED(IDC_COLOR_Y2, OnColorY2)
	ON_BN_CLICKED(IDC_COLOR_Y3, OnColorY3)
	ON_BN_CLICKED(IDC_COLOR_Y4, OnColorY4)
	ON_BN_CLICKED(IDC_COLOR_Y5, OnColorY5)
	ON_BN_CLICKED(IDC_COLOR_Y6, OnColorY6)
	ON_BN_CLICKED(IDC_COLOR_Y7, OnColorY7)
	ON_BN_CLICKED(IDC_COLOR_Y8, OnColorY8)
	ON_BN_CLICKED(IDC_COLOR_Y9, OnColorY9)
	ON_BN_CLICKED(IDC_COLOR_Y10, OnColorY10)
	ON_EN_CHANGE(IDC_EQY1, OnChangeEqy1)
	ON_EN_CHANGE(IDC_EQY2, OnChangeEqy2)
	ON_EN_CHANGE(IDC_EQY3, OnChangeEqy3)
	ON_EN_CHANGE(IDC_EQY4, OnChangeEqy4)
	ON_EN_CHANGE(IDC_EQY5, OnChangeEqy5)
	ON_EN_CHANGE(IDC_EQY6, OnChangeEqy6)
	ON_EN_CHANGE(IDC_EQY7, OnChangeEqy7)
	ON_EN_CHANGE(IDC_EQY8, OnChangeEqy8)
	ON_EN_CHANGE(IDC_EQY9, OnChangeEqy9)
	ON_EN_CHANGE(IDC_EQY10, OnChangeEqy10)
	ON_BN_CLICKED(IDC_ON_Y1, OnOnY1)
	ON_BN_CLICKED(IDC_ON_Y2, OnOnY2)
	ON_BN_CLICKED(IDC_ON_Y3, OnOnY3)
	ON_BN_CLICKED(IDC_ON_Y4, OnOnY4)
	ON_BN_CLICKED(IDC_ON_Y5, OnOnY5)
	ON_BN_CLICKED(IDC_ON_Y6, OnOnY6)
	ON_BN_CLICKED(IDC_ON_Y7, OnOnY7)
	ON_BN_CLICKED(IDC_ON_Y8, OnOnY8)
	ON_BN_CLICKED(IDC_ON_Y9, OnOnY9)
	ON_BN_CLICKED(IDC_ON_Y10, OnOnY10)
	ON_EN_KILLFOCUS(IDC_EQY1, OnKillfocusEq1)
	ON_EN_KILLFOCUS(IDC_EQY2, OnKillfocusEq2)
	ON_EN_KILLFOCUS(IDC_EQY3, OnKillfocusEq3)
	ON_EN_KILLFOCUS(IDC_EQY4, OnKillfocusEq4)
	ON_EN_KILLFOCUS(IDC_EQY5, OnKillfocusEq5)
	ON_EN_KILLFOCUS(IDC_EQY6, OnKillfocusEq6)
	ON_EN_KILLFOCUS(IDC_EQY7, OnKillfocusEq7)
	ON_EN_KILLFOCUS(IDC_EQY8, OnKillfocusEq8)
	ON_EN_KILLFOCUS(IDC_EQY9, OnKillfocusEq9)
	ON_EN_KILLFOCUS(IDC_EQY10, OnKillfocusEq10)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_ON_Y1, IDC_ON_Y10, EnableDisableFn)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsZero message handlers

/*********************************************************/
// GraphOptionsZero::EnableDisableFn(UINT nID)
// Pre: none
// Post: controls updated
// Return Value: none
// Intent: to update the controls based on the current
//		   variables
/*********************************************************/
void GraphOptionsZero::EnableDisableFn(UINT nID)
{
	int nButton = nID - IDC_ON_Y1;
	ASSERT( nButton >= 0 && nButton < 10 );
	
	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y1)){
		m_ColorButton1.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY1.EnableWindow();
		ChangedEq[0] = true;
	}
	else{
		m_ColorButton1.ModifyStyle(0, WS_DISABLED);
		m_ctrlY1.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y2)){
		m_ColorButton2.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY2.EnableWindow();
		ChangedEq[1] = true;
	}
	else{
		m_ColorButton2.ModifyStyle(0, WS_DISABLED);
		m_ctrlY2.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y3)){
		m_ColorButton3.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY3.EnableWindow();
		ChangedEq[2] = true;
	}
	else{
		m_ColorButton3.ModifyStyle(0, WS_DISABLED);
		m_ctrlY3.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y4)){
		m_ColorButton4.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY4.EnableWindow();
		ChangedEq[3] = true;
	}
	else{
		m_ColorButton4.ModifyStyle(0, WS_DISABLED);
		m_ctrlY4.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y5)){
		m_ColorButton5.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY5.EnableWindow();
		ChangedEq[4] = true;
	}
	else{
		m_ColorButton5.ModifyStyle(0, WS_DISABLED);
		m_ctrlY5.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y6)){
		m_ColorButton6.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY6.EnableWindow();
		ChangedEq[5] = true;
	}
	else{
		m_ColorButton6.ModifyStyle(0, WS_DISABLED);
		m_ctrlY6.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y7)){
		m_ColorButton7.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY7.EnableWindow();
		ChangedEq[6] = true;
	}
	else{
		m_ColorButton7.ModifyStyle(0, WS_DISABLED);
		m_ctrlY7.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y8)){
		m_ColorButton8.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY8.EnableWindow();
		ChangedEq[7] = true;
	}
	else{
		m_ColorButton8.ModifyStyle(0, WS_DISABLED);
		m_ctrlY8.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y9)){
		m_ColorButton9.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY9.EnableWindow();
		ChangedEq[8] = true;
	}
	else{
		m_ColorButton9.ModifyStyle(0, WS_DISABLED);
		m_ctrlY9.EnableWindow(false);
	}

	if(BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y10)){
		m_ColorButton10.ModifyStyle(WS_DISABLED, 0);
		m_ctrlY10.EnableWindow();
		ChangedEq[9] = true;
	}
	else{
		m_ColorButton10.ModifyStyle(0, WS_DISABLED);
		m_ctrlY10.EnableWindow(false);
	}

	m_ColorButton1.Invalidate();
	m_ColorButton2.Invalidate();
	m_ColorButton3.Invalidate();
	m_ColorButton4.Invalidate();
	m_ColorButton5.Invalidate();
	m_ColorButton6.Invalidate();
	m_ColorButton7.Invalidate();
	m_ColorButton8.Invalidate();
	m_ColorButton9.Invalidate();
	m_ColorButton10.Invalidate();
}

/*********************************************************/
// GraphOptionsZero::InitOptions()
// Pre: none
// Post: none
// Return Value: none
// Intent: initialize the controls
/*********************************************************/
void GraphOptionsZero::InitOptions()
{
	EnableDisableFn(0);
}

/*********************************************************/
// GraphOptionsZero::OnInitDialog() 
// Pre: none
// Post: none
// Return Value: true
// Intent: initialize the controls
/*********************************************************/
BOOL GraphOptionsZero::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	EnableDisableFn(IDC_ON_Y10);

	m_ColorButton1.SetTrackSelection(true);
	m_ColorButton2.SetTrackSelection(true);
	m_ColorButton3.SetTrackSelection(true);
	m_ColorButton4.SetTrackSelection(true);
	m_ColorButton5.SetTrackSelection(true);
	m_ColorButton6.SetTrackSelection(true);
	m_ColorButton7.SetTrackSelection(true);
	m_ColorButton8.SetTrackSelection(true);
	m_ColorButton9.SetTrackSelection(true);
	m_ColorButton10.SetTrackSelection(true);

	UpdateEqType();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************/
// GraphOptionsZero::OnKillActive()
// Pre: none
// Post: none
// Return Value: parent handles this
// Intent: to notify me that the tab is losing focus
//		   all ewuations are made sure to be valid or
//		   we reutrn false and stay on this tab
/*********************************************************/
BOOL GraphOptionsZero::OnKillActive() 
{
	OnKillfocusEq1();
	OnKillfocusEq2();
	OnKillfocusEq3();
	OnKillfocusEq4();
	OnKillfocusEq5();
	OnKillfocusEq6();
	OnKillfocusEq7();
	OnKillfocusEq8();
	OnKillfocusEq9();
	OnKillfocusEq10();

	return CPropertyPage::OnKillActive();
}

/*********************************************************/
// GraphOptionsZero::OnKillfocusEq1()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq1() 
{
	CString Val;
	GetDlgItem(IDC_EQY1)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y1, 0);

	EnableDisableFn(IDC_ON_Y1);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq2()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq2() 
{
	CString Val;
	GetDlgItem(IDC_EQY2)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y2, 0);

	EnableDisableFn(IDC_ON_Y2);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq3()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq3() 
{
	CString Val;
	GetDlgItem(IDC_EQY3)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y3, 0);

	EnableDisableFn(IDC_ON_Y3);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq4()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq4() 
{
	CString Val;
	GetDlgItem(IDC_EQY4)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y4, 0);

	EnableDisableFn(IDC_ON_Y4);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq5()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq5() 
{
	CString Val;
	GetDlgItem(IDC_EQY5)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y5, 0);

	EnableDisableFn(IDC_ON_Y5);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq6()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq6() 
{
	CString Val;
	GetDlgItem(IDC_EQY6)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y6, 0);

	EnableDisableFn(IDC_ON_Y6);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq7()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq7() 
{
	CString Val;
	GetDlgItem(IDC_EQY7)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y7, 0);

	EnableDisableFn(IDC_ON_Y7);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq8()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq8() 
{
	CString Val;
	GetDlgItem(IDC_EQY8)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y8, 0);

	EnableDisableFn(IDC_ON_Y8);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq9()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq9() 
{
	CString Val;
	GetDlgItem(IDC_EQY9)->GetWindowText(Val);

	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y9, 0);

	EnableDisableFn(IDC_ON_Y9);
}
/*********************************************************/
// GraphOptionsZero::OnKillfocusEq10()
// Pre: none
// Post: none
// Return Value: none
// Intent: validates the equation or you cna't leave field
/*********************************************************/
void GraphOptionsZero::OnKillfocusEq10() 
{
	CString Val;
	GetDlgItem(IDC_EQY10)->GetWindowText(Val);
	if(Val.IsEmpty())
		CheckDlgButton(IDC_ON_Y10, 0);
	EnableDisableFn(IDC_ON_Y10);
}

void GraphOptionsZero::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

void GraphOptionsZero::OnColorY1() { SetDirty() ; m_ColorButton1.OnClicked();}
void GraphOptionsZero::OnColorY2() { SetDirty() ; m_ColorButton2.OnClicked();}
void GraphOptionsZero::OnColorY3() { SetDirty() ; m_ColorButton3.OnClicked();}
void GraphOptionsZero::OnColorY4() { SetDirty() ; m_ColorButton4.OnClicked();}
void GraphOptionsZero::OnColorY5() { SetDirty() ; m_ColorButton5.OnClicked();}
void GraphOptionsZero::OnColorY6() { SetDirty() ; m_ColorButton6.OnClicked();}
void GraphOptionsZero::OnColorY7() { SetDirty() ; m_ColorButton7.OnClicked();}
void GraphOptionsZero::OnColorY8() { SetDirty() ; m_ColorButton8.OnClicked();}
void GraphOptionsZero::OnColorY9() { SetDirty() ; m_ColorButton9.OnClicked();}
void GraphOptionsZero::OnColorY10() { SetDirty() ; m_ColorButton10.OnClicked();}

void GraphOptionsZero::OnChangeEqy1() { ChangedEq[0] = true; SetDirty() ;}
void GraphOptionsZero::OnChangeEqy2() { ChangedEq[1] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy3() { ChangedEq[2] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy4() { ChangedEq[3] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy5() { ChangedEq[4] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy6() { ChangedEq[5] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy7() { ChangedEq[6] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy8() { ChangedEq[7] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy9() { ChangedEq[8] = true;  SetDirty() ;}
void GraphOptionsZero::OnChangeEqy10() { ChangedEq[9] = true;  SetDirty() ;}

void GraphOptionsZero::OnOnY1() { SetDirty() ; EnableDisableFn(IDC_ON_Y1);}
void GraphOptionsZero::OnOnY2() { SetDirty() ; EnableDisableFn(IDC_ON_Y2);}
void GraphOptionsZero::OnOnY3() { SetDirty() ; EnableDisableFn(IDC_ON_Y3);}
void GraphOptionsZero::OnOnY4() { SetDirty() ; EnableDisableFn(IDC_ON_Y4);}
void GraphOptionsZero::OnOnY5() { SetDirty() ; EnableDisableFn(IDC_ON_Y5);}
void GraphOptionsZero::OnOnY6() { SetDirty() ; EnableDisableFn(IDC_ON_Y6);}
void GraphOptionsZero::OnOnY7() { SetDirty() ; EnableDisableFn(IDC_ON_Y7);}
void GraphOptionsZero::OnOnY8() { SetDirty() ; EnableDisableFn(IDC_ON_Y8);}
void GraphOptionsZero::OnOnY9() { SetDirty() ; EnableDisableFn(IDC_ON_Y9);}
void GraphOptionsZero::OnOnY10() { SetDirty() ; EnableDisableFn(IDC_ON_Y10);}

bool GraphOptionsZero::IsFunctionEnabled(int eq)
{
	switch(eq)
	{
	case 0: return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y1));
	case 1: return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y2));
	case 2: return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y3));
	case 3:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y4));
	case 4:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y5));
	case 5:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y6));
	case 6:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y7));
	case 7:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y8));
	case 8:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y9));
	case 9:	return (BST_CHECKED == IsDlgButtonChecked(IDC_ON_Y10));
	}
	return false;	
}

/*********************************************************/
// GraphOptionsTwo::OnApply()
// Pre: none
// Post: message is sent to CGrphCalcDlg
// Return Value: parent handles this
// Intent: to send notification to parent dlg that the user
//		   has hit th eapply button
/*********************************************************/
BOOL GraphOptionsZero::OnApply() 
{
	if(m_fDirty)
		{
		for(int i(0); i <= 9; ++i){
			if(ChangedEq[i])
				return false;
		}

		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
		m_fDirty = false;
		}
	
	return CPropertyPage::OnApply();
}

BOOL GraphOptionsZero::OnSetActive() 
{
	UpdateEqType();
	return CPropertyPage::OnSetActive();
}
void GraphOptionsZero::UpdateEqType()
{
	switch(m_Mode){
	case 0:
		{
			GetDlgItem(IDC_ON_Y1)->SetWindowText("y1");
			GetDlgItem(IDC_ON_Y2)->SetWindowText("y2");
			GetDlgItem(IDC_ON_Y3)->SetWindowText("y3");
			GetDlgItem(IDC_ON_Y4)->SetWindowText("y4");
			GetDlgItem(IDC_ON_Y5)->SetWindowText("y5");
			GetDlgItem(IDC_ON_Y6)->SetWindowText("y6");
			GetDlgItem(IDC_ON_Y7)->SetWindowText("y7");
			GetDlgItem(IDC_ON_Y8)->SetWindowText("y8");
			GetDlgItem(IDC_ON_Y9)->SetWindowText("y9");
			GetDlgItem(IDC_ON_Y10)->SetWindowText("y10");
			break;
		}
	case 1:
		{
			GetDlgItem(IDC_ON_Y1)->SetWindowText("r1");
			GetDlgItem(IDC_ON_Y2)->SetWindowText("r2");
			GetDlgItem(IDC_ON_Y3)->SetWindowText("r3");
			GetDlgItem(IDC_ON_Y4)->SetWindowText("r4");
			GetDlgItem(IDC_ON_Y5)->SetWindowText("r5");
			GetDlgItem(IDC_ON_Y6)->SetWindowText("r6");
			GetDlgItem(IDC_ON_Y7)->SetWindowText("r7");
			GetDlgItem(IDC_ON_Y8)->SetWindowText("r8");
			GetDlgItem(IDC_ON_Y9)->SetWindowText("r9");
			GetDlgItem(IDC_ON_Y10)->SetWindowText("r10");
			break;
		}
	}
}

BOOL GraphOptionsZero::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	LoadHelpFile(HELP_PAGE_2D_EUCLIDEANVSPOLAREQUATIONS);
	return true;
	//return CPropertyPage::OnHelpInfo(pHelpInfo);
}
