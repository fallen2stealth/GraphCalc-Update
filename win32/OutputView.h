#if !defined(AFX_OUTPUTVIEW_H__C8EBFA78_B9F5_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_OUTPUTVIEW_H__C8EBFA78_B9F5_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCalculator.h"

enum EOutputEntry{EXPRESSION, LONG_OUTPUT, ANSWER, BASE};


// OutputView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OutputView dialog

class OutputView : public CPropertyPage
{
	DECLARE_DYNCREATE(OutputView)

// Construction
public:
	
	void SaveOutputToFile(CString strFile);
	void LoadOutput();
	void SaveOutput();
	void Print();
	void AddEntry(CString heading, CString body="");
	OutputView();
	~OutputView();
	
	void ClearOutput();
	void OnEnter(CString Formula, CCalculator &Calculator, CComboBox *FormulaCtrl);
	
	CHARFORMAT m_AnswerFont;
	CHARFORMAT m_LongOutputFont;
	CHARFORMAT m_ExpressionFont;
	CHARFORMAT m_BaseFont;

	LOGFONT m_LFAnswerFont;
	LOGFONT m_LFLongOutputFont;
	LOGFONT m_LFExpressionFont;
	LOGFONT m_LFBaseFont;

	bool m_LongOutput;
	bool m_fOutputWindow;

// Dialog Data
	//{{AFX_DATA(OutputView)
	enum { IDD = IDD_OUTPUT };
	CRichEditCtrl	m_Result;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(OutputView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(OutputView)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKillfocusOutput(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMenu m_MenuOutput;


	int m_TotalCharacters;
	void AddEntry(CString input, CString long_output, CString answer, CString base);
	CPrintInfo m_Info;
	void DisplayString(CString str, CHARFORMAT font, UINT align);
	void PrintString(CDC &dc, CRect &r, CString str, LOGFONT lgfont, COLORREF color, UINT align, UINT print_mode);
	LOGFONT GetPrintLogFont(EOutputEntry entry, CDC &dc);
	int FindMaxPageEntry(int start, CRect r, int right, CDC &dc);
	void AddAnswerString(CString str);
	void AddBaseString(CString str);
	void AddDetailedOutputString(CString str);
	void AddInputString(CString str);
	void PrintExpression(CDC &dc, CRect &r, CString str);
	void PrintLongOutput(CDC &dc, CRect &r, CString str);
	void PrintAnswer(CDC &dc, CRect &r, UINT i, UINT right);
	void PrintBase(CDC &dc, CRect &r, CString str);
	void SetPrintRectangle(CDC &dc, CRect &r, CString str);
//	void UpdateMenu(CMenu* pMenu);
	CArray<CString, CString> m_Expressions;
	CArray<CString, CString> m_LongOutputs;
	CArray<CString, CString> m_Answers;
	CArray<CString, CString> m_Bases;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTVIEW_H__C8EBFA78_B9F5_11D2_98BC_00104B0D20F9__INCLUDED_)
