#if !defined(AFX_GRAPHOPTIONSTWO_H__50D4ADD7_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRAPHOPTIONSTWO_H__50D4ADD7_B16E_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphOptionsTwo.h : header file
//
#include "ColourPicker.h"
#include "CCalculator.h"
/////////////////////////////////////////////////////////////////////////////
// GraphOptionsTwo dialog

class GraphOptionsTwo : public CPropertyPage
{
	DECLARE_DYNCREATE(GraphOptionsTwo)

// Construction
public:
	GraphOptionsTwo();
	~GraphOptionsTwo();
	CCalculator *m_Calculator;
	bool m_fDirty;

// Dialog Data
	//{{AFX_DATA(GraphOptionsTwo)
	enum { IDD = IDD_GRAPH_OPTIONS_2 };
	CColourPicker m_BackgroundClr;
	CColourPicker m_AxisClr;
	CColourPicker m_GridClr;
	CColourPicker m_CoordsClr;
	CColourPicker m_TextClr;
	CColourPicker m_AreaClr;
	BOOL	m_Axis;
	BOOL	m_Coords;
	BOOL	m_Labels;
	BOOL	m_Grid;
	int		m_Width;
	int		m_ZoomPerc;
	double	m_ZoomDecPrec;
	BOOL	m_CursorPos;
	int		m_Style;
	int		m_GridSize;
	int		m_AxisSize;
	BOOL	m_FixedGrid;
	CString	m_strFontSize;
	BOOL	m_fGridLabels;
	int		m_nGridLabelInterval;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GraphOptionsTwo)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GraphOptionsTwo)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnGrid();
	afx_msg void OnAxis();
	afx_msg void OnCoords();
	afx_msg void OnLabels();
	afx_msg void OnChangeWidth();
	afx_msg void OnChangeZoomDecPrec();
	afx_msg void OnColorAxis();
	afx_msg void OnColorBackground();
	afx_msg void OnColorCoords();
	afx_msg void OnColorGrid();
	afx_msg void OnColorText();
	afx_msg void OnColorArea();
	afx_msg void OnCursorPos();
	afx_msg void OnStyle();
	afx_msg void OnChangeAxisSize();
	afx_msg void OnChangeGridSize();
	afx_msg void OnChangeFixedGrid();
	afx_msg void OnChangeFontSize();
	afx_msg void OnGridLabels();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetDirty();
	
	void Grid(bool fDirty);
	void Axis(bool fDirty);
	void Coords(bool fDirty);
	void Style(bool fDirty);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHOPTIONSTWO_H__50D4ADD7_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
