#if !defined(AFX_GRAPHTABNAMEDLG_H__DC9855C0_D40D_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRAPHTABNAMEDLG_H__DC9855C0_D40D_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphTabNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphTabNameDlg dialog

class CGraphTabNameDlg : public CDialog
{
// Construction
public:
	CGraphTabNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphTabNameDlg)
	enum { IDD = IDD_RENAME_GRAPH };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphTabNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphTabNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHTABNAMEDLG_H__DC9855C0_D40D_11D2_98BC_00104B0D20F9__INCLUDED_)
