// 3DGraphOptions.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGraphOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DGraphOptions

IMPLEMENT_DYNAMIC(C3DGraphOptions, CPropertySheet)

C3DGraphOptions::C3DGraphOptions(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

C3DGraphOptions::C3DGraphOptions(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_Equations);
	AddPage(&m_RangeWire);
	AddPage(&m_Axis);
	AddPage(&m_Ticks);
	m_StartTab = 0;
}

C3DGraphOptions::~C3DGraphOptions()
{
}


BEGIN_MESSAGE_MAP(C3DGraphOptions, CPropertySheet)
	//{{AFX_MSG_MAP(C3DGraphOptions)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGraphOptions message handlers

BOOL C3DGraphOptions::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	/*CWnd* pWnd = GetDlgItem(IDHELP);
	if(pWnd)
		pWnd->ShowWindow(FALSE);

	CRect rc;
	pWnd = GetDlgItem(IDOK);     
	pWnd->GetWindowRect(&rc);  
	rc.left += 81;  
	rc.right += 81;
	ScreenToClient(&rc);
    pWnd->MoveWindow(&rc);

	pWnd = GetDlgItem(IDCANCEL);     
	pWnd->GetWindowRect(&rc);  
	rc.left += 81;  
	rc.right += 81;
	ScreenToClient(&rc);
    pWnd->MoveWindow(&rc);

	pWnd = GetDlgItem(ID_APPLY_NOW);     
	pWnd->GetWindowRect(&rc);  
	rc.left += 81;  
	rc.right += 81;
	ScreenToClient(&rc);
    pWnd->MoveWindow(&rc);*/

	SetActivePage(m_StartTab);

	UpdateGraphMode(m_Equations.m_Mode);
	
	return bResult;
}

void C3DGraphOptions::UpdateGraphMode(int mode)
{
	m_Axis.m_Mode = mode;
	m_Ticks.m_Mode = mode;
	m_RangeWire.m_Mode = mode;
}