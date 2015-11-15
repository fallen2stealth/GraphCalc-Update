#if !defined(AFX_OPTIONSDLG_H__79B17F5C_25C0_49F8_A0D6_1B8D3BA6A5CD__INCLUDED_)
#define AFX_OPTIONSDLG_H__79B17F5C_25C0_49F8_A0D6_1B8D3BA6A5CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CDialog
{
// Construction
public:
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS };
	BOOL	m_bDetailedOutput;
	BOOL	m_bSaveExprHistory;
	BOOL	m_bSaveOutputHistory;
	BOOL	m_bSaveSettings;
	CString	m_sScriptFile;
	CString	m_sSettingsFile;
	BOOL	m_bSoundEffects;
	BOOL	m_bStartupScript;
	BOOL	m_bTooltips;
	BOOL	m_bCommandErrors;
	BOOL	m_bDispScriptProgressDlg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnStartupScriptEnabled();
	afx_msg void OnSettingsBrowse();
	afx_msg void OnSaveSettings();
	afx_msg void OnScriptBrowse();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool GetFile(CString &file, char BASED_CODE *szFilter);
	bool m_bOk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__79B17F5C_25C0_49F8_A0D6_1B8D3BA6A5CD__INCLUDED_)
