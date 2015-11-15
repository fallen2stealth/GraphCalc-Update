#if !defined(AFX_GRAPHVIEW_H__C8EBFA40_B9F5_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRAPHVIEW_H__C8EBFA40_B9F5_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCalculator.h"
#include "OutputView.h"
#include "GraphOptions.h"	// Added by ClassView
#include "GraphEuclidean.h"
#include "GraphPolar.h"
#include "2DGraphParametric.h"
#include "Structs.h"
#include "2DNSliderDlg.h"
#include "FlatEditEq.h"
#include "EvaluateDlg.h"
#include "Print.h"	// Added by ClassView
// GraphView.h : header file
//

#define threshold 10000

// Constants used for displaying a graph
const int h_space(0);
const int v_space(0);
const long double min_increment(0.0000001);

#if !defined(PRINT_OPTIONS)
#define PRINT_OPTIONS
#define EQUATION_LIST_NOREPLOT_Y	75
#define EQUATION_LIST_NOREPLOT_X	175
#define EQUATION_LIST_REPLOT_Y	1.5
#define EQUATION_LIST_REPLOT_X	5
#endif

#if !defined (DISTSTATUSE)
#define DISTSTATUSE
enum DistStatusE {OFF, FIRST, SECOND, DONE};
#endif

#if !defined (DRAWE)
#define DRAWE
enum DrawE {BMP, SCRN, PRINT};
#endif

#if !defined (GRAPHSTYLE)
#define GRAPHSTYLE
enum LineStyleE {GRAPH_STYLE_LINE, GRAPH_STYLE_POINT};
struct SEquationStyle{
	LineStyleE line;
	int		   size;
};
#endif


#if !defined (LINESTYLE)
#define LINESTYLE
struct SLineStyle{
	COLORREF	color;
	int			size;
	};
#endif

#if !defined (INFOBARCTRL)
#define INFOBARCTRL

enum {GRAPH2D_INFOBAR_EQUATION_UPDATE=0, 
	   GRAPH2D_INFOBAR_EQUATIONS, 
	   GRAPH2D_INFOBAR_PARAMETRIC_EQS,
	   GRAPH2D_INFOBAR_CURSOR_POSITION, 
	   GRAPH2D_INFOBAR_TRACE, 
	   GRAPH2D_INFOBAR_AREA, 
	   GRAPH2D_INFOBAR_DISTANCE,
	   GRAPH2D_INFOBAR_GROUPS};

struct InfoBarCtrl
{
	UINT	nID;
	UINT	left;
	UINT	top;
	UINT	width;
	UINT	height;
};

struct InfoBarGroup
{
	UINT			start_y;
	UINT			height;
	bool			bOn;
	InfoBarCtrl*  	pCtrls;
};

struct InforBarEq{
	UINT nIDEqOn;
	UINT nIDEqStr;
};

struct InforBarParametricEq{
	UINT nIDEqOn;
	UINT nIDEqX;
	UINT nIDEqY;
	UINT nIDEqXLabel;
	UINT nIDEqYLabel;
};

enum {PARAMETRIC_EQ_NONE=0, PARAMETRIC_EQ_X, PARAMETRIC_EQ_Y};
	
#endif
	
/////////////////////////////////////////////////////////////////////////////
// CGraphView dialog

class CGraphView : public CPropertyPage
{
	DECLARE_DYNCREATE(CGraphView)

// Construction
public:	
	
	InfoBarGroup g_InfoBarGroups[GRAPH2D_INFOBAR_GROUPS];
	
	friend CGraphEuclidean;
	friend CGraphPolar;
	friend C2DGraphParametric;

	bool m_fNSliderOn;
	bool m_fToolbarOn;
	
	void OnSaveAsBitmap();
	void SaveBitmap(CString file);
	
	CGraphEuclidean m_EuclideanGraph;
	CGraphPolar		m_PolarGraph;
	C2DGraphParametric m_ParametricGraph;
	
	GraphOptions	*GrphOptionsDlg;
	bool			m_fSaveSettings;
	
	SPoint 	m_DrawFontSize;
	SPoint 	m_ActiveDrawFontSize;

	EGraphMode m_Mode;

	
	int ToolbarHeight();
	void ShowInfoBar(bool fShow=true);
	void PaintNow();
	void RePaintNow();
	void TangentLine(long double eq, long double x);
	void FindArea(int eq1, int eq2, long double Xmin, long double Xmax, bool fAbsolute=false);
	void FindDistance(int eq1, int eq2, long double Xmin, long double Xmax);
	void SetBackgroundColor(CString color);
	void SetAxisColor(CString color);
	void SetGridColor(CString color);
	void SetCoordinatesColor(CString color);
	void SetOtherTextColor(CString color);
	void SetAreaColor(CString color);
	void SetTraceState(bool fTrace)
		{
		if(fTrace != m_Trace) ToggleTrace();
		}
	void FindAreaOff()
		{
		m_FindArea = false;
		#ifdef GRAPH2D_INFOBAR
			SetInfoBarCtrlSet(GRAPH2D_INFOBAR_AREA, false);
		#endif
		}		

	void SetEquation(int eq, CString val, UINT xy=0);
	void EmptyAllEquations();
	void SetEquationState(int eq, bool val);
	void SetAllEquationState(bool val);
	void SetEquationColor(int eq, CString val);
	void CenterGraph(long double x, long double y);

	void SetCursorPositionState(bool fOn)
		{
		g_InfoBarGroups[GRAPH2D_INFOBAR_CURSOR_POSITION].bOn = m_CursorPos = fOn;

		#ifdef GRAPH2D_INFOBAR
			if(this->m_hWnd)
				SetInfoBarCtrlSet(GRAPH2D_INFOBAR_CURSOR_POSITION, fOn);
		#endif
		}
	
	void ValidateRanges();

	void ExpandEquations();
	void ExpandEquationsValidate();
	
	////////////////////////////////////////////////////////////////////////
	//////// MEMBER FUNCTIONS /////////
	///////////////////////////////////
	void DoCopy();

	CGraphView(CCalculator *Calc, OutputView* output);
	CGraphView();
	~CGraphView();

	void InitVariables(CCalculator *Calc, OutputView* output);
	bool IsDistanceOn();
	
	// Functions to handle some graphing things
	void GraphOff();
	void DataExchange();
	/////////////////////////////////////////////////

	// Functions called from menus via CGrphCalcDlg
	void OnGraphZoomInXY();
	void OnGraphZoomOutXY();
	void OnGraphZoomInX();
	void OnGraphZoomInY();
	void OnGraphZoomOutX();
	void OnGraphZoomOutY();
	void OnGraphZoomDecimal();
	void OnGraphZoomStandard();
	void OnGraphZoomTrig();
	void OnGraphZoomInteger();
	void OnGraphZoomFit();
	void OnGraphZoomPreviousRange();
	void OnGraphFindArea();
	void OnMenuGraphTrace();
	void Options(int tab);
	void OnGraphDistance();
	void OnTangentLine();
	void OnGraphEvaluate();
	void OnClearTangentLines();
	void OnCopyGraph();
	void OnGraphPrint();
	void On2DGraphAnalysisIntercepts();
	void On2DGraphAnalysisIntersectionof2equations();
	void OnCalculateMinMax();
	void OnAnalysisTable();
	void OnAnalysisNslider();
	void OnToolbar();
	void OnCreateAnimationScript();
	void CreateAnimationRealTimeScript(CString strFile, double nMin, double nStep, double nMax, UINT nLoopType, int nTimesThrough);
	void CreateAnimationFramesScript(CString strFile, double nMin, double nStep, double nMax, UINT nLoopType, int nTimesThrough);

	//////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER VARIABLES /////////
	///////////////////////////////////
	bool	m_fInfoBar;
	bool	m_Redraw;
	bool	m_Drawing;
	bool	m_FindArea;
	bool	m_Trace;
	int		m_graph_height;
	int		m_graph_width;
	EquationT m_Equations[10];
	CString m_astrEquationsRaw[10];
	
	DistStatusE m_Distance;
	
	////////////////////////////////

	COLORREF	m_BackgroundClr;
	COLORREF	m_CoordsClr;
	COLORREF	m_TextClr;
	COLORREF	m_AreaClr;
	int			m_nGridLabelInterval; // 0 means no labels  value must be integer >= 0
	int			m_ZoomPerc;
	long double m_ZoomDecPrec;
	long double m_AreaDeltaX;
	SEquationStyle		m_Style;
	bool		m_Grid;
	bool		m_FixedGrid;
	bool		m_Axis;
	bool		m_Coords;
	bool		m_Labels;
	bool		m_CursorPos;
	bool		m_FullWindow;

	SLineStyle m_AxisStyle;
	SLineStyle m_GridStyle;
	//////////////////////////////////
	

// Dialog Data
	//{{AFX_DATA(CGraphView)
	enum { IDD = IDD_GRAPH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	CFlatEditEq	m_aEquationEditCtrls[10];
	CFlatEditEq	m_aParametricEquationEditCtrls[10];
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGraphView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive( );
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	CToolBar m_wndToolBar;

	// Generated message map functions
	//{{AFX_MSG(CGraphView)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void ToggleTrace();
	afx_msg void OnUpdateGraphGraphTrace(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateGraphFindarea(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg UINT OnGetDlgCode();
	virtual BOOL OnInitDialog();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);

	
	afx_msg void On2DNSliderClosing(WPARAM wParam, LPARAM lParam);
#ifdef GRAPH2D_INFOBAR
	afx_msg void OnInfoBarEqOn();
	//afx_msg void OnInfoBarEqChange();
	//afx_msg void OnInfoBarEqUpdate();
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:	
	CDC* GetOffsetDC();
	void InitToolbar();
	void PositionToolbar();
	void InitializeInfoBarCtrlGroups();

#ifdef GRAPH2D_INFOBAR
	void PositionInfoBar();
	void RePositionInfoBar(CPoint ptStart);
	void UpdateInfoBar(bool fAll=false);
	void UpdateInfoBarCtrls(bool fAll=false);
	void SetInfoBarCtrlSet(UINT setID, bool fOn);
	void SetInfoBarRedraw(bool fRedraw=true);
	void InvalidateInfoBarCtrls();
	void UpdateInfoBarEquations();
	void UpdateInfoBarEquation(UINT eq);
	void UpdateInfoBarEquationColors();
	void InvalidateEquationColors();
	void UpdateInfoBarTrace();
	void UpdateInfoBarTraceCtrls();
	void UpdateInfoBarPolarCtrls();
	void UpdateInfoBarCursorPosition();
	CString GetCursorXStr();
	CString GetCursorYStr();
	CString GetCursorThetaStr();
	CString GetCursorRStr();
#endif

	bool ExpandEq(int eq, CString &expnEq);
	bool ExpandEq(int eq, CString &expnEq, CString strEqStack);
	void DrawTangentLine(int eq, CDC *pDC);
	

	void DrawEquations(CDC *pDC);
	COLORREF ColorLookup(CString color);
	void DrawEquationLegend(CDC *pDC, CRect eq_rect, const CSize &graph_size);
	void DrawEquationList(CDC *pDC, const CSize &graph_size, const CPoint &max_range, const CPoint &org);
	void DrawTitle(CDC *pDC, const CSize &graph_size);
	
	CPrint *m_PrintDlg;
	
	CString GetAreaStr();
	CString GetDistanceStr();
	CString GetTraceCoordsStr();
	void DrawText(CDC *pDC);
	
	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER FUNCTIONS /////////
	///////////////////////////////////

	void InitGraphOptions();

	// Functions for drawing graph
	void DrawGraph(CBitmap *bitmap);
	void DrawAll();
	void DrawGraphBitmap(CDC *pDC);

	CString GetCursorPosStr();

	//void DrawTangentLine(CDC *pDC, int eq);
	void DrawDistance(CDC *pDC);

	void DrawTrace(CDC *pDC);
	void DrawGrid(CDC *pDC);
	void DrawCoordsLabels(CDC *pDC);
	void DrawAxis(CDC *pDC);

	void DrawArea(CDC *pDC);
	CString GetDyDxStr(UINT nEq, long double x);
	//void GraphSeq(CDC *pDC);
	//void GraphPolar(CDC *pDC);

	void EraseDistance(CDC *pDC);
	//void GraphSimult( int num_points, long double x_ratio, long double y_ratio, long double increment, CClientDC *pDC);
	///////////////////////////////


	double GetXPixelIncrement();
	double GetYPixelIncrement();
	
	
	// Handle various interfaces with user manipulating graph view
	void KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int GetRegion(CPoint point);
	void ScrollZoom(short amount);
	void Pan(int rgn);
	void SetMyCursor(int rgn);
	void NextTraceEq(int direction);
	////////////////////////////////

	// Functions for editing current range
	void SwapPrevCurRanges();
	void SetPreviousRange();
	void StoreCurrentRange();
	void HandPan(int x_dpixels, int y_dpixels);
	void ZoomRect();
	void ZoomX(long double zoom_amount);
	void ZoomY(long double zoom_amount);
	void ZoomXY(long double zoom_amount);
	bool ValidateIncrement(long double Xmin, long double Xmax, 
						   long double Ymin, long double Ymax);
	////////////////////////////////

	// Functions for maping graph coordinates to screen cordinates
	int GraphToScreenX(long double x, int precision);	
	int GraphToScreenY(long double y);
	long double ScreenToGraphX(int x, int precision);
	long double ScreenToGraphY(int y);
	//int GraphToBitmapX(long double x, int precision);	
	//int GraphToBitmapY(long double y);
	///////////////////////////////////

	// MISC functions
	void UpdateMenu(CMenu* pMenu);
	void FormatDecimalToString(CString &str, long double num, int decplaces);
	void Integrate(bool fAbsolute=false);
	//long double DyDx(int eq, long double x);
	void InitTangentLine(int eq, long double x);
	
	//CString GetTangentEquation(int eq, long double x);
	

	C2DNSliderDlg *m_pSliderDlg;
	
	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER VARIABLES /////////
	///////////////////////////////////

	// variables used in drawing graph
	CRect		m_GraphThreshold;
	CRgn		m_GraphRgn;
	CBitmap		m_MemBitmap;
	CCalculator *m_Calculator;
	CPoint		m_cursor_pos;
	DrawE		m_GraphDestination;



	// handle zooming parameters
	bool		m_ButtonZoom;
	CPoint		m_ZoomPrevPt;
	CPoint		m_ZoomPt;

	CPoint		m_ptHandMove;
	///////////////////////////////

	// variables for tangent lines
	long double m_Tangent[10];
	bool m_TangentLine[10];
	////////////////////////////////

	// variables used in finding an area
	long double m_AreaXmin;
	long double m_AreaXmax;
	long double m_Area;
	int			m_AreaEq;
	int			m_AreaEq2;
	////////////////////////////////

	// variables for distance
	long double m_DistancePrevX;
	long double m_DistanceOneX;
	long double m_DistanceTwoX;
	int m_DistanceEqTwo;
	int m_DistanceEqOne;
	////////////////////////////////
	
	// variables for tracing
	int			m_TraceEq;
	int			m_PrevTraceEq;
	////////////////////////////////
	
	OutputView		*m_OutputView;
	UINT			m_PrevMsgTime;
	CMenu m_Menu2DGraph;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHVIEW_H__C8EBFA40_B9F5_11D2_98BC_00104B0D20F9__INCLUDED_)
