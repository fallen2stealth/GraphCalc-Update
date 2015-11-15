#if !defined(AFX_EQUATIONSOLVERDLG_H__066963F9_EB1D_44A9_9946_917359983E48__INCLUDED_)
#define AFX_EQUATIONSOLVERDLG_H__066963F9_EB1D_44A9_9946_917359983E48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EquationSolverDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEquationSolverDlg dialog

class CEquationSolverDlg : public CDialog
{
// Construction
public:
	CEquationSolverDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEquationSolverDlg)
	enum { IDD = IDD_EQUATION_SOLVER };
	CString	m_strEq;
	CString	m_strGuess;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquationSolverDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEquationSolverDlg)
	afx_msg void OnSolve();
	afx_msg void OnKillfocusGuess();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long double Solve(CString eq, CString var, double min, double max);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EQUATIONSOLVERDLG_H__066963F9_EB1D_44A9_9946_917359983E48__INCLUDED_)
