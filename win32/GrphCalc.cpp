// GrphCalc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "GrphCalcDlg.h"
#include "globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGrphCalcApp

BEGIN_MESSAGE_MAP(CGrphCalcApp, CWinApp)
	//{{AFX_MSG_MAP(CGrphCalcApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrphCalcApp construction

CGrphCalcApp::CGrphCalcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	free((void*)m_pszProfileName);
	m_pszProfileName=_tcsdup(_T("graphcalc.ini"));

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGrphCalcApp object

CGrphCalcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGrphCalcApp initialization

BOOL CGrphCalcApp::InitInstance()
{

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	//SetRegistryKey("GraphCalc");
	//SetDialogBkColor();        
	//SetDialogBkColor(RGB(192, 192, 192), RGB(0, 0, 0));
		
	AfxInitRichEdit();

	Enable3dControls();			// Call this when using MFC in a shared DLL
	
	// needed for accelerator keys
	ghAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	CGrphCalcDlg dlg;
	m_pMainWnd = &dlg;

	//m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	//RegisterShellFileTypes();

	int nResponse = dlg.DoModal();
	

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CGrphCalcApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
	if (code < 0)
		CWinApp::ProcessMessageFilter(code, lpMsg);
	
	if (ghDlg && ghAccelTable)
	{
		if (::TranslateAccelerator(ghDlg, ghAccelTable, lpMsg))
			return(TRUE);
	}
	
	return CWinApp::ProcessMessageFilter(code, lpMsg);
}

int CGrphCalcApp::ExitInstance()
{
	return CWinApp::ExitInstance();

}



BOOL CGrphCalcApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::OnIdle(lCount);
}
