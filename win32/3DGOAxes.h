#if !defined(AFX_3DGOAXES_H__9BEB6905_E496_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_3DGOAXES_H__9BEB6905_E496_11D3_9D44_0050DA62956A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGOAxes.h : header file
//

#include "CCalculator.h"
#include "ColourPicker.h"
/////////////////////////////////////////////////////////////////////////////
// C3DGOAxes dialog

class C3DGOAxes : public CPropertyPage
{
	DECLARE_DYNCREATE(C3DGOAxes)

// Construction
public:
	int m_Mode;
	void UpdateGraphMode();
	C3DGOAxes();
	~C3DGOAxes();

	CCalculator *m_Calculator;

// Dialog Data
	//{{AFX_DATA(C3DGOAxes)
	enum { IDD = IDD_3DGRAPH_AXIS };
	BOOL	m_AxisOn;
	BOOL	m_LabelsOn;
	UINT	m_AxisWidth;
	CString	m_XOrigin;
	CString	m_YOrigin;
	CString	m_ZOrigin;
	CString	m_Angle;
	CColourPicker m_Xcolor;
	CColourPicker m_Ycolor;
	CColourPicker m_Zcolor;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C3DGOAxes)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C3DGOAxes)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusXOrigin();
	afx_msg void OnKillfocusYOrigin();
	afx_msg void OnKillfocusZOrigin();	
	afx_msg void OnKillfocusAngle();
	afx_msg void OnChangeXOrigin();
	afx_msg void OnChangeYOrigin();
	afx_msg void OnChangeZOrigin();
	afx_msg void OnChangeAngle();
	afx_msg void OnChangeAxisOn();
	afx_msg void OnChangeLabelsOn();
	afx_msg void OnChangeAxisWidth();
	afx_msg void OnXColor();
	afx_msg void OnYColor();
	afx_msg void OnZColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	void SetEnabledFields(int bEnabled);
	void ComputeValue(UINT field);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGOAXES_H__9BEB6905_E496_11D3_9D44_0050DA62956A__INCLUDED_)
