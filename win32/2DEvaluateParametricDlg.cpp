// 2DEvaluateParametricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "grphcalc.h"
#include "2DEvaluateParametricDlg.h"
#include "globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2DEvaluateParametricDlg dialog


C2DEvaluateParametricDlg::C2DEvaluateParametricDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DEvaluateParametricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DEvaluateParametricDlg)
	m_nEq = 1;
	//}}AFX_DATA_INIT
}


void C2DEvaluateParametricDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DEvaluateParametricDlg)
	DDX_Text(pDX, IDC_EQ, m_nEq);
	DDV_MinMaxInt(pDX, m_nEq, 1, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DEvaluateParametricDlg, CDialog)
	//{{AFX_MSG_MAP(C2DEvaluateParametricDlg)
	ON_CBN_SELCHANGE(IDC_EQ, OnSelchangeEq)
	ON_EN_CHANGE(IDC_T, OnChangeT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DEvaluateParametricDlg message handlers

BOOL C2DEvaluateParametricDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Initialize equation field with active equations
	int count(0), i(0);
	CComboBox *comboEqs = (CComboBox*)GetDlgItem(IDC_EQ);

	for(i; i < MAX_PARAMETRIC_EQUATIONS; ++i){
		if(m_Eqs[i].disp){
			CString str;
			str.Format("%d", i+1);
			comboEqs->InsertString(count++, str);
		}
	}
	comboEqs->SetCurSel(0);

	for(i = 0; i < MAX_PARAMETRIC_EQUATIONS; ++i){
		if(m_Eqs[i].disp){
			SetDlgItemText(IDC_XT , m_Eqs[i].xt);
			SetDlgItemText(IDC_YT , m_Eqs[i].yt);
			break;
		}
	}

	SetDlgItemText(IDC_T, "0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DEvaluateParametricDlg::OnSelchangeEq() 
{
	UpdateData();

	// update equations displayed
	SetDlgItemText(IDC_XT , m_Eqs[m_nEq-1].xt);
	SetDlgItemText(IDC_YT , m_Eqs[m_nEq-1].yt);

	// now update x and y values
	OnChangeT();
}

void C2DEvaluateParametricDlg::OnChangeT() 
{
	if(m_nEq < 0 || m_nEq > 4)
		{
		Assert(0);
		return;
		}

	long double dX, dY, dT;
	CString strT;
	GetDlgItemText(IDC_T, strT); // get T string

	// return if t is invalid value
	if(strT.IsEmpty() || !g_Calculator->IsValid(strT))
		return;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);

	g_Calculator->Compute(strT, dT, this->m_hWnd);
	g_Calculator->Compute(m_Eqs[m_nEq-1].xt, "t", dT, dX, this->m_hWnd);
	g_Calculator->Compute(m_Eqs[m_nEq-1].yt, "t", dT, dY, this->m_hWnd);

	SetDlgItemText(IDC_X, ConvertForDisplay(dX));
	SetDlgItemText(IDC_Y, ConvertForDisplay(dY));
	
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	
}


