#if !defined(AFX_TANGENTDLG_H__8C5EB481_4840_11D3_98BE_00104B0D20F9__INCLUDED_)
#define AFX_TANGENTDLG_H__8C5EB481_4840_11D3_98BE_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TangentDlg.h : header file
//
#include "CCalculator.h"
#include "graphview.h"
/////////////////////////////////////////////////////////////////////////////
// CTangentDlg dialog

class CTangentDlg : public CDialog
{
// Construction
public:
	void PassEq(EquationT *eqs, CCalculator *calc, EGraphMode mode);
	CTangentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTangentDlg)
	enum { IDD = IDD_TANGENT };
	CComboBox	m_EqCtrl;
	int	m_Eq;
	CString	m_X;
	CString	m_EqString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTangentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTangentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEq();
	EGraphMode m_Mode;
	EquationT *m_Eqs;
	CCalculator *m_Calculator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TANGENTDLG_H__8C5EB481_4840_11D3_98BE_00104B0D20F9__INCLUDED_)
