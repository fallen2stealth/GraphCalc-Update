// 3DGOTickMarks.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGOTickMarks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DGOTickMarks property page

IMPLEMENT_DYNCREATE(C3DGOTickMarks, CPropertyPage)

C3DGOTickMarks::C3DGOTickMarks() : CPropertyPage(C3DGOTickMarks::IDD)
{
	//{{AFX_DATA_INIT(C3DGOTickMarks)
	m_bTicksOn = FALSE;
	m_iWidth = 1;
	m_iLength = 2.0;
	m_dXint = 2.0;
	m_dYint = 2.0;
	m_dZint = 2.0;
	m_ColorMode = 0;
	//}}AFX_DATA_INIT

	m_Xclr.SetSelectionMode(CP_MODE_BK);
	m_Xclr.SetColour(RGB(0,0,255));
	m_Yclr.SetSelectionMode(CP_MODE_BK);
	m_Yclr.SetColour(RGB(0,255,0));
	m_Zclr.SetSelectionMode(CP_MODE_BK);
	m_Zclr.SetColour(RGB(255,0,0));
}

C3DGOTickMarks::~C3DGOTickMarks()
{
}

void C3DGOTickMarks::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGOTickMarks)
	DDX_Check(pDX, IDC_TICKS_ON, m_bTicksOn);
	DDX_Text(pDX, IDC_WIDTH, m_iWidth);
	DDV_MinMaxUInt(pDX, m_iWidth, 1, 50);
	DDX_Text(pDX, IDC_LENGTH, m_iLength);
	DDV_MinMaxDouble(pDX, m_iLength, 1.e-004, 1000);
	DDX_Text(pDX, IDC_XINT, m_dXint);
	DDV_MinMaxDouble(pDX, m_dXint, 1.e-006, 10000000000.);
	DDX_Text(pDX, IDC_YINT, m_dYint);
	DDV_MinMaxDouble(pDX, m_dYint, 1.e-006, 10000000000.);
	DDX_Text(pDX, IDC_ZINT, m_dZint);
	DDV_MinMaxDouble(pDX, m_dZint, 1.e-006, 10000000000.);
	DDX_Control(pDX, IDC_X_COLOR, m_Xclr);
	DDX_Control(pDX, IDC_Y_COLOR, m_Yclr);
	DDX_Control(pDX, IDC_Z_COLOR, m_Zclr);
	DDX_Radio(pDX, IDC_CUSTOM_COLORS, m_ColorMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGOTickMarks, CPropertyPage)
	//{{AFX_MSG_MAP(C3DGOTickMarks)
	ON_EN_CHANGE(IDC_XINT, OnChangeValue)
	ON_WM_VSCROLL()
	ON_EN_CHANGE(IDC_WIDTH, OnChangeWidth)
	ON_BN_CLICKED(IDC_CUSTOM_COLORS, OnClickedColorMode)
	ON_BN_CLICKED(IDC_X_COLOR, OnXclr)
	ON_BN_CLICKED(IDC_Y_COLOR, OnYclr)
	ON_BN_CLICKED(IDC_Z_COLOR, OnZclr)
	ON_BN_CLICKED(IDC_TICKS_ON, OnChangeTicksOn)
	ON_BN_CLICKED(IDC_AXIS_COLORS, OnClickedColorMode)
	ON_EN_CHANGE(IDC_YINT, OnChangeValue)
	ON_EN_CHANGE(IDC_ZINT, OnChangeValue)
	ON_EN_CHANGE(IDC_X_COLOR, OnChangeValue)
	ON_EN_CHANGE(IDC_Y_COLOR, OnChangeValue)
	ON_EN_CHANGE(IDC_Z_COLOR, OnChangeValue)
	ON_EN_CHANGE(IDC_LENGTH, OnChangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGOTickMarks message handlers

BOOL C3DGOTickMarks::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CSpinButtonCtrl *pWidth = (CSpinButtonCtrl*) GetDlgItem(IDC_WIDTH_SPIN);
	pWidth->SetRange(1, 50);
	pWidth->SetPos(m_iWidth);	

	m_Xclr.SetTrackSelection(true);
	m_Yclr.SetTrackSelection(true);
	m_Zclr.SetTrackSelection(true);

	SetEnabledFields();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DGOTickMarks::OnXclr() { SetModified(true); m_Xclr.OnClicked();}
void C3DGOTickMarks::OnYclr() { SetModified(true); m_Yclr.OnClicked();}
void C3DGOTickMarks::OnZclr() { SetModified(true); m_Zclr.OnClicked();}

void C3DGOTickMarks::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(nSBCode == SB_ENDSCROLL){
		return;
	}
	
	switch(pScrollBar->GetDlgCtrlID()){
	case IDC_WIDTH_SPIN:
		{
			SetDlgItemInt(IDC_WIDTH, nPos);
			SetModified(true);
			break;
		}
	}
	
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

void C3DGOTickMarks::OnChangeValue(){	SetModified(true);  }

void C3DGOTickMarks::OnChangeTicksOn(){	
	SetEnabledFields();
	SetModified(true);  
}

void C3DGOTickMarks::OnClickedColorMode(){	
	
	UpdateData();
	
	if(m_ColorMode == 0){
		m_Xclr.ModifyStyle(WS_DISABLED, 0);
		m_Yclr.ModifyStyle(WS_DISABLED, 0);
		m_Zclr.ModifyStyle(WS_DISABLED, 0);
		GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(true);		
		GetDlgItem(IDC_Y_CLR_TEXT)->EnableWindow(true);
		GetDlgItem(IDC_Z_CLR_TEXT)->EnableWindow(true);
	}
	else{
		m_Xclr.ModifyStyle(0, WS_DISABLED);
		m_Yclr.ModifyStyle(0, WS_DISABLED);
		m_Zclr.ModifyStyle(0, WS_DISABLED);
		GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Y_CLR_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Z_CLR_TEXT)->EnableWindow(false);
	}

	if(m_Mode == 1){
		GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(false);
		m_Xclr.ModifyStyle(0, WS_DISABLED);
	}

	m_Xclr.Invalidate();
	m_Yclr.Invalidate();
	m_Zclr.Invalidate();

	SetModified(true);  
}

BOOL C3DGOTickMarks::OnApply() 
{
	UpdateData();
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_3DOPTIONS_CHANGE, 0, 0);
	
	return CPropertyPage::OnApply();
}

void C3DGOTickMarks::OnChangeWidth() 
{
	CSpinButtonCtrl *pS = (CSpinButtonCtrl*) GetDlgItem(IDC_WIDTH_SPIN);
	m_iWidth = GetDlgItemInt(IDC_WIDTH);
	pS->SetPos(m_iWidth);
	SetModified(true);
}

void C3DGOTickMarks::SetEnabledFields()
{
	UpdateData();

	if(m_bTicksOn == 1){
		GetDlgItem(IDC_WIDTH)->EnableWindow(true);
		GetDlgItem(IDC_WIDTH_SPIN)->EnableWindow(true);
		GetDlgItem(IDC_YINT)->EnableWindow(true);
		GetDlgItem(IDC_ZINT)->EnableWindow(true);
		GetDlgItem(IDC_LENGTH)->EnableWindow(true);
		GetDlgItem(IDC_CUSTOM_COLORS)->EnableWindow(true);
		GetDlgItem(IDC_AXIS_COLORS)->EnableWindow(true);
		
		GetDlgItem(IDC_Y_INT_TEXT)->EnableWindow(true);
		GetDlgItem(IDC_Z_INT_TEXT)->EnableWindow(true);
		GetDlgItem(IDC_Y_CLR_TEXT)->EnableWindow(true);
		GetDlgItem(IDC_Z_CLR_TEXT)->EnableWindow(true);

		switch(m_Mode){
		case 0:
			GetDlgItem(IDC_X_INT_TEXT)->EnableWindow(true);
			GetDlgItem(IDC_XINT)->EnableWindow(true);
			
			if(m_ColorMode == 0){
				m_Xclr.ModifyStyle(WS_DISABLED, 0);
				m_Yclr.ModifyStyle(WS_DISABLED, 0);
				m_Zclr.ModifyStyle(WS_DISABLED, 0);
			}
			else{
				m_Xclr.ModifyStyle(0, WS_DISABLED);
				m_Yclr.ModifyStyle(0, WS_DISABLED);
				m_Zclr.ModifyStyle(0, WS_DISABLED);
			}			

			m_Xclr.Invalidate();
			m_Yclr.Invalidate();
			m_Zclr.Invalidate();

			GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(true);
			break;
		case 1:
			GetDlgItem(IDC_X_INT_TEXT)->EnableWindow(false);
			GetDlgItem(IDC_XINT)->EnableWindow(false);

			if(m_ColorMode == 0){
				m_Yclr.ModifyStyle(WS_DISABLED, 0);
				m_Zclr.ModifyStyle(WS_DISABLED, 0);
			}
			else{
				m_Yclr.ModifyStyle(0, WS_DISABLED);
				m_Zclr.ModifyStyle(0, WS_DISABLED);
			}			

			m_Xclr.ModifyStyle(0, WS_DISABLED);
			m_Xclr.Invalidate();
			m_Yclr.Invalidate();
			m_Zclr.Invalidate();

			GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(false);			
			break;
		}

		OnClickedColorMode();
	}
	else{
		GetDlgItem(IDC_WIDTH)->EnableWindow(false);
		GetDlgItem(IDC_WIDTH_SPIN)->EnableWindow(false);
		GetDlgItem(IDC_XINT)->EnableWindow(false);
		GetDlgItem(IDC_YINT)->EnableWindow(false);
		GetDlgItem(IDC_ZINT)->EnableWindow(false);
		GetDlgItem(IDC_LENGTH)->EnableWindow(false);
		GetDlgItem(IDC_CUSTOM_COLORS)->EnableWindow(false);
		GetDlgItem(IDC_AXIS_COLORS)->EnableWindow(false);
		
		GetDlgItem(IDC_X_INT_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Y_INT_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Z_INT_TEXT)->EnableWindow(false);

		GetDlgItem(IDC_X_CLR_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Y_CLR_TEXT)->EnableWindow(false);
		GetDlgItem(IDC_Z_CLR_TEXT)->EnableWindow(false);
		m_Xclr.ModifyStyle(0, WS_DISABLED);
		m_Xclr.Invalidate();
		m_Yclr.ModifyStyle(0, WS_DISABLED);
		m_Yclr.Invalidate();
		m_Zclr.ModifyStyle(0, WS_DISABLED);
		m_Zclr.Invalidate();
	}
}

void C3DGOTickMarks::UpdateGraphMode()
{
	SetEnabledFields();

	switch(m_Mode){
	case 0:
		GetDlgItem(IDC_Y_INT_TEXT)->SetWindowText("y");
		GetDlgItem(IDC_Y_CLR_TEXT)->SetWindowText("y");
		break;
	case 1:
		GetDlgItem(IDC_Y_INT_TEXT)->SetWindowText("t");
		GetDlgItem(IDC_Y_CLR_TEXT)->SetWindowText("t");
		break;
	}
}

BOOL C3DGOTickMarks::OnSetActive() 
{
	UpdateGraphMode();
	
	return CPropertyPage::OnSetActive();
}
