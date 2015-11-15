#if !defined(AFX_PROGRAMOPTIONS_H__1F9E2640_C394_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_PROGRAMOPTIONS_H__1F9E2640_C394_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgramOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgramOptions dialog

class CProgramOptions : public CDialog
{
// Construction
public:
	CProgramOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgramOptions)
	enum { IDD = IDD_PROG_OPTIONS };
	int		m_SndEffects;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgramOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgramOptions)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMOPTIONS_H__1F9E2640_C394_11D2_98BC_00104B0D20F9__INCLUDED_)
