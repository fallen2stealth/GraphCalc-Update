#if !defined(AFX_2DOPTIONSMODE_H__5216ED48_7080_45DB_9C62_F9C75B3607AE__INCLUDED_)
#define AFX_2DOPTIONSMODE_H__5216ED48_7080_45DB_9C62_F9C75B3607AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2DOptionsMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C2DOptionsMode dialog

class C2DOptionsMode : public CPropertyPage
{
	DECLARE_DYNCREATE(C2DOptionsMode)

// Construction
public:
	C2DOptionsMode();
	~C2DOptionsMode();
	bool m_fDirty;

// Dialog Data
	//{{AFX_DATA(C2DOptionsMode)
	enum { IDD = IDD_2DGRAPH_OPTIONS_MODE };
	int		m_nMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C2DOptionsMode)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C2DOptionsMode)
	afx_msg void OnMode();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	void SetDirty();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2DOPTIONSMODE_H__5216ED48_7080_45DB_9C62_F9C75B3607AE__INCLUDED_)
