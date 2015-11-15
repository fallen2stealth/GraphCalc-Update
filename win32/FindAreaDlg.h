#if !defined(AFX_FINDAREADLG_H__2F633520_F779_11D2_98BD_00104B0D20F9__INCLUDED_)
#define AFX_FINDAREADLG_H__2F633520_F779_11D2_98BD_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindAreaDlg.h : header file
//
#include "CCalculator.h"
#include "graphview.h"

/////////////////////////////////////////////////////////////////////////////
// CFindAreaDlg dialog

class CFindAreaDlg : public CDialog
{
// Construction
public:
	CFindAreaDlg(CWnd* pParent = NULL);   // standard constructor
	PassEq(EquationT *eqs, CCalculator *calc);

// Dialog Data
	//{{AFX_DATA(CFindAreaDlg)
	enum { IDD = IDD_INTEGRATE };
	CButton	m_BetweenCtrl;
	CComboBox	m_Equation2Ctrl;
	CComboBox	m_EquationCtrl;
	int		m_Equation;
	int		m_Equation2;
	CString	m_Xmax;
	CString	m_Xmin;
	BOOL	m_Between;
	CString	m_EqString2;
	CString	m_EqString;
	BOOL	m_fAbsolute;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindAreaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindAreaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBetween();
	afx_msg void OnSelchangeEquation();
	afx_msg void OnSelchangeEquation2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEqs();
	void UpdateEqLists();
	EquationT *m_Eqs;
	CCalculator *m_Calculator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDAREADLG_H__2F633520_F779_11D2_98BD_00104B0D20F9__INCLUDED_)
