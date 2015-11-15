// NewUnitCategoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "NewUnitCategoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewUnitCategoryDlg dialog


CNewUnitCategoryDlg::CNewUnitCategoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewUnitCategoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewUnitCategoryDlg)
	m_BaseOne = _T("");
	m_BaseTwo = _T("");
	m_Category = _T("");
	m_TypeOne = _T("");
	m_TypeTwo = _T("");
	m_Conversion = _T("");
	//}}AFX_DATA_INIT
}


void CNewUnitCategoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewUnitCategoryDlg)
	DDX_Text(pDX, IDC_BASE_ONE, m_BaseOne);
	DDX_Text(pDX, IDC_BASE_TWO, m_BaseTwo);
	DDX_Text(pDX, IDC_CATEGORY, m_Category);
	DDX_Text(pDX, IDC_TYPE_ONE, m_TypeOne);
	DDX_Text(pDX, IDC_TYPE_TWO, m_TypeTwo);
	DDX_Text(pDX, IDC_BASE_CONVERSION, m_Conversion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewUnitCategoryDlg, CDialog)
	//{{AFX_MSG_MAP(CNewUnitCategoryDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewUnitCategoryDlg message handlers
