#if !defined(AFX_3DGORENDERMODE_H__B638F3A3_D19E_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_3DGORENDERMODE_H__B638F3A3_D19E_11D3_9D44_0050DA62956A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGORenderMode.h : header file
//
#include "ColourPicker.h"
/////////////////////////////////////////////////////////////////////////////
// C3DGORenderMode dialog

class C3DGORenderMode : public CDialog
{
// Construction
public:
	int m_Mode;
	C3DGORenderMode(CWnd* pParent = NULL);   // standard constructor
	void SetModified(bool val);
	bool GetModified(){ return m_Modified; }

// Dialog Data
	//{{AFX_DATA(C3DGORenderMode)
	enum { IDD = IDD_3DGRAPH_RENDER };
	int		m_RenderMode;
	int		m_ShadingModel;
	CColourPicker m_XminYmin;
	CColourPicker m_XminYmax;
	CColourPicker m_XmaxYmin;
	CColourPicker m_XmaxYmax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DGORenderMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3DGORenderMode)
	afx_msg void OnXmaxYmaxColor();
	afx_msg void OnXmaxYminColor();
	afx_msg void OnXminYmaxColor();
	afx_msg void OnXminYminColor();
	afx_msg void OnPaint();
	afx_msg void OnShadingModel();
	afx_msg void OnShadingModelElevation();
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	virtual BOOL OnInitDialog();
	afx_msg void OnRenderMode();
	afx_msg void OnRenderSurfaceTopwires();
	afx_msg void OnRenderSurfaceWires();
	afx_msg void OnRenderSurfce();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);

private:
	void InvalidateSwatch();
	bool m_Modified;
	void EnableColors();
	CDC *m_GradientDC;
	void GenerateGradientSquare();
	void UpdateShadingMethod();

	int		m_PrevRenderMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGORENDERMODE_H__B638F3A3_D19E_11D3_9D44_0050DA62956A__INCLUDED_)
