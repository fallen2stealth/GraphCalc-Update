// 2DEqIntersectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "2DEqIntersectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCalculator *g_Calculator;
extern CString g_strApplicationDirectory;
/////////////////////////////////////////////////////////////////////////////
// C2DEqIntersectionDlg dialog


C2DEqIntersectionDlg::C2DEqIntersectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DEqIntersectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DEqIntersectionDlg)
	m_nEq1 = 0;
	m_nEq2 = 0;
	m_strGuess = _T("0");
	m_strEq1 = _T("");
	m_strEq2 = _T("");
	//}}AFX_DATA_INIT
}


void C2DEqIntersectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DEqIntersectionDlg)
	DDX_Control(pDX, IDC_EQUATION1_PICKER, m_Eq1Ctrl);
	DDX_Control(pDX, IDC_EQUATION2_PICKER, m_Eq2Ctrl);
	DDX_Text(pDX, IDC_EQUATION1_PICKER, m_nEq1);
	DDX_Text(pDX, IDC_EQUATION2_PICKER, m_nEq2);
	DDX_Text(pDX, IDC_GUESS, m_strGuess);
	DDX_Text(pDX, IDC_EQUATION1, m_strEq1);
	DDX_Text(pDX, IDC_EQUATION2, m_strEq2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DEqIntersectionDlg, CDialog)
	//{{AFX_MSG_MAP(C2DEqIntersectionDlg)
	ON_EN_KILLFOCUS(IDC_GUESS, OnKillfocusGuess)
	ON_BN_CLICKED(ID_SOLVE, OnSolve)
	ON_CBN_SELCHANGE(IDC_EQUATION1_PICKER, OnSelchangeEquation1Picker)
	ON_CBN_SELCHANGE(IDC_EQUATION2_PICKER, OnSelchangeEquation2Picker)
	ON_BN_CLICKED(IDC_CENTER_GRAPH, OnCenterGraph)
	ON_BN_CLICKED(IDC_Help, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DEqIntersectionDlg message handlers

void C2DEqIntersectionDlg::OnKillfocusGuess() 
{
	CString Val;
	long double answer;

	GetDlgItem(IDC_GUESS)->GetWindowText(Val);

	if(g_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	g_Calculator->DecimalToString(Val, answer);
	if(Val != "0" && Val.Find(".") != -1)
		Val.TrimRight("0");
	Val.TrimRight(".");

	GetDlgItem(IDC_GUESS)->SetWindowText(Val);
}

void C2DEqIntersectionDlg::OnSolve() 
{
	BeginWaitCursor();
	
	UpdateData();
	long double ldX, ldY, ldGuess;
	CString strX, strY;

	SetDlgItemText(IDC_Y, "");
	SetDlgItemText(IDC_X, "");
	GetDlgItem(IDC_CENTER_GRAPH)->EnableWindow(false);

	// convert guess to double
	if(g_Calculator->Compute(m_strGuess, ldGuess, this->m_hWnd) != SUCCESSFULL)
		goto Error;

	// solve
	switch(g_Calculator->EqSolver(m_Eqs[m_nEq1-1].eq + "=" + m_Eqs[m_nEq2-1].eq, "x", ldGuess, ldX, strX))
	{	
	case SUCCESSFULL:
		{
		g_Calculator->FormatString(strX);
		SetDlgItemText(IDC_X, strX);
		m_x = ldX;

		// calculate y
		if(g_Calculator->Compute(m_Eqs[m_nEq1-1].eq, "x", ldX, ldY, this->m_hWnd) != SUCCESSFULL)
			goto Error;
		
		m_y = ldY;
		g_Calculator->DecimalToStringSci(strY, ldY);
		g_Calculator->FormatString(strY);
		SetDlgItemText(IDC_Y, strY);
		GetDlgItem(IDC_CENTER_GRAPH)->EnableWindow(true);
		
		break;
		}
	case UNDEFINED_VALUE:
		{
		SetDlgItemText(IDC_X, "error: undefined value");
		break;
		}
	case ZERO_SLOPE:
		{
		SetDlgItemText(IDC_X, "error: zero slope");
		break;
		}	
	case INFINITE_VALUE:
		{
		SetDlgItemText(IDC_X, "error: infinite value");
		break;
		}		
	case INVALID_EQ:
		{
		SetDlgItemText(IDC_X, "error: invalid equation");
		break;
		}		
	case NO_ROOTS:
	case UNKNOWNERR:
	default:
		SetDlgItemText(IDC_X, "error: no intersection found");
	}

	Error:
		EndWaitCursor();
	
}

void C2DEqIntersectionDlg::OnSelchangeEquation1Picker() 
{
	UpdateEqLists();
	UpdateEqs();
}

void C2DEqIntersectionDlg::OnSelchangeEquation2Picker() 
{
	UpdateEqs();
}

BOOL C2DEqIntersectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Initialize equation field with active equations
	int count1(0), count2(0);
	CString str;

	for(int i(0); i <= 9; ++i){
		if(m_Eqs[i].disp){
			str.Format("%d", i+1);
			m_Eq1Ctrl.InsertString(count1++, str);

			if(count1 > 1){
				str.Format("%d", i+1);
				m_Eq2Ctrl.InsertString(count2++, str);
			}

			if(count1 == 1)
			{	
				m_nEq1 = i+1;
				m_strEq1 = m_Eqs[i].eq;
			}
			if(count2 == 1)
			{
				m_nEq2 = i+1;
				m_strEq2 = m_Eqs[i].eq;
			}
		}
	}

	m_Eq1Ctrl.SetCurSel(0);
	m_Eq2Ctrl.SetCurSel(0);

	SetDlgItemText(IDC_EQUATION1, m_strEq1);
	SetDlgItemText(IDC_EQUATION2, m_strEq2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DEqIntersectionDlg::UpdateEqs()
{
	UpdateData(true);

	if(!m_Eqs[m_nEq1 - 1].disp)
		m_strEq1.Empty();
	else
		m_strEq1 = m_astrEquations[m_nEq1 - 1];

	if(!m_Eqs[m_nEq2 - 1].disp)
		m_strEq2.Empty();
	else
		m_strEq2 = m_astrEquations[m_nEq2 - 1];

	UpdateData(false);
}

void C2DEqIntersectionDlg::UpdateEqLists()
{
	int count(0);
	UpdateData(true);

	m_Eq2Ctrl.ResetContent();

	for(int i(0); i <= 9; ++i)
		if(m_Eqs[i].disp && m_nEq1 != i + 1){
			CString str;
			str.Format("%d", i+1);
			m_Eq2Ctrl.InsertString(count++, str);
			m_nEq2 = i + 1;
		}

	m_Eq2Ctrl.SetCurSel(1);	
	m_Eq2Ctrl.Invalidate();
	UpdateData(false);
}

void C2DEqIntersectionDlg::OnCenterGraph() 
{
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_2DGRAPH_CENTER, (WPARAM)&m_x, (LPARAM)&m_y);
}

BOOL C2DEqIntersectionDlg::PreTranslateMessage(MSG* pMsg) 
{
	// seems to be the only way to grab
	// when the escape key is pressed
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		{
		EndDialog(IDOK);
		return true;
		}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void C2DEqIntersectionDlg::OnHelp() 
{
	LoadHelpFile(HELP_PAGE_2D_EQUATIONINTERSECTION);
}
