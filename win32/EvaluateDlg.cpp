// EvaluateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "EvaluateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEvaluateDlg dialog


CEvaluateDlg::CEvaluateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEvaluateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEvaluateDlg)
	m_Eq = 1;
	m_X = _T("0");
	m_Y = _T("0");
	m_EqString = _T("");
	//}}AFX_DATA_INIT
}

void CEvaluateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEvaluateDlg)
	DDX_Control(pDX, IDC_EQ, m_EqCtrl);
	DDX_Text(pDX, IDC_EQ, m_Eq);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_EQS, m_EqString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEvaluateDlg, CDialog)
	//{{AFX_MSG_MAP(CEvaluateDlg)
	ON_CBN_SELCHANGE(IDC_EQ, OnSelchangeEq)
	ON_EN_CHANGE(IDC_X, OnChangeX)
	ON_CBN_DROPDOWN(IDC_EQ, OnDropdownEq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEvaluateDlg message handlers

BOOL CEvaluateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Initialize equation field with active equations
	int count(0), i(0);

	for(i; i <= 9; ++i){
		if(m_Eqs[i].disp){
			CString str;
			str.Format("%d", i+1);
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
	UpdateY();
	
	switch(m_Mode){
	case EUCLIDEAN:	
		SetDlgItemText(IDC_X_TEXT, "x");
		SetDlgItemText(IDC_Y_TEXT, "y");
		break;
	case POLAR:	
		SetDlgItemText(IDC_X_TEXT, "theta");
		SetDlgItemText(IDC_Y_TEXT, "r");
		break;
	}
	
	// END ////////////////////////////////////////////	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEvaluateDlg::OnDropdownEq() 
{
	// ok, why the fuck do I have this function
	// there is no way that the list of displayed equations can change
	// while this dialog is up, this is just a waste of time.
	
	UpdateData(true);

	int cur_sel_index(0);

	m_EqCtrl.ResetContent();
	int count(0);
	for(int i(0); i <= 9; ++i){
		if(m_Eqs[i].disp){
			if(i < (m_Eq - 1))
				++cur_sel_index;

			CString str;
			str.Format("%d", i+1);
			m_EqCtrl.InsertString(count++, str);
		}
	}

	if(m_EqCtrl.GetCount() == 0){
		m_EqCtrl.InsertString(0, "0");
		m_Eq = 0;
	}

	m_EqCtrl.SetCurSel(cur_sel_index);	
	m_EqCtrl.Invalidate();
	UpdateData(false);	

	UpdateEq();
	UpdateY();
}


void CEvaluateDlg::PassVars(EquationT *eqs, CCalculator *calc, EGraphMode mode)
{
	m_Eqs = eqs;
	m_Calculator = calc;
	m_Mode = mode;
}

void CEvaluateDlg::OnSelchangeEq() 
{
	UpdateEq();
	UpdateY();
}

void CEvaluateDlg::OnChangeX() 
{
	UpdateY();
}

void CEvaluateDlg::UpdateY()
{
	UpdateData(true);
	
	if(m_Eq == 0){
		UpdateData(false);
		return;
	}

	if(!m_Eqs[m_Eq - 1].disp || m_Eqs[m_Eq - 1].eq.IsEmpty()){
		UpdateData(false);
		UpdateEq();
		return;
	}

	long double x, ans;

	if(!m_Calculator->IsValid(m_X)){
		UpdateData(false);
		return;
	}

	m_Calculator->SetErrorMode(ERROR_MODE_SILENT);

	if(m_X.IsEmpty())
		m_Calculator->Compute("0", x, this->m_hWnd);
	else
		m_Calculator->Compute(m_X, x, this->m_hWnd);

	CArray<VariableT, VariableT> mmvariables; 
	VariableT var;
	if (m_Mode == POLAR) var.str = "t";
	else         var.str = "x";
	var.num = x;
	mmvariables.Add(var);
	m_Calculator->Compute(m_Eqs[m_Eq - 1].eq, &mmvariables, ans, this->m_hWnd);

	m_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	m_Y = ConvertForDisplay(ans);

	UpdateData(false);
}

void CEvaluateDlg::UpdateEq()
{
	UpdateData(true);

	if(m_Eq == 0)
		m_EqString = "no equations in graph";
	else if(!m_Eqs[m_Eq - 1].disp)
		m_EqString.Empty();
	else
		m_EqString = m_Eqs[m_Eq - 1].eq;

	UpdateData(false);
}

