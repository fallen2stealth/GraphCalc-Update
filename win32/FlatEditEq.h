#if !defined(AFX_FLATEDITEQ_H__46708541_BF4D_4941_8456_FF98394019FE__INCLUDED_)
#define AFX_FLATEDITEQ_H__46708541_BF4D_4941_8456_FF98394019FE__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlatEditEq.h : header file
//

#include "FlatEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CFlatEditEq window

class CFlatEditEq : public CFlatEdit
{
// Construction
public:
	CFlatEditEq();

// Attributes
public:
	CWnd 	*m_pwndParent;
	int 	m_nEq;
	UINT	m_uParametricEq;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatEditEq)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFlatEditEq();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFlatEditEq)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ); 
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG 

	DECLARE_MESSAGE_MAP()

private:
	void UpdateGraph();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATEDITEQ_H__46708541_BF4D_4941_8456_FF98394019FE__INCLUDED_)
