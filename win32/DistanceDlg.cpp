// DistanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "DistanceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistanceDlg dialog


CDistanceDlg::CDistanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDistanceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDistanceDlg)
	m_Equation = 0;
	m_Equation2 = 0;
	m_Xmax = _T("1");
	m_Xmin = _T("-1");
	m_Between = FALSE;
	m_EqString2 = _T("");
	m_EqString = _T("");
	//}}AFX_DATA_INIT
}

void CDistanceDlg::PassEq(EquationT *eqs, CCalculator *calc, EGraphMode mode){
	m_Eqs = eqs;
	m_Calculator = calc;
	m_Mode = mode;
}

void CDistanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDistanceDlg)
	DDX_Control(pDX, IDC_BETWEEN, m_BetweenCtrl);
	DDX_Control(pDX, IDC_EQUATION2, m_Equation2Ctrl);
	DDX_Control(pDX, IDC_EQUATION, m_EquationCtrl);
	DDX_Text(pDX, IDC_EQUATION, m_Equation);
	DDV_MinMaxInt(pDX, m_Equation, 1, 10);
	DDX_Text(pDX, IDC_EQUATION2, m_Equation2);
	DDV_MinMaxInt(pDX, m_Equation2, 1, 10);
	DDX_Text(pDX, IDC_XMAX, m_Xmax);
	DDX_Text(pDX, IDC_XMIN, m_Xmin);
	DDX_Check(pDX, IDC_BETWEEN, m_Between);
	DDX_Text(pDX, IDC_EQS2, m_EqString2);
	DDX_Text(pDX, IDC_EQS, m_EqString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDistanceDlg, CDialog)
	//{{AFX_MSG_MAP(CDistanceDlg)
	ON_BN_CLICKED(IDC_BETWEEN, OnBetween)
	ON_CBN_SELCHANGE(IDC_EQUATION, OnSelchangeEquation)
	ON_CBN_SELCHANGE(IDC_EQUATION2, OnSelchangeEquation2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDistanceDlg message handlers


BOOL CDistanceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Initialize equation field with active equations
	int count1(0), count2(0);

	for(int i(0); i <= 9; ++i){
		if(m_Eqs[i].disp){
			CString str;
			m_Calculator->DecimalToString(str, i+1);
			m_EquationCtrl.InsertString(count1++, str);

			if(count1 > 1){
				m_Equation = i;
				CString str;
				m_Calculator->DecimalToString(str, i+1);
				m_Equation2Ctrl.InsertString(count2++, str);
			}

			if(count2 == 1)
				m_Equation2 = i;
		}
	}

	if(m_Equation2Ctrl.GetCount() == 0){
		CString str;
		m_Calculator->DecimalToString(str, m_Equation+1);
		m_Equation2Ctrl.InsertString(0, str);
		m_Equation2 = m_Equation;
	}
	if(m_EquationCtrl.GetCount() <= 1)
		m_BetweenCtrl.EnableWindow(false);

	m_EquationCtrl.SetCurSel(0);
	m_Equation2Ctrl.SetCurSel(0);

	m_EqString = m_Eqs[m_Equation].eq;
	m_EqString2 = m_Eqs[m_Equation2].eq;
	
	UpdateEqs();

	// END ////////////////////////////////////////////

	OnBetween();

	switch(m_Mode){
	case EUCLIDEAN:	
		SetDlgItemText(IDC_XMIN_TEXT, "X min");
		SetDlgItemText(IDC_XMAX_TEXT, "X max");
		break;
	case POLAR:	
		SetDlgItemText(IDC_XMIN_TEXT, "Theta min");
		SetDlgItemText(IDC_XMAX_TEXT, "Theta max");
		break;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDistanceDlg::OnBetween() 
{
	if(BST_CHECKED == IsDlgButtonChecked(IDC_BETWEEN))
		m_Equation2Ctrl.EnableWindow();
	else
		m_Equation2Ctrl.EnableWindow(false);
}

void CDistanceDlg::UpdateEqLists()
{
	int count(0);
	UpdateData(true);

	m_Equation2Ctrl.ResetContent();

	for(int i(0); i <= 9; ++i)
		if(m_Eqs[i].disp && m_Equation != i + 1){
			CString str;
			m_Calculator->DecimalToString(str, i+1);
			m_Equation2Ctrl.InsertString(count++, str);
			m_Equation2 = i + 1;
		}

	m_Equation2Ctrl.SetCurSel(1);	
	m_Equation2Ctrl.Invalidate();
	UpdateData(false);
}

void CDistanceDlg::UpdateEqs()
{
	UpdateData(true);

	if(!m_Eqs[m_Equation - 1].disp)
		m_EqString.Empty();
	else
		m_EqString = m_Eqs[m_Equation - 1].eq;

	if(!m_Eqs[m_Equation2 - 1].disp)
		m_EqString2.Empty();
	else
		m_EqString2 = m_Eqs[m_Equation2 - 1].eq;

	UpdateData(false);
}

void CDistanceDlg::OnSelchangeEquation() 
{
	UpdateEqLists();
	UpdateEqs();
}
void CDistanceDlg::OnSelchangeEquation2() 
{
	UpdateEqs();
}
