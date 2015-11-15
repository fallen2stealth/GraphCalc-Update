#if !defined(AFX_2DEQINTERSECTIONDLG_H__A6E5077F_8B1D_4C71_B1A9_41F6D28A8D80__INCLUDED_)
#define AFX_2DEQINTERSECTIONDLG_H__A6E5077F_8B1D_4C71_B1A9_41F6D28A8D80__INCLUDED_

#include "CCalculator.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DEqIntersectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DEqIntersectionDlg dialog

class C2DEqIntersectionDlg : public CDialog
{
// Construction
public:
	C2DEqIntersectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C2DEqIntersectionDlg)
	enum { IDD = IDD_2DGRAPH_EQ_INTERSECTION };
	CComboBox	m_Eq1Ctrl;
	CComboBox	m_Eq2Ctrl;
	int		m_nEq1;
	int		m_nEq2;
	CString	m_strGuess;
	CString	m_strEq1;
	CString	m_strEq2;
	//}}AFX_DATA

	EquationT *m_Eqs;
	CString *m_astrEquations;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DEqIntersectionDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DEqIntersectionDlg)
	afx_msg void OnKillfocusGuess();
	afx_msg void OnSolve();
	afx_msg void OnSelchangeEquation1Picker();
	afx_msg void OnSelchangeEquation2Picker();
	virtual BOOL OnInitDialog();
	afx_msg void OnCenterGraph();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEqs();
	void UpdateEqLists();
	long double m_x, m_y;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DEQINTERSECTIONDLG_H__A6E5077F_8B1D_4C71_B1A9_41F6D28A8D80__INCLUDED_)
