#if !defined(AFX_CALCULATORVIEW_H__90096E1E_C105_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_CALCULATORVIEW_H__90096E1E_C105_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GraphView.h"

// CalculatorView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalculatorView

class CCalculatorView : public CPropertySheet
{
	DECLARE_DYNAMIC(CCalculatorView)

// Construction
public:
	CCalculatorView(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCalculatorView(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CImageList m_imageTab;

// Attributes
public:
	bool initialzed;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorView)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg LRESULT OnResizePage(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CRect m_PageRect;
	virtual ~CCalculatorView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalculatorView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void Initialization();

	CFont m_fontTab;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORVIEW_H__90096E1E_C105_11D2_98BC_00104B0D20F9__INCLUDED_)
