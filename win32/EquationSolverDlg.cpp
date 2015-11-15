// EquationSolverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "EquationSolverDlg.h"
#include "CCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCalculator *g_Calculator;
extern CString g_strApplicationDirectory;
/////////////////////////////////////////////////////////////////////////////
// CEquationSolverDlg dialog


CEquationSolverDlg::CEquationSolverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEquationSolverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEquationSolverDlg)
	m_strEq = _T("");
	m_strGuess = _T("0");
	//}}AFX_DATA_INIT
}


void CEquationSolverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEquationSolverDlg)
	DDX_Text(pDX, IDC_EQ, m_strEq);
	DDX_Text(pDX, IDC_GUESS, m_strGuess);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEquationSolverDlg, CDialog)
	//{{AFX_MSG_MAP(CEquationSolverDlg)
	ON_BN_CLICKED(ID_SOLVE, OnSolve)
	ON_EN_KILLFOCUS(IDC_GUESS, OnKillfocusGuess)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_Help, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquationSolverDlg message handlers

void CEquationSolverDlg::OnSolve() 
{
	UpdateData();
	long double ldAnswer, ldGuess;
	CString strAnswer;

	// convert guess to double
	if(g_Calculator->Compute(m_strGuess, ldGuess, this->m_hWnd) != SUCCESSFULL)
		return;

	// solve
	switch(g_Calculator->EqSolver(m_strEq, "x", ldGuess, ldAnswer, strAnswer))
	{
	case UNDEFINED_VALUE:
		{
		SetDlgItemText(IDC_ANSWER, "error: undefined value");
		break;
		}
	case ZERO_SLOPE:
		{
		SetDlgItemText(IDC_ANSWER, "error: zero slope");
		break;
		}	
	case INFINITE_VALUE:
		{
		SetDlgItemText(IDC_ANSWER, "error: infinite value");
		break;
		}	
	case NO_ROOTS:
		{
		SetDlgItemText(IDC_ANSWER, "error: no roots found");
		break;
		}			
	case SUCCESSFULL:
		{
		g_Calculator->FormatString(strAnswer);
		SetDlgItemText(IDC_ANSWER, strAnswer);
		break;
		}
	case INVALID_EQ:
		{
		SetDlgItemText(IDC_ANSWER, "error: invalid equation");
		break;
		}		
	case UNKNOWNERR:
	default:
		SetDlgItemText(IDC_ANSWER, "error: unknown error");
	}
}

void CEquationSolverDlg::OnKillfocusGuess() 
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

void CEquationSolverDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	//WM_KEYDOWN  VK_ESCAPE
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CEquationSolverDlg::PreTranslateMessage(MSG* pMsg) 
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

void CEquationSolverDlg::OnHelp() 
{
	LoadHelpFile(HELP_PAGE_EQUATIONSOLVER);
}
