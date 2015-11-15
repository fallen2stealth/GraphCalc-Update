#if !defined(AFX_INSERTCONSTANTDLG_H__C39FE141_D4E5_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_INSERTCONSTANTDLG_H__C39FE141_D4E5_11D2_98BC_00104B0D20F9__INCLUDED_

#include "CCalculator.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertConstantDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertConstantDlg dialog

class CInsertConstantDlg : public CDialog
{
// Construction
public:
	CCalculator *m_Calculator;
	CInsertConstantDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertConstantDlg)
	enum { IDD = IDD_INSERT_CONSTANT };
	CComboBox	m_CategoryCtrl;
	CString	m_Category;
	CString	m_Name;
	CString	m_Value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertConstantDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertConstantDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTCONSTANTDLG_H__C39FE141_D4E5_11D2_98BC_00104B0D20F9__INCLUDED_)
