#if !defined(AFX_GRAPHOPTIONSONE_H__50D4ADD5_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRAPHOPTIONSONE_H__50D4ADD5_B16E_11D2_98BC_00104B0D20F9__INCLUDED_

#include "CCalculator.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphOptionsOne.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GraphOptionsOne dialog

class GraphOptionsOne : public CPropertyPage
{
	DECLARE_DYNCREATE(GraphOptionsOne)

// Construction
public:
	GraphOptionsOne();
	~GraphOptionsOne();

	CCalculator *m_Calculator;
	bool m_fDirty;

// Dialog Data
	//{{AFX_DATA(GraphOptionsOne)
	enum { IDD = IDD_GRAPH_OPTIONS_1 };
	CString	m_Xscl;
	CString	m_Xmax;
	CString	m_Xmin;
	CString	m_Yscl;
	CString	m_Ymax;
	CString	m_Ymin;
	int	m_AreaPrec;
	int		m_LinePrec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GraphOptionsOne)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GraphOptionsOne)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusXint();
	afx_msg void OnKillfocusXmax();
	afx_msg void OnKillfocusXmin();
	afx_msg void OnKillfocusYint();
	afx_msg void OnKillfocusYmax();
	afx_msg void OnKillfocusYmin();
	afx_msg void OnChangeXint();
	afx_msg void OnChangeXmax();
	afx_msg void OnChangeXmin();
	afx_msg void OnChangeYint();
	afx_msg void OnChangeYmax();
	afx_msg void OnChangeYmin();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetDirty();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHOPTIONSONE_H__50D4ADD5_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
