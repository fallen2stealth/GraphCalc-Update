// 2DEquationInterceptsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "2DEquationInterceptsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCalculator *g_Calculator;
extern CString g_strApplicationDirectory;
/////////////////////////////////////////////////////////////////////////////
// C2DEquationInterceptsDlg dialog


C2DEquationInterceptsDlg::C2DEquationInterceptsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DEquationInterceptsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DEquationInterceptsDlg)
	m_nEq = 0;
	m_strEq = _T("");
	m_strGuess = _T("0");
	m_strXIntercept = _T("");
	m_strYIntercept = _T("");
	//}}AFX_DATA_INIT
}


void C2DEquationInterceptsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DEquationInterceptsDlg)
	DDX_Control(pDX, IDC_EQUATION_PICKER, m_EqCtrl);
	DDX_Text(pDX, IDC_EQUATION_PICKER, m_nEq);
	DDX_Text(pDX, IDC_EQUATION, m_strEq);
	DDX_Text(pDX, IDC_GUESS, m_strGuess);
	DDX_Text(pDX, IDC_X_INTERCEPT, m_strXIntercept);
	DDX_Text(pDX, IDC_Y_INTERCEPT, m_strYIntercept);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DEquationInterceptsDlg, CDialog)
	//{{AFX_MSG_MAP(C2DEquationInterceptsDlg)
	ON_EN_KILLFOCUS(IDC_GUESS, OnKillfocusGuess)
	ON_BN_CLICKED(ID_SOLVE, OnSolve)
	ON_CBN_SELCHANGE(IDC_EQUATION_PICKER, OnSelchangeEquationPicker)
	ON_CBN_DROPDOWN(IDC_EQUATION_PICKER, OnDropdownEquationPicker)
	ON_BN_CLICKED(IDC_CENTER_GRAPH, OnCenterGraph)
	ON_BN_CLICKED(IDC_Help, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DEquationInterceptsDlg message handlers

void C2DEquationInterceptsDlg::OnKillfocusGuess() 
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

void C2DEquationInterceptsDlg::OnSolve() 
{
	UpdateData();
	long double ldAnswer, ldGuess;
	CString strAnswer;

	GetDlgItem(IDC_CENTER_GRAPH)->EnableWindow(false);

	// convert guess to double
	if(g_Calculator->Compute(m_strGuess, ldGuess, this->m_hWnd) != SUCCESSFULL)
		return;

	// solve
	switch(g_Calculator->EqSolver(m_Eqs[m_nEq-1].eq, "x", ldGuess, ldAnswer, strAnswer))
	{
	case UNDEFINED_VALUE:
		{
		SetDlgItemText(IDC_X_INTERCEPT, "error: undefined value");
		break;
		}
	case ZERO_SLOPE:
		{
		SetDlgItemText(IDC_X_INTERCEPT, "error: zero slope");
		break;
		}	
	case INFINITE_VALUE:
		{
		SetDlgItemText(IDC_X_INTERCEPT, "error: infinite value");
		break;
		}	
	case NO_ROOTS:
		{
		SetDlgItemText(IDC_X_INTERCEPT, "error: no roots found");
		break;
		}			
	case SUCCESSFULL:
		{
		m_x = ldAnswer;
		g_Calculator->FormatString(strAnswer);
		SetDlgItemText(IDC_X_INTERCEPT, strAnswer);
		GetDlgItem(IDC_CENTER_GRAPH)->EnableWindow(true);
		break;
		}
	case INVALID_EQ:
		{
		SetDlgItemText(IDC_X_INTERCEPT, "error: invalid equation");
		break;
		}		
	case UNKNOWNERR:
	default:
		SetDlgItemText(IDC_X_INTERCEPT, "error: unknown error");
	}
}

void C2DEquationInterceptsDlg::OnSelchangeEquationPicker() 
{
	UpdateEq();
	UpdateYIntercept();
}

void C2DEquationInterceptsDlg::OnDropdownEquationPicker() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL C2DEquationInterceptsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
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
			m_strEq = m_Eqs[i].eq;
			m_nEq = i+1;
			break;
		}
	}

	SetDlgItemText(IDC_EQUATION, m_strEq);

	// determine y-intercept
	UpdateYIntercept();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DEquationInterceptsDlg::UpdateYIntercept()
{
	long double ans;
	CString yint;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	g_Calculator->Compute(m_Eqs[m_nEq-1].eq, "x", 0, ans, this->m_hWnd);
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	g_Calculator->DecimalToStringSci(yint, ans);
	SetDlgItemText(IDC_Y_INTERCEPT, yint);
}

void C2DEquationInterceptsDlg::UpdateEq()
{
	UpdateData(true);

	if(m_nEq == 0)
		m_strEq = "no equations in graph";
	else if(!m_Eqs[m_nEq-1].disp)
		m_strEq.Empty();
	else
		m_strEq = m_astrEquations[m_nEq-1];

	UpdateData(false);
}

void C2DEquationInterceptsDlg::OnCenterGraph() 
{
	long double y=0;
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_2DGRAPH_CENTER, (WPARAM)&m_x, (LPARAM)&y);
}

BOOL C2DEquationInterceptsDlg::PreTranslateMessage(MSG* pMsg) 
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

void C2DEquationInterceptsDlg::OnHelp() 
{
	LoadHelpFile(HELP_PAGE_2D_EQUATIONINTERCEPTS);
}
