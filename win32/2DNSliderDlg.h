#if !defined(AFX_2DNSLIDERDLG_H__C8E145EC_78B2_40FC_8388_803EDDFE07D2__INCLUDED_)
#define AFX_2DNSLIDERDLG_H__C8E145EC_78B2_40FC_8388_803EDDFE07D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DNSliderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DNSliderDlg dialog

class C2DNSliderDlg : public CDialog
{
// Construction
public:
	C2DNSliderDlg(CWnd* pParent = NULL);   // standard constructor
	long double GetFieldValue(UINT nID);

// Dialog Data
	//{{AFX_DATA(C2DNSliderDlg)
	enum { IDD = IDD_2DGRAPH_N };
	double		m_dMin;
	double		m_dMax;
	double		m_dStep;
	UINT	m_cMilliseconds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2DNSliderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C2DNSliderDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeNMin();
	afx_msg void OnChangeNMax();
	afx_msg void OnChangeNStep();
	afx_msg void OnClose();
	afx_msg void OnKillfocusNMax();
	afx_msg void OnKillfocusNMin();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAnimate();
	afx_msg void OnChangeMilliseconds();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateSliderCtrl();
	void SetSliderValue(double val);
	void SetSliderRange();
	bool ValidateStep();


	CWnd *m_pParent;
	CRect m_positionRect;
	bool	m_fTimer;
	bool	m_fForwardAnimate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DNSLIDERDLG_H__C8E145EC_78B2_40FC_8388_803EDDFE07D2__INCLUDED_)
