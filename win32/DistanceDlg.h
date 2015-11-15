#if !defined(AFX_DISTANCEDLG_H__5296AD88_4A97_11D3_98BE_00104B0D20F9__INCLUDED_)
#define AFX_DISTANCEDLG_H__5296AD88_4A97_11D3_98BE_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DistanceDlg.h : header file
//
#include "CCalculator.h"
#include "graphview.h"
/////////////////////////////////////////////////////////////////////////////
// CDistanceDlg dialog

class CDistanceDlg : public CDialog
{
// Construction
public:
	CDistanceDlg(CWnd* pParent = NULL);   // standard constructor
	void PassEq(EquationT *eqs, CCalculator *calc, EGraphMode mode);

// Dialog Data
	//{{AFX_DATA(CDistanceDlg)
	enum { IDD = IDD_DISTANCE };
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
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDistanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDistanceDlg)
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
	EGraphMode m_Mode;
	CCalculator *m_Calculator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISTANCEDLG_H__5296AD88_4A97_11D3_98BE_00104B0D20F9__INCLUDED_)
