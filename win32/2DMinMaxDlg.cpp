// 2DMinMaxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "2DMinMaxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CString g_strApplicationDirectory;
/////////////////////////////////////////////////////////////////////////////
// C2DMinMaxDlg dialog


C2DMinMaxDlg::C2DMinMaxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C2DMinMaxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C2DMinMaxDlg)
	m_nEq = -1;
	m_strMax = _T("10");
	m_strMin = _T("-10");
	m_strEq = _T("");
	//}}AFX_DATA_INIT
}


void C2DMinMaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DMinMaxDlg)
	DDX_Control(pDX, IDC_EQUATION_PICKER, m_EqCtrl);
	DDX_Text(pDX, IDC_EQUATION_PICKER, m_nEq);
	DDX_Text(pDX, IDC_MAX, m_strMax);
	DDX_Text(pDX, IDC_MIN, m_strMin);
	DDX_Text(pDX, IDC_EQUATION, m_strEq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DMinMaxDlg, CDialog)
	//{{AFX_MSG_MAP(C2DMinMaxDlg)
	ON_BN_CLICKED(ID_SOLVE, OnSolve)
	ON_CBN_SELCHANGE(IDC_EQUATION_PICKER, OnSelchangeEquationPicker)
	ON_EN_KILLFOCUS(IDC_MIN, OnKillfocusMin)
	ON_EN_KILLFOCUS(IDC_MAX, OnKillfocusMax)
	ON_BN_CLICKED(IDC_CENTER_GRAPH, OnCenterGraph)
	ON_BN_CLICKED(IDC_Help, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DMinMaxDlg message handlers

void C2DMinMaxDlg::OnSolve() 
{
	UpdateData();
	int minmax;
	long double ldAnswer, ldMin, ldMax;
	CString strAnswer;

	SetDlgItemText(IDC_X, "");
	SetDlgItemText(IDC_Y, "");
	SetDlgItemText(IDC_RESULTS, "Calculating...");

	GetDlgItem(IDC_CENTER_GRAPH)->EnableWindow(false);

	// convert min and max to double
	if(g_Calculator->Compute(m_strMin, ldMin, this->m_hWnd) != SUCCESSFULL)
		return;
	if(g_Calculator->Compute(m_strMax, ldMax, this->m_hWnd) != SUCCESSFULL)
		return;

	// solve
	switch(g_Calculator->MinMaxSolverBisection(m_Eqs[m_nEq-1].eq, "x", ldMin, ldMax, ldAnswer, strAnswer, minmax))
	{
	case UNDEFINED_VALUE:
		{
		SetDlgItemText(IDC_RESULTS, "Error: undefined value");
		break;
		}
	case INFINITE_VALUE:
		{
		SetDlgItemText(IDC_RESULTS, "Error: infinite value");
		break;
		}	
	case NO_ROOTS:
		{
		SetDlgItemText(IDC_RESULTS, "No stationary points found");
		break;
		}			
	case SUCCESSFULL:
		{
		g_Calculator->FormatString(strAnswer);
		SetDlgItemText(IDC_X, strAnswer);

		m_x = ldAnswer;

		long double ans;
		CString strY;
		g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
		g_Calculator->Compute(m_Eqs[m_nEq-1].eq, "x", ldAnswer, ans, this->m_hWnd);
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		g_Calculator->DecimalToStringSci(strY, ans);
		SetDlgItemText(IDC_Y, strY);

		m_y = ans;

		if(minmax > 0)
			SetDlgItemText(IDC_RESULTS, "Maximum found at...");
		else if(minmax < 0)
			SetDlgItemText(IDC_RESULTS, "Minimum found at...");
		else
			SetDlgItemText(IDC_RESULTS, "Error determining minimum or maximum");			

		GetDlgItem(IDC_CENTER_GRAPH)->EnableWindow(true);
		
		break;
		}
	case INVALID_EQ:
		{
		SetDlgItemText(IDC_RESULTS, "Error: invalid equation");
		break;
		}		
	case UNKNOWNERR:
	default:
		SetDlgItemText(IDC_RESULTS, "Error: unknown error");
	}
}

BOOL C2DMinMaxDlg::OnInitDialog() 
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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C2DMinMaxDlg::OnSelchangeEquationPicker() 
{
	UpdateEq();
}

void C2DMinMaxDlg::OnKillfocusMin() 
{
	CString Val;
	long double answer;

	GetDlgItem(IDC_MIN)->GetWindowText(Val);

	if(g_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	g_Calculator->DecimalToString(Val, answer);
	if(Val != "0" && Val.Find(".") != -1)
		Val.TrimRight("0");
	Val.TrimRight(".");

	GetDlgItem(IDC_MIN)->SetWindowText(Val);	
}

void C2DMinMaxDlg::OnKillfocusMax() 
{
	CString Val;
	long double answer;

	GetDlgItem(IDC_MAX)->GetWindowText(Val);

	if(g_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL)
		return;

	g_Calculator->DecimalToString(Val, answer);
	if(Val != "0" && Val.Find(".") != -1)
		Val.TrimRight("0");
	Val.TrimRight(".");

	GetDlgItem(IDC_MAX)->SetWindowText(Val);	
}

void C2DMinMaxDlg::UpdateEq()
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

void C2DMinMaxDlg::OnCenterGraph() 
{
	CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SendMessage(WM_2DGRAPH_CENTER, (WPARAM)&m_x, (LPARAM)&m_y);
}

BOOL C2DMinMaxDlg::PreTranslateMessage(MSG* pMsg) 
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

void C2DMinMaxDlg::OnHelp() 
{
	LoadHelpFile(HELP_PAGE_2D_EQUATIONMINMAX);
}
