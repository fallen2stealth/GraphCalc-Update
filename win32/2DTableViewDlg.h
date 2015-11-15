#if !defined(AFX_2DTABLEVIEWDLG_H__ECB92CD9_963E_4AD6_82E3_3B763F74512B__INCLUDED_)
#define AFX_2DTABLEVIEWDLG_H__ECB92CD9_963E_4AD6_82E3_3B763F74512B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DTableViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DTableViewDlg dialog

class C2DTableViewDlg : public CDialog
{
// Construction
public:
	C2DTableViewDlg(CWnd* pParent = NULL);   // standard constructor
	~C2DTableViewDlg();

// Dialog Data
	//{{AFX_DATA(C2DTableViewDlg)
	enum { IDD = IDD_2DGRAPH_TABLEVIEW };
	CListCtrl	m_ctrlTableList;
	//}}AFX_DATA

	EquationT 	*m_Eqs;
	CString 	*m_astrEquations;
	EGraphMode 	m_Mode;
	long double m_ldMin;
	long double m_ldMax;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DTableViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DTableViewDlg)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnHelpButton();
	afx_msg void OnHelp();
	afx_msg void OnExport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ExportToCSV(CString strFile);
	long double ComputeValue(UINT field);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DTABLEVIEWDLG_H__ECB92CD9_963E_4AD6_82E3_3B763F74512B__INCLUDED_)
