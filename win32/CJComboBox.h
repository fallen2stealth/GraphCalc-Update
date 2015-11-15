#if !defined(CJCOMBOBOX_H_INCLUDED)
#define CJCOMBOBOX_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FC_DRAWNORMAL	0x00000001
#define FC_DRAWRAISED	0x00000002
#define FC_DRAWPRESSD	0x00000004

/////////////////////////////////////////////////////////////////////////////
// CCJComboBox window

class CCJComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CCJComboBox)

// Construction
public:
	CCJComboBox();

// Attributes
public:
	bool m_bLBtnDown;

// Operations
public:
	void DrawCombo(DWORD dwStyle, COLORREF clrTopLeft, COLORREF clrBottomRight);
	int Offset();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCJComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCJComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCJComboBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(CJCOMBOBOX_H_INCLUDED)
