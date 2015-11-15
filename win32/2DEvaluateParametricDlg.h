#if !defined(AFX_2DEVALUATEPARAMETRICDLG_H__B1EDC51A_D225_48DD_A354_2A1DF7B960CE__INCLUDED_)
#define AFX_2DEVALUATEPARAMETRICDLG_H__B1EDC51A_D225_48DD_A354_2A1DF7B960CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DEvaluateParametricDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DEvaluateParametricDlg dialog

class C2DEvaluateParametricDlg : public CDialog
{
// Construction
public:
  	ParametricEquationT *m_Eqs;
  	
	C2DEvaluateParametricDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C2DEvaluateParametricDlg)
	enum { IDD = IDD_2DGRAPH_EVALUATE_PARAMETRIC };
	int	m_nEq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DEvaluateParametricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DEvaluateParametricDlg)
	afx_msg void OnSelchangeEq();
	afx_msg void OnChangeT();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DEVALUATEPARAMETRICDLG_H__B1EDC51A_D225_48DD_A354_2A1DF7B960CE__INCLUDED_)
