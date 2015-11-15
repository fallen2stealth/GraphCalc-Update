#if !defined(AFX_SAVESCRIPTDLG_H__955B125E_9E86_46CF_8AAA_1D7B75295BE5__INCLUDED_)
#define AFX_SAVESCRIPTDLG_H__955B125E_9E86_46CF_8AAA_1D7B75295BE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveScriptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveScriptDlg dialog

class CSaveScriptDlg : public CDialog
{
// Construction
public:
	CSaveScriptDlg(CWnd* pParent = NULL);   // standard constructor
	CComboBox *m_pFormulaCtrl;

// Dialog Data
	//{{AFX_DATA(CSaveScriptDlg)
	enum { IDD = IDD_SAVE_COMMANDS };
	CListBox	m_CommandsCtrl;
	CString	m_sFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveScriptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveScriptDlg)
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVESCRIPTDLG_H__955B125E_9E86_46CF_8AAA_1D7B75295BE5__INCLUDED_)
