// TangentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "TangentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTangentDlg dialog


CTangentDlg::CTangentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTangentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTangentDlg)
	m_Eq = 0;
	m_X = _T("0");
	m_EqString = _T("");
	//}}AFX_DATA_INIT
}


void CTangentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTangentDlg)
	DDX_Control(pDX, IDC_EQ, m_EqCtrl);
	DDX_Text(pDX, IDC_EQ, m_Eq);
	DDV_MinMaxInt(pDX, m_Eq, 1, 10);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_EQS, m_EqString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTangentDlg, CDialog)
	//{{AFX_MSG_MAP(CTangentDlg)
	ON_CBN_SELCHANGE(IDC_EQ, OnSelchangeEq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTangentDlg message handlers

BOOL CTangentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int count(0), i(0);

	for(; i <= 9; ++i){
		if(m_Eqs[i].disp){
			CString str;
			m_Calculator->DecimalToString(str, i+1);
			m_EqCtrl.InsertString(count++, str);
		}
	}
	m_EqCtrl.SetCurSel(0);

	for(i = 0; i <= 9; ++i){
		if(m_Eqs[i].disp){
			m_EqString = m_Eqs[i].eq;
			break;
		}
	}

	UpdateEq();

	switch(m_Mode){
	case EUCLIDEAN:	
		SetDlgItemText(IDC_X_TEXT, "X value");
		break;
	case POLAR:	
		SetDlgItemText(IDC_X_TEXT, "Theta value");
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTangentDlg::PassEq(EquationT *eqs, CCalculator *calc, EGraphMode mode)
{
	m_Eqs = eqs;
	m_Calculator = calc;
	m_Mode = mode;
}

void CTangentDlg::OnSelchangeEq() 
{
	// TODO: Add your control notification handler code here
	UpdateEq();
}

void CTangentDlg::UpdateEq()
{
	UpdateData(true);

	if(!m_Eqs[m_Eq - 1].disp)
		m_EqString.Empty();
	else
		m_EqString = m_Eqs[m_Eq - 1].eq;

	UpdateData(false);
}