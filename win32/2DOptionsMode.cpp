// 2DOptionsMode.cpp : implementation file
//

#include "stdafx.h"
#include "grphcalc.h"
#include "2DOptionsMode.h"
#include "GraphOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsMode property page

IMPLEMENT_DYNCREATE(C2DOptionsMode, CPropertyPage)

C2DOptionsMode::C2DOptionsMode() : CPropertyPage(C2DOptionsMode::IDD)
{
	//{{AFX_DATA_INIT(C2DOptionsMode)
	m_nMode = -1;
	//}}AFX_DATA_INIT

	m_fDirty = false;
}

C2DOptionsMode::~C2DOptionsMode()
{
}

void C2DOptionsMode::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2DOptionsMode)
	DDX_Radio(pDX, IDC_MODE, m_nMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2DOptionsMode, CPropertyPage)
	//{{AFX_MSG_MAP(C2DOptionsMode)
	ON_BN_CLICKED(IDC_MODE, OnMode)
	ON_BN_CLICKED(IDC_MODE2, OnMode)
	ON_BN_CLICKED(IDC_MODE3, OnMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsMode message handlers
void C2DOptionsMode::SetDirty() 
{
	m_fDirty = true;
	SetModified(true);
}

void C2DOptionsMode::OnMode() 
{
	UpdateData();
	GraphOptions *pWnd = (GraphOptions*)GetParent();
	pWnd->UpdateGraphMode(m_nMode);
	SetDirty() ;
}

BOOL C2DOptionsMode::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// we need to get all the tabs set up correctly
	GraphOptions *pWnd = (GraphOptions*)GetParent();
	pWnd->UpdateGraphMode(m_nMode);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL C2DOptionsMode::OnApply() 
{
	if(m_fDirty)
	{
		CDialog* pDlg = STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
		m_fDirty = false;
	}
	
	return CPropertyPage::OnApply();
}
