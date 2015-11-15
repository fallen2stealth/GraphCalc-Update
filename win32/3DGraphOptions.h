#if !defined(AFX_3DGRAPHOPTIONS_H__B638F3A5_D19E_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_3DGRAPHOPTIONS_H__B638F3A5_D19E_11D3_9D44_0050DA62956A__INCLUDED_

#include "3DGOEquations.h"	// Added by ClassView
#include "3DGOAxes.h"	// Added by ClassView
#include "3DGORangeAxisWire.h"	// Added by ClassView
#include "3DGOTickMarks.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGraphOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3DGraphOptions

class C3DGraphOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(C3DGraphOptions)

// Construction
public:
	C3DGraphOptions(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	C3DGraphOptions(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	void UpdateGraphMode(int mode);
	int m_StartTab;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DGraphOptions)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	C3DGOAxes m_Axis;
	C3DGORangeWire m_RangeWire;
	C3DGOEquations m_Equations;
	C3DGOTickMarks m_Ticks;

	virtual ~C3DGraphOptions();

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DGraphOptions)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGRAPHOPTIONS_H__B638F3A5_D19E_11D3_9D44_0050DA62956A__INCLUDED_)
