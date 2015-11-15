#if !defined(AFX_GRAPHOPTIONS_H__50D4ADD6_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRAPHOPTIONS_H__50D4ADD6_B16E_11D2_98BC_00104B0D20F9__INCLUDED_

#include "GraphOptionsOne.h"	// Added by ClassView
#include "GraphOptionsTwo.h"	// Added by ClassView
#include "GraphOptionsZero.h"	// Added by ClassView
#include "GraphOptionsPolar.h"	// Added by ClassView
#include "2DOptionsMode.h"
#include "2DOptionsParametricEqs.h"
#include "2DOptionsParametricRange.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GraphOptions

class GraphOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(GraphOptions)

// Construction
public:
	GraphOptions(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	GraphOptions(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:
	void UpdateGraphMode(int mode);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GraphOptions)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_StartTab;

	C2DOptionsMode m_Mode;
	C2DOptionsParametricEqs m_ParametricEqs;
	C2DOptionsParametricRange m_ParametricRange;
	CGraphOptionsPolar m_PolarRange;
	GraphOptionsZero m_GOP0;
	GraphOptionsTwo m_GOP2;
	GraphOptionsOne m_GOP1;
	virtual ~GraphOptions();

	// Generated message map functions
protected:
	//{{AFX_MSG(GraphOptions)
		// NOTE - the ClassWizard will add and remove member functions here.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int		m_ActiveRangeTab;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHOPTIONS_H__50D4ADD6_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
