// GraphOptionsPolar.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphOptionsPolar.h"
#include "CCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool *ChangedPolarRng;
//extern CCalculator *Calculator;

void AFXAPI DDV_StringToDecimal( CDataExchange* pDX, int nIDC, CString& value, int changed_index, 
								long double min, long double max, CCalculator *Calculator)
{
	long double answer;
	bool error(false);
	CString fieldS, msg;

	pDX->m_pDlgWnd->GetDlgItem(nIDC)->GetWindowText(fieldS);

	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		if(!ChangedPolarRng[changed_index])
			return;
		
		ChangedPolarRng[changed_index] = false;
		
		if(Calculator->Compute(fieldS, answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
			error = true;
			msg = "Invalid Expression Entered";
		}
		
		if(!error){
			if(answer < min || answer > max){
				error = true;
				msg.Format("Value must be between %f and %f", min, max);
			}
			else{
				value.Format("%.15f", answer);
				if(value != "0" && value.Find(".") != -1)
					value.TrimRight("0");
				value.TrimRight(".");
			}
		}
		
		if(error)
		{
			pDX->m_pDlgWnd->MessageBox(msg);
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
	}	
}

void AFXAPI DDV_ViewRange( CDataExchange* pDX, int nIDC, CString& value, CCalculator *Calculator)
{
	long double answer, answer2;
	bool error(false);
	CString Xmax, Xmin, Ymax, Ymin, msg;

	pDX->m_pDlgWnd->GetDlgItem(IDC_XMAX)->GetWindowText(Xmax);
	pDX->m_pDlgWnd->GetDlgItem(IDC_XMIN)->GetWindowText(Xmin);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YMAX)->GetWindowText(Ymax);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YMIN)->GetWindowText(Ymin);

	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		switch(nIDC){
		case IDC_XMAX:
			if(!ChangedPolarRng[6])
				return;

			ChangedPolarRng[6] = false;

			if(Calculator->Compute(Xmax, answer, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
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
			
			value.Format("%.15f", answer);

			break;
		case IDC_XMIN:
			if(!ChangedPolarRng[5])
				return;

			ChangedPolarRng[5] = false;

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
			
			value.Format("%.15f", answer);

			break;
		case IDC_YMAX:
			if(!ChangedPolarRng[8])
				return;

			ChangedPolarRng[8] = false;

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
			
			value.Format("%.15f", answer);

			break;
		case IDC_YMIN:
			if(!ChangedPolarRng[7])
				return;

			ChangedPolarRng[7] = false;

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
			
			value.Format("%.15f", answer);

			break;
		}
		
		if(value != "0" && value.Find(".") != -1)
			value.TrimRight("0");

		value.TrimRight(".");

		if(error)
		{
			pDX->m_pDlgWnd->MessageBox(msg);
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
// CGraphOptionsPolar property page

IMPLEMENT_DYNCREATE(CGraphOptionsPolar, CPropertyPage)

CGraphOptionsPolar::CGraphOptionsPolar() : CPropertyPage(CGraphOptionsPolar::IDD)
{
	//{{AFX_DATA_INIT(CGraphOptionsPolar)
	m_GridAngle = _T(".5");
	m_GridSpacing = _T("3");
	m_ThetaMax = _T("6.28318530717959");
	m_ThetaMin = _T("0");
	m_ThetaStep = _T("0.1");
	m_Xmax = _T("10");
	m_Xmin = _T("-10");
	m_Ymax = _T("10");
	m_Ymin = _T("-10");
	//}}AFX_DATA_INIT

	m_fDirty = false;

	ChangedPolarRng = new bool[9];

	for(int i(0); i <= 8; ++i)
		ChangedPolarRng[i] = false;
}

CGraphOptionsPolar::~CGraphOptionsPolar()
{
	delete ChangedPolarRng;
}

void CGraphOptionsPolar::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphOptionsPolar)
	DDX_Text(pDX, IDC_GRIDANGLE, m_GridAngle);

	DDV_StringToDecimal(pDX, IDC_GRIDANGLE, m_GridAngle, 3, 0.0001, MAX_POALR_GRID_ANGLE_DEGREES, m_Calculator);

	DDX_Text(pDX, IDC_GRIDSPACING, m_GridSpacing);
	DDV_StringToDecimal(pDX, IDC_GRIDSPACING, m_GridSpacing, 4, 0.0001, 1000000000, m_Calculator);
	DDX_Text(pDX, IDC_THETAMAX, m_ThetaMax);
	DDX_Text(pDX, IDC_THETAMIN, m_ThetaMin);
	DDX_Text(pDX, IDC_THETASTEP, m_ThetaStep);
	DDV_StringToDecimal(pDX, IDC_THETASTEP, m_ThetaStep, 2, 0.0000001, 10000, m_Calculator);
	DDX_Text(pDX, IDC_XMAX, m_Xmax);
	DDV_ViewRange(pDX, IDC_XMAX, m_Xmax, m_Calculator);
	DDX_Text(pDX, IDC_XMIN, m_Xmin);
	DDV_ViewRange(pDX, IDC_XMIN, m_Xmin, m_Calculator);
	DDX_Text(pDX, IDC_YMAX, m_Ymax);
	DDV_ViewRange(pDX, IDC_YMAX, m_Ymax, m_Calculator);
	DDX_Text(pDX, IDC_YMIN, m_Ymin);
	DDV_ViewRange(pDX, IDC_YMIN, m_Ymin, m_Calculator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphOptionsPolar, CPropertyPage)
	//{{AFX_MSG_MAP(CGraphOptionsPolar)
	ON_EN_KILLFOCUS(IDC_YMIN, OnKillfocusYmin)
	ON_EN_KILLFOCUS(IDC_YMAX, OnKillfocusYmax)
	ON_EN_KILLFOCUS(IDC_XMIN, OnKillfocusXmin)
	ON_EN_KILLFOCUS(IDC_XMAX, OnKillfocusXmax)
	ON_EN_KILLFOCUS(IDC_THETAMIN, OnKillfocusThetamin)
	ON_EN_KILLFOCUS(IDC_THETAMAX, OnKillfocusThetamax)
	ON_EN_KILLFOCUS(IDC_THETASTEP, OnKillfocusThetastep)
	ON_EN_CHANGE(IDC_YMIN, OnChangeYmin)
	ON_EN_CHANGE(IDC_YMAX, OnChangeYmax)
	ON_EN_CHANGE(IDC_XMIN, OnChangeXmin)
	ON_EN_CHANGE(IDC_XMAX, OnChangeXmax)
	ON_EN_CHANGE(IDC_THETASTEP, OnChangeThetastep)
	ON_EN_CHANGE(IDC_THETAMIN, OnChangeThetamin)
	ON_EN_CHANGE(IDC_THETAMAX, OnChangeThetamax)
	ON_EN_KILLFOCUS(IDC_GRIDANGLE, OnKillfocusGridangle)
	ON_EN_CHANGE(IDC_GRIDANGLE, OnChangeGridangle)
	ON_EN_CHANGE(IDC_GRIDSPACING, OnChangeGridspacing)
	ON_EN_KILLFOCUS(IDC_GRIDSPACING, OnKillfocusGridspacing)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphOptionsPolar message handlers

void CGraphOptionsPolar::UpdateValue(UINT field)
{
	CString Val, oldVal;
	long double answer;
	GetDlgItem(field)->GetWindowText(Val);
	oldVal = Val;
	
	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)	return;
	m_Calculator->DecimalToString(Val, answer);
	if(Val != "0" && Val.Find(".") != -1)
		Val.TrimRight("0");
	Val.TrimRight(".");

	if(oldVal != Val)
		GetDlgItem(field)->SetWindowText(Val);
}

void CGraphOptionsPolar::OnKillfocusYmin() { UpdateValue(IDC_YMIN); }
void CGraphOptionsPolar::OnKillfocusYmax() { UpdateValue(IDC_YMAX); }
void CGraphOptionsPolar::OnKillfocusXmin() { UpdateValue(IDC_XMIN); }
void CGraphOptionsPolar::OnKillfocusXmax() { UpdateValue(IDC_XMAX); }
void CGraphOptionsPolar::OnKillfocusThetamin() { UpdateValue(IDC_THETAMIN); }
void CGraphOptionsPolar::OnKillfocusThetamax() { UpdateValue(IDC_THETAMAX); }
void CGraphOptionsPolar::OnKillfocusThetastep() { UpdateValue(IDC_THETASTEP); }
void CGraphOptionsPolar::OnKillfocusGridangle() { UpdateValue(IDC_GRIDANGLE); }
void CGraphOptionsPolar::OnKillfocusGridspacing() { UpdateValue(IDC_GRIDSPACING); }

void CGraphOptionsPolar::OnChangeYmin()   { ChangedPolarRng[7] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeYmax()   { ChangedPolarRng[8] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeXmin()   { ChangedPolarRng[5] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeXmax()   { ChangedPolarRng[6] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeThetastep()   { ChangedPolarRng[2] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeThetamin()   { ChangedPolarRng[0] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeThetamax()   { ChangedPolarRng[1] = true; SetDirty() ; }
void CGraphOptionsPolar::OnChangeGridangle()   { ChangedPolarRng[3] = true; SetDirty() ; } 
void CGraphOptionsPolar::OnChangeGridspacing()   { ChangedPolarRng[4] = true; SetDirty() ; }

void CGraphOptionsPolar::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

BOOL CGraphOptionsPolar::OnApply() 
{
	if(m_fDirty)
		{
		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
		m_fDirty = false;
		}
	
	return CPropertyPage::OnApply();
}

BOOL CGraphOptionsPolar::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	LoadHelpFile(HELP_PAGE_2D_THETARANGE);
	return true;
}
