#if !defined(AFX_INSERTUNITDLG_H__406D97C0_D708_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_INSERTUNITDLG_H__406D97C0_D708_11D2_98BC_00104B0D20F9__INCLUDED_

#include "CCalculator.h"	// Added by ClassView
#include "NewUnitCategoryDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertUnitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertUnitDlg dialog

class CInsertUnitDlg : public CDialog
{
// Construction
public:
	CCalculator *m_Calculator;
	CNewUnitCategoryDlg m_NewCategoryDlg;
	CInsertUnitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertUnitDlg)
	enum { IDD = IDD_INSERT_CONVERSION };
	CComboBox	m_TypeCtrl;
	CComboBox	m_CategoryCtrl;
	CString	m_BaseUnit;
	CString	m_Category;
	CString	m_Name;
	CString	m_Type;
	CString	m_Value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertUnitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertUnitDlg)
	afx_msg void OnKillfocusUnittype();
	afx_msg void OnKillfocusCategory();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_NewCat;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTUNITDLG_H__406D97C0_D708_11D2_98BC_00104B0D20F9__INCLUDED_)
