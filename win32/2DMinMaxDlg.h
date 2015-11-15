#if !defined(AFX_2DMINMAXDLG_H__4CE49197_090A_4DE6_87BC_81B53676D879__INCLUDED_)
#define AFX_2DMINMAXDLG_H__4CE49197_090A_4DE6_87BC_81B53676D879__INCLUDED_

#include "CCalculator.h"
extern CCalculator *g_Calculator;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DMinMaxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DMinMaxDlg dialog

class C2DMinMaxDlg : public CDialog
{
// Construction
public:
	C2DMinMaxDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C2DMinMaxDlg)
	enum { IDD = IDD_2DGRAPH_EQ_MINMAX };
	CComboBox	m_EqCtrl;
	int		m_nEq;
	CString	m_strMax;
	CString	m_strMin;
	CString	m_strEq;
	//}}AFX_DATA

	EquationT 	*m_Eqs;
	CString 	*m_astrEquations;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DMinMaxDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DMinMaxDlg)
	afx_msg void OnSolve();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEquationPicker();
	afx_msg void OnKillfocusMin();
	afx_msg void OnKillfocusMax();
	afx_msg void OnCenterGraph();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEq();

	long double m_x, m_y;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DMINMAXDLG_H__4CE49197_090A_4DE6_87BC_81B53676D879__INCLUDED_)
