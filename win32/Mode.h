#if !defined(AFX_MODE_H__627D8A80_B18F_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_MODE_H__627D8A80_B18F_11D2_98BC_00104B0D20F9__INCLUDED_

#include "CCalculator.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Mode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Mode dialog

class Mode : public CDialog
{
// Construction
public:
	Mode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Mode)
	enum { IDD = IDD_MODE };
	CEdit	m_FloatCtrl;
	int		m_TrigUnits;
	int		m_DecPlaces;
	BOOL	m_Float;
	int		m_OutputMode;
	int		m_Base;
	int		m_IntlMode;
	int		m_DecimalSeperatorAmount;
	CString	m_DecimalSpaceSeperator;
	BOOL	m_DecimalSeperator;
	CString	m_NumberSpaceSeperator;
	int		m_NumberSeperatorAmount;
	BOOL	m_NumberSeperator;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Mode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Mode)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnFloat();
	afx_msg void OnChangeBase();
	afx_msg void OnNumSep();
	afx_msg void OnDecSep();
	afx_msg void OnChangeDecChar();
	afx_msg void OnChangeNumChar();
	afx_msg void OnSelchangeNumFreq();
	afx_msg void OnSelchangeDecFreq();
	afx_msg void OnChangeDecimalPlaces();
	afx_msg void OnRadio3();
	afx_msg void OnIntlmode();
	afx_msg void OnScientific();
	afx_msg void OnRadio4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateSample();
	double m_Sample;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODE_H__627D8A80_B18F_11D2_98BC_00104B0D20F9__INCLUDED_)
