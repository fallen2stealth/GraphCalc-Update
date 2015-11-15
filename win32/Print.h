#if !defined(AFX_PRINT_H__C6234D40_8BFF_11D3_9CE9_00104B0D20F9__INCLUDED_)
#define AFX_PRINT_H__C6234D40_8BFF_11D3_9CE9_00104B0D20F9__INCLUDED_

#include "CCalculator.h"	// Added by ClassView
#include "stdafx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Print.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrint dialog

class CPrint : public CDialog
{
// Construction
public:
	int m_graph_height;
	int m_graph_width;
	CPrint(CWnd* pParent = NULL);   // standard constructor
	CPrintDialog m_PrintDlg;
	CCalculator *m_Calculator;

// Dialog Data
	//{{AFX_DATA(CPrint)
	enum { IDD = IDD_PRINT };
	BOOL	m_bCenter;
	BOOL	m_bEquations;
	CString	m_sHeight;
	CString	m_sHUnits;
	CString	m_sWidth;
	CString	m_sWUnits;
	BOOL	m_bTitleOn;
	CString	m_sTitle;
	int		m_iPageSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrint)
	afx_msg void OnSetup();
	afx_msg void OnTitleOn();
	afx_msg void OnCenter();
	afx_msg void OnEquations();
	afx_msg void OnChangeWidth();
	afx_msg void OnChangeHeight();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeWidthUnits();
	afx_msg void OnSelchangeHeightUnits();
	afx_msg void OnAutosize();
	afx_msg void OnPagesize();
	afx_msg void OnSpecify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InvalidatePreview();
	void UpdateSizeView();
	void SetDimensionsW(double w);
	void SetDimensionsH(double h);

	bool m_bRepaintPreview;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT_H__C6234D40_8BFF_11D3_9CE9_00104B0D20F9__INCLUDED_)
