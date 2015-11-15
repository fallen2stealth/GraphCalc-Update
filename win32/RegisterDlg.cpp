// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "RegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegisterDlg)
	m_sName = _T("");
	m_sCode = _T("");
	//}}AFX_DATA_INIT
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterDlg)
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDX_Text(pDX, IDC_CODE, m_sCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	//{{AFX_MSG_MAP(CRegisterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg message handlers

void CRegisterDlg::OnOK() 
{
		

	CDialog::OnOK();
}
