// InsertConstantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "InsertConstantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertConstantDlg dialog


CInsertConstantDlg::CInsertConstantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertConstantDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertConstantDlg)
	m_Category = _T("Physics");
	m_Name = _T("");
	m_Value = _T("");
	//}}AFX_DATA_INIT
}


void CInsertConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertConstantDlg)
	DDX_Control(pDX, IDC_CATEGORY, m_CategoryCtrl);
	DDX_CBString(pDX, IDC_CATEGORY, m_Category);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_VALUE, m_Value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertConstantDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertConstantDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertConstantDlg message handlers

BOOL CInsertConstantDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int size = m_Calculator->m_Constants.GetSize();

	for(int i(0); i < size; ++i)
		m_CategoryCtrl.InsertString(i, m_Calculator->m_Constants[i].name);

	m_CategoryCtrl.SelectString(0, m_Calculator->m_Constants[0].name);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
