#if !defined(AFX_COMMANDDLG_H__2A897D44_270F_49AB_84FB_8694F2EE73D7__INCLUDED_)
#define AFX_COMMANDDLG_H__2A897D44_270F_49AB_84FB_8694F2EE73D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg dialog

class CCommandDlg : public CDialog
{
// Construction
public:
	CCommandDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommandDlg)
	enum { IDD = IDD_COMMANDS };
	CListBox	m_CommandCtrl;
	CString	m_sCommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommandDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDDLG_H__2A897D44_270F_49AB_84FB_8694F2EE73D7__INCLUDED_)
