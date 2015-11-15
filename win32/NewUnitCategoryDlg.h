#if !defined(AFX_NEWUNITCATEGORYDLG_H__3224A080_D737_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_NEWUNITCATEGORYDLG_H__3224A080_D737_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewUnitCategoryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewUnitCategoryDlg dialog

class CNewUnitCategoryDlg : public CDialog
{
// Construction
public:
	CNewUnitCategoryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewUnitCategoryDlg)
	enum { IDD = IDD_NEW_UNIT_CATEGORY };
	CString	m_BaseOne;
	CString	m_BaseTwo;
	CString	m_Category;
	CString	m_TypeOne;
	CString	m_TypeTwo;
	CString	m_Conversion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewUnitCategoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewUnitCategoryDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWUNITCATEGORYDLG_H__3224A080_D737_11D2_98BC_00104B0D20F9__INCLUDED_)
