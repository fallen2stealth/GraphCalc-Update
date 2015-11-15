#if !defined(AFX_PROMPTVALDLG_H__E091BA28_F834_40A2_8407_5DECF1D9BF8C__INCLUDED_)
#define AFX_PROMPTVALDLG_H__E091BA28_F834_40A2_8407_5DECF1D9BF8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PromptValDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPromptValDlg dialog

class CPromptValDlg : public CDialog
{
// Construction
public:
	CPromptValDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_msg;
	CString m_var;
	
// Dialog Data
	//{{AFX_DATA(CPromptValDlg)
	enum { IDD = IDD_PROMPTVAL };
	CString	m_strValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPromptValDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPromptValDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROMPTVALDLG_H__E091BA28_F834_40A2_8407_5DECF1D9BF8C__INCLUDED_)
