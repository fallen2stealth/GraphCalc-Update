#if !defined(AFX_3DGOTICKMARKS_H__7B65622C_E3FE_4294_9BC7_87829674328D__INCLUDED_)
#define AFX_3DGOTICKMARKS_H__7B65622C_E3FE_4294_9BC7_87829674328D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGOTickMarks.h : header file
//
#include "ColourPicker.h"
/////////////////////////////////////////////////////////////////////////////
// C3DGOTickMarks dialog

class C3DGOTickMarks : public CPropertyPage
{
	DECLARE_DYNCREATE(C3DGOTickMarks)

// Construction
public:
	int m_Mode;
	C3DGOTickMarks();
	~C3DGOTickMarks();
	void UpdateGraphMode();

// Dialog Data
	//{{AFX_DATA(C3DGOTickMarks)
	enum { IDD = IDD_3DGRAPH_TICKMARKS };
	BOOL	m_bTicksOn;
	UINT	m_iWidth;
	double	m_iLength;
	double	m_dXint;
	double	m_dYint;
	double	m_dZint;
	CColourPicker m_Xclr;
	CColourPicker m_Yclr;
	CColourPicker m_Zclr;
	int		m_ColorMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C3DGOTickMarks)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C3DGOTickMarks)
	afx_msg void OnChangeValue();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeWidth();
	afx_msg void OnClickedColorMode();
	afx_msg void OnXclr();
	afx_msg void OnYclr();
	afx_msg void OnZclr();
	afx_msg void OnChangeTicksOn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetEnabledFields();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGOTICKMARKS_H__7B65622C_E3FE_4294_9BC7_87829674328D__INCLUDED_)
