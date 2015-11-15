// CatalogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "CatalogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatalogDlg dialog


CCatalogDlg::CCatalogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatalogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatalogDlg)
	m_Operator = _T("");
	//}}AFX_DATA_INIT
}


void CCatalogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatalogDlg)
	DDX_Control(pDX, IDC_OPERATOR, m_OperatorCtrl);
	DDX_LBString(pDX, IDC_OPERATOR, m_Operator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCatalogDlg, CDialog)
	//{{AFX_MSG_MAP(CCatalogDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatalogDlg message handlers

/*********************************************************/
// CCatalogDlg::OnInitDialog()
// Pre: none
// Post: m_OperatirCtrl contains lis tof operators
// Return Value: true if function is succesful
// Intent: to initialize dialog and operators
/*********************************************************/
BOOL CCatalogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_OperatorCtrl.AddString("+");	
	m_OperatorCtrl.AddString("-");	
	m_OperatorCtrl.AddString("*");	
	m_OperatorCtrl.AddString("/");	
	m_OperatorCtrl.AddString("^");	
	m_OperatorCtrl.AddString("(");	
	m_OperatorCtrl.AddString(")");	
	m_OperatorCtrl.AddString("x");	
	m_OperatorCtrl.AddString("sqrt");	
	m_OperatorCtrl.AddString("sin");	
	m_OperatorCtrl.AddString("arcsin");	
	m_OperatorCtrl.AddString("sinh");	
	m_OperatorCtrl.AddString("cos");	
	m_OperatorCtrl.AddString("arccos");	
	m_OperatorCtrl.AddString("cosh");	
	m_OperatorCtrl.AddString("tan");	
	m_OperatorCtrl.AddString("arctan");	
	m_OperatorCtrl.AddString("tanh");	
	m_OperatorCtrl.AddString("log");	
	m_OperatorCtrl.AddString("ln");	
	m_OperatorCtrl.AddString("!");	
	m_OperatorCtrl.AddString("ncr");	
	m_OperatorCtrl.AddString("npr");	
	m_OperatorCtrl.AddString("==");	
	m_OperatorCtrl.AddString(">");	
	m_OperatorCtrl.AddString("<");	
	m_OperatorCtrl.AddString("<=");	
	m_OperatorCtrl.AddString(">=");	
	m_OperatorCtrl.AddString("!=");	
	m_OperatorCtrl.AddString("abs(a)");	
	m_OperatorCtrl.AddString("int(a)");
	m_OperatorCtrl.AddString("ipart(a)");
	m_OperatorCtrl.AddString("fpart(a)");
	m_OperatorCtrl.AddString("gcd(a:b)");
	m_OperatorCtrl.AddString("lcm(a:b)");
	m_OperatorCtrl.AddString("min(a:b)");
	m_OperatorCtrl.AddString("max(a:b)");
	m_OperatorCtrl.AddString("convbase");
	m_OperatorCtrl.AddString("irand(a:b)");
	m_OperatorCtrl.AddString("frand(a:b)");
	m_OperatorCtrl.AddString("round(a)");
	m_OperatorCtrl.AddString("ans");
	m_OperatorCtrl.AddString("mod");
	m_OperatorCtrl.AddString("mean(a:b:c:d)");
	m_OperatorCtrl.AddString("med(a:b:c:d)");
	m_OperatorCtrl.AddString("mode(a:b:c:d)");
	m_OperatorCtrl.AddString("stdev(a:b:c:d)");
	m_OperatorCtrl.AddString("variance(a:b:c:d)");
	m_OperatorCtrl.AddString("fib(a)");
	m_OperatorCtrl.AddString(",");
	m_OperatorCtrl.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
