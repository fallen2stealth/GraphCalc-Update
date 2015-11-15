#if !defined(AFX_EVALUATEDLG_H__21E95B4E_4819_11D3_98BE_00104B0D20F9__INCLUDED_)
#define AFX_EVALUATEDLG_H__21E95B4E_4819_11D3_98BE_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EvaluateDlg.h : header file
//

#include "CCalculator.h"

#if !defined(EGRAPHMODE)
#define EGRAPHMODE
enum EGraphMode{EUCLIDEAN, POLAR};
#endif

/////////////////////////////////////////////////////////////////////////////
// CEvaluateDlg dialog

class CEvaluateDlg : public CDialog
{
// Construction
public:
	CEvaluateDlg(CWnd* pParent = NULL);   // standard constructor
	void PassVars(EquationT *eqs, CCalculator *calc, EGraphMode mode);

// Dialog Data
	//{{AFX_DATA(CEvaluateDlg)
	enum { IDD = IDD_EVALUATE };
	CComboBox	m_EqCtrl;
	int	m_Eq;
	CString	m_X;
	CString	m_Y;
	CString	m_EqString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEvaluateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEvaluateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEq();
	afx_msg void OnChangeX();
	afx_msg void OnDropdownEq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEq();
	void UpdateY();
	EGraphMode m_Mode;
	EquationT *m_Eqs;
	CCalculator *m_Calculator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVALUATEDLG_H__21E95B4E_4819_11D3_98BE_00104B0D20F9__INCLUDED_)
