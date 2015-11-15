#if !defined(AFX_GRAPHOPTIONSPOLAR_H__D3407960_E22D_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_GRAPHOPTIONSPOLAR_H__D3407960_E22D_11D3_9D44_0050DA62956A__INCLUDED_

#include "CCalculator.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphOptionsPolar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphOptionsPolar dialog

class CGraphOptionsPolar : public CPropertyPage
{
	DECLARE_DYNCREATE(CGraphOptionsPolar)

// Construction
public:
	CGraphOptionsPolar();
	~CGraphOptionsPolar();

	CCalculator *m_Calculator;
	bool m_fDirty;

// Dialog Data
	//{{AFX_DATA(CGraphOptionsPolar)
	enum { IDD = IDD_GRAPH_OPTIONS_POLAR };
	CString	m_GridAngle;
	CString	m_GridSpacing;
	CString	m_ThetaMax;
	CString	m_ThetaMin;
	CString	m_ThetaStep;
	CString	m_Xmax;
	CString	m_Xmin;
	CString	m_Ymax;
	CString	m_Ymin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGraphOptionsPolar)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGraphOptionsPolar)
	afx_msg void OnKillfocusYmin();
	afx_msg void OnKillfocusYmax();
	afx_msg void OnKillfocusXmin();
	afx_msg void OnKillfocusXmax();
	afx_msg void OnKillfocusThetamin();
	afx_msg void OnKillfocusThetamax();
	afx_msg void OnKillfocusThetastep();
	afx_msg void OnChangeYmin();
	afx_msg void OnChangeYmax();
	afx_msg void OnChangeXmin();
	afx_msg void OnChangeXmax();
	afx_msg void OnChangeThetastep();
	afx_msg void OnChangeThetamin();
	afx_msg void OnChangeThetamax();
	afx_msg void OnKillfocusGridangle();
	afx_msg void OnChangeGridangle();
	afx_msg void OnChangeGridspacing();
	afx_msg void OnKillfocusGridspacing();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateValue(UINT field);
	
	void SetDirty();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHOPTIONSPOLAR_H__D3407960_E22D_11D3_9D44_0050DA62956A__INCLUDED_)
