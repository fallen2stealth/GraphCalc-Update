// GraphOptionsOne.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphOptionsOne.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//CCalculator *Calculator;
bool *ChangedRng;

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsOne property page

IMPLEMENT_DYNCREATE(GraphOptionsOne, CPropertyPage)

GraphOptionsOne::GraphOptionsOne() : CPropertyPage(GraphOptionsOne::IDD)
{
	//{{AFX_DATA_INIT(GraphOptionsOne)
	m_Xscl = _T("");
	m_Xmax = _T("");
	m_Xmin = _T("");
	m_Yscl = _T("");
	m_Ymax = _T("");
	m_Ymin = _T("");
	m_AreaPrec = 3;
	m_LinePrec = 100;
	//}}AFX_DATA_INIT

	m_fDirty = false;

	ChangedRng = new bool[6];

	for(int i(0); i <= 5; ++i)
		ChangedRng[i] = false;

	//Calculator = new CCalculator;
}

GraphOptionsOne::~GraphOptionsOne()
{
	delete ChangedRng;
}

void AFXAPI DDV_Range( CDataExchange* pDX, int nIDC, CString& value, CCalculator *Calculator)
{
	long double answer, answer2;
	bool error(false);
	CString Xscl, Xmax, Xmin, Yscl, Ymax, Ymin, msg;

	pDX->m_pDlgWnd->GetDlgItem(IDC_XINT)->GetWindowText(Xscl);
	pDX->m_pDlgWnd->GetDlgItem(IDC_XMAX)->GetWindowText(Xmax);
	pDX->m_pDlgWnd->GetDlgItem(IDC_XMIN)->GetWindowText(Xmin);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YINT)->GetWindowText(Yscl);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YMAX)->GetWindowText(Ymax);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YMIN)->GetWindowText(Ymin);

	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		switch(nIDC){
		case IDC_XINT:
			if(!ChangedRng[0])
				return;

			ChangedRng[0] = false;

			if(Calculator->Compute("abs(" + Xscl + ")", answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}
			
			if(answer == 0)
				value = "1";
			else
				Calculator->DecimalToString(value, answer);

			break;
		case IDC_XMAX:
			if(!ChangedRng[1])
				return;

			ChangedRng[1] = false;

			if(Calculator->Compute( Xmax, answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}
			if(Calculator->Compute(Xmin, answer2, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}

			if(answer <= answer2)
				answer = answer2 + 5;
			
			Calculator->DecimalToString(value, answer);

			break;
		case IDC_XMIN:
			if(!ChangedRng[2])
				return;

			ChangedRng[2] = false;

			if(Calculator->Compute(Xmin, answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}
			if(Calculator->Compute(Xmax, answer2, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}

			if(answer >= answer2)
				answer = answer2 - 5;
			
			Calculator->DecimalToString(value, answer);

			break;
		case IDC_YINT:
			if(!ChangedRng[3])
				return;

			ChangedRng[3] = false;

			if(Calculator->Compute("abs(" + Yscl + ")", answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}
			
			if(answer == 0)
				value = "1";
			else
				Calculator->DecimalToString(value, answer);

			break;
		case IDC_YMAX:
			if(!ChangedRng[4])
				return;

			ChangedRng[4] = false;

			if(Calculator->Compute(Ymax, answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}
			if(Calculator->Compute(Ymin, answer2, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}

			if(answer <= answer2)
				answer = answer2 + 5;
			
			Calculator->DecimalToString(value, answer);

			break;
		case IDC_YMIN:
			if(!ChangedRng[5])
				return;

			ChangedRng[5] = false;

			if(Calculator->Compute( Ymin, answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}
			if(Calculator->Compute(Ymax, answer2, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
				error = true;
				msg = "Invalid Expression Entered";
				break;
			}

			if(answer >= answer2)
				answer = answer2 - 5;
			
			Calculator->DecimalToString(value, answer);

			break;
		}

		CleanupAnswer(value);

		if(error)
		{
			pDX->m_pDlgWnd->MessageBox(msg);
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
	}	
}

void GraphOptionsOne::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GraphOptionsOne)
	DDX_Text(pDX, IDC_XINT, m_Xscl);
	DDV_Range(pDX, IDC_XINT, m_Xscl, m_Calculator);
	DDX_Text(pDX, IDC_XMAX, m_Xmax);
	DDV_Range(pDX, IDC_XMAX, m_Xmax, m_Calculator);
	DDX_Text(pDX, IDC_XMIN, m_Xmin);
	DDV_Range(pDX, IDC_XMIN, m_Xmin, m_Calculator);
	DDX_Text(pDX, IDC_YINT, m_Yscl);
	DDV_Range(pDX, IDC_YINT, m_Yscl, m_Calculator);
	DDX_Text(pDX, IDC_YMAX, m_Ymax);
	DDV_Range(pDX, IDC_YMAX, m_Ymax, m_Calculator);
	DDX_Text(pDX, IDC_YMIN, m_Ymin);
	DDV_Range(pDX, IDC_YMIN, m_Ymin, m_Calculator);
	DDX_Text(pDX, IDC_AREAPREC, m_AreaPrec);
	DDV_MinMaxInt(pDX, m_AreaPrec, 1, 10);
	DDX_Slider(pDX, IDC_LINE_RESOLUTION, m_LinePrec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GraphOptionsOne, CPropertyPage)
	//{{AFX_MSG_MAP(GraphOptionsOne)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_XINT, OnKillfocusXint)
	ON_EN_KILLFOCUS(IDC_XMAX, OnKillfocusXmax)
	ON_EN_KILLFOCUS(IDC_XMIN, OnKillfocusXmin)
	ON_EN_KILLFOCUS(IDC_YINT, OnKillfocusYint)
	ON_EN_KILLFOCUS(IDC_YMAX, OnKillfocusYmax)
	ON_EN_KILLFOCUS(IDC_YMIN, OnKillfocusYmin)
	ON_EN_CHANGE(IDC_XINT, OnChangeXint)
	ON_EN_CHANGE(IDC_XMAX, OnChangeXmax)
	ON_EN_CHANGE(IDC_XMIN, OnChangeXmin)
	ON_EN_CHANGE(IDC_YINT, OnChangeYint)
	ON_EN_CHANGE(IDC_YMAX, OnChangeYmax)
	ON_EN_CHANGE(IDC_YMIN, OnChangeYmin)
	ON_WM_VSCROLL()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsOne message handlers
/*********************************************************/
// GraphOptionsTwo::OnInitDialog()
// Pre: none
// Post: none
// Return Value: handled by parent function
// Intent: to initialize variables and control items
/*********************************************************/
BOOL GraphOptionsOne::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// Set Spin control
	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_AREAPREC_SPIN);
	pSpin->SetRange(1, 10);
	pSpin->SetPos(m_AreaPrec);

	// Set Resolution Control
	CString str;
	CSliderCtrl *pSlide = (CSliderCtrl*) GetDlgItem(IDC_LINE_RESOLUTION);
	pSlide->SetRange(1,100);

	pSlide->SetPos(m_LinePrec);

	if(m_LinePrec == 100)
		str.Format("Continuous");
	else
		str.Format("%d%% of the pixels computed", m_LinePrec);
	
	SetDlgItemText(IDC_LINE_TRACK, str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************/
// GraphOptionsTwo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
// Pre: none
// Post: controls updated
// Return Value: none
// Intent: to handle the user moving the sliders for the various
//		   settings
/*********************************************************/
void GraphOptionsOne::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar->GetDlgCtrlID() == IDC_LINE_RESOLUTION){
		
		//Control Line Precision
		CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
		CString str;
		m_LinePrec = pSlide->GetPos();
	
		if(m_LinePrec == 100)
			str.Format("Continuous");
		else
			str.Format("%d%% of the pixels computed", m_LinePrec);
	
		SetDlgItemText(IDC_LINE_TRACK, str);

	}

	SetDirty() ;
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*********************************************************/
// GraphOptionsOne::OnKillfocusXint()
// Pre: none
// Post: none
// Return Value: none
// Intent: to evaluate the value in the field
/*********************************************************/
void GraphOptionsOne::OnKillfocusXint() 
{
	CString Val;
	long double answer;

	GetDlgItem(IDC_XINT)->GetWindowText(Val);

	if(m_Calculator->Compute("abs(" + Val + ")", answer, this->m_hWnd) != SUCCESSFULL)
		return;
	
	m_Calculator->DecimalToString(Val, answer);
	CleanupAnswer(Val);

	GetDlgItem(IDC_XINT)->SetWindowText(Val);
}
/*********************************************************/
// GraphOptionsOne::OnKillfocusXmax()
// Pre: none
// Post: none
// Return Value: none
// Intent: to evaluate the value in the field
/*********************************************************/
void GraphOptionsOne::OnKillfocusXmax() 
{
	CString Val;
	long double answer;

	GetDlgItem(IDC_XMAX)->GetWindowText(Val);

	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	m_Calculator->DecimalToString(Val, answer);
	CleanupAnswer(Val);

	if(Val != Val)
		GetDlgItem(IDC_XMAX)->SetWindowText(Val);
}
/*********************************************************/
// GraphOptionsOne::OnKillfocusXmin()
// Pre: none
// Post: none
// Return Value: none
// Intent: to evaluate the value in the field
/*********************************************************/
void GraphOptionsOne::OnKillfocusXmin() 
{
	CString Val, oldVal;
	long double answer;

	GetDlgItem(IDC_XMIN)->GetWindowText(Val);
	oldVal = Val;

	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	m_Calculator->DecimalToString(Val, answer);
	CleanupAnswer(Val);

	if(oldVal != Val)
		GetDlgItem(IDC_XMIN)->SetWindowText(Val);
}
/*********************************************************/
// GraphOptionsOne::OnKillfocusYint()
// Pre: none
// Post: none
// Return Value: none
// Intent: to evaluate the value in the field
/*********************************************************/
void GraphOptionsOne::OnKillfocusYint() 
{
	CString Val, oldVal;
	long double answer;

	GetDlgItem(IDC_YINT)->GetWindowText(Val);
	oldVal = Val;

	if(m_Calculator->Compute("abs(" + Val + ")", answer, this->m_hWnd) != SUCCESSFULL)
		return;

	m_Calculator->DecimalToString(Val, answer);
	CleanupAnswer(Val);

	if(oldVal != Val)
		GetDlgItem(IDC_YINT)->SetWindowText(Val);
}
/*********************************************************/
// GraphOptionsOne::OnKillfocusYmax()
// Pre: none
// Post: none
// Return Value: none
// Intent: to evaluate the value in the field
/*********************************************************/
void GraphOptionsOne::OnKillfocusYmax() 
{
	CString Val, oldVal;
	long double answer;

	GetDlgItem(IDC_YMAX)->GetWindowText(Val);
	oldVal = Val;

	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	m_Calculator->DecimalToString(Val, answer);
	CleanupAnswer(Val);

	if(oldVal != Val)
		GetDlgItem(IDC_YMAX)->SetWindowText(Val);
}
/*********************************************************/
// GraphOptionsOne::OnKillfocusYmin()
// Pre: none
// Post: none
// Return Value: none
// Intent: to evaluate the value in the field
/*********************************************************/
void GraphOptionsOne::OnKillfocusYmin() 
{
	CString Val, oldVal;
	long double answer;

	GetDlgItem(IDC_YMIN)->GetWindowText(Val);
	oldVal = Val;

	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	m_Calculator->DecimalToString(Val, answer);
	CleanupAnswer(Val);

	if(oldVal != Val)
		GetDlgItem(IDC_YMIN)->SetWindowText(Val);
}

void GraphOptionsOne::OnChangeXint()  { ChangedRng[0] = true;  SetDirty() ; }
void GraphOptionsOne::OnChangeXmax()  { ChangedRng[1] = true; SetDirty() ; }
void GraphOptionsOne::OnChangeXmin()  { ChangedRng[2] = true; SetDirty() ; }
void GraphOptionsOne::OnChangeYint()  { ChangedRng[3] = true; SetDirty() ; }
void GraphOptionsOne::OnChangeYmax()  { ChangedRng[4] = true; SetDirty() ; }
void GraphOptionsOne::OnChangeYmin()  { ChangedRng[5] = true; SetDirty() ; }

/*********************************************************/
// GraphOptionsTwo::OnApply()
// Pre: none
// Post: message is sent to CGrphCalcDlg
// Return Value: parent handles this
// Intent: to send notification to parent dlg that the user
//		   has hit th eapply button
/*********************************************************/
BOOL GraphOptionsOne::OnApply() 
{
	if(m_fDirty)
		{
		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
		m_fDirty = false;
		}

	return CPropertyPage::OnApply();
}

void GraphOptionsOne::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

void GraphOptionsOne::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode == SB_ENDSCROLL){
		return;
	}

	if(pScrollBar->GetDlgCtrlID() == IDC_AREAPREC_SPIN){
		UpdateData(true);
		m_AreaPrec = nPos;
		UpdateData(false);
		SetDirty() ;
	}
	
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL GraphOptionsOne::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	LoadHelpFile(HELP_PAGE_2D_RANGE);
	return true;
}
