#if !defined(AFX_2DCREATEANIMATIONSCRIPTDLG_H__993957C3_A40E_4914_B57F_00120E3B4538__INCLUDED_)
#define AFX_2DCREATEANIMATIONSCRIPTDLG_H__993957C3_A40E_4914_B57F_00120E3B4538__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DCreateAnimationScriptDlg.h : header file
//

enum {ANIMATION_TYPE_REALTIME=0, ANIMATION_TYPE_FRAMES};
enum {ANIMATION_RANGE_ONEWAY=0, ANIMATION_RANGE_LOOP};
enum {ANIMATION_RANGE_LOOP_X=0, ANIMATION_RANGE_LOOP_INFINITE};

/////////////////////////////////////////////////////////////////////////////
// C2DCreateAnimationScriptDlg dialog

class C2DCreateAnimationScriptDlg : public CDialog
{
// Construction
public:
	C2DCreateAnimationScriptDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C2DCreateAnimationScriptDlg)
	enum { IDD = IDD_2DGRAPH_CREATE_ANIMATION };
	int		m_nType;
	int		m_nRangeOption;
	int		m_nXTimes;
	UINT	m_nTimesThrough;
	BOOL	m_fRun;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DCreateAnimationScriptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DCreateAnimationScriptDlg)
	afx_msg void EnableDisableControls();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DCREATEANIMATIONSCRIPTDLG_H__993957C3_A40E_4914_B57F_00120E3B4538__INCLUDED_)
