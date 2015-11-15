#if !defined(AFX_CATALOGDLG_H__32E53942_20BC_11D3_98BE_00104B0D20F9__INCLUDED_)
#define AFX_CATALOGDLG_H__32E53942_20BC_11D3_98BE_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CatalogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCatalogDlg dialog

class CCatalogDlg : public CDialog
{
// Construction
public:
	CCatalogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCatalogDlg)
	enum { IDD = IDD_CATALOG };
	CListBox	m_OperatorCtrl;
	CString	m_Operator;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatalogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCatalogDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATALOGDLG_H__32E53942_20BC_11D3_98BE_00104B0D20F9__INCLUDED_)
