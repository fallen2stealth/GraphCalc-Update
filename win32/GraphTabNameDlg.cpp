// GraphTabNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphTabNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphTabNameDlg dialog


CGraphTabNameDlg::CGraphTabNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphTabNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphTabNameDlg)
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CGraphTabNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphTabNameDlg)
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphTabNameDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphTabNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphTabNameDlg message handlers
