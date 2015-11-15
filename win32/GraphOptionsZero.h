#if !defined(AFX_GRAPHOPTIONSZERO_H__49BDE141_B20F_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRAPHOPTIONSZERO_H__49BDE141_B20F_11D2_98BC_00104B0D20F9__INCLUDED_


//#include "GraphOptions.h"	// Added by ClassView
#include "ColourPicker.h"
#include "CCalculator.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "GraphView.h"	// Added by ClassView
// GraphOptionsZero.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// GraphOptionsZero dialog

class GraphOptionsZero : public CPropertyPage
{
	DECLARE_DYNCREATE(GraphOptionsZero)

// Construction
public:
	//GraphOptions *m_pGraphOptions;
	void InitOptions();
	GraphOptionsZero();
	~GraphOptionsZero();

	EGraphMode m_Mode;
	CCalculator *m_Calculator;
	bool m_fDirty;

// Dialog Data
	//{{AFX_DATA(GraphOptionsZero)
	enum { IDD = IDD_GRAPH_OPTIONS_0 };
	CColourPicker	m_ColorButton1;
	CColourPicker	m_ColorButton2;
	CColourPicker	m_ColorButton3;
	CColourPicker	m_ColorButton4;
	CColourPicker	m_ColorButton5;
	CColourPicker	m_ColorButton6;
	CColourPicker	m_ColorButton7;
	CColourPicker	m_ColorButton8;
	CColourPicker	m_ColorButton9;
	CColourPicker	m_ColorButton10;
	CEdit	m_ctrlY1;
	CEdit	m_ctrlY10;
	CEdit	m_ctrlY2;
	CEdit	m_ctrlY3;
	CEdit	m_ctrlY4;
	CEdit	m_ctrlY5;
	CEdit	m_ctrlY6;
	CEdit	m_ctrlY7;
	CEdit	m_ctrlY8;
	CEdit	m_ctrlY9;
	CString	m_Y1;
	CString	m_Y10;
	CString	m_Y2;
	CString	m_Y3;
	CString	m_Y4;
	CString	m_Y5;
	CString	m_Y6;
	CString	m_Y7;
	CString	m_Y8;
	CString	m_Y9;
	BOOL	m_Yon1;
	BOOL	m_Yon10;
	BOOL	m_Yon2;
	BOOL	m_Yon3;
	BOOL	m_Yon4;
	BOOL	m_Yon5;
	BOOL	m_Yon6;
	BOOL	m_Yon7;
	BOOL	m_Yon8;
	BOOL	m_Yon9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GraphOptionsZero)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GraphOptionsZero)
	virtual BOOL OnInitDialog();
	afx_msg void OnColorY1();
	afx_msg void OnColorY2();
	afx_msg void OnColorY3();
	afx_msg void OnColorY4();
	afx_msg void OnColorY5();
	afx_msg void OnColorY6();
	afx_msg void OnColorY7();
	afx_msg void OnColorY8();
	afx_msg void OnColorY9();
	afx_msg void OnColorY10();
	afx_msg void OnChangeEqy1();
	afx_msg void OnChangeEqy2();
	afx_msg void OnChangeEqy3();
	afx_msg void OnChangeEqy4();
	afx_msg void OnChangeEqy5();
	afx_msg void OnChangeEqy6();
	afx_msg void OnChangeEqy7();
	afx_msg void OnChangeEqy8();
	afx_msg void OnChangeEqy9();
	afx_msg void OnChangeEqy10();
	afx_msg void OnOnY1();
	afx_msg void OnOnY2();
	afx_msg void OnOnY3();
	afx_msg void OnOnY4();
	afx_msg void OnOnY5();
	afx_msg void OnOnY6();
	afx_msg void OnOnY7();
	afx_msg void OnOnY8();
	afx_msg void OnOnY9();
	afx_msg void OnOnY10();
	afx_msg void OnKillfocusEq1();
	afx_msg void OnKillfocusEq2();
	afx_msg void OnKillfocusEq3();
	afx_msg void OnKillfocusEq4();
	afx_msg void OnKillfocusEq5();
	afx_msg void OnKillfocusEq6();
	afx_msg void OnKillfocusEq7();
	afx_msg void OnKillfocusEq8();
	afx_msg void OnKillfocusEq9();
	afx_msg void OnKillfocusEq10();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	afx_msg void EnableDisableFn(UINT nID);
	
	DECLARE_MESSAGE_MAP()

private:
	void UpdateEqType();
	bool IsFunctionEnabled(int eq);
	
	void SetDirty();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHOPTIONSZERO_H__49BDE141_B20F_11D2_98BC_00104B0D20F9__INCLUDED_)
