#if !defined(AFX_3DGOEQUATIONS_H__F2F4DF20_D11C_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_3DGOEQUATIONS_H__F2F4DF20_D11C_11D3_9D44_0050DA62956A__INCLUDED_

#include "ButtonShade.h"
#include "3DGORenderMode.h"	// Added by ClassView
#include "CCalculator.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGOEquations.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DGOEquations dialog

class C3DGOEquations : public CPropertyPage
{
	DECLARE_DYNCREATE(C3DGOEquations)

// Construction
public:
	CButtonShade m_EqRenderButton;
	CButtonShade m_Eq2RenderButton;
	CButtonShade m_Eq3RenderButton;
	CButtonShade m_Eq4RenderButton;
	CButtonShade m_Eq5RenderButton;
	CButtonShade m_Eq6RenderButton;
	C3DGOEquations();
	~C3DGOEquations();
	CCalculator *m_Calculator;

// Dialog Data
	//{{AFX_DATA(C3DGOEquations)
	enum { IDD = IDD_3DGRAPH_EQUATIONS };
	CString	m_Eq;
	CString	m_Eq2;
	CString	m_Eq3;
	CString	m_Eq4;
	CString	m_Eq5;
	CString	m_Eq6;
	BOOL	m_Eq_On;
	BOOL	m_Eq2_On;
	BOOL	m_Eq3_On;
	BOOL	m_Eq4_On;
	BOOL	m_Eq5_On;
	BOOL	m_Eq6_On;
	int		m_Mode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C3DGOEquations)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C3DGOEquations)
	afx_msg void OnEqShading();
	afx_msg void OnEqShading2();
	afx_msg void OnEqShading3();
	afx_msg void OnEqShading4();
	afx_msg void OnEqShading5();
	afx_msg void OnEqShading6();
	afx_msg void On3dEqOn();
	afx_msg void On3dEqOn2();
	afx_msg void On3dEqOn3();
	afx_msg void On3dEqOn4();
	afx_msg void On3dEqOn5();
	afx_msg void On3dEqOn6();
	afx_msg void OnChange3dEq();
	afx_msg void OnChange3dEq2();
	afx_msg void OnChange3dEq3();
	afx_msg void OnChange3dEq4();
	afx_msg void OnChange3dEq5();
	afx_msg void OnChange3dEq6();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocus3dEq();
	afx_msg void OnKillfocus3dEq2();
	afx_msg void OnKillfocus3dEq3();
	afx_msg void OnKillfocus3dEq4();
	afx_msg void OnKillfocus3dEq5();
	afx_msg void OnKillfocus3dEq6();
	afx_msg void OnClickedMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void UpdateEqStatus(UINT nID);

private:
	void Register(UINT on);
	void ClearEmptyEq(UINT eq, UINT eq_on);
	void AlterEqStatus(UINT on, UINT eq, UINT eq_shade);
	void UpdateEqType();
	int EqIDtoNum(UINT id);
	bool IsFunctionEnabled(int eq);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGOEQUATIONS_H__F2F4DF20_D11C_11D3_9D44_0050DA62956A__INCLUDED_)
