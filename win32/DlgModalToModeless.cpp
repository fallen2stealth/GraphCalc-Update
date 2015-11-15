// DlgModalToModeless.cpp : implementation file
//

#include "stdafx.h"
#include "DlgModalToModeless.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgModalToModeless

IMPLEMENT_DYNCREATE(CDlgModalToModeless, CWinThread)

CDlgModalToModeless::CDlgModalToModeless()
{
	m_pDlg = NULL;
}


void CDlgModalToModeless::DoDialog(CDialog *pDlg)
{
	m_pDlg = pDlg;
	m_pMainWnd = pDlg;	// Set MainWnd to Dlg so it doesn't lock the app window
	CreateThread();
}


BOOL CDlgModalToModeless::InitInstance()
{
	if (m_pDlg)
		m_pDlg->DoModal();
	return FALSE;	// MFC will do the cleanup for us
}

int CDlgModalToModeless::ExitInstance()
{
	delete m_pDlg;
	//delete m_pMainWnd;
	//m_pDlg = NULL;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDlgModalToModeless, CWinThread)
	//{{AFX_MSG_MAP(CDlgModalToModeless)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgModalToModeless message handlers
