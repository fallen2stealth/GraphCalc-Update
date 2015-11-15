#if !defined(AFX_BUTTONSHADE_H__D56C8863_D29B_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_BUTTONSHADE_H__D56C8863_D29B_11D3_9D44_0050DA62956A__INCLUDED_

#include "3DGORenderMode.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonShade.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonShade window

class CButtonShade : public CButton
{
// Construction
public:
	CButtonShade();

// Attributes
public:
	C3DGORenderMode m_3DRenderDlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonShade)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ClearModified();
	virtual ~CButtonShade();
	bool OnClicked();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonShade)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void SetWindowSize();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSHADE_H__D56C8863_D29B_11D3_9D44_0050DA62956A__INCLUDED_)
