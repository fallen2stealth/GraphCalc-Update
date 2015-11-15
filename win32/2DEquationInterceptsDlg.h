#if !defined(AFX_2DEQUATIONINTERCEPTSDLG_H__5C04963D_CD46_4D7D_AAFE_D68D46E081BC__INCLUDED_)
#define AFX_2DEQUATIONINTERCEPTSDLG_H__5C04963D_CD46_4D7D_AAFE_D68D46E081BC__INCLUDED_

#include "CCalculator.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DEquationInterceptsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DEquationInterceptsDlg dialog

class C2DEquationInterceptsDlg : public CDialog
{
// Construction
public:
	C2DEquationInterceptsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C2DEquationInterceptsDlg)
	enum { IDD = IDD_2DGRAPH_INTERCEPTS };
	CComboBox	m_EqCtrl;
	int		m_nEq;
	CString	m_strEq;
	CString	m_strGuess;
	CString	m_strXIntercept;
	CString	m_strYIntercept;
	//}}AFX_DATA

	EquationT *m_Eqs;
	CString *m_astrEquations;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DEquationInterceptsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DEquationInterceptsDlg)
	afx_msg void OnKillfocusGuess();
	afx_msg void OnSolve();
	afx_msg void OnSelchangeEquationPicker();
	afx_msg void OnDropdownEquationPicker();
	virtual BOOL OnInitDialog();
	afx_msg void OnCenterGraph();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEq();
	void UpdateYIntercept();
	long double m_x;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DEQUATIONINTERCEPTSDLG_H__5C04963D_CD46_4D7D_AAFE_D68D46E081BC__INCLUDED_)
