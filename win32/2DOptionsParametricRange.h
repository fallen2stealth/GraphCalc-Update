#if !defined(AFX_2DOPTIONSPARAMETRICRANGE_H__655E317B_2EF4_4AE3_B85C_A00AC288A480__INCLUDED_)
#define AFX_2DOPTIONSPARAMETRICRANGE_H__655E317B_2EF4_4AE3_B85C_A00AC288A480__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DOptionsParametricRange.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsParametricRange dialog

class C2DOptionsParametricRange : public CPropertyPage
{
	DECLARE_DYNCREATE(C2DOptionsParametricRange)

// Construction
public:
	C2DOptionsParametricRange();
	~C2DOptionsParametricRange();

// Dialog Data
	//{{AFX_DATA(C2DOptionsParametricRange)
	enum { IDD = IDD_2DGRAPH_OPTIONS_PARAMETRIC_RANGE };
	CString	m_strTmax;
	CString	m_strTmin;
	CString	m_strTstep;
	CString	m_strXscl;
	CString	m_strXmax;
	CString	m_strXmin;
	CString	m_strYscl;
	CString	m_strYmax;
	CString	m_strYmin;
	//}}AFX_DATA

	long double	m_dTmax;
	long double	m_dTmin;
	long double	m_dTstep;
	long double	m_dXscl;
	long double	m_dXmax;
	long double	m_dXmin;
	long double	m_dYscl;
	long double	m_dYmax;
	long double	m_dYmin;
	bool m_fDirty;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C2DOptionsParametricRange)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C2DOptionsParametricRange)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusTmax();
	afx_msg void OnKillfocusTmin();
	afx_msg void OnKillfocusTstep();
	afx_msg void OnKillfocusXint();
	afx_msg void OnKillfocusXmax();
	afx_msg void OnKillfocusXmin();
	afx_msg void OnKillfocusYint();
	afx_msg void OnKillfocusYmax();
	afx_msg void OnKillfocusYmin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool ValidateRanges();
	bool ValidateFieldValues();
	bool ValidateField(UINT nID);
	long double GetFieldValue(UINT nID);
	void SetDirty();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DOPTIONSPARAMETRICRANGE_H__655E317B_2EF4_4AE3_B85C_A00AC288A480__INCLUDED_)
