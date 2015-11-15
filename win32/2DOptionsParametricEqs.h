#if !defined(AFX_2DOPTIONSPARAMETRICEQS_H__378ACFD1_F1E9_40C0_AA08_F075F88A45A1__INCLUDED_)
#define AFX_2DOPTIONSPARAMETRICEQS_H__378ACFD1_F1E9_40C0_AA08_F075F88A45A1__INCLUDED_

#include "ColourPicker.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DOptionsParametricEqs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsParametricEqs dialog

class C2DOptionsParametricEqs : public CPropertyPage
{
	DECLARE_DYNCREATE(C2DOptionsParametricEqs)

// Construction
public:
	C2DOptionsParametricEqs();
	~C2DOptionsParametricEqs();
	bool m_fDirty;

// Dialog Data
	//{{AFX_DATA(C2DOptionsParametricEqs)
	enum { IDD = IDD_2DGRAPH_OPTIONS_PARAMETRIC_EQUATIONS };
	CColourPicker	m_ColorButton[MAX_2D_PARAMETRIC_EQS];
	CString	m_strX[MAX_2D_PARAMETRIC_EQS];
	CString	m_strY[MAX_2D_PARAMETRIC_EQS];
	BOOL	m_fOn[MAX_2D_PARAMETRIC_EQS];
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C2DOptionsParametricEqs)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C2DOptionsParametricEqs)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnValueChanged();
	//}}AFX_MSG
	afx_msg void OnEqOnOff(UINT nID);
	afx_msg void OnColorButton(UINT nID);
	DECLARE_MESSAGE_MAP()

private:
	bool ValidateEquations();
	bool ValidateParametricEquation(UINT nIndex);

	void SetDirty();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DOPTIONSPARAMETRICEQS_H__378ACFD1_F1E9_40C0_AA08_F075F88A45A1__INCLUDED_)
