#if !defined(AFX_3DGORANGEAXISWIRE_H__B638F3A4_D19E_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_3DGORANGEAXISWIRE_H__B638F3A4_D19E_11D3_9D44_0050DA62956A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGORangeAxisWire.h : header file
//
#include "ColourPicker.h"
#include "CCalculator.h"
/////////////////////////////////////////////////////////////////////////////
// C3DGORangeWire dialog

class C3DGORangeWire : public CPropertyPage
{
	DECLARE_DYNCREATE(C3DGORangeWire)

// Construction
public:
	int m_Mode;
	void UpdateGraphMode();
	C3DGORangeWire();
	~C3DGORangeWire();
	CCalculator *m_Calculator;

// Dialog Data
	//{{AFX_DATA(C3DGORangeWire)
	enum { IDD = IDD_3DGRAPH_RANGE_AXIS_WIRE };
	UINT	m_WireWidth;
	CString	m_Xmax;
	CString	m_Xmin;
	CString	m_Ymax;
	CString	m_Ymin;
	UINT	m_YIntervals;
	UINT	m_XIntervals;
	UINT	m_WireInterval;
	CColourPicker m_BGcolor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C3DGORangeWire)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C3DGORangeWire)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusXmin();
	afx_msg void OnKillfocusXmax();
	afx_msg void OnKillfocusYmin();
	afx_msg void OnKillfocusYmax();
	afx_msg void OnChangeWireWidth();
	afx_msg void OnChangeWireInterval();
	afx_msg void OnChangeXInterval();
	afx_msg void OnChangeYInterval();
	afx_msg void OnChangeXmin();
	afx_msg void OnChangeXmax();
	afx_msg void OnChangeYmin();
	afx_msg void OnChangeYmax();
	afx_msg void OnBGColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateWireIntervalRange();
	void ComputeValue(UINT field);

	int m_max_interval;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGORANGEAXISWIRE_H__B638F3A4_D19E_11D3_9D44_0050DA62956A__INCLUDED_)
