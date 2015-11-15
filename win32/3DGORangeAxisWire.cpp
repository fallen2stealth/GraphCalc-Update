// 3DGORangeAxisWire.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGORangeAxisWire.h"
#include "CCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CCalculator *Calculator;
bool *ChangedRAW;

void AFXAPI DDV_3DRange( CDataExchange* pDX, int nIDC, CString& value, CCalculator *Calculator )
{
	long double xmin, xmax, ymin, ymax;
	bool error(false);
	CString Xmax, Xmin,  Ymax, Ymin, msg;

	pDX->m_pDlgWnd->GetDlgItem(IDC_XMAX)->GetWindowText(Xmax);
	pDX->m_pDlgWnd->GetDlgItem(IDC_XMIN)->GetWindowText(Xmin);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YMAX)->GetWindowText(Ymax);
	pDX->m_pDlgWnd->GetDlgItem(IDC_YMIN)->GetWindowText(Ymin);
	
	// from dialog to class ?
	if( pDX->m_bSaveAndValidate)
	{
		switch(nIDC){
			case IDC_XMIN:{ if(ChangedRAW[0]){ ChangedRAW[0] = false; break;} else return;	}
			case IDC_XMAX:{ if(ChangedRAW[1]){ ChangedRAW[1] = false; break;} else return;	}
			case IDC_YMIN:{ if(ChangedRAW[2]){ ChangedRAW[2] = false; break;} else return;	}
			case IDC_YMAX:{ if(ChangedRAW[3]){ ChangedRAW[3] = false; break;} else return;	}
		}

		if(Calculator->Compute(Xmin, xmin, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
			error = true;
			msg = "Invalid Expression Entered";
		}
		if(Calculator->Compute(Xmax, xmax, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
			error = true;
			msg = "Invalid Expression Entered";
		}		
		if(Calculator->Compute(Ymax, ymax, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
			error = true;
			msg = "Invalid Expression Entered";
		}
		if(Calculator->Compute(Ymin, ymin, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
			error = true;
			msg = "Invalid Expression Entered";
		}


		if(!error){
			switch(nIDC){
			case IDC_XMAX:
				if(xmax <= xmin) xmax = xmin + 5;			
				value.Format("%f", xmax);
				break;
			case IDC_XMIN:
				if(xmin >= xmax) xmin = xmax - 5;			
				value.Format("%f", xmin);			
				break;
			case IDC_YMAX:			
				if(ymax <= ymin) ymax = ymin + 5;			
				value.Format("%f", ymax);			
				break;
			case IDC_YMIN:			
				if(ymin >= ymax)  ymin = ymax - 5;			
				value.Format("%f", ymin);
				break;
			}

			CleanupAnswer(value);
		}
		else
		{
			pDX->m_pDlgWnd->MessageBox(msg);
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
	}	
}

/////////////////////////////////////////////////////////////////////////////
// C3DGORangeWire property page
IMPLEMENT_DYNCREATE(C3DGORangeWire, CPropertyPage)

C3DGORangeWire::C3DGORangeWire() : CPropertyPage(C3DGORangeWire::IDD)
{
	//{{AFX_DATA_INIT(C3DGORangeWire)
	m_WireWidth = 1;
	m_WireInterval = 1;
	m_Xmax = _T("10");
	m_Xmin = _T("-10");
	m_Ymax = _T("10");
	m_Ymin = _T("-10");
	m_YIntervals = 50;
	m_XIntervals = 50;
	//}}AFX_DATA_INIT
	
	m_BGcolor.SetSelectionMode(CP_MODE_BK);
	m_BGcolor.SetColour(RGB(0,0,0));

	ChangedRAW = new bool[4];

	for(int i(0); i <= 3; ++i)
		ChangedRAW[i] = false;	
}

C3DGORangeWire::~C3DGORangeWire()
{
	delete ChangedRAW;
}

void C3DGORangeWire::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGORangeWire)
	DDX_Text(pDX, IDC_WIRE_WIDTH, m_WireWidth);
	DDV_MinMaxUInt(pDX, m_WireWidth, 1, 20);
	DDX_Text(pDX, IDC_WIRE_RES, m_WireInterval);
	DDV_MinMaxUInt(pDX, m_WireInterval, 1, m_max_interval);
	DDX_Text(pDX, IDC_XMAX, m_Xmax);
	DDV_3DRange(pDX, IDC_XMAX, m_Xmax, m_Calculator);
	DDX_Text(pDX, IDC_XMIN, m_Xmin);
	DDV_3DRange(pDX, IDC_XMIN, m_Xmin, m_Calculator);
	DDX_Text(pDX, IDC_YMAX, m_Ymax);
	DDV_3DRange(pDX, IDC_YMAX, m_Ymax, m_Calculator);
	DDX_Text(pDX, IDC_YMIN, m_Ymin);
	DDV_3DRange(pDX, IDC_YMIN, m_Ymin, m_Calculator);
	DDX_Text(pDX, IDC_Y_INTERVAL, m_YIntervals);
	DDV_MinMaxUInt(pDX, m_YIntervals, 1, 1000);
	DDX_Text(pDX, IDC_X_INTERVAL, m_XIntervals);
	DDV_MinMaxUInt(pDX, m_XIntervals, 1, 1000);
	DDX_Control(pDX, IDC_BG_COLOR, m_BGcolor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGORangeWire, CPropertyPage)
	//{{AFX_MSG_MAP(C3DGORangeWire)
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_XMIN, OnKillfocusXmin)
	ON_EN_KILLFOCUS(IDC_XMAX, OnKillfocusXmax)
	ON_EN_KILLFOCUS(IDC_YMIN, OnKillfocusYmin)
	ON_EN_KILLFOCUS(IDC_YMAX, OnKillfocusYmax)
	ON_EN_CHANGE(IDC_WIRE_WIDTH, OnChangeWireWidth)
	ON_EN_CHANGE(IDC_WIRE_RES, OnChangeWireInterval)
	ON_EN_CHANGE(IDC_X_INTERVAL, OnChangeXInterval)
	ON_EN_CHANGE(IDC_Y_INTERVAL, OnChangeYInterval)
	ON_EN_CHANGE(IDC_XMIN, OnChangeXmin)
	ON_EN_CHANGE(IDC_XMAX, OnChangeXmax)
	ON_EN_CHANGE(IDC_YMIN, OnChangeYmin)
	ON_EN_CHANGE(IDC_YMAX, OnChangeYmax)
	ON_BN_CLICKED(IDC_BG_COLOR, OnBGColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGORangeWire message handlers

BOOL C3DGORangeWire::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CSpinButtonCtrl *pXint = (CSpinButtonCtrl*) GetDlgItem(IDC_X_INTERVAL_SPIN);
	pXint->SetRange(1, 10000);
	pXint->SetPos(m_XIntervals);	

	CSpinButtonCtrl *pYint = (CSpinButtonCtrl*) GetDlgItem(IDC_Y_INTERVAL_SPIN);
	pYint->SetRange(1, 10000);
	pYint->SetPos(m_YIntervals);	

	CSpinButtonCtrl *pWW = (CSpinButtonCtrl*) GetDlgItem(IDC_WIRE_WIDTH_SPIN);
	pWW->SetRange(1, 20);
	pWW->SetPos(m_WireWidth);	

	CSpinButtonCtrl *pWI = (CSpinButtonCtrl*) GetDlgItem(IDC_WIRE_SPACE_SPIN);
	if(m_XIntervals > m_YIntervals){
		m_max_interval = m_XIntervals;
		pWI->SetRange(1, m_XIntervals);
	}
	else{
		m_max_interval = m_YIntervals;
		pWI->SetRange(1, m_YIntervals);
	}
	pWI->SetPos(m_WireInterval);
	
	UpdateGraphMode();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DGORangeWire::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode == SB_ENDSCROLL){
		return;
	}
	
	switch(pScrollBar->GetDlgCtrlID()){
	case IDC_X_INTERVAL_SPIN:
		{
			SetDlgItemInt(IDC_X_INTERVAL, nPos);
			SetModified(true);
			break;
		}
	case IDC_Y_INTERVAL_SPIN:
		{
			SetDlgItemInt(IDC_Y_INTERVAL, nPos);
			SetModified(true);
			break;
		}
	case IDC_WIRE_WIDTH_SPIN:
		{
			SetDlgItemInt(IDC_WIRE_WIDTH, nPos);
			SetModified(true);
			break;
		}
	case IDC_WIRE_SPACE_SPIN:
		{
			SetDlgItemInt(IDC_WIRE_RES, nPos);
			SetModified(true);
			break;
		}
	}
	
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}


void C3DGORangeWire::OnChangeXInterval() 
{ 
	CSpinButtonCtrl *pXint = (CSpinButtonCtrl*) GetDlgItem(IDC_X_INTERVAL_SPIN);
	m_XIntervals = GetDlgItemInt(IDC_X_INTERVAL);
	pXint->SetPos(m_XIntervals);
	UpdateWireIntervalRange();
	SetModified(true);
}

void C3DGORangeWire::OnChangeYInterval() 
{
	CSpinButtonCtrl *pYint = (CSpinButtonCtrl*) GetDlgItem(IDC_Y_INTERVAL_SPIN);
	m_YIntervals = GetDlgItemInt(IDC_Y_INTERVAL);
	pYint->SetPos(m_YIntervals);
	UpdateWireIntervalRange();
	SetModified(true);
}

void C3DGORangeWire::OnChangeWireWidth() 
{
	CSpinButtonCtrl *pWW = (CSpinButtonCtrl*) GetDlgItem(IDC_WIRE_WIDTH_SPIN);
	m_WireWidth = GetDlgItemInt(IDC_WIRE_WIDTH);
	pWW->SetPos(m_WireWidth);
	SetModified(true);
}

void C3DGORangeWire::OnChangeWireInterval() 
{
	CSpinButtonCtrl *pWI = (CSpinButtonCtrl*) GetDlgItem(IDC_WIRE_SPACE_SPIN);
	m_WireInterval = GetDlgItemInt(IDC_WIRE_RES);
	pWI->SetPos(m_WireInterval);
	SetModified(true);
}

void C3DGORangeWire::UpdateWireIntervalRange()
{
	CSpinButtonCtrl *pWI = (CSpinButtonCtrl*) GetDlgItem(IDC_WIRE_SPACE_SPIN);
	if(m_XIntervals > m_YIntervals){
		m_max_interval = m_XIntervals;
		pWI->SetRange(1, m_XIntervals);
	}
	else{
		m_max_interval = m_YIntervals;
		pWI->SetRange(1, m_YIntervals);
	}
}


void C3DGORangeWire::ComputeValue(UINT field)
{
	CString Val;
	long double answer;

	GetDlgItem(field)->GetWindowText(Val);

	int obase = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL){
		GetDlgItem(field)->SetFocus();
		m_Calculator->m_base = obase;
		return;
	}

	m_Calculator->DecimalToString(Val, answer);
	m_Calculator->m_base = obase;
	CleanupAnswer(Val);
	GetDlgItem(field)->SetWindowText(Val);
}

void C3DGORangeWire::OnKillfocusXmin() { ComputeValue(IDC_XMIN); }
void C3DGORangeWire::OnKillfocusXmax() { ComputeValue(IDC_XMAX); }
void C3DGORangeWire::OnKillfocusYmin() { ComputeValue(IDC_YMIN); }
void C3DGORangeWire::OnKillfocusYmax() { ComputeValue(IDC_YMAX); }

void C3DGORangeWire::OnChangeXmin() { ChangedRAW[0] = true; SetModified(true); }
void C3DGORangeWire::OnChangeXmax() { ChangedRAW[1] = true; SetModified(true); }
void C3DGORangeWire::OnChangeYmin() { ChangedRAW[2] = true; SetModified(true); }
void C3DGORangeWire::OnChangeYmax() { ChangedRAW[3] = true; SetModified(true); }
void C3DGORangeWire::OnBGColor() { m_BGcolor.OnClicked(); }



BOOL C3DGORangeWire::OnApply() 
{
	UpdateData();
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_3DOPTIONS_CHANGE, 0, 0);
	
	return CPropertyPage::OnApply();
}

void C3DGORangeWire::UpdateGraphMode()
{
	switch(m_Mode){
	case 0:
		GetDlgItem(IDC_XR_MIN_TEXT)->SetWindowText("x min");
		GetDlgItem(IDC_XR_MAX_TEXT)->SetWindowText("x max");
		GetDlgItem(IDC_XR_INT_TEXT)->SetWindowText("x intervals");
		GetDlgItem(IDC_YT_MIN_TEXT)->SetWindowText("y min");
		GetDlgItem(IDC_YT_MAX_TEXT)->SetWindowText("y max");
		GetDlgItem(IDC_YT_INT_TEXT)->SetWindowText("y intervals");
		GetDlgItem(IDC_XYRT_TEXT)->SetWindowText("x/y intervals");
		break;
	case 1:
		GetDlgItem(IDC_XR_MIN_TEXT)->SetWindowText("r min");
		GetDlgItem(IDC_XR_MAX_TEXT)->SetWindowText("r max");
		GetDlgItem(IDC_XR_INT_TEXT)->SetWindowText("r intervals");
		GetDlgItem(IDC_YT_MIN_TEXT)->SetWindowText("t min");
		GetDlgItem(IDC_YT_MAX_TEXT)->SetWindowText("t max");
		GetDlgItem(IDC_YT_INT_TEXT)->SetWindowText("t intervals");
		GetDlgItem(IDC_XYRT_TEXT)->SetWindowText("r/t intervals");
		break;
	}
}

BOOL C3DGORangeWire::OnSetActive() 
{
	UpdateGraphMode();
	
	return CPropertyPage::OnSetActive();
}
