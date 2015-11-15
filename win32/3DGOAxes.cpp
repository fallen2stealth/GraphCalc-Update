// 3DGOAxes.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGOAxes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CCalculator *Calculator;
bool *ChangedA;

void AFXAPI DDV_ExpressionValidation( CDataExchange* pDX, int nIDC, CString& value, CCalculator *Calculator)
{
	if( pDX->m_bSaveAndValidate)
	{
		switch(nIDC){
			case IDC_X_ORIGIN:{ if(ChangedA[0]){ ChangedA[0] = false; break;} else return;	}
			case IDC_Y_ORIGIN:{ if(ChangedA[1]){ ChangedA[1] = false; break;} else return;	}
			case IDC_Z_ORIGIN:{ if(ChangedA[2]){ ChangedA[2] = false; break;} else return;	}
			case IDC_ANGLE:{ if(ChangedA[3]){ ChangedA[3] = false; break;} else return;	}
		}

		long double ans;
		if(Calculator->Compute(value, ans, pDX->m_pDlgWnd->m_hWnd) != SUCCESSFULL){
			pDX->m_pDlgWnd->MessageBox("Invalid Expression Entered");
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
		else if(nIDC == IDC_ANGLE && ans <= 0){
			pDX->m_pDlgWnd->MessageBox("Angle must be greater than 0");
			pDX->PrepareEditCtrl(nIDC);
			pDX->Fail();
		}
		else{
			value.Format("%f", ans);
			if(value != "0" && value.Find(".") != -1)
				value.TrimRight("0");

			value.TrimRight(".");
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// C3DGOAxes property page

IMPLEMENT_DYNCREATE(C3DGOAxes, CPropertyPage)

C3DGOAxes::C3DGOAxes() : CPropertyPage(C3DGOAxes::IDD)
{
	//{{AFX_DATA_INIT(C3DGOAxes)
		// NOTE: the ClassWizard will add member initialization here
	m_XOrigin = _T("0");
	m_YOrigin = _T("0");
	m_ZOrigin = _T("0");
	m_Angle = _T("pi/6");
	m_AxisOn = TRUE;
	m_LabelsOn = TRUE;
	m_AxisWidth = 1;
	//}}AFX_DATA_INIT
	
	m_Xcolor.SetSelectionMode(CP_MODE_BK);
	m_Ycolor.SetSelectionMode(CP_MODE_BK);
	m_Zcolor.SetSelectionMode(CP_MODE_BK);

	m_Xcolor.SetColour(RGB(0,0,175));
	m_Ycolor.SetColour(RGB(0,175,0));
	m_Zcolor.SetColour(RGB(175,0,0));

	ChangedA = new bool[4];
	for(int i(0); i < 4; ++i)
		ChangedA[i] = false;	
}

C3DGOAxes::~C3DGOAxes()
{
	delete ChangedA;
}

void C3DGOAxes::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGOAxes)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_X_ORIGIN, m_XOrigin);
	DDV_ExpressionValidation(pDX, IDC_X_ORIGIN, m_XOrigin, m_Calculator);
	DDX_Text(pDX, IDC_Y_ORIGIN, m_YOrigin);
	DDV_ExpressionValidation(pDX, IDC_Y_ORIGIN, m_YOrigin, m_Calculator);
	DDX_Text(pDX, IDC_Z_ORIGIN, m_ZOrigin);
	DDV_ExpressionValidation(pDX, IDC_Z_ORIGIN, m_ZOrigin, m_Calculator);
	DDX_Text(pDX, IDC_ANGLE, m_Angle);
	DDV_ExpressionValidation(pDX, IDC_ANGLE, m_Angle, m_Calculator);
	DDX_Check(pDX, IDC_AXIS_ON, m_AxisOn);
	DDX_Text(pDX, IDC_AXIS_WIDTH, m_AxisWidth);
	DDV_MinMaxUInt(pDX, m_AxisWidth, 1, 20);
	DDX_Control(pDX, IDC_X_COLOR, m_Xcolor);
	DDX_Control(pDX, IDC_Y_COLOR, m_Ycolor);
	DDX_Control(pDX, IDC_Z_COLOR, m_Zcolor);
	DDX_Check(pDX, IDC_LABELS_ON, m_LabelsOn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGOAxes, CPropertyPage)
	//{{AFX_MSG_MAP(C3DGOAxes)
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS(IDC_X_ORIGIN, OnKillfocusXOrigin)
	ON_EN_KILLFOCUS(IDC_Y_ORIGIN, OnKillfocusYOrigin)
	ON_EN_KILLFOCUS(IDC_Z_ORIGIN, OnKillfocusZOrigin)
	ON_EN_KILLFOCUS(IDC_ANGLE, OnKillfocusAngle)
	ON_EN_CHANGE(IDC_X_ORIGIN, OnChangeXOrigin)
	ON_EN_CHANGE(IDC_Y_ORIGIN, OnChangeYOrigin)
	ON_EN_CHANGE(IDC_Z_ORIGIN, OnChangeZOrigin)
	ON_EN_CHANGE(IDC_ANGLE, OnChangeAngle)
	ON_BN_CLICKED(IDC_AXIS_ON, OnChangeAxisOn)
	ON_BN_CLICKED(IDC_LABELS_ON, OnChangeLabelsOn)
	ON_EN_CHANGE(IDC_AXIS_WIDTH, OnChangeAxisWidth)
	ON_BN_CLICKED(IDC_X_COLOR, OnXColor)
	ON_BN_CLICKED(IDC_Y_COLOR, OnYColor)
	ON_BN_CLICKED(IDC_Z_COLOR, OnZColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGOAxes message handlers

void C3DGOAxes::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode == SB_ENDSCROLL){
		return;
	}
	
	switch(pScrollBar->GetDlgCtrlID()){
	case IDC_AXIS_WIDTH_SPIN:
		{
			SetDlgItemInt(IDC_AXIS_WIDTH, nPos);
			SetModified(true);
			break;
		}
	}
	
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL C3DGOAxes::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	CSpinButtonCtrl *pAW = (CSpinButtonCtrl*) GetDlgItem(IDC_AXIS_WIDTH_SPIN);
	pAW->SetRange(1, 20);
	pAW->SetPos(m_AxisWidth);

	SetEnabledFields(m_AxisOn);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DGOAxes::OnChangeAxisWidth() 
{ 
	CSpinButtonCtrl *pAW = (CSpinButtonCtrl*) GetDlgItem(IDC_AXIS_WIDTH_SPIN);
	m_AxisWidth = GetDlgItemInt(IDC_AXIS_WIDTH);
	pAW->SetPos(m_AxisWidth);
	SetModified(true);
	SetEnabledFields(IsDlgButtonChecked(IDC_AXIS_ON));
}

void C3DGOAxes::ComputeValue(UINT field)
{
	CString Val;
	long double answer;

	GetDlgItem(field)->GetWindowText(Val);

	if(m_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL){
		GetDlgItem(field)->SetFocus();
		return;
	}

	Val.Format("%.15f", answer);
	CleanupAnswer(Val);
	GetDlgItem(field)->SetWindowText(Val);
}

void C3DGOAxes::OnKillfocusXOrigin() {	ComputeValue(IDC_X_ORIGIN); }
void C3DGOAxes::OnKillfocusYOrigin() {	ComputeValue(IDC_Y_ORIGIN); }
void C3DGOAxes::OnKillfocusZOrigin() {	ComputeValue(IDC_Z_ORIGIN); }
void C3DGOAxes::OnKillfocusAngle() {	ComputeValue(IDC_ANGLE); }

void C3DGOAxes::OnChangeXOrigin() { ChangedA[0] = true; SetModified(true); }
void C3DGOAxes::OnChangeYOrigin() { ChangedA[1] = true; SetModified(true); }
void C3DGOAxes::OnChangeZOrigin() { ChangedA[2] = true; SetModified(true); }
void C3DGOAxes::OnChangeAngle() { ChangedA[3] = true; SetModified(true); }
void C3DGOAxes::OnChangeAxisOn() { SetModified(true); SetEnabledFields(IsDlgButtonChecked(IDC_AXIS_ON));}
void C3DGOAxes::OnChangeLabelsOn() { SetModified(true); }

void C3DGOAxes::OnXColor() { m_Xcolor.OnClicked(); SetModified(true);}
void C3DGOAxes::OnYColor() { m_Ycolor.OnClicked(); SetModified(true);}
void C3DGOAxes::OnZColor() { m_Zcolor.OnClicked(); SetModified(true);}

BOOL C3DGOAxes::OnApply() 
{
	UpdateData();
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_3DOPTIONS_CHANGE, 0, 0);
	
	return CPropertyPage::OnApply();
}

void C3DGOAxes::SetEnabledFields(int bEnabled)
{
	m_AxisOn = bEnabled;

	if(m_AxisOn == 1){
		GetDlgItem(IDC_AXIS_WIDTH)->EnableWindow(true);
		GetDlgItem(IDC_AXIS_WIDTH_SPIN)->EnableWindow(true);

		switch(m_Mode){
		case 0:
			GetDlgItem(IDC_X_ORIGIN)->EnableWindow(true);
			GetDlgItem(IDC_Y_ORIGIN)->EnableWindow(true);
			GetDlgItem(IDC_Z_ORIGIN)->EnableWindow(true);
			GetDlgItem(IDC_X_ORG_TEXT)->EnableWindow(true);
			GetDlgItem(IDC_Y_ORG_TEXT)->EnableWindow(true);
			GetDlgItem(IDC_Z_ORG_TEXT)->EnableWindow(true);
			
			GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(true);
			m_Xcolor.ModifyStyle(WS_DISABLED, 0);
			m_Xcolor.Invalidate();	

			GetDlgItem(IDC_ANGLE_TEXT)->EnableWindow(false);
			GetDlgItem(IDC_ANGLE)->EnableWindow(false);

			break;
		case 1:
			GetDlgItem(IDC_X_ORIGIN)->EnableWindow(false);
			GetDlgItem(IDC_Y_ORIGIN)->EnableWindow(false);
			GetDlgItem(IDC_Z_ORIGIN)->EnableWindow(false);
			GetDlgItem(IDC_X_ORG_TEXT)->EnableWindow(false);
			GetDlgItem(IDC_Y_ORG_TEXT)->EnableWindow(false);
			GetDlgItem(IDC_Z_ORG_TEXT)->EnableWindow(false);
			
			GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(false);
			m_Xcolor.ModifyStyle(0, WS_DISABLED);
			m_Xcolor.Invalidate();

			GetDlgItem(IDC_ANGLE_TEXT)->EnableWindow(true);
			GetDlgItem(IDC_ANGLE)->EnableWindow(true);
			break;
		}

		GetDlgItem(IDC_Y_CLR_TEXT)->EnableWindow(true);
		GetDlgItem(IDC_Z_CLR_TEXT)->EnableWindow(true);
		m_Ycolor.ModifyStyle(WS_DISABLED, 0);
		m_Ycolor.Invalidate();
		m_Zcolor.ModifyStyle(WS_DISABLED, 0);
		m_Zcolor.Invalidate();
	}
	else{
		GetDlgItem(IDC_AXIS_WIDTH)->EnableWindow(false);
		GetDlgItem(IDC_AXIS_WIDTH_SPIN)->EnableWindow(false);
		
		GetDlgItem(IDC_X_ORIGIN)->EnableWindow(false);
		GetDlgItem(IDC_Y_ORIGIN)->EnableWindow(false);
		GetDlgItem(IDC_Z_ORIGIN)->EnableWindow(false);
		GetDlgItem(IDC_X_ORG_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Y_ORG_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Z_ORG_TEXT)->EnableWindow(false);

		GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(false);
		m_Xcolor.ModifyStyle(0, WS_DISABLED);
		m_Xcolor.Invalidate();

		GetDlgItem(IDC_ANGLE_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_ANGLE)->EnableWindow(false);

		GetDlgItem(IDC_Y_CLR_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Z_CLR_TEXT)->EnableWindow(false);
		m_Ycolor.ModifyStyle(0, WS_DISABLED);
		m_Ycolor.Invalidate();
		m_Zcolor.ModifyStyle(0, WS_DISABLED);
		m_Zcolor.Invalidate();
	}
}

void C3DGOAxes::UpdateGraphMode()
{
	SetEnabledFields(IsDlgButtonChecked(IDC_AXIS_ON));
	switch(m_Mode){
	case 0:
		GetDlgItem(IDC_Y_CLR_TEXT)->SetWindowText("y");
		break;
	case 1:
		GetDlgItem(IDC_Y_CLR_TEXT)->SetWindowText("t");
		break;
	}
}

BOOL C3DGOAxes::OnSetActive() 
{
	UpdateGraphMode();	
	return CPropertyPage::OnSetActive();
}
