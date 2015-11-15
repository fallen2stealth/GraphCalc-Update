// PromptValDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "PromptValDlg.h"
#include "CCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCalculator *g_Calculator;

/////////////////////////////////////////////////////////////////////////////
// CPromptValDlg dialog


CPromptValDlg::CPromptValDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPromptValDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPromptValDlg)
	m_strValue = _T("");
	//}}AFX_DATA_INIT
}


void CPromptValDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPromptValDlg)
	DDX_Text(pDX, IDC_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPromptValDlg, CDialog)
	//{{AFX_MSG_MAP(CPromptValDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPromptValDlg message handlers

void CPromptValDlg::OnOK() 
{
	CString Val;
	long double answer;

	GetDlgItem(IDC_VALUE)->GetWindowText(Val);

	if(g_Calculator->Compute(Val, answer, this->m_hWnd) != SUCCESSFULL){
		GetDlgItem(IDC_VALUE)->SetFocus();
		return;
	}

	g_Calculator->DecimalToString(Val, answer);
	
	if(Val != "0" && Val.Find(".") != -1)
		Val.TrimRight("0");
	Val.TrimRight(".");

	m_strValue = Val;
	
	CDialog::OnOK();
}

BOOL CPromptValDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_VARIABLE, m_var + ":");
	((CEdit*)GetDlgItem(IDC_MESSAGE))->SetWindowText(m_msg);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
