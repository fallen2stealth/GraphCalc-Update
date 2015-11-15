// GrphCalc.h : main header file for the GRPHCALC application
//

#if !defined(AFX_GRPHCALC_H__B5836224_B7D1_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRPHCALC_H__B5836224_B7D1_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "globals.h"

/////////////////////////////////////////////////////////////////////////////
// CGrphCalcApp:
// See GrphCalc.cpp for the implementation of this class
//

class CGrphCalcApp : public CWinApp
{
public:
	CGrphCalcApp();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrphCalcApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGrphCalcApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPHCALC_H__B5836224_B7D1_11D2_98BC_00104B0D20F9__INCLUDED_)
