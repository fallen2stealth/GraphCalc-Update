#if !defined(AFX_3DGRAPHEVALUATEDLG_H__EE07019C_207A_46BC_ACC6_0BBF094EF88B__INCLUDED_)
#define AFX_3DGRAPHEVALUATEDLG_H__EE07019C_207A_46BC_ACC6_0BBF094EF88B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGraphEvaluateDlg.h : header file
//

#include "CCalculator.h"
#include "Structs.h"

#if !defined(EGRAPHMODE)
#define EGRAPHMODE
enum EGraphMode{EUCLIDEAN, POLAR};
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DGraphEvaluateDlg dialog

class C3DGraphEvaluateDlg : public CDialog
{
// Construction
public:
	C3DGraphEvaluateDlg(CWnd* pParent = NULL);   // standard constructor

	void PassVars(S3DEquation *eqs, CCalculator *calc, EGraphMode mode);

// Dialog Data
	//{{AFX_DATA(C3DGraphEvaluateDlg)
	enum { IDD = IDD_3DGRAPH_EVALUATE };
	CComboBox	m_EqCtrl;
	int		m_iEq;
	CString	m_sEq;
	CString	m_sX;
	CString	m_sY;
	CString	m_sZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DGraphEvaluateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3DGraphEvaluateDlg)
	afx_msg void OnSelchangeEq();
	afx_msg void OnDropdownEq();
	afx_msg void OnChangeX();
	afx_msg void OnChangeY();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	void UpdateEq();
	void UpdateZ();
	EGraphMode m_Mode;
	S3DEquation *m_Eqs;
	CCalculator *m_Calculator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGRAPHEVALUATEDLG_H__EE07019C_207A_46BC_ACC6_0BBF094EF88B__INCLUDED_)
