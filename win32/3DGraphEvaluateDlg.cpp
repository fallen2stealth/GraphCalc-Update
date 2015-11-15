// 3DGraphEvaluateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGraphEvaluateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DGraphEvaluateDlg dialog


C3DGraphEvaluateDlg::C3DGraphEvaluateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C3DGraphEvaluateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DGraphEvaluateDlg)
	m_iEq = 1;
	m_sEq = _T("");
	m_sX = _T("0");
	m_sY = _T("0");
	m_sZ = _T("0");
	//}}AFX_DATA_INIT
}


void C3DGraphEvaluateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGraphEvaluateDlg)
	DDX_Control(pDX, IDC_EQ, m_EqCtrl);
	DDX_Text(pDX, IDC_EQ, m_iEq);
	DDX_Text(pDX, IDC_EQS, m_sEq);
	DDX_Text(pDX, IDC_X, m_sX);
	DDX_Text(pDX, IDC_Y, m_sY);
	DDX_Text(pDX, IDC_Z, m_sZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGraphEvaluateDlg, CDialog)
	//{{AFX_MSG_MAP(C3DGraphEvaluateDlg)
	ON_CBN_SELCHANGE(IDC_EQ, OnSelchangeEq)
	ON_CBN_DROPDOWN(IDC_EQ, OnDropdownEq)
	ON_EN_CHANGE(IDC_X, OnChangeX)
	ON_EN_CHANGE(IDC_Y, OnChangeY)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGraphEvaluateDlg message handlers
BOOL C3DGraphEvaluateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Initialize equation field with active equations
	int count(0), i(0);
	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	for(i; i < MAX_3D_EQS; ++i){
		if(m_Eqs[i].on){
			CString str;
			m_Calculator->DecimalToString(str, i+1);
			m_EqCtrl.InsertString(count++, str);
		}
	}
	m_EqCtrl.SetCurSel(0);

	for(i = 0; i < MAX_3D_EQS; ++i){
		if(m_Eqs[i].on){
			m_sEq = m_Eqs[i].eq;
			break;
		}
	}
	m_Calculator->m_base = base;

	UpdateEq();
	UpdateZ();
	
	switch(m_Mode){
	case EUCLIDEAN:	
		SetDlgItemText(IDC_X_TEXT, "x");
		SetDlgItemText(IDC_Y_TEXT, "y");
		break;
	case POLAR:	
		SetDlgItemText(IDC_X_TEXT, "r");
		SetDlgItemText(IDC_Y_TEXT, "t");
		break;
	}
	
	// END ////////////////////////////////////////////	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DGraphEvaluateDlg::PassVars(S3DEquation *eqs, CCalculator *calc, EGraphMode mode)
{
	m_Eqs = eqs;
	m_Calculator = calc;
	m_Mode = mode;
}

void C3DGraphEvaluateDlg::OnDropdownEq() 
{
	UpdateData(true);
	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	int cur_sel_index(0);

	m_EqCtrl.ResetContent();
	int count(0);
	for(int i(0); i < MAX_3D_EQS; ++i){
		if(m_Eqs[i].on){
			if(i < (m_iEq - 1))
				++cur_sel_index;

			CString str;
			m_Calculator->DecimalToString(str, i+1);
			m_EqCtrl.InsertString(count++, str);
		}
	}

	if(m_EqCtrl.GetCount() == 0){
		m_EqCtrl.InsertString(0, "0");
		m_iEq = 0;
	}

	m_EqCtrl.SetCurSel(cur_sel_index);	
	m_EqCtrl.Invalidate();
	m_Calculator->m_base = base;
	UpdateData(false);	

	UpdateEq();
	UpdateZ();
}

void C3DGraphEvaluateDlg::OnSelchangeEq() 
{
	UpdateEq();
	UpdateZ();
}

void C3DGraphEvaluateDlg::OnChangeX(){	UpdateZ(); }
void C3DGraphEvaluateDlg::OnChangeY(){	UpdateZ(); }

void C3DGraphEvaluateDlg::UpdateZ()
{
	UpdateData(true);
	
	if(m_iEq == 0){
		UpdateData(false);
		return;
	}

	if(!m_Eqs[m_iEq - 1].on || m_Eqs[m_iEq - 1].eq.IsEmpty()){
		UpdateData(false);
		UpdateEq();
		return;
	}

	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	long double x, y, ans;

	if(!m_Calculator->IsValid(m_sX) || !m_Calculator->IsValid(m_sY)){
		UpdateData(false);
		m_Calculator->m_base = base;
		return;
	}

	m_Calculator->SetErrorMode(ERROR_MODE_SILENT);

	if(m_sX.IsEmpty())
		m_Calculator->Compute("0", x, this->m_hWnd);
	else
		m_Calculator->Compute(m_sX, x, this->m_hWnd);

	if(m_sY.IsEmpty())
		m_Calculator->Compute("0", y, this->m_hWnd);
	else
		m_Calculator->Compute(m_sY, y, this->m_hWnd);

	CArray<VariableT, VariableT> variables; 
	VariableT var;

	switch(m_Mode){
	case EUCLIDEAN:	
		var.str = "x";
		var.num = x;
		variables.Add(var);
		var.str = "y";
		var.num = y;
		variables.Add(var);
		break;
	case POLAR:	
		var.str = "r";
		var.num = x;
		variables.Add(var);
		var.str = "t";
		var.num = y;
		variables.Add(var);
		break;
	}
	
	m_Calculator->Compute3D(m_Eqs[m_iEq - 1].eq, &variables, ans, this->m_hWnd);

	m_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);


	// if answer is to big or too small we need ot go to scientific notation
	// or if the user is in scientific mode
	if(ans > 9999999999999
	|| ans < -9999999999999
	|| ((ans < 0.0000000000001) && (ans > 0))
	|| (ans > -0.0000000000001 && (ans < 0))){
		
		m_sZ.Format("%e", ans);

		if(-HUGE_VAL == ans || HUGE_VAL == ans)
			m_sZ = "overflow";		
	}
	else
		m_Calculator->DecimalToString(m_sZ, ans);

	UpdateData(false);
	m_Calculator->m_base = base;
}

void C3DGraphEvaluateDlg::UpdateEq()
{
	UpdateData(true);

	if(m_iEq == 0)
		m_sEq = "no equations in graph";
	else if(!m_Eqs[m_iEq - 1].on)
		m_sEq.Empty();
	else
		m_sEq = m_Eqs[m_iEq - 1].eq;

	UpdateData(false);
}