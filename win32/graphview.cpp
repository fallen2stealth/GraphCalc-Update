// GraphView.cpp : implementation file
//
/*********************************************************/
// 
// Pre:
// Post:
// Return Value:
// Intent:
/*********************************************************/

#include "stdafx.h"
#include "GrphCalc.h"
#include "GraphView.h"
#include "FindAreaDlg.h"
#include "TangentDlg.h"
#include "DistanceDlg.h"
#include "Bitmap.h"
#include "Print.h"
#include "ClientCapture.h"
#include "GrphCalcDlg.h"
#include "2DEquationInterceptsDlg.h"
#include "2DEqIntersectionDlg.h"
#include "2DMinMaxDlg.h"
#include "2DTableViewDlg.h"
#include "Afxpriv.h" 
#include "2DCreateAnimationScriptDlg.h"
#include "2DEvaluateParametricDlg.h"

VariableT GetVariable(CString var, long double num){
	VariableT param;
	param.str = var;
	param.num = num;
	return param;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphView property page

IMPLEMENT_DYNCREATE(CGraphView, CPropertyPage)

/*********************************************************/
// CGraphView::CGraphView() : CPropertyPage(CGraphView::IDD)
// Pre: none
// Post: object is constructed
// Return Value: none
// Intent: to construct object
/*********************************************************/
CGraphView::CGraphView() : CPropertyPage(CGraphView::IDD)
{

	InitializeInfoBarCtrlGroups();
	m_pSliderDlg = 0;
	m_fNSliderOn = false;
	m_fToolbarOn = true;

	m_DrawFontSize.x = 6;
	m_DrawFontSize.y = 14;
	
	m_ActiveDrawFontSize.x = m_DrawFontSize.x;
	m_ActiveDrawFontSize.y = m_DrawFontSize.y;
	m_fSaveSettings = false;
}

/*********************************************************/
// CGraphView::CGraphView(CCalculator *Calc) : CPropertyPage(CGraphView::IDD)
// Pre: none
// Post: object is constructed, variables initialized
// Return Value: none
// Intent: to construct object
/*********************************************************/
CGraphView::CGraphView(CCalculator *Calc, OutputView* output) : CPropertyPage(CGraphView::IDD)
{
	//{{AFX_DATA_INIT(CGraphView)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	InitializeInfoBarCtrlGroups();
	m_pSliderDlg = 0;
	m_fNSliderOn = false;
	m_fToolbarOn = true;
	
	InitVariables(Calc, output);
	m_ActiveDrawFontSize.x = m_DrawFontSize.x;
	m_ActiveDrawFontSize.y = m_DrawFontSize.y;
	m_fSaveSettings = false;
}

/*********************************************************/
// CGraphView::~CGraphView()
// Pre: none
// Post: object is destructed
// Return Value: none
// Intent: to destruct object
/*********************************************************/
CGraphView::~CGraphView()
{
}

/*********************************************************/
// CGraphView::InitVariables(CCalculator *Calc)
// Pre: none
// Post: initializes all variables
// Return Value: none
// Intent: to initialize all values
/*********************************************************/
void CGraphView::InitVariables(CCalculator *Calc, OutputView* output)
{
	for(int m(0); m < 10; ++m){
		m_Tangent[m] = 0;
		m_TangentLine[m] = false;
	}

	m_Drawing = false;
	m_fInfoBar = true;
	m_nGridLabelInterval = 2;

	m_OutputView = output;
	m_Distance = OFF;
	m_GraphDestination = SCRN;

	m_Calculator = Calc;
	m_FullWindow = false;
	m_graph_height = 372;
	m_graph_width = 356;
	m_Trace = false;
	m_TraceEq = 0;
	m_ButtonZoom = false;
	m_FindArea = false;
	m_AreaDeltaX = 0.001;

	for(int i = 0; i < 10; ++i){
		m_Equations[i].disp = false;
		m_Equations[i].eq.Empty();
		m_astrEquationsRaw[i].Empty();
	}

	if(m_GraphRgn.m_hObject == NULL)
		m_GraphRgn.CreateRectRgn(h_space+1, v_space+1, h_space + m_graph_width - 1, v_space + m_graph_height - 1);
	else
		m_GraphRgn.SetRectRgn(h_space+1, v_space+1, h_space + m_graph_width - 1, v_space + m_graph_height - 1);

	m_GraphThreshold = CRect(h_space, v_space - threshold, h_space + m_graph_width, v_space + m_graph_height + threshold);

	///////// INIT GRAPH OPTIONS ////////////
	m_Equations[0].eq.Empty();
	m_Equations[0].disp = false;
	m_Equations[0].color = RGB(128,0,0);
	m_Equations[1].eq.Empty();
	m_Equations[1].disp = false;
	m_Equations[1].color = RGB(0,128,0);
	m_Equations[2].eq.Empty();
	m_Equations[2].disp = false;
	m_Equations[2].color = RGB(0,0,128);
	m_Equations[3].eq.Empty();
	m_Equations[3].disp = false;
	m_Equations[3].color = RGB(128,128,0);
	m_Equations[4].eq.Empty();
	m_Equations[4].disp = false;
	m_Equations[4].color = RGB(0,128,128);
	m_Equations[5].eq.Empty();
	m_Equations[5].disp = false;
	m_Equations[5].color = RGB(128,0,128);
	m_Equations[6].eq.Empty();
	m_Equations[6].disp = false;
	m_Equations[6].color = RGB(64,0,0);
	m_Equations[7].eq.Empty();
	m_Equations[7].disp = false;
	m_Equations[7].color = RGB(0,64,0);
	m_Equations[8].eq.Empty();
	m_Equations[8].disp = false;
	m_Equations[8].color = RGB(0,0,64);
	m_Equations[9].eq.Empty();
	m_Equations[9].disp = false;
	m_Equations[9].color = RGB(64,64,0);

	m_Style.line = GRAPH_STYLE_LINE;
	m_Style.size = 1;
	m_Grid = false;
	m_FixedGrid = true;
	m_Axis = true;
	m_Coords = true;
	m_Labels = false;
	m_CursorPos = true;
	m_ZoomPerc = 200;
	m_ZoomDecPrec = 0.05;

	m_GridStyle.color = RGB(215,215,215);
	m_GridStyle.size = 1;
	
	m_AxisStyle.color = RGB(90,90,90);
	m_AxisStyle.size = 1;

	m_BackgroundClr = RGB(255,255,255);
	m_CoordsClr = RGB(128,128,128);
	m_TextClr = RGB(192,128,128);
	m_AreaClr = RGB(192,192,230);
	
	m_Mode = EUCLIDEAN;
	//m_Mode = POLAR;

	m_Redraw = true;
}

void CGraphView::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_EQ_1, m_aEquationEditCtrls[0]);
	DDX_Control(pDX, IDC_EQ_2, m_aEquationEditCtrls[1]);
	DDX_Control(pDX, IDC_EQ_3, m_aEquationEditCtrls[2]);
	DDX_Control(pDX, IDC_EQ_4, m_aEquationEditCtrls[3]);
	DDX_Control(pDX, IDC_EQ_5, m_aEquationEditCtrls[4]);
	DDX_Control(pDX, IDC_EQ_6, m_aEquationEditCtrls[5]);
	DDX_Control(pDX, IDC_EQ_7, m_aEquationEditCtrls[6]);
	DDX_Control(pDX, IDC_EQ_8, m_aEquationEditCtrls[7]);
	DDX_Control(pDX, IDC_EQ_9, m_aEquationEditCtrls[8]);
	DDX_Control(pDX, IDC_EQ_10, m_aEquationEditCtrls[9]);
	DDX_Control(pDX, IDC_EQ_X1, m_aParametricEquationEditCtrls[0]);
	DDX_Control(pDX, IDC_EQ_Y1, m_aParametricEquationEditCtrls[1]);
	DDX_Control(pDX, IDC_EQ_X2, m_aParametricEquationEditCtrls[2]);
	DDX_Control(pDX, IDC_EQ_Y2, m_aParametricEquationEditCtrls[3]);
	DDX_Control(pDX, IDC_EQ_X3, m_aParametricEquationEditCtrls[4]);
	DDX_Control(pDX, IDC_EQ_Y3, m_aParametricEquationEditCtrls[5]);
	DDX_Control(pDX, IDC_EQ_X4, m_aParametricEquationEditCtrls[6]);
	DDX_Control(pDX, IDC_EQ_Y4, m_aParametricEquationEditCtrls[7]);
	DDX_Control(pDX, IDC_EQ_X5, m_aParametricEquationEditCtrls[8]);
	DDX_Control(pDX, IDC_EQ_Y5, m_aParametricEquationEditCtrls[9]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphView, CPropertyPage)
	ON_MESSAGE(WM_2DGRAPH_N_SLIDER_CLOSING,On2DNSliderClosing)
	//{{AFX_MSG_MAP(CGraphView)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_GRAPH_GRAPHTRACE, ToggleTrace)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_GRAPHTRACE, OnUpdateGraphGraphTrace)
	ON_WM_LBUTTONDBLCLK()
	ON_UPDATE_COMMAND_UI(ID_GRAPH_FINDAREA, OnUpdateGraphFindarea)
	ON_WM_SIZE()
	ON_WM_GETDLGCODE()
	ON_WM_CAPTURECHANGED()
	ON_WM_INITMENUPOPUP()
	ON_WM_CREATE()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
#ifdef GRAPH2D_INFOBAR
	ON_BN_CLICKED(IDC_EQ_ON_1, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_2, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_3, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_4, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_5, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_6, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_7, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_8, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_9, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_EQ_ON_10, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_PARAMETRIC_EQ_1, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_PARAMETRIC_EQ_2, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_PARAMETRIC_EQ_3, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_PARAMETRIC_EQ_4, OnInfoBarEqOn)
	ON_BN_CLICKED(IDC_PARAMETRIC_EQ_5, OnInfoBarEqOn)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphView message handlers

/*********************************************************/
// CGraphView::OnOptionsGraph() 
// Pre: none
// Post: graph settings are updated
// Return Value: none
// Intent: to show the user the graph options dialog
/*********************************************************/
void CGraphView::Options(int tab) 
{
	GrphOptionsDlg = new GraphOptions("Graph Options");
	
	GrphOptionsDlg->m_GOP0.m_Calculator = m_Calculator;
	GrphOptionsDlg->m_GOP1.m_Calculator = m_Calculator;
	GrphOptionsDlg->m_PolarRange.m_Calculator = m_Calculator;
	GrphOptionsDlg->m_GOP2.m_Calculator = m_Calculator;

	InitGraphOptions();
	m_Trace = false;
	
	GraphInfoBar(SetInfoBarCtrlSet(GRAPH2D_INFOBAR_TRACE, false));

	GrphOptionsDlg->m_StartTab = tab;

	if(GrphOptionsDlg->DoModal() == IDOK)
		DataExchange();

	delete GrphOptionsDlg;
}

/*********************************************************/
// CGraphView::DataExchange()
// Pre: GrphOptionsDlg != NULL
// Post: all graph settings are extraced from GrphOptionsDlg
// Return Value: none
// Intent: to extract the settings from the graph options
/*********************************************************/
void CGraphView::DataExchange()
{
	if(!GrphOptionsDlg)
		return;
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	StoreCurrentRange();

	
	//////////////////////////////
	// Mode tab
	m_Mode = (EGraphMode)GrphOptionsDlg->m_Mode.m_nMode;
	
	// TODO: ADD CODE TO CAPTURE ERRORS FROM Compute();

	//////////////////////////////
	// Euclidean Range tab
	if(GrphOptionsDlg->m_GOP1.m_fDirty)
		{
		m_Calculator->Compute(GrphOptionsDlg->m_GOP1.m_Ymin, m_EuclideanGraph.m_EuclideanRange.Ymin, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_GOP1.m_Ymax, m_EuclideanGraph.m_EuclideanRange.Ymax, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_GOP1.m_Yscl, m_EuclideanGraph.m_EuclideanRange.Yscl, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_GOP1.m_Xmin, m_EuclideanGraph.m_EuclideanRange.Xmin, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_GOP1.m_Xmax, m_EuclideanGraph.m_EuclideanRange.Xmax, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_GOP1.m_Xscl, m_EuclideanGraph.m_EuclideanRange.Xscl, this->m_hWnd);
		m_AreaDeltaX = pow(10,(-1*GrphOptionsDlg->m_GOP1.m_AreaPrec));
		m_EuclideanGraph.SetLinePrec(GrphOptionsDlg->m_GOP1.m_LinePrec);
		}

	//////////////////////////////
	// Polar Range tab
	if(GrphOptionsDlg->m_PolarRange.m_fDirty)
		{
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_ThetaMin, m_PolarGraph.m_PolarRange.Theta_min, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_ThetaMax, m_PolarGraph.m_PolarRange.Theta_max, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_ThetaStep, m_PolarGraph.m_PolarRange.Theta_step, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_GridAngle, m_PolarGraph.m_PolarRange.GridAngle, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_GridSpacing, m_PolarGraph.m_PolarRange.GridRadius, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_Ymin, m_PolarGraph.m_PolarRange.Ymin, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_Ymax, m_PolarGraph.m_PolarRange.Ymax, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_Xmin, m_PolarGraph.m_PolarRange.Xmin, this->m_hWnd);
		m_Calculator->Compute(GrphOptionsDlg->m_PolarRange.m_Xmax, m_PolarGraph.m_PolarRange.Xmax, this->m_hWnd);
		}

	//////////////////////////////
	// Euclidean Equations
	if(GrphOptionsDlg->m_GOP0.m_fDirty)
		{
		m_astrEquationsRaw[0] = GrphOptionsDlg->m_GOP0.m_Y1;
		m_Equations[0].disp = GrphOptionsDlg->m_GOP0.m_Yon1;
		m_Equations[0].color = GrphOptionsDlg->m_GOP0.m_ColorButton1.GetColour();
		m_astrEquationsRaw[1] = GrphOptionsDlg->m_GOP0.m_Y2;
		m_Equations[1].disp = GrphOptionsDlg->m_GOP0.m_Yon2;
		m_Equations[1].color = GrphOptionsDlg->m_GOP0.m_ColorButton2.GetColour();
		m_astrEquationsRaw[2] = GrphOptionsDlg->m_GOP0.m_Y3;
		m_Equations[2].disp = GrphOptionsDlg->m_GOP0.m_Yon3;
		m_Equations[2].color = GrphOptionsDlg->m_GOP0.m_ColorButton3.GetColour();
		m_astrEquationsRaw[3] = GrphOptionsDlg->m_GOP0.m_Y4;
		m_Equations[3].disp = GrphOptionsDlg->m_GOP0.m_Yon4;
		m_Equations[3].color = GrphOptionsDlg->m_GOP0.m_ColorButton4.GetColour();
		m_astrEquationsRaw[4] = GrphOptionsDlg->m_GOP0.m_Y5;
		m_Equations[4].disp = GrphOptionsDlg->m_GOP0.m_Yon5;
		m_Equations[4].color = GrphOptionsDlg->m_GOP0.m_ColorButton5.GetColour();
		m_astrEquationsRaw[5] = GrphOptionsDlg->m_GOP0.m_Y6;
		m_Equations[5].disp = GrphOptionsDlg->m_GOP0.m_Yon6;
		m_Equations[5].color = GrphOptionsDlg->m_GOP0.m_ColorButton6.GetColour();
		m_astrEquationsRaw[6] = GrphOptionsDlg->m_GOP0.m_Y7;
		m_Equations[6].disp = GrphOptionsDlg->m_GOP0.m_Yon7;
		m_Equations[6].color = GrphOptionsDlg->m_GOP0.m_ColorButton7.GetColour();
		m_astrEquationsRaw[7] = GrphOptionsDlg->m_GOP0.m_Y8;
		m_Equations[7].disp = GrphOptionsDlg->m_GOP0.m_Yon8;
		m_Equations[7].color = GrphOptionsDlg->m_GOP0.m_ColorButton8.GetColour();
		m_astrEquationsRaw[8] = GrphOptionsDlg->m_GOP0.m_Y9;
		m_Equations[8].disp = GrphOptionsDlg->m_GOP0.m_Yon9;
		m_Equations[8].color = GrphOptionsDlg->m_GOP0.m_ColorButton9.GetColour();
		m_astrEquationsRaw[9] = GrphOptionsDlg->m_GOP0.m_Y10;
		m_Equations[9].disp = GrphOptionsDlg->m_GOP0.m_Yon10;
		m_Equations[9].color = GrphOptionsDlg->m_GOP0.m_ColorButton10.GetColour();

		ExpandEquations();
		}

	//////////////////////////////
	// Display Tab
	if(GrphOptionsDlg->m_GOP2.m_fDirty)
		{
		m_Style.line = (ELineStyle)GrphOptionsDlg->m_GOP2.m_Style;
		m_Grid = (GrphOptionsDlg->m_GOP2.m_Grid == 1);
		m_Axis = (GrphOptionsDlg->m_GOP2.m_Axis == 1);
		m_Coords = (GrphOptionsDlg->m_GOP2.m_Coords == 1);
		m_Labels = (GrphOptionsDlg->m_GOP2.m_Labels == 1);
		m_Style.size = GrphOptionsDlg->m_GOP2.m_Width;
		m_ZoomPerc = GrphOptionsDlg->m_GOP2.m_ZoomPerc;
		m_ZoomDecPrec = GrphOptionsDlg->m_GOP2.m_ZoomDecPrec;
		m_AxisStyle.size = GrphOptionsDlg->m_GOP2.m_AxisSize;
		m_GridStyle.size = GrphOptionsDlg->m_GOP2.m_GridSize;
		m_FixedGrid = (GrphOptionsDlg->m_GOP2.m_FixedGrid == 1);
		SetCursorPositionState(GrphOptionsDlg->m_GOP2.m_CursorPos == 1);
		
		m_nGridLabelInterval = (GrphOptionsDlg->m_GOP2.m_fGridLabels == 1) ? GrphOptionsDlg->m_GOP2.m_nGridLabelInterval : 0;

		int fsize = atoi(GrphOptionsDlg->m_GOP2.m_strFontSize);
		if(fsize > 24)
			fsize = 24;
		else if(fsize < 6)
			fsize = 6;
		
		m_ActiveDrawFontSize.y = m_DrawFontSize.y = fsize;

		m_BackgroundClr = GrphOptionsDlg->m_GOP2.m_BackgroundClr.GetColour();
		m_AxisStyle.color = GrphOptionsDlg->m_GOP2.m_AxisClr.GetColour();
		m_GridStyle.color = GrphOptionsDlg->m_GOP2.m_GridClr.GetColour();
		m_CoordsClr = GrphOptionsDlg->m_GOP2.m_CoordsClr.GetColour();
		m_TextClr = GrphOptionsDlg->m_GOP2.m_TextClr.GetColour();
		m_AreaClr = GrphOptionsDlg->m_GOP2.m_AreaClr.GetColour();
		}

	//////////////////////////////
	// Parametric Equations
	if(GrphOptionsDlg->m_ParametricEqs.m_fDirty)
		{
		for(int i=0; i < MAX_2D_PARAMETRIC_EQS; ++i)
			{
			m_ParametricGraph.m_Equations[i].xt = GrphOptionsDlg->m_ParametricEqs.m_strX[i];
			m_ParametricGraph.m_Equations[i].yt = GrphOptionsDlg->m_ParametricEqs.m_strY[i];
			m_ParametricGraph.m_Equations[i].disp = (1==GrphOptionsDlg->m_ParametricEqs.m_fOn[i]);
			m_ParametricGraph.m_Equations[i].color = GrphOptionsDlg->m_ParametricEqs.m_ColorButton[i].GetColour();
			}
		}

	//////////////////////////////
	// Parametric Range
	if(GrphOptionsDlg->m_ParametricRange.m_fDirty)
		{
		m_ParametricGraph.m_Tmax = GrphOptionsDlg->m_ParametricRange.m_dTmax;
		m_ParametricGraph.m_Tmin = GrphOptionsDlg->m_ParametricRange.m_dTmin;
		m_ParametricGraph.m_Tstep = GrphOptionsDlg->m_ParametricRange.m_dTstep;
		m_ParametricGraph.m_Xscl = GrphOptionsDlg->m_ParametricRange.m_dXscl;
		m_ParametricGraph.m_Xmax = GrphOptionsDlg->m_ParametricRange.m_dXmax;
		m_ParametricGraph.m_Xmin = GrphOptionsDlg->m_ParametricRange.m_dXmin;
		m_ParametricGraph.m_Yscl = GrphOptionsDlg->m_ParametricRange.m_dYscl;
		m_ParametricGraph.m_Ymax = GrphOptionsDlg->m_ParametricRange.m_dYmax;
		m_ParametricGraph.m_Ymin = GrphOptionsDlg->m_ParametricRange.m_dYmin;
		}


	
	// do some validation and cleanup work
	ValidateRanges();

	for(m_TraceEq = 0; m_TraceEq < 10; ++m_TraceEq){
			if(m_Equations[m_TraceEq].disp)
				 break;
	}

	if(m_TraceEq > 9)
		m_Trace = false;

	m_Calculator->m_base = old_base;

	// must update infobar
	GraphInfoBar(UpdateInfoBarEquations());
}

#if !defined(TRIMNUMBER)
#define TRIMNUMBER
void TrimNumber(CString &str){
	if(str != "0" && str.Find(".") != -1)
		str.TrimRight("0");
	str.TrimRight(".");
}
#endif

//extern void TrimNumber(CString &str);
/*********************************************************/
// CGraphView::InitGraphOptions()
// Pre: GrphOptionsDlg != NULL
// Post: all variables in GrphOptionsDlg are set
// Return Value: none
// Intent: to initialize the settings in the graph
//		   options dialog box
/*********************************************************/
void CGraphView::InitGraphOptions()
{
	GrphOptionsDlg->m_PolarRange.m_ThetaMin.Format("%.15f", m_PolarGraph.m_PolarRange.Theta_min);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_ThetaMin);
	GrphOptionsDlg->m_PolarRange.m_ThetaMax.Format("%.15f", m_PolarGraph.m_PolarRange.Theta_max);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_ThetaMax);
	GrphOptionsDlg->m_PolarRange.m_ThetaStep.Format("%.15f", m_PolarGraph.m_PolarRange.Theta_step);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_ThetaStep);
	GrphOptionsDlg->m_PolarRange.m_GridAngle.Format("%.15f", m_PolarGraph.m_PolarRange.GridAngle);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_GridAngle);
	GrphOptionsDlg->m_PolarRange.m_GridSpacing.Format("%.15f", m_PolarGraph.m_PolarRange.GridRadius);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_GridSpacing);
	GrphOptionsDlg->m_PolarRange.m_Xmin.Format("%.15f", m_PolarGraph.m_PolarRange.Xmin);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_Xmin);
	GrphOptionsDlg->m_PolarRange.m_Xmax.Format("%.15f", m_PolarGraph.m_PolarRange.Xmax);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_Xmax);
	GrphOptionsDlg->m_PolarRange.m_Ymin.Format("%.15f", m_PolarGraph.m_PolarRange.Ymin);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_Ymin);
	GrphOptionsDlg->m_PolarRange.m_Ymax.Format("%.15f", m_PolarGraph.m_PolarRange.Ymax);
	TrimNumber(GrphOptionsDlg->m_PolarRange.m_Ymax);

	GrphOptionsDlg->m_GOP1.m_Ymin.Format("%.15f", m_EuclideanGraph.m_EuclideanRange.Ymin);
	TrimNumber(GrphOptionsDlg->m_GOP1.m_Ymin);
	GrphOptionsDlg->m_GOP1.m_Ymax.Format("%.15f", m_EuclideanGraph.m_EuclideanRange.Ymax);
	TrimNumber(GrphOptionsDlg->m_GOP1.m_Ymax);
	GrphOptionsDlg->m_GOP1.m_Yscl.Format("%.15f", m_EuclideanGraph.m_EuclideanRange.Yscl);
	TrimNumber(GrphOptionsDlg->m_GOP1.m_Yscl);
	GrphOptionsDlg->m_GOP1.m_Xmin.Format("%.15f", m_EuclideanGraph.m_EuclideanRange.Xmin);
	TrimNumber(GrphOptionsDlg->m_GOP1.m_Xmin);
	GrphOptionsDlg->m_GOP1.m_Xmax.Format("%.15f", m_EuclideanGraph.m_EuclideanRange.Xmax);
	TrimNumber(GrphOptionsDlg->m_GOP1.m_Xmax);
	GrphOptionsDlg->m_GOP1.m_Xscl.Format("%.15f", m_EuclideanGraph.m_EuclideanRange.Xscl);
	TrimNumber(GrphOptionsDlg->m_GOP1.m_Xscl);

	GrphOptionsDlg->m_GOP1.m_LinePrec = m_EuclideanGraph.GetLinePrec();
	
	GrphOptionsDlg->m_GOP1.m_AreaPrec = 1;
	while(m_AreaDeltaX != pow(10,(-1*GrphOptionsDlg->m_GOP1.m_AreaPrec)))
		++GrphOptionsDlg->m_GOP1.m_AreaPrec;

	GrphOptionsDlg->m_GOP0.m_Y1 = m_astrEquationsRaw[0];
	GrphOptionsDlg->m_GOP0.m_Yon1 = m_Equations[0].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton1.SetColour(m_Equations[0].color);
	GrphOptionsDlg->m_GOP0.m_Y2 = m_astrEquationsRaw[1];
	GrphOptionsDlg->m_GOP0.m_Yon2 = m_Equations[1].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton2.SetColour(m_Equations[1].color);
	GrphOptionsDlg->m_GOP0.m_Y3 = m_astrEquationsRaw[2];
	GrphOptionsDlg->m_GOP0.m_Yon3 = m_Equations[2].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton3.SetColour(m_Equations[2].color);
	GrphOptionsDlg->m_GOP0.m_Y4 = m_astrEquationsRaw[3];
	GrphOptionsDlg->m_GOP0.m_Yon4 = m_Equations[3].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton4.SetColour(m_Equations[3].color);
	GrphOptionsDlg->m_GOP0.m_Y5 = m_astrEquationsRaw[4];
	GrphOptionsDlg->m_GOP0.m_Yon5 = m_Equations[4].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton5.SetColour(m_Equations[4].color);
	GrphOptionsDlg->m_GOP0.m_Y6 = m_astrEquationsRaw[5];
	GrphOptionsDlg->m_GOP0.m_Yon6 = m_Equations[5].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton6.SetColour(m_Equations[5].color);
	GrphOptionsDlg->m_GOP0.m_Y7 = m_astrEquationsRaw[6];
	GrphOptionsDlg->m_GOP0.m_Yon7 = m_Equations[6].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton7.SetColour(m_Equations[6].color);
	GrphOptionsDlg->m_GOP0.m_Y8 = m_astrEquationsRaw[7];
	GrphOptionsDlg->m_GOP0.m_Yon8 = m_Equations[7].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton8.SetColour(m_Equations[7].color);
	GrphOptionsDlg->m_GOP0.m_Y9 = m_astrEquationsRaw[8];
	GrphOptionsDlg->m_GOP0.m_Yon9 = m_Equations[8].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton9.SetColour(m_Equations[8].color);
	GrphOptionsDlg->m_GOP0.m_Y10 = m_astrEquationsRaw[9];
	GrphOptionsDlg->m_GOP0.m_Yon10 = m_Equations[9].disp;
	GrphOptionsDlg->m_GOP0.m_ColorButton10.SetColour(m_Equations[9].color);

	GrphOptionsDlg->m_Mode.m_nMode = GrphOptionsDlg->m_GOP0.m_Mode = m_Mode;

	GrphOptionsDlg->m_GOP2.m_Style = m_Style.line;
	GrphOptionsDlg->m_GOP2.m_Width = m_Style.size;
	GrphOptionsDlg->m_GOP2.m_Grid = m_Grid;
	GrphOptionsDlg->m_GOP2.m_Axis = m_Axis;
	GrphOptionsDlg->m_GOP2.m_Coords = m_Coords;
	GrphOptionsDlg->m_GOP2.m_Labels = m_Labels;
	GrphOptionsDlg->m_GOP2.m_CursorPos = m_CursorPos;
	GrphOptionsDlg->m_GOP2.m_ZoomPerc = m_ZoomPerc;
	GrphOptionsDlg->m_GOP2.m_ZoomDecPrec = m_ZoomDecPrec;
	GrphOptionsDlg->m_GOP2.m_AxisSize = m_AxisStyle.size;
	GrphOptionsDlg->m_GOP2.m_GridSize = m_GridStyle.size;
	GrphOptionsDlg->m_GOP2.m_FixedGrid = m_FixedGrid;
	GrphOptionsDlg->m_GOP2.m_nGridLabelInterval = m_nGridLabelInterval;

	GrphOptionsDlg->m_GOP2.m_strFontSize.Format("%d", int(m_DrawFontSize.y));

	GrphOptionsDlg->m_GOP2.m_BackgroundClr.SetColour(m_BackgroundClr);
	GrphOptionsDlg->m_GOP2.m_AxisClr.SetColour(m_AxisStyle.color);
	GrphOptionsDlg->m_GOP2.m_GridClr.SetColour(m_GridStyle.color);
	GrphOptionsDlg->m_GOP2.m_CoordsClr.SetColour(m_CoordsClr);
	GrphOptionsDlg->m_GOP2.m_TextClr.SetColour(m_TextClr);
	GrphOptionsDlg->m_GOP2.m_AreaClr.SetColour(m_AreaClr);

	// load parametric equations
	for(int i=0; i < MAX_2D_PARAMETRIC_EQS; ++i)
		{
		GrphOptionsDlg->m_ParametricEqs.m_strX[i] = m_ParametricGraph.m_Equations[i].xt;
		GrphOptionsDlg->m_ParametricEqs.m_strY[i] = m_ParametricGraph.m_Equations[i].yt;
		GrphOptionsDlg->m_ParametricEqs.m_fOn[i]= m_ParametricGraph.m_Equations[i].disp;
		GrphOptionsDlg->m_ParametricEqs.m_ColorButton[i].SetColour(m_ParametricGraph.m_Equations[i].color);
		}

	// load parametric range
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strTmax, m_ParametricGraph.m_Tmax);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strTmin, m_ParametricGraph.m_Tmin);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strTstep, m_ParametricGraph.m_Tstep);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strXscl, m_ParametricGraph.m_Xscl);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strXmax, m_ParametricGraph.m_Xmax);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strXmin, m_ParametricGraph.m_Xmin);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strYscl, m_ParametricGraph.m_Yscl);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strYmax, m_ParametricGraph.m_Ymax);
	g_Calculator->DecimalToStringSci(GrphOptionsDlg->m_ParametricRange.m_strYmin, m_ParametricGraph.m_Ymin);
	
	GrphOptionsDlg->m_ParametricRange.m_dTmax = m_ParametricGraph.m_Tmax;
	GrphOptionsDlg->m_ParametricRange.m_dTmin = m_ParametricGraph.m_Tmin;
	GrphOptionsDlg->m_ParametricRange.m_dTstep = m_ParametricGraph.m_Tstep;
	GrphOptionsDlg->m_ParametricRange.m_dXscl = m_ParametricGraph.m_Xscl;
	GrphOptionsDlg->m_ParametricRange.m_dXmax = m_ParametricGraph.m_Xmax;
	GrphOptionsDlg->m_ParametricRange.m_dXmin = m_ParametricGraph.m_Xmin;
	GrphOptionsDlg->m_ParametricRange.m_dYscl = m_ParametricGraph.m_Yscl;
	GrphOptionsDlg->m_ParametricRange.m_dYmax = m_ParametricGraph.m_Ymax;
	GrphOptionsDlg->m_ParametricRange.m_dYmin = m_ParametricGraph.m_Ymin;

}

/*********************************************************/
// CGraphView::OnMouseMove(UINT nFlags, CPoint point) 
// Pre: mouse moves
// Post: none
// Return Value: none
// Intent: called by framework to handle actions when 
//		   mouse moves
/*********************************************************/
void CGraphView::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_cursor_pos = point;
	m_cursor_pos.y -= m_fToolbarOn ? ToolbarHeight() : 0;

	CDC *pDC = GetOffsetDC();
	DrawText(pDC);
	ReleaseDC(pDC);

	if (m_ButtonZoom) {

        /* Do not draw outside the window's client area */
	
		CRect rgn;
		m_GraphRgn.GetRgnBox(&rgn);
        if (m_cursor_pos.x < rgn.left) {
             m_cursor_pos.x = rgn.left;
         } 
		else if (m_cursor_pos.x >= rgn.right){
             m_cursor_pos.x = rgn.right-1;
        }
        if (m_cursor_pos.y < rgn.top){   
			 m_cursor_pos.y = rgn.top;
		}
		else if (m_cursor_pos.y > rgn.bottom){
			 m_cursor_pos.y = rgn.bottom;
		}

		/* If the mouse position has changed, then clear the */
		/* previous rectangle and draw the new one.          */

		 if ((m_cursor_pos.x != m_ZoomPrevPt.x) || (m_cursor_pos.y != m_ZoomPrevPt.y)) {
			 CDC *pDC = GetOffsetDC();
		
             pDC->SetROP2(R2_NOT);          /* Erases the previous box */
             pDC->MoveTo(m_ZoomPt.x, m_ZoomPt.y);
             pDC->LineTo(m_ZoomPt.x, m_ZoomPrevPt.y);
             pDC->LineTo(m_ZoomPrevPt.x, m_ZoomPrevPt.y);
             pDC->LineTo(m_ZoomPrevPt.x, m_ZoomPt.y);
             pDC->LineTo(m_ZoomPt.x, m_ZoomPt.y);

             /* Get the current mouse position */
             m_ZoomPrevPt = m_cursor_pos;

			 // If Shift is down make the selection a square
			 if(nFlags == (MK_LBUTTON | MK_SHIFT)){
				int w, h;
				
				w = abs(m_ZoomPt.x - m_ZoomPrevPt.x);
				h = abs(m_ZoomPt.y - m_ZoomPrevPt.y);

				if(w != h){
					if(w > h){
						if(m_ZoomPrevPt.y > m_ZoomPt.y)
							m_ZoomPrevPt.y = m_ZoomPt.y + w;
						else
							m_ZoomPrevPt.y = m_ZoomPt.y - w;
					}
					else{
						if(m_ZoomPrevPt.x > m_ZoomPt.x)
							m_ZoomPrevPt.x = m_ZoomPt.x + h;
						else
							m_ZoomPrevPt.x = m_ZoomPt.x - h;
					}
				}
			 }

             pDC->MoveTo(m_ZoomPt.x, m_ZoomPt.y); /* Draws the new box */
             pDC->LineTo(m_ZoomPt.x, m_ZoomPrevPt.y);
             pDC->LineTo(m_ZoomPrevPt.x, m_ZoomPrevPt.y);
             pDC->LineTo(m_ZoomPrevPt.x, m_ZoomPt.y);
             pDC->LineTo(m_ZoomPt.x, m_ZoomPt.y);

			 ReleaseDC(pDC);
         }
    }
	else if(nFlags == (MK_LBUTTON | MK_CONTROL))
		{
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_HAND_MOVE)));
		CPoint newPt = point;
		newPt.y -= m_fToolbarOn ? ToolbarHeight() : 0;
		HandPan(m_ptHandMove.x - point.x, newPt.y - m_ptHandMove.y);
		m_ptHandMove = newPt;
		}
	else
		SetMyCursor(GetRegion(m_cursor_pos));

	CPropertyPage::OnMouseMove(nFlags, point);
}

/*********************************************************/
// CGraphView::GetRegion(CPoint point)
// Pre: none
// Post: none
// Return Value: the region in the graph that point is in
// Intent: to find out which region of the graph point is in
//		   the graph has been split up into 9 regions so that
//		   we can display an alternate cursor for each region
/*********************************************************/
int CGraphView::GetRegion(CPoint point)
{
	int edge_width = int(0.1*m_graph_width);

	CRect rect;

	rect = CRect(h_space, v_space, h_space + edge_width, v_space + edge_width);
	if(rect.PtInRect(point))
			return 1;

	rect = CRect(h_space + edge_width, v_space, h_space + m_graph_width - edge_width, v_space + edge_width);
	if(rect.PtInRect(point))
			return 2;

	rect = CRect(h_space + m_graph_width - edge_width, v_space, h_space + m_graph_width, v_space + edge_width);
	if(rect.PtInRect(point))
			return 3;

	rect = CRect(h_space, v_space + edge_width, h_space + edge_width, v_space + m_graph_height - edge_width);
	if(rect.PtInRect(point))
			return 4;

	rect = CRect(h_space + edge_width, v_space + edge_width, h_space + m_graph_width - edge_width, 
					v_space + m_graph_height - edge_width);
	if(rect.PtInRect(point))
			return 5;

	rect = CRect(h_space + m_graph_width - edge_width, v_space + edge_width, 
					h_space + m_graph_width, v_space + m_graph_height - edge_width);
	if(rect.PtInRect(point))
			return 6;

	rect = CRect(h_space, v_space + m_graph_height - edge_width, h_space + edge_width, v_space + m_graph_height);
	if(rect.PtInRect(point))
			return 7;

	rect = CRect(h_space + edge_width, v_space + m_graph_height - edge_width, 
					h_space + m_graph_width - edge_width, v_space + m_graph_height);
	if(rect.PtInRect(point))
			return 8;

	rect = CRect(h_space + m_graph_width - edge_width, v_space + m_graph_height - edge_width, 
					h_space + m_graph_width, v_space + m_graph_height);
	if(rect.PtInRect(point))
			return 9;

	return 0;
}

/*********************************************************/
// CGraphView::OnLButtonDown(UINT nFlags, CPoint point) 
// Pre: none
// Post: none
// Return Value: none
// Intent: called by framework to handle left mouse clicks
/*********************************************************/
void CGraphView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();

	point.y -= m_fToolbarOn ? ToolbarHeight() : 0;
	int region = GetRegion(point);

	if(region != 5 && region != 0){
			SetMyCursor(region);
			Pan(region);
	}
	else if(region == 5){
		if(nFlags & MK_CONTROL)
			{
			SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_HAND_MOVE)));
			m_ptHandMove = point;
			}
		else
			{
			m_ButtonZoom = true;
			m_ZoomPt = point;
			m_ZoomPrevPt = point;
			}
	}

	CPropertyPage::OnLButtonDown(nFlags, point);
}

/*********************************************************/
// CGraphView::OnLButtonUp(UINT nFlags, CPoint point) 
// Pre: none
// Post: none
// Return Value: none
// Intent: called by framework to handle when the left
//		   mouse button goes up
/*********************************************************/
void CGraphView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	point.y -= m_fToolbarOn ? ToolbarHeight() : 0;
	
	int region = GetRegion(point);

	if(region != 5 && region != 0)
		SetMyCursor(region);

	if(m_ButtonZoom){
		CDC *pDC = GetOffsetDC();
		pDC->SetROP2(R2_NOT);          /* Erases the previous box */
		pDC->MoveTo(m_ZoomPt.x, m_ZoomPt.y);
		pDC->LineTo(m_ZoomPt.x, m_ZoomPrevPt.y);
		pDC->LineTo(m_ZoomPrevPt.x, m_ZoomPrevPt.y);
		pDC->LineTo(m_ZoomPrevPt.x, m_ZoomPt.y);
		pDC->LineTo(m_ZoomPt.x, m_ZoomPt.y);

		ZoomRect();
	}

	m_ButtonZoom = false;

	CPropertyPage::OnLButtonUp(nFlags, point);
}

/*********************************************************/
// CGraphView::Pan(int rgn)
// Pre: none
// Post: the range variables are adjusted
// Return Value:none
// Intent: to pan in a given direction depending on the
//		   region given by rgn
/*********************************************************/
void CGraphView::Pan(int rgn)
{
	StoreCurrentRange();
	
	long double x_pan_amount, y_pan_amount;
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			x_pan_amount = 0.1 * (m_EuclideanGraph.m_EuclideanRange.Xmax - m_EuclideanGraph.m_EuclideanRange.Xmin);
			y_pan_amount = 0.1 * (m_EuclideanGraph.m_EuclideanRange.Ymax - m_EuclideanGraph.m_EuclideanRange.Ymin);
			
			switch(rgn){
			case 1:
				m_EuclideanGraph.m_EuclideanRange.Xmax -= x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Xmin -= x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymax += y_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymin += y_pan_amount;
				break;
			case 2:
				m_EuclideanGraph.m_EuclideanRange.Ymax += y_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymin += y_pan_amount;
				break;
			case 3:		
				m_EuclideanGraph.m_EuclideanRange.Xmax += x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Xmin += x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymax += y_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymin += y_pan_amount;
				break;
			case 4:
				m_EuclideanGraph.m_EuclideanRange.Xmax -= x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Xmin -= x_pan_amount;
				break;
			case 6:
				m_EuclideanGraph.m_EuclideanRange.Xmax += x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Xmin += x_pan_amount;
				break;
			case 7:
				m_EuclideanGraph.m_EuclideanRange.Xmax -= x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Xmin -= x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymax -= y_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymin -= y_pan_amount;
				break;
			case 8:
				m_EuclideanGraph.m_EuclideanRange.Ymax -= y_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymin -= y_pan_amount;
				break;
			case 9:
				m_EuclideanGraph.m_EuclideanRange.Xmax += x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Xmin += x_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymax -= y_pan_amount;
				m_EuclideanGraph.m_EuclideanRange.Ymin -= y_pan_amount;
				break;
			}
			break;
		}
	case POLAR:
		{
			x_pan_amount = 0.1 * (m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin);
			y_pan_amount = 0.1 * (m_PolarGraph.m_PolarRange.Ymax - m_PolarGraph.m_PolarRange.Ymin);
			
			switch(rgn){
			case 1:
				m_PolarGraph.m_PolarRange.Xmax -= x_pan_amount;
				m_PolarGraph.m_PolarRange.Xmin -= x_pan_amount;
				m_PolarGraph.m_PolarRange.Ymax += y_pan_amount;
				m_PolarGraph.m_PolarRange.Ymin += y_pan_amount;
				break;
			case 2:
				m_PolarGraph.m_PolarRange.Ymax += y_pan_amount;
				m_PolarGraph.m_PolarRange.Ymin += y_pan_amount;
				break;
			case 3:		
				m_PolarGraph.m_PolarRange.Xmax += x_pan_amount;
				m_PolarGraph.m_PolarRange.Xmin += x_pan_amount;
				m_PolarGraph.m_PolarRange.Ymax += y_pan_amount;
				m_PolarGraph.m_PolarRange.Ymin += y_pan_amount;
				break;
			case 4:
				m_PolarGraph.m_PolarRange.Xmax -= x_pan_amount;
				m_PolarGraph.m_PolarRange.Xmin -= x_pan_amount;
				break;
			case 6:
				m_PolarGraph.m_PolarRange.Xmax += x_pan_amount;
				m_PolarGraph.m_PolarRange.Xmin += x_pan_amount;
				break;
			case 7:
				m_PolarGraph.m_PolarRange.Xmax -= x_pan_amount;
				m_PolarGraph.m_PolarRange.Xmin -= x_pan_amount;
				m_PolarGraph.m_PolarRange.Ymax -= y_pan_amount;
				m_PolarGraph.m_PolarRange.Ymin -= y_pan_amount;
				break;
			case 8:
				m_PolarGraph.m_PolarRange.Ymax -= y_pan_amount;
				m_PolarGraph.m_PolarRange.Ymin -= y_pan_amount;
				break;
			case 9:
				m_PolarGraph.m_PolarRange.Xmax += x_pan_amount;
				m_PolarGraph.m_PolarRange.Xmin += x_pan_amount;
				m_PolarGraph.m_PolarRange.Ymax -= y_pan_amount;
				m_PolarGraph.m_PolarRange.Ymin -= y_pan_amount;
				break;
			}
			break;
		}	
	case PARAMETRIC:
		{
			x_pan_amount = 0.1 * (m_ParametricGraph.m_Xmax - m_ParametricGraph.m_Xmin);
			y_pan_amount = 0.1 * (m_ParametricGraph.m_Ymax - m_ParametricGraph.m_Ymin);
			
			switch(rgn){
			case 1:
				m_ParametricGraph.m_Xmax -= x_pan_amount;
				m_ParametricGraph.m_Xmin -= x_pan_amount;
				m_ParametricGraph.m_Ymax += y_pan_amount;
				m_ParametricGraph.m_Ymin += y_pan_amount;
				break;
			case 2:
				m_ParametricGraph.m_Ymax += y_pan_amount;
				m_ParametricGraph.m_Ymin += y_pan_amount;
				break;
			case 3:		
				m_ParametricGraph.m_Xmax += x_pan_amount;
				m_ParametricGraph.m_Xmin += x_pan_amount;
				m_ParametricGraph.m_Ymax += y_pan_amount;
				m_ParametricGraph.m_Ymin += y_pan_amount;
				break;
			case 4:
				m_ParametricGraph.m_Xmax -= x_pan_amount;
				m_ParametricGraph.m_Xmin -= x_pan_amount;
				break;
			case 6:
				m_ParametricGraph.m_Xmax += x_pan_amount;
				m_ParametricGraph.m_Xmin += x_pan_amount;
				break;
			case 7:
				m_ParametricGraph.m_Xmax -= x_pan_amount;
				m_ParametricGraph.m_Xmin -= x_pan_amount;
				m_ParametricGraph.m_Ymax -= y_pan_amount;
				m_ParametricGraph.m_Ymin -= y_pan_amount;
				break;
			case 8:
				m_ParametricGraph.m_Ymax -= y_pan_amount;
				m_ParametricGraph.m_Ymin -= y_pan_amount;
				break;
			case 9:
				m_ParametricGraph.m_Xmax += x_pan_amount;
				m_ParametricGraph.m_Xmin += x_pan_amount;
				m_ParametricGraph.m_Ymax -= y_pan_amount;
				m_ParametricGraph.m_Ymin -= y_pan_amount;
				break;
			}
			break;
		}
	}
	m_Redraw = true;
	OnPaint();
	//Invalidate();
}

/*********************************************************/
// CGraphView::SetMyCursor(int rgn)
// Pre: none
// Post: none
// Return Value: none
// Intent: to set the cursor base on the given region rgn
/*********************************************************/
void CGraphView::SetMyCursor(int rgn)
{
	switch(rgn){
	case 1:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_UL)));
		break;
	case 2:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_UP)));
		break;
	case 3:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_UR)));
		break;
	case 4:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_LEFT)));
		break;
	case 5:
		break;
	case 6:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_RIGHT)));
		break;
	case 7:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_LL)));
		break;
	case 8:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_DOWN)));
		break;
	case 9:
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_POINT_LR)));
		break;
	}
}

/*********************************************************/
// CGraphView::GraphOff()
// Pre: none
// Post: none
// Return Value: none
// Intent: to turn all the equations off
/*********************************************************/
void CGraphView::GraphOff()
{
	for(int i = 0; i < 10; ++i)
		m_Equations[i].disp = false;
		
	m_Redraw = true;
	//OnPaint();
}

/*********************************************************/
// CGraphView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
// Pre: none
// Post: none
// Return Value: none
// Intent: called by KeyDown when a key is pressed
/*********************************************************/
void CGraphView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	// currently all functions that are acessible
	// by pressing keys are only aplicable when you are tracing
	if(!m_Trace)
		return;
	
	int x;
	if(m_Mode == EUCLIDEAN){
		x = m_EuclideanGraph.GetTracePixel();
		m_EuclideanGraph.SetTracePixel(GraphToScreenX(m_EuclideanGraph.GetTraceX(), m_EuclideanGraph.GetLinePrec()));
		
		if(abs(m_EuclideanGraph.GetTracePixel() - x) < 5)
			m_EuclideanGraph.SetTracePixel(x);
	}

	m_PrevTraceEq = m_TraceEq;

	switch(nChar){
	case VK_RIGHT:
	case VK_NUMPAD6:
		{
			switch(m_Mode){
			case EUCLIDEAN:
				m_EuclideanGraph.SetPrevTracePixel(m_EuclideanGraph.GetTracePixel());
				m_EuclideanGraph.SetTracePixel(m_EuclideanGraph.GetTracePixel() + 1);
				break;
			case POLAR:
				m_PolarGraph.IncreaseTraceTheta();
				break;
			case PARAMETRIC:
				m_ParametricGraph.IncreaseTraceT();
				break;
			}
			break;
		}
	case VK_LEFT:
	case VK_NUMPAD4:
		{
			switch(m_Mode){
			case EUCLIDEAN:
				m_EuclideanGraph.SetPrevTracePixel(m_EuclideanGraph.GetTracePixel());
				m_EuclideanGraph.SetTracePixel(m_EuclideanGraph.GetTracePixel() - 1);
				break;
			case POLAR:
				m_PolarGraph.DecreaseTraceTheta();
				break;
			case PARAMETRIC:
				m_ParametricGraph.DecreaseTraceT();
				break;
			}
			break;
		}
	case VK_UP:
	case VK_NUMPAD8:
		NextTraceEq(1);
		break;
	case VK_DOWN:
	case VK_NUMPAD2:
		NextTraceEq(0);		
		break;
	case 't':
	case 'T':
		{
			if(m_TangentLine[m_TraceEq])
				m_TangentLine[m_TraceEq] = false;
			else{
				m_TangentLine[m_TraceEq] = true;
				switch(m_Mode){
				case EUCLIDEAN:
					{
					InitTangentLine(m_TraceEq, m_EuclideanGraph.GetTraceX());
					break;
					}
				case POLAR:
					{
					InitTangentLine(m_TraceEq, m_PolarGraph.GetTraceTheta());
					break;
					}
				case PARAMETRIC:
					{
					InitTangentLine(m_TraceEq, m_ParametricGraph.m_TraceT);
					break;
					}
				}
			}
			//Invalidate(true);
			m_Redraw = true;
			OnPaint();
			break;
		}		
	case 'D':
		{
			switch(m_Distance){
			case OFF:
				{
					m_Distance = SECOND;
					m_DistanceEqOne = m_TraceEq;
					m_DistanceEqTwo = m_TraceEq;

					switch(m_Mode){
					case EUCLIDEAN:
						{
							m_DistanceOneX = m_EuclideanGraph.GetTraceX();
							m_DistancePrevX = m_EuclideanGraph.GetTraceX();
							m_DistanceTwoX = m_EuclideanGraph.GetTraceX();
							break;
						}
					case POLAR:
						{
							m_PolarGraph.SetDistanceThetaOne(m_PolarGraph.GetTraceTheta());
							m_PolarGraph.SetDistanceThetaTwo(m_PolarGraph.GetTraceTheta());
							m_PolarGraph.SetDistanceThetaPrev(m_PolarGraph.GetTraceTheta());
							break;
						}
					}
					break;
				}
			case SECOND:
				{
					m_Distance = DONE;
					m_DistanceEqTwo = m_TraceEq;

					switch(m_Mode){
					case EUCLIDEAN:
						{
							m_DistanceTwoX = m_EuclideanGraph.GetTraceX();
							break;
						}
					case POLAR:
						{
							m_PolarGraph.SetDistanceThetaTwo(m_PolarGraph.GetTraceTheta());
							break;
						}
					}
					break;
				}
			case DONE:
				{
					m_Distance = OFF;
					Invalidate();
					break;
				}
			}

			if(m_Mode == PARAMETRIC)
				MessageBox("distance not implemetned");
			break;
		}
	}
	

	if((nChar == VK_NUMPAD4 || nChar == VK_NUMPAD6 ||
		nChar == VK_LEFT || nChar == VK_RIGHT) && (m_Mode == EUCLIDEAN)){
		m_EuclideanGraph.SetTraceX(ScreenToGraphX(m_EuclideanGraph.GetTracePixel(), m_EuclideanGraph.GetLinePrec()));
	}
	
	if(m_Distance == SECOND){
		
		switch(m_Mode){
		case EUCLIDEAN:
			{
				m_DistanceTwoX = m_EuclideanGraph.GetTraceX();
				break;
			}
		case POLAR:
			{
				m_PolarGraph.SetDistanceThetaPrev(m_PolarGraph.GetDistanceThetaTwo());
				m_PolarGraph.SetDistanceThetaTwo(m_PolarGraph.GetTraceTheta());
				break;
			}
		}
		
		m_DistanceEqTwo = m_TraceEq;
	}
	
	CDC *pDC = GetOffsetDC();
	EraseDistance(pDC);
	DrawText(pDC);
	DrawTrace(pDC);
	DrawDistance(pDC);
	ReleaseDC(pDC);

	CPropertyPage::OnKeyDown(nChar, nRepCnt, nFlags);
}

/*********************************************************/
// CGraphView::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
// Pre: none
// Post: none
// Return Value: none
// Intent: called by the framework when a key is pressed
/*********************************************************/
void CGraphView::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	OnKeyDown(nChar, nRepCnt, nFlags);
}

/*********************************************************/
// CGraphView::ValidateRanges()
// Pre: none
// Post: range is adjusted
// Return Value: none
// Intent: to validate the range and adjust if any part
//		   of it is invalid
/*********************************************************/
void CGraphView::ValidateRanges()
{
	switch(m_Mode){
	case EUCLIDEAN: m_EuclideanGraph.ValidateRanges();	break;
	case POLAR: m_PolarGraph.ValidateRanges(m_Calculator->m_trig_state);	break;
	case PARAMETRIC: m_ParametricGraph.ValidateRanges(); break;
	}
}

/*********************************************************/
// bool CGraphView::ValidateIncrement(long double Xmin, long double Xmax, 
//								      long double Ymin, long double Ymax)
// Pre: none
// Post: none
// Return Value: true if we have a valid increment
// Intent: to validate that we have a valid increment
//		   this is necessary so that we don't have overflow
//		   or underflow when drawing the graphs
/*********************************************************/
bool CGraphView::ValidateIncrement(long double Xmin, long double Xmax, 
								   long double Ymin, long double Ymax)
{
	int x_num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_width);
	double x_increment = (Xmax - Xmin) / x_num_points;

	int y_num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_height);
	double y_increment = (Ymax - Ymin) / x_num_points;

	if(y_increment < min_increment || x_increment < min_increment)
		return false;
	else
		return true;
}

/*********************************************************/
// CGraphView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles init stuff before handlign popup menu
/*********************************************************/
void CGraphView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	UpdateMenu(pPopupMenu);
}

/*********************************************************/
// CGraphView::UpdateMenu(CMenu* pMenu)
// Pre: none
// Post: none
// Return Value: none
// Intent: it updates the controls of the individual menu items
//		   this is needed because htis is a dialog based app
//		   and the updating is not automatically done for us
/*********************************************************/
void CGraphView::UpdateMenu(CMenu* pMenu)
{
	CCmdUI cmdUI;
	for (UINT n = 0; n < pMenu->GetMenuItemCount(); ++n)
	{
	    CMenu* pSubMenu = pMenu->GetSubMenu(n);
	    if (pSubMenu == NULL)
	    {
			cmdUI.m_nIndexMax = pMenu->GetMenuItemCount();
			for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
			{
			    cmdUI.m_nIndex = i;
				cmdUI.m_nID = pMenu->GetMenuItemID(i);
				cmdUI.m_pMenu = pMenu;
				cmdUI.DoUpdate(this, FALSE);
			}
	    }
	}
}

/*********************************************************/
// CGraphView::OnContextMenu(CWnd* pWnd, CPoint point)
// Pre: UpdateMenu is called
// Post: none
// Return Value: none
// Intent: displays the graphing menu
/*********************************************************/
void CGraphView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CRect Window;
	GetWindowRect(Window);	//Get Window Coords to subtract from Screen coords.
	CPoint client = point;
	ScreenToClient(&client);

	if(GetRegion(client) != 0){
		CMenu graph;	
		graph.CreatePopupMenu();
		CMenu PopUp2DGraph;
		PopUp2DGraph.LoadMenu(IDR_2DGRAPH);
		graph.InsertMenu(3, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)PopUp2DGraph.m_hMenu, "2D Graph");
		PopUp2DGraph.Detach();

		graph.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
											point.x, point.y, this);
	}
	SetFocus();
}

/*********************************************************/
// CGraphView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
// Pre: none
// Post: ngraph is zoomed
// Return Value: result of parent function call
// Intent: called by framework to handle zooming from scrolling
//		   the mouse wheel
/*********************************************************/
BOOL CGraphView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	ScreenToClient(&pt);

	if(m_GraphRgn.PtInRegion(pt))
		ScrollZoom(zDelta);
	
	return CPropertyPage::OnMouseWheel(nFlags, zDelta, pt);
}

/*********************************************************/
// CGraphView::OnMenuGraphTrace()
// Pre: none
// Post: none
// Return Value: none
// Intent: to all correct trace menu
//		   it is here for backwards compatability with nameing
//		   I used earlier
/*********************************************************/
void CGraphView::OnMenuGraphTrace()
{
	ToggleTrace();
}

/*********************************************************/
// CGraphView::ToggleTrace()
// Pre: none
// Post: tracing variables are updated, trace is toggled on or off
// Return Value: none
// Intent: to turn on or off tracing
/*********************************************************/
void CGraphView::ToggleTrace() 
{	
	CRect window(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space);

	if(m_Trace)
		g_InfoBarGroups[GRAPH2D_INFOBAR_TRACE].bOn = m_Trace = false;
	else{
		if(m_Mode != PARAMETRIC)
			{
			for(m_TraceEq = 0; m_TraceEq < 10; ++m_TraceEq){
				if(m_Equations[m_TraceEq].disp)
					 break;
			}

			if(m_TraceEq > 9)
				return; // no equations drawn, don't bother tracing
			}

		g_InfoBarGroups[GRAPH2D_INFOBAR_TRACE].bOn = m_Trace = true;

		switch(m_Mode){
		case EUCLIDEAN: m_EuclideanGraph.InitializeTrace(window);	break;
		case POLAR: m_PolarGraph.InitializeTrace();	break;
		case PARAMETRIC: 
			if(!m_ParametricGraph.InitializeTrace(m_TraceEq))
				return; // no equations drawn, don't bother tracing
			break;
		}
		
	}
	m_PrevTraceEq = m_TraceEq;
	
	#ifdef GRAPH2D_INFOBAR
	PositionInfoBar();
	UpdateInfoBarTraceCtrls();	
	#endif
	
	if(!m_Trace){ // trace has been turned off, clean up and restore graph to non-trace state		
		int old_base = m_Calculator->m_base;
		m_Calculator->m_base = 10;
		CDC *pDC = GetOffsetDC();
		
		switch(m_Mode){
		case EUCLIDEAN: 
			m_EuclideanGraph.ClearPrevTrace(m_Equations[m_PrevTraceEq].eq,
				m_MemBitmap,
				window,
				m_Calculator,
				pDC);
			break;
		case POLAR: m_PolarGraph.ClearPrevTrace(m_Equations[m_PrevTraceEq].eq,
						m_MemBitmap,
						window,
						m_Calculator,
						pDC);
			break;
		case PARAMETRIC: m_ParametricGraph.ClearPrevTrace(m_PrevTraceEq,
														m_MemBitmap,
														window,
														pDC);
			break;
		}
		
		ReleaseDC(pDC);
		m_Calculator->m_base = old_base;
		PaintNow();
	}
	else{
		CDC *pDC = GetOffsetDC();
		DrawText(pDC);
		DrawTrace(pDC);
		ReleaseDC(pDC);
	}
	
}

/*********************************************************/
// CGraphView::OnUpdateGraphGraphTrace(CCmdUI* pCmdUI) 
// Pre: none
// Post: none
// Return Value: none
// Intent: to update trace menu item
/*********************************************************/
void CGraphView::OnUpdateGraphGraphTrace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Trace);
}

/*********************************************************/
// CGraphView::OnUpdateGraphFindarea(CCmdUI* pCmdUI) 
// Pre: none
// Post: none
// Return Value: none
// Intent: to update the find area menu item
/*********************************************************/
void CGraphView::OnUpdateGraphFindarea(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_FindArea);
	if(m_Mode == POLAR || m_Mode == PARAMETRIC)
		pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);
}

void CGraphView::FindArea(int eq1, int eq2, long double Xmin, long double Xmax, bool fAbsolute)
{
	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	if(m_EuclideanGraph.m_EuclideanRange.Xmin >= m_EuclideanGraph.m_EuclideanRange.Xmax)
		m_EuclideanGraph.m_EuclideanRange.Xmin = m_EuclideanGraph.m_EuclideanRange.Xmax - 1;
	
	if(eq1 == eq2)
		eq2 = -1;
	
	if(eq2 < 0 || eq2 > 9)
		eq2 = -1;
	
	m_FindArea = true;
	m_AreaXmin = Xmin;
	m_AreaXmax = Xmax;
	m_AreaEq = eq1;
	m_AreaEq2 = eq2;
	
	Integrate(fAbsolute);
	
	/////// Get Data for output to output window
	CString heading, body, eq1S, eq2S, x1S, x2S, areaS;
	
	m_Calculator->DecimalToString(eq1S, m_AreaEq + 1);
	FormatDecimalToString(x1S, m_AreaXmin, 4);
	FormatDecimalToString(x2S, m_AreaXmax, 4);
	
	int decplc = 1;
	while(m_AreaDeltaX != pow(10,(-1*decplc)))
		++decplc;
	FormatDecimalToString(areaS, m_Area, decplc);
	
	heading = "find area";
	body = "equation 1:  y" + eq1S + " = " + m_astrEquationsRaw[m_AreaEq] + "\n";
	if(m_AreaEq2 != -1){
		m_Calculator->DecimalToString(eq2S, m_AreaEq2 + 1);
		body += "equation 2:  y" + eq2S + " = " + m_astrEquationsRaw[m_AreaEq2] + "\n";
	}
	body += "x1 = " + x1S + "\n"
		+ "x2 = " + x2S + "\n";
	if(fAbsolute)
		body += "absolute area = " + areaS;
	else
		body += "area = " + areaS;
	
	m_OutputView->AddEntry(heading, body);
	////////////////////////

	#ifdef GRAPH2D_INFOBAR
		SetInfoBarCtrlSet(GRAPH2D_INFOBAR_AREA, true);
		if(fAbsolute)
			SetDlgItemText(IDC_AREA_VALUE, areaS + " (absolute)");
		else
			SetDlgItemText(IDC_AREA_VALUE, areaS);
	#endif
		
	m_Redraw = true;
	OnPaint();
	m_Calculator->m_base = base;
}


/*********************************************************/
// CGraphView::OnGraphFindArea()
// Pre: none
// Post: toggles finding area
// Return Value: none
// Intent: to handle finding an area.  it toggles the state
//		   if finding area is being turned on, the user is
//		   prompted for information regarding what they want
//		   to find the area of
/*********************************************************/
void CGraphView::OnGraphFindArea() 
{
	if(m_Mode != EUCLIDEAN)
		{
		MessageBox("Find area is only available in Euclidean mode.", "Feature not available", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
		}
	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	bool found_eq(false);
	for(int i(0); i <= 9; ++i){
		if(m_Equations[i].disp)
			found_eq = true;
	}
	if(!found_eq){
		AfxMessageBox("You do not have any equations drawn to find the area with");
		m_Calculator->m_base = base;
		return;
	}

	CFindAreaDlg get_area;
	get_area.PassEq(m_Equations, m_Calculator);

	if(m_FindArea){
		FindAreaOff();
		RePaintNow();
	}
	else if(get_area.DoModal() == IDOK){

		if(get_area.m_Xmin.IsEmpty())
			get_area.m_Xmin = "-1";
		if(get_area.m_Xmax.IsEmpty())
			get_area.m_Xmax = "1";

		if(m_Calculator->Compute(get_area.m_Xmin, m_AreaXmin, this->m_hWnd) != SUCCESSFULL){
			m_Calculator->m_base = base;
			return;
		}

		if(m_Calculator->Compute(get_area.m_Xmax, m_AreaXmax, this->m_hWnd) != SUCCESSFULL){
			m_Calculator->m_base = base;
			return;
		}
		
		if(get_area.m_Between && (get_area.m_Equation2 != get_area.m_Equation))
			get_area.m_Equation2 -= 1;
		else
			get_area.m_Equation2 = -1;

		FindArea(get_area.m_Equation - 1, get_area.m_Equation2, m_AreaXmin, m_AreaXmax, get_area.m_fAbsolute==1);		
	}
	m_Calculator->m_base = base;
}

/*********************************************************/
// CGraphView::ScreenToGraphX(int x, int precision)
// Pre: none
// Post: none
// Return Value: the mapped screen value of x
// Intent: to map a screen x value to the graph x value
/*********************************************************/
long double CGraphView::ScreenToGraphX(int x, int precision)
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			double points = (double(precision) * double(m_graph_width) / 100.0);
			double increment = double((m_EuclideanGraph.m_EuclideanRange.Xmax - m_EuclideanGraph.m_EuclideanRange.Xmin) / points);
			return (m_EuclideanGraph.m_EuclideanRange.Xmin + (double(x - h_space) * increment));
		}
	case POLAR:
		{
			
			double points = (double(precision) * double(m_graph_width) / 100.0);
			double increment = double((m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin) / points);
			return (m_PolarGraph.m_PolarRange.Xmin + (double(x - h_space) * increment));
		}
	case PARAMETRIC:
		return m_ParametricGraph.ScreenToGraphX(CRect(0,0,m_graph_width,m_graph_height), x);
	}
	return 0;
}

/*********************************************************/
// CGraphView::GraphToScreenX(long double x, int precision)
// Pre: none 
// Post: none
// Return Value: the mapped graph value of x
// Intent: to map an x graph value to the screen
/*********************************************************/
int CGraphView::GraphToScreenX(long double x, int precision)
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			double points = (double(precision) * double(m_graph_width) / 100.0);
			double increment = double((m_EuclideanGraph.m_EuclideanRange.Xmax - m_EuclideanGraph.m_EuclideanRange.Xmin) / points);
			return int(((x - m_EuclideanGraph.m_EuclideanRange.Xmin) / increment) + h_space);
		}
	case POLAR:
		{
			double points = (double(precision) * double(m_graph_width) / 100.0);
			double increment = double((m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin) / points);
			return int(((x - m_PolarGraph.m_PolarRange.Xmin) / increment) + h_space);
		}
	case PARAMETRIC:
		return m_ParametricGraph.GraphToScreenX(CRect(0,0,m_graph_width,m_graph_height), x);
	}
	return 0;
}

/*********************************************************/
// CGraphView::ScreenToGraphY(int y)
// Pre: none
// Post: none
// Return Value: the mapped screen value of y
// Intent: to map a screen y value to the graph y value
/*********************************************************/
long double CGraphView::ScreenToGraphY(int y)
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			long double y_ratio = double((m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin))/double(m_graph_height);
			return m_EuclideanGraph.m_EuclideanRange.Ymax - ((y - v_space) * y_ratio);
		}
	case POLAR:
		{
			long double y_ratio = double((m_PolarGraph.m_PolarRange.Ymax-m_PolarGraph.m_PolarRange.Ymin))/double(m_graph_height);
			return m_PolarGraph.m_PolarRange.Ymax - ((y - v_space) * y_ratio);
		}
	case PARAMETRIC:
		{
			return m_ParametricGraph.ScreenToGraphY(CRect(0,0,m_graph_width,m_graph_height), y);
		}
	}
	return 0;
}

/*********************************************************/
// CGraphView::GraphToScreenY(long double y)
// Pre: none
// Post: none
// Return Value: the mapped graph value of y
// Intent: to map an y graph value to the screen
/*********************************************************/
int CGraphView::GraphToScreenY(long double y)
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			long double y_ratio = double((m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin))/double(m_graph_height);
			return int((m_EuclideanGraph.m_EuclideanRange.Ymax - y) / y_ratio) + v_space;
		}
	case POLAR:
		{
			long double y_ratio = double((m_PolarGraph.m_PolarRange.Ymax-m_PolarGraph.m_PolarRange.Ymin))/double(m_graph_height);
			return int((m_PolarGraph.m_PolarRange.Ymax - y) / y_ratio) + v_space;
		}
	}
	return 0;
}

/*********************************************************/
// CGraphView::Integrate()
// Pre: 0 <= m_TraceEq <= 9
// Post: m_Area is set
// Return Value: none
// Intent: to find the area between m_AreaEq and the x axis
//		   or the area between m_AreaEq and m_AreaEq2
/*********************************************************/
void CGraphView::Integrate(bool fAbsolute)
{
	long double x1(m_AreaXmin), x2(m_AreaXmin+m_AreaDeltaX), y, y2;
	ErrorT error;
	
	m_Area = 0;

	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);

	if(m_AreaEq2 == -1){
		while (x2 <= m_AreaXmax){
			CArray<VariableT, VariableT> mmvariables; 
			mmvariables.Add(GetVariable(((m_Mode == POLAR) ? "r" : "x") , ((x1 + x2)/2.0)));
			if((error = m_Calculator->Compute(m_Equations[m_AreaEq].eq, &mmvariables, y, this->m_hWnd)) != SUCCESSFULL)
				{
				if(DIV_ZERO == error)
					continue;
				else
					goto Error;
				}

			if(fAbsolute)
				m_Area += g_Calculator->abs(y*m_AreaDeltaX);
			else
				m_Area += y*m_AreaDeltaX;
			
			x1 = x2;
			x2 += m_AreaDeltaX;
		}
	}
	else{
		while (x2 <= m_AreaXmax){
			CArray<VariableT, VariableT> mmvariables; 
			mmvariables.Add(GetVariable(((m_Mode == POLAR) ? "r" : "x") , ((x1 + x2)/2.0)));
			if((error = m_Calculator->Compute(m_Equations[m_AreaEq].eq, &mmvariables, y, this->m_hWnd)) != SUCCESSFULL)
				{
				if(DIV_ZERO == error)
					continue;
				else
					goto Error;
				}

			if((error = m_Calculator->Compute(m_Equations[m_AreaEq2].eq, &mmvariables, y2, this->m_hWnd)) != SUCCESSFULL)
				{
				if(DIV_ZERO == error)
					continue;
				else
					goto Error;
				}

			if(fAbsolute)
				m_Area += g_Calculator->abs((y - y2)*m_AreaDeltaX);
			else
				m_Area += (y - y2)*m_AreaDeltaX;
			
			x1 = x2;
			x2 += m_AreaDeltaX;
		}

		m_Area = m_Calculator->abs(m_Area);
	}

	Error:
		m_Calculator->m_base = old_base;
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
}

/*********************************************************/
// CGraphView::OnLButtonDblClk(UINT nFlags, CPoint point)
// Pre: none
// Post: none
// Return Value: none
// Intent: caled by framework to handle double clicks
/*********************************************************/
void CGraphView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	SetFocus();

	if(point.x < m_graph_width)
		{
		switch(m_Mode){
		case EUCLIDEAN:
			{
				long double half_x_range = (m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin)/2.0;
				long double half_y_range = (m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin)/2.0;
				
				StoreCurrentRange();
				
				// center graph on point
				m_EuclideanGraph.m_EuclideanRange.Xmax = ScreenToGraphX(point.x, 100) + half_x_range;
				m_EuclideanGraph.m_EuclideanRange.Xmin = m_EuclideanGraph.m_EuclideanRange.Xmax - (half_x_range * 2.0);
				m_EuclideanGraph.m_EuclideanRange.Ymax = ScreenToGraphY(point.y) + half_y_range;
				m_EuclideanGraph.m_EuclideanRange.Ymin = m_EuclideanGraph.m_EuclideanRange.Ymax - (half_y_range * 2.0);
				break;
			}
		case POLAR:
			{
				long double half_x_range = (m_PolarGraph.m_PolarRange.Xmax-m_PolarGraph.m_PolarRange.Xmin)/2.0;
				long double half_y_range = (m_PolarGraph.m_PolarRange.Ymax-m_PolarGraph.m_PolarRange.Ymin)/2.0;
				
				StoreCurrentRange();
				
				// center graph on point
				m_PolarGraph.m_PolarRange.Xmax = ScreenToGraphX(point.x, 100) + half_x_range;
				m_PolarGraph.m_PolarRange.Xmin = m_PolarGraph.m_PolarRange.Xmax - (half_x_range * 2.0);
				m_PolarGraph.m_PolarRange.Ymax = ScreenToGraphY(point.y) + half_y_range;
				m_PolarGraph.m_PolarRange.Ymin = m_PolarGraph.m_PolarRange.Ymax - (half_y_range * 2.0);
				break;
			}
		case PARAMETRIC:
			{
				long double half_x_range = (m_ParametricGraph.m_Xmax-m_ParametricGraph.m_Xmin)/2.0;
				long double half_y_range = (m_ParametricGraph.m_Ymax-m_ParametricGraph.m_Ymin)/2.0;
				
				StoreCurrentRange();
				
				// center graph on point
				m_ParametricGraph.m_Xmax = ScreenToGraphX(point.x, 100) + half_x_range;
				m_ParametricGraph.m_Xmin = m_ParametricGraph.m_Xmax - (half_x_range * 2.0);
				m_ParametricGraph.m_Ymax = ScreenToGraphY(point.y) + half_y_range;
				m_ParametricGraph.m_Ymin = m_ParametricGraph.m_Ymax - (half_y_range * 2.0);
				break;
			}
		}

		m_Redraw = true;
		OnPaint();
		}

	CPropertyPage::OnLButtonDblClk(nFlags, point);
}

/*********************************************************/
// CGraphView::StoreCurrentRange()
// Pre: none
// Post: range is stored
// Return Value: none
// Intent: to store the current range
/*********************************************************/
void CGraphView::StoreCurrentRange()
{
	switch(m_Mode){
	case EUCLIDEAN:	{ m_EuclideanGraph.StoreCurrentRange();	break;	}		
	case POLAR:	{	m_PolarGraph.StoreCurrentRange();	break;	}	
	case PARAMETRIC:	{	m_ParametricGraph.StoreCurrentRange();	break;	}
	}
}

/*********************************************************/
// CGraphView::SetPreviousRange()
// Pre: none
// Post: none
// Return Value: none
// Intent: sets the previous range
/*********************************************************/
void CGraphView::SetPreviousRange()
{
	switch(m_Mode){
	case EUCLIDEAN:	{	m_EuclideanGraph.SetPreviousRange();	break;	}	
	case POLAR:	{	m_PolarGraph.SetPreviousRange();	break;	}
	case PARAMETRIC:	{	m_ParametricGraph.SetPreviousRange();	break;	}
	}
}

/*********************************************************/
// CGraphView::SwapPrevCurRanges()
// Pre: none
// Post: ranges are swapped
// Return Value: none
// Intent: to swp the previous range with the current one
/*********************************************************/
void CGraphView::SwapPrevCurRanges()
{
	switch(m_Mode){
	case EUCLIDEAN:	{	m_EuclideanGraph.SwapPrevCurRanges();	break;	}
	case POLAR:	{	m_PolarGraph.SwapPrevCurRanges();	break;	}
	case PARAMETRIC:	{	m_ParametricGraph.SwapPrevCurRanges();	break;	}
	}
}

BOOL CGraphView::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == 256 && m_Trace && m_PrevMsgTime != pMsg->time){
		m_PrevMsgTime = pMsg->time;

		if(pMsg->wParam == 37){
			OnKeyDown(VK_LEFT, 1, 75);
			return true;
		}
		if(pMsg->wParam == 38){
			OnKeyDown(VK_NUMPAD8, 1, 72);			
			return true;
		}
		if(pMsg->wParam == 39){
			OnKeyDown(VK_RIGHT, 1, 77);
			return true;
		}
		if(pMsg->wParam == 40){
			OnKeyDown(VK_NUMPAD2, 1, 80);
			return true;
		}
	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CGraphView::NextTraceEq(int direction)
{
	if(m_Mode == PARAMETRIC)
		{
		m_ParametricGraph.NextTraceEq(direction, m_TraceEq);
		return;
		}
	
	if(direction == 1){
		if(m_TraceEq >= 9)
			m_TraceEq = 0;
		else
			++m_TraceEq;
		
		for(m_TraceEq; m_TraceEq < 10; ++m_TraceEq){
			
			if(m_Equations[m_TraceEq].disp)
				break;
			else if(m_TraceEq == 9)
				m_TraceEq = -1;
		}
	}
	else{
		if(m_TraceEq <= 0)
			m_TraceEq = 9;
		else
			--m_TraceEq;
		
		for(m_TraceEq; m_TraceEq >= 0; --m_TraceEq){
			if(m_Equations[m_TraceEq].disp)
				break;
			else if(m_TraceEq == 0)
				m_TraceEq = 10;
		}
	}
}

void CGraphView::OnGraphEvaluate()
{
	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	switch(m_Mode){
		case EUCLIDEAN:
		case POLAR:
			{
			bool found_eq(false);
			for(int i(0); i <= 9; ++i){
				if(m_Equations[i].disp)
					found_eq = true;
			}
			if(!found_eq){
				AfxMessageBox("You do not have any equations drawn to evaluate");
				return;
			}

			CEvaluateDlg eval;
			eval.PassVars(m_Equations, m_Calculator, m_Mode);
			eval.DoModal();
			}
		case PARAMETRIC:
			{
			bool found_eq(false);
			for(int i(0); i < MAX_PARAMETRIC_EQUATIONS; ++i){
				if(m_ParametricGraph.m_Equations[i].disp)
					found_eq = true;
			}
			if(!found_eq){
				AfxMessageBox("You do not have any equations drawn to evaluate");
				return;
			}

			C2DEvaluateParametricDlg eval;
			eval.m_Eqs = m_ParametricGraph.m_Equations;
			eval.DoModal();			
			break;
			}
		}

	m_Calculator->m_base = base;
}

void CGraphView::OnCalculateMinMax()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	bool found_eq(false);
	for(int i(0); i <= 9; ++i){
		if(m_Equations[i].disp)
			found_eq = true;
	}
	if(!found_eq){
		AfxMessageBox("You do not have any equations drawn.");
		return;
	}

	C2DMinMaxDlg dlg;
	dlg.m_Eqs = m_Equations;
	dlg.m_astrEquations = m_astrEquationsRaw;
	dlg.DoModal();

	m_Calculator->m_base = old_base;
}

void CGraphView::On2DGraphAnalysisIntercepts()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	bool found_eq(false);
	for(int i(0); i <= 9; ++i){
		if(m_Equations[i].disp)
			found_eq = true;
	}
	if(!found_eq){
		AfxMessageBox("You do not have any equations drawn.");
		return;
	}

	C2DEquationInterceptsDlg intercepts;
	intercepts.m_Eqs = m_Equations;
	intercepts.m_astrEquations = m_astrEquationsRaw;
	intercepts.DoModal();

	m_Calculator->m_base = old_base;
}

void CGraphView::On2DGraphAnalysisIntersectionof2equations()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	int found_eq(0);
	for(int i(0); i <= 9; ++i){
		if(m_Equations[i].disp)
			++found_eq;
	}
	if(found_eq < 2){
		AfxMessageBox("You need at least 2 equations to find an intersection.");
		return;
	}

	C2DEqIntersectionDlg intercept;
	intercept.m_Eqs = m_Equations;
	intercept.m_astrEquations = m_astrEquationsRaw;	
	intercept.DoModal();

	m_Calculator->m_base = old_base;
}

void CGraphView::OnAnalysisTable()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	bool found_eq(false);
	for(int i(0); i <= 9; ++i){
		if(m_Equations[i].disp)
			found_eq = true;
	}
	if(!found_eq){
		AfxMessageBox("You do not have any equations drawn.");
		return;
	}

	C2DTableViewDlg dlg;
	switch(m_Mode){
	case POLAR:
		dlg.m_ldMin = m_PolarGraph.m_PolarRange.Theta_min;
		dlg.m_ldMax = m_PolarGraph.m_PolarRange.Theta_max;
		break;
	case EUCLIDEAN:
		dlg.m_ldMin = m_EuclideanGraph.m_EuclideanRange.Xmin;
		dlg.m_ldMax = m_EuclideanGraph.m_EuclideanRange.Xmax;
		break;
	}
	
	dlg.m_Eqs = m_Equations;
	dlg.m_astrEquations = m_astrEquationsRaw;
	dlg.m_Mode = m_Mode;
	dlg.DoModal();

	m_Calculator->m_base = old_base;
}

void CGraphView::TangentLine(long double eq, long double x)
{	
	InitTangentLine(eq, x);
	m_Redraw = true;
	OnPaint();
}

void CGraphView::OnTangentLine()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}

	if(m_Mode != PARAMETRIC)
		{
		int i=0;
		for(i = 0; i < 10; ++i){
			if(m_Equations[i].disp)
				 break;
			}
		if(i > 9)
			return; // no equations drawn, don't bother tracing
		}
	
	CTangentDlg tang;

	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	tang.PassEq(m_Equations, m_Calculator, m_Mode);
	
	if(tang.DoModal() == IDOK){
		long double x;

		if(tang.m_X.IsEmpty())
			tang.m_X = "0";

		if(m_Calculator->Compute(tang.m_X, x, this->m_hWnd) != SUCCESSFULL){
			m_Calculator->m_base = base;
			return;
		}

		InitTangentLine(tang.m_Eq - 1, x);
		m_Redraw = true;
		OnPaint();
	}

	m_Calculator->m_base = base;
}

void CGraphView::InitTangentLine(int eq, long double x)
{
	long double slope;
	
	m_TangentLine[eq] = true;
	m_Tangent[eq] = x;
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	CString heading, body, eqS, xS, mS;
	
	m_Calculator->DecimalToString(eqS, eq);
	FormatDecimalToString(xS, x, 4);
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			switch(m_EuclideanGraph.DyDx(m_Equations[eq].eq, m_Calculator, x, slope))
				{
				case DIV_ZERO: 
					{
					m_TangentLine[eq] = false;
					heading = "undefined point, tangent line not plotted";
					AfxMessageBox("The equation is not defined at the specified point and can not be drawn");
					break;
					}
				case SUCCESSFULL:
					{
					FormatDecimalToString(mS, slope, 4);
						
					if(mS == "infinitely large"){
						m_TangentLine[eq] = false;
						heading = "infinite slope, tangent line not plotted";
						AfxMessageBox("The slope of the tangent line is infinite and can not be drawn");
					}
					else{	
						heading = "tangent line on";
						body = "equation y" + eqS + " = " + m_astrEquationsRaw[eq] + "\n"
							+ "tangent equation = " + m_EuclideanGraph.GetTangentEquation(m_Equations[eq].eq, m_Calculator, x) + "\n"
							+ "x = " + xS + "\n"
							+ "dy/dx = " + mS;
					}			
					break;
					}
				default:
					{
					m_TangentLine[eq] = false;
					heading = "error calculating point, tangent line not plotted";
					AfxMessageBox("The equation could not be evaluated at the specified point and can not be drawn");
					break;
					}
				}
			break;
		}
	case POLAR:
		{
			switch(m_PolarGraph.DyDx(m_Equations[eq].eq, m_Calculator, x, slope))
				{
				case DIV_ZERO: 
					{
					m_TangentLine[eq] = false;
					heading = "undefined point, tangent line not plotted";
					AfxMessageBox("The equation is not defined at the specified point and can not be drawn");
					break;
					}
				case SUCCESSFULL:
					{
					FormatDecimalToString(mS, slope, 4);
						
					if(mS == "infinitely large"){
						m_TangentLine[eq] = false;
						heading = "infinite slope, tangent line not plotted";
						AfxMessageBox("The slope of the tangent line is infinite and can not be drawn");
					}
					else{	
						heading = "tangent line on";
						body = "equation r" + eqS + " = " + m_astrEquationsRaw[eq] + "\n"
						+ "tangent equation = " + m_PolarGraph.GetTangentEquation(m_Equations[eq].eq, m_Calculator, x) + "\n"
						+ "theta = " + xS + "\n"
						+ "dy/dx = " + mS;
					}			
					break;
					}
				default:
					{
					m_TangentLine[eq] = false;
					heading = "error calculating point, tangent line not plotted";
					AfxMessageBox("The equation could not be evaluated at the specified point and can not be drawn");
					break;
					}
				}
		
			break;
		}
	case PARAMETRIC:
		{
			switch(m_ParametricGraph.DyDx(m_ParametricGraph.m_Equations[eq].xt, m_ParametricGraph.m_Equations[eq].yt, x, slope))
				{
				case DIV_ZERO: 
					{
					m_TangentLine[eq] = false;
					heading = "undefined point, tangent line not plotted";
					AfxMessageBox("The equation is not defined at the specified point and can not be drawn");
					break;
					}
				case SUCCESSFULL:
					{
					FormatDecimalToString(mS, slope, 4);
						
					if(mS == "infinitely large"){
						m_TangentLine[eq] = false;
						heading = "infinite slope, tangent line not plotted";
						AfxMessageBox("The slope of the tangent line is infinite and can not be drawn");
					}
					else{	
						heading = "tangent line on";
						body = "equation y" + eqS + " = " + m_astrEquationsRaw[eq] + "\n"
							+ "tangent equation = " + m_ParametricGraph.GetTangentEquation(m_ParametricGraph.m_Equations[eq].xt, m_ParametricGraph.m_Equations[eq].yt, x) + "\n"
							+ "x = " + xS + "\n"
							+ "dy/dx = " + mS;
					}			
					break;
					}
				default:
					{
					m_TangentLine[eq] = false;
					heading = "error calculating point, tangent line not plotted";
					AfxMessageBox("The equation could not be evaluated at the specified point and can not be drawn");
					break;
					}
				}
			break;
		}
	}	
	
	m_OutputView->AddEntry(heading, body);
	m_Calculator->m_base = old_base;
}

void CGraphView::FormatDecimalToString(CString &str, long double num, int decplaces)
{
	if(-HUGE_VAL == num || HUGE_VAL == num)
		str = "infinitely large";
	else if(num > 9999999999999
	|| num < -9999999999999
	|| ((num < 0.0000000000001) && (num > 0))
	|| (num > -0.0000000000001 && (num < 0))){
		
		str.Format("%e", num);		
	}
	else
		str.Format("%.*f", decplaces,  num);

	DecimalForDisplay(str);
}

void CGraphView::FindDistance(int eq1, int eq2, long double Xmin, long double Xmax)
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	int base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	m_Distance = DONE;

	m_DistanceEqOne = eq1;
	m_DistanceEqTwo = eq2;
	m_DistanceOneX = Xmin;
	m_DistanceTwoX = Xmax;

	/////// Get Data for output to output window
	CString heading, body, eq1S, eq2S, x1S, x2S, distS;
	distS = GetDistanceStr();

	switch(m_Mode){
	case EUCLIDEAN:
		{
			
			FormatDecimalToString(x1S, m_DistanceOneX, 4);
			FormatDecimalToString(x2S, m_DistanceTwoX, 4);
			m_Calculator->DecimalToString(eq1S, m_DistanceEqOne);
			m_Calculator->DecimalToString(eq2S, m_DistanceEqTwo);
			
			heading = "distance";
			body  = "equation 1:  y" + eq1S + " = " + m_astrEquationsRaw[m_DistanceEqOne] + "\n";
			body += "equation 2:  y" + eq2S + " = " + m_astrEquationsRaw[m_DistanceEqTwo] + "\n";
			body += "x1 = " + x1S + "\n"
				  + "x2 = " + x2S + "\n"
				  + "Distance = " + distS;
			
			break;
		}
	case POLAR:
		{
			FormatDecimalToString(x1S, Xmin, 4); // theta min
			FormatDecimalToString(x2S, Xmax, 4); // theta max
			m_Calculator->DecimalToString(eq1S, m_DistanceEqOne);
			m_Calculator->DecimalToString(eq2S, m_DistanceEqTwo);

			m_PolarGraph.SetDistanceThetaOne(Xmin);
			m_PolarGraph.SetDistanceThetaTwo(Xmax);
			
			heading = "distance";
			body  = "equation 1:  r" + eq1S + " = " + m_astrEquationsRaw[m_DistanceEqOne] + "\n";
			body += "equation 2:  r" + eq2S + " = " + m_astrEquationsRaw[m_DistanceEqTwo] + "\n";
			body += "t1 = " + x1S + "\n"
				+ "t2 = " + x2S + "\n"
				+ "Distance = " + distS;
			break;
		}
	}	

	#ifdef GRAPH2D_INFOBAR
		SetInfoBarCtrlSet(GRAPH2D_INFOBAR_DISTANCE, true);
		SetDlgItemText(IDC_DISTANCE_VALUE, distS);
	#endif
	
	m_OutputView->AddEntry(heading, body);
	////////////////////////
	
	RePaintNow();
	m_Calculator->m_base = base;
}

void CGraphView::OnGraphDistance()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	if(m_Distance != OFF){
		m_Distance = OFF;
		#ifdef GRAPH2D_INFOBAR
			SetInfoBarCtrlSet(GRAPH2D_INFOBAR_DISTANCE, false);
		#endif
		PaintNow();
		return;
	}
	else{
		
		int base = m_Calculator->m_base;
		m_Calculator->m_base = 10;
		
		bool found_eq(false);
		for(int i(0); i <= 9; ++i){
			if(m_Equations[i].disp)
				found_eq = true;
		}
		if(!found_eq){
			AfxMessageBox("You do not have any equations drawn to find the area with");
			m_Calculator->m_base = base;
			return;
		}
		
		CDistanceDlg dist;
		dist.PassEq(m_Equations, m_Calculator, m_Mode);
		
		if(dist.DoModal() == IDOK){
			
			if(dist.m_Xmin.IsEmpty())
				dist.m_Xmin = "-1";
			if(dist.m_Xmax.IsEmpty())
				dist.m_Xmax = "1";
			
			long double val1, val2;

			if(m_Calculator->Compute(dist.m_Xmin, val1, this->m_hWnd) != SUCCESSFULL){
				m_Calculator->m_base = base;
				return;
			}
			
			if(m_Calculator->Compute(dist.m_Xmax, val2, this->m_hWnd) != SUCCESSFULL){
				m_Calculator->m_base = base;
				return;
			}

			m_DistanceEqOne = dist.m_Equation - 1;
			
			if(dist.m_Between)
				m_DistanceEqTwo = dist.m_Equation2 - 1;
			else
				m_DistanceEqTwo = m_DistanceEqOne;
			
			FindDistance(m_DistanceEqOne, m_DistanceEqTwo, val1, val2);
			
		}
		m_Calculator->m_base = base;
	}
	
}

bool CGraphView::IsDistanceOn()
{
	if(m_Distance != OFF)
		return true;
	else
		return false;
}

UINT CopyGraph( LPVOID pParam )
{
	CGraphView* pView = (CGraphView*)pParam;
	pView->DoCopy();
	return 0;
}

void CGraphView::DoCopy(){
#ifndef GRAPHCALC_LIGHT
    m_GraphDestination = BMP;
	CBitmap bmp;

	DrawGraph(&bmp);
	
	CDC *pDC = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&bmp);

	DrawTrace(&MemDC);
	DrawDistance(&MemDC);
	DrawText(&MemDC);
	
	MemDC.SelectObject(pOldBitmap);

	m_GraphDestination = SCRN;	
	CopyBitmapToClipboard(this, bmp, 0);
#endif
}

void CGraphView::OnCopyGraph()
{
	AfxBeginThread(CopyGraph, this);
}

void CGraphView::OnClearTangentLines()
{
	for(int i(0); i < 10; ++i)
		m_TangentLine[i] = false;

	RePaintNow();
}

DWORD fpw_bak;
//----------------------------------------------------------
// get_fpcw - Get the floating-point control word.
//----------------------------------------------------------
DWORD get_fpcw()
{
	DWORD _fpcw=0;
	_asm fstcw  word ptr _fpcw
		return _fpcw;
}

//----------------------------------------------------------
// set_fpcw - Set the floating-point control word.
//----------------------------------------------------------
void set_fpcw(DWORD _fpcw)
{
	_asm fldcw  word ptr _fpcw
}

void CGraphView::OnGraphPrint() 
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	fpw_bak = get_fpcw();
	m_PrintDlg = new CPrint();

	m_PrintDlg->m_Calculator = m_Calculator;
	m_PrintDlg->m_graph_width = m_graph_width;
	m_PrintDlg->m_graph_height = m_graph_height;

	if(m_PrintDlg->DoModal() == IDCANCEL){            // Get printer settings from user
		set_fpcw(fpw_bak);
		return;
	}
	
	CDC dc;
	dc.Attach(m_PrintDlg->m_PrintDlg.GetPrinterDC());         // Attach a printer DC
	dc.SetViewportOrg(0,0);
    dc.m_bPrinting = TRUE;
	
	DOCINFO di;                                 // Initialise print document details
    ::ZeroMemory (&di, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = "GraphCalc Graph";
	
	BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job

    // Get the printing extents and store in the m_rectDraw field of a 
    // CPrintInfo object
    CPrintInfo Info;
    Info.m_rectDraw.SetRect(0,0, 
		dc.GetDeviceCaps(HORZRES), 
		dc.GetDeviceCaps(VERTRES));
    Info.m_nCurPage = 1;
	int w(m_graph_width), h(m_graph_height);
	
	// PRINTING DRAWING AND VIEWPORT OPTIONS
	bool centered(m_PrintDlg->m_bCenter == 1);
	
	// SET COORDINATES AND MAPPING
	dc.SetMapMode(MM_ANISOTROPIC);
	
	if(!bPrintingOK){
		set_fpcw(fpw_bak);
		MessageBox("There was an error while printing.  It could be that you have run out of memory or your printer is not set up correctly.",
			"Error Printing", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
	}
	
	// start page
	dc.StartPage();    	

	//////////////////////////////////////////////
	/// REPLOT
	dc.SetWindowExt(Info.m_rectDraw.Width(), Info.m_rectDraw.Height());
	dc.SetViewportExt(Info.m_rectDraw.Width(), Info.m_rectDraw.Height());
	dc.SelectClipRgn(NULL);
	
	switch(m_PrintDlg->m_iPageSize){
	case 1:
		{
			double scale;
			if((double(Info.m_rectDraw.Width()) / double(m_graph_width)) > 
				(double(Info.m_rectDraw.Height()) / double(m_graph_height)))
				scale = (double(Info.m_rectDraw.Height()) / 2.0) / double(m_graph_height);
			else
				scale = (double(Info.m_rectDraw.Width()) / 2.0) / double(m_graph_width);
			
			m_graph_height *= scale;
			m_graph_width *= scale;
			break;
		}
	case 0:
		{
			m_graph_width = Info.m_rectDraw.Width();
			m_graph_height = Info.m_rectDraw.Height();
			break;
		}
	default:
		{
			long double ww, hh;
			m_Calculator->StringToDecimal(m_PrintDlg->m_sWidth, 10, ww);
			m_Calculator->StringToDecimal(m_PrintDlg->m_sHeight, 10, hh);
			ww = m_Calculator->abs(ww);
			hh = m_Calculator->abs(hh);
			
			if(ww == 0)
				ww = 4;
			if(hh == 0)
				hh = 4;
			
			if(m_PrintDlg->m_sWUnits == "cm")
				ww *= 0.39370078740157;
			m_graph_width = dc.GetDeviceCaps(LOGPIXELSX) * ww;
			if(m_PrintDlg->m_sHUnits == "cm")
				hh *= 0.39370078740157;
			m_graph_height = dc.GetDeviceCaps(LOGPIXELSY) * hh;
			break;
		}
	}
	
	////////
	// we now have the graph width and height set in pixels
	////////
	
	CPoint max_range(Info.m_rectDraw.Width(), Info.m_rectDraw.Height());
	CPoint org(0,0);
	
	if(m_PrintDlg->m_bTitleOn){
		org.y += (dc.GetDeviceCaps(LOGPIXELSY) * (0.25 + 0.125));
		max_range.y -= (dc.GetDeviceCaps(LOGPIXELSY) * (0.25 + 0.125));
	}
	if(m_PrintDlg->m_bEquations)
		max_range.y -= (dc.GetDeviceCaps(LOGPIXELSY) * (1.5 + 0.125));
	
	if(m_graph_width > max_range.x)
		m_graph_width = max_range.x;
	if(m_graph_height > max_range.y)
		m_graph_height = max_range.y;
	
	////////
	// we now have the width and height of graph that we will display with
	// and also the max width and height possible
	////////
	
	if(centered){
		org.x = (double(Info.m_rectDraw.Width()) / 2.0) - (double(m_graph_width) / 2.0);
		
		double hh(m_graph_height);
		if(m_PrintDlg->m_bTitleOn)
			hh += (dc.GetDeviceCaps(LOGPIXELSY) * (0.25 + 0.125));
		if(m_PrintDlg->m_bEquations)
			hh += (dc.GetDeviceCaps(LOGPIXELSY) * (1.5 + 0.125));
		
		org.y += (double(Info.m_rectDraw.Height()) / 2.0) - (hh / 2.0);
	}
	
	
	if(m_PrintDlg->m_bTitleOn)
		DrawTitle(&dc, CSize(m_graph_width, m_graph_height));
	
	dc.SetViewportOrg(org.x, org.y);
	////////
	// the viewport origin is now set
	////////
	
	CPoint ul(0,0), lr(m_graph_width, m_graph_height);
	dc.LPtoDP(&ul);  // convert points ot device units
	dc.LPtoDP(&lr);  // convert points ot device units
	m_GraphRgn.SetRectRgn(ul.x, ul.y, lr.x, lr.y);
	
	////////
	// the clipping rectangle is now set
	////////
	m_ActiveDrawFontSize.x = dc.GetDeviceCaps(LOGPIXELSX)*0.058;
	m_ActiveDrawFontSize.y = dc.GetDeviceCaps(LOGPIXELSY)*0.085;
	////////
	// font used for title is set
	////////
	
	if(m_PrintDlg->m_bEquations)
		DrawEquationList(&dc, CSize(m_graph_width, m_graph_height), max_range, org);
	
	/// END REPLOT
	//////////////////////////////////////////////
		
	// Set clip rectangle
	dc.SelectClipRgn(&m_GraphRgn);
	m_GraphThreshold = CRect(0, 0 - threshold, m_graph_width, m_graph_height + threshold);            
	
	// DRAW GRAPH BACKGROUND
	CBrush brush(m_BackgroundClr), *pOldBrush;
	pOldBrush = dc.SelectObject(&brush);
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
	CPen* pOldPen = dc.SelectObject(&penBlack);
	dc.Rectangle(0, 0, m_graph_width, m_graph_height);
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	pOldBrush = 0;
	delete pOldBrush;
	
	m_GraphDestination = PRINT;
	// Draw PARTS OF GRAPH //
	DrawArea(&dc);

	if(m_Grid)
		DrawGrid(&dc);
	if(m_Coords)
		DrawCoordsLabels(&dc);
	if(m_Axis)
		DrawAxis(&dc);

	DrawEquations(&dc);
	DrawTrace(&dc);
	DrawDistance(&dc);
	DrawText(&dc);
	
	bPrintingOK = (dc.EndPage() > 0);       // end page
	
	////////////////////////////////////////
	// OnCompletePrinting
	m_ActiveDrawFontSize.x = m_DrawFontSize.x;
	m_ActiveDrawFontSize.y = m_DrawFontSize.y;

	m_graph_width = w;
	m_graph_height = h;	
    if (bPrintingOK)
        dc.EndDoc();                            // end a print job
    else
        dc.AbortDoc();                          // abort job.
	
    dc.Detach();                                // detach the printer DC
	m_GraphDestination = SCRN;
	
	delete m_PrintDlg;
	set_fpcw(fpw_bak);
}

void CGraphView::DrawEquationList(CDC *pDC, const CSize &graph_size, const CPoint &max_range, const CPoint &org)
{
	CBrush brush(RGB(255,255,255)), *pOldBrush;
	pOldBrush = pDC->SelectObject(&brush);
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);
	pDC->SelectObject(&brush);
	
	//////////// Draw Equations List Box
	CPoint estart;
	CPoint eend;
	
	// replot
	estart.x = 0;
	estart.y = graph_size.cy +(0.125 * pDC->GetDeviceCaps(LOGPIXELSY));
	eend.x = graph_size.cx;
	eend.y = graph_size.cy + ((1.5 + 0.125) * pDC->GetDeviceCaps(LOGPIXELSY));
	
	int ew(graph_size.cx);
	if(ew < (5 * pDC->GetDeviceCaps(LOGPIXELSX))) // check for min eqs list size
		ew = (5 * pDC->GetDeviceCaps(LOGPIXELSX));
	
	if(ew > (max_range.x * pDC->GetDeviceCaps(LOGPIXELSX)))
		ew = max_range.x;
	if((eend.y - estart.y) > (max_range.y * pDC->GetDeviceCaps(LOGPIXELSY)))
		eend.y = estart.y + max_range.y;
	
	estart.x = (double(graph_size.cx) / 2.0) - (double(ew) / 2.0);
	if(estart.x < (-1*org.x))
		estart.x = org.x;
	
	eend.x = estart.x + ew;
	// end replot


	pDC->Rectangle(estart.x, estart.y, eend.x, eend.y);
	//////////// END Draw Equations List Box
	
	//////////// Draw Key boxes
	DrawEquationLegend(pDC, CRect(estart, eend), graph_size);
	//////////// END Draw Key boxes
	
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CGraphView::DrawEquationLegend(CDC *pDC, CRect eq_rect, const CSize &graph_size)
{
	double space_frac, size, space;

	CPoint start1;
	CPoint start2;

	// replot
	space_frac = 0.5;
	size = 1.5 / (5 + (6*space_frac));
	space = size * space_frac;
	
	size *= pDC->GetDeviceCaps(LOGPIXELSY);
	space *= pDC->GetDeviceCaps(LOGPIXELSY);
	
	start1.x = eq_rect.left + (0.25 * pDC->GetDeviceCaps(LOGPIXELSX));
	start1.y = eq_rect.top;
	start2.x = eq_rect.left + (eq_rect.Width() / 2) + (0.25 * pDC->GetDeviceCaps(LOGPIXELSX));
	start2.y = eq_rect.top;
	// end replot

	// count total displayed eqs
	int total_count(0), i, count;
	for(i = 0; i < 10; ++i){
		if(m_Equations[i].disp)
			++total_count;
	}

	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);
	CFont eqFont;
	eqFont.CreateFont(size/1.5, 
					 (size/4.0),
						 0,0,
						 FW_REGULAR,
						 FALSE,FALSE,
						 0,
						 ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						 DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_PITCH | FF_SWISS, 
						 "Arial");
	CFont *pOldFont = pDC->SelectObject(&eqFont);

	// do column 1
	count = (total_count / 2);
	count += (total_count % 2);
	int cur(-1);
	for(i = 0; cur < (count - 1); ++i){
		if(m_Equations[i].disp){
			++cur;
			int x = start1.x;
			int y = start1.y + cur*size + (cur + 1)*space;

			CBrush brush(m_Equations[i].color), *pOldBrush;
			pOldBrush = pDC->SelectObject(&brush);

			pDC->Rectangle(x, y, x+size, y+size);
			pDC->SetTextAlign(TA_LEFT);
			pDC->SetTextColor(RGB(0,0,0));
			pDC->TextOut( x + (1.5*size), y + (size/2) - ((size/1.5)/2.0), m_astrEquationsRaw[i]);
			
			pDC->SelectObject(pOldBrush);
		}
	}

	// do column 2
	count = (total_count / 2);
	cur = -1;
	for(; (cur < (count - 1)) && (i < 10); ++i){
		if(m_Equations[i].disp){
			++cur;
			int x = start2.x;
			int y = start2.y + cur*size + (cur + 1)*space;

			CBrush brush(m_Equations[i].color), *pOldBrush;
			pOldBrush = pDC->SelectObject(&brush);

			pDC->Rectangle(x, y, x+size, y+size);
			pDC->SetTextAlign(TA_LEFT);
			pDC->SetTextColor(RGB(0,0,0));
			pDC->TextOut( x + (1.5*size), y + (size/2) - ((size/1.5)/2.0), m_astrEquationsRaw[i]);
			
			pDC->SelectObject(pOldBrush);
		}
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CGraphView::DrawTitle(CDC *pDC, const CSize &graph_size)
{
	CFont titleFont;
	pDC->SetViewportOrg(0, 0);

	// replot
	titleFont.CreateFont(pDC->GetDeviceCaps(LOGPIXELSY)*0.35, 
						 pDC->GetDeviceCaps(LOGPIXELSX)*0.18,
						 0,0,
						 FW_BOLD,
						 FALSE,FALSE,
						 0,
						 ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						 DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_PITCH | FF_SWISS, 
						 "Arial");
	
	CFont *pOldFont = pDC->SelectObject(&titleFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetTextAlign(TA_LEFT);
	pDC->TextOut(0, 0, m_PrintDlg->m_sTitle);
	pDC->SelectObject(pOldFont);
}



void CGraphView::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);

	PositionToolbar();
	
#ifdef GRAPH2D_INFOBAR
	RePositionInfoBar(CPoint(cx - GRAPH2D_INFOBAR_WIDTH, m_fToolbarOn ? ToolbarHeight() : 0));
#endif
}

void CGraphView::SetEquation(int eq, CString val, UINT xy)
{
	switch(xy)
		{
		case PARAMETRIC_EQ_NONE:
			{
			Assert(eq >= 0 && eq <= 9);
			if(eq < 0 || eq > 9)
				return;

			m_astrEquationsRaw[eq] = val;
			ExpandEquations();
			break;
			}
		case PARAMETRIC_EQ_X:
		case PARAMETRIC_EQ_Y:
			Assert(eq >= 0 && eq <= 4 && (xy == 1 || xy == 2));
			if(eq < 0 || eq > 4)
				return;

			switch(xy){
				case PARAMETRIC_EQ_X: m_ParametricGraph.m_Equations[eq].xt = val; break;
				case PARAMETRIC_EQ_Y: m_ParametricGraph.m_Equations[eq].yt = val; break;
				}
			break;
		}				

	GraphInfoBar(UpdateInfoBarEquation(eq));
}

void CGraphView::EmptyAllEquations()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	int i;
	for(i=0; i < MAX_EQUATIONS; ++i)
		{
		m_Equations[i].disp = false;
		m_Equations[i].eq = m_astrEquationsRaw[i] = "";
		}
	ExpandEquations();
	GraphInfoBar(UpdateInfoBarEquations());
}

void CGraphView::SetAllEquationState(bool val)
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	for(int i=0; i < MAX_EQUATIONS; ++i)
		m_Equations[i].disp = val;
	
	for(i=0; i < MAX_EQUATIONS; ++i)
		m_Equations[i].disp = val;

	
	GraphInfoBar(UpdateInfoBarEquations());
}
void CGraphView::SetEquationState(int eq, bool val)
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	Assert(eq >= 0 && eq <= 9);
	
	if(eq < 0 || eq > 9)
		return;

	m_Equations[eq].disp = val;
	GraphInfoBar(UpdateInfoBarEquation(eq));
}

void CGraphView::SetEquationColor(int eq, CString val)
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}
	
	Assert(eq >= 0 && eq <= 9);
	
	if(eq < 0 || eq > 9)
		return;

	m_Equations[eq].color = ColorLookup(val);
	GraphInfoBar(UpdateInfoBarEquationColors());
}

void CGraphView::SetBackgroundColor(CString color){ m_BackgroundClr = ColorLookup(color); }
void CGraphView::SetAxisColor(CString color){ m_AxisStyle.color = ColorLookup(color); }
void CGraphView::SetGridColor(CString color){ m_GridStyle.color = ColorLookup(color); }
void CGraphView::SetCoordinatesColor(CString color){ m_CoordsClr = ColorLookup(color); }
void CGraphView::SetOtherTextColor(CString color){ m_TextClr = ColorLookup(color); }
void CGraphView::SetAreaColor(CString color){ m_AreaClr = ColorLookup(color); }


COLORREF CGraphView::ColorLookup(CString color)
{
	if(color == "Black")					return RGB(0x00, 0x00, 0x00);
    else if(color == "Brown")				return RGB(0xA5, 0x2A, 0x00);
    else if(color == "Dark Olive Green")	return RGB(0x00, 0x40, 0x40);
    else if(color == "Dark Green")			return RGB(0x00, 0x55, 0x00);
    else if(color == "Dark Teal")			return RGB(0x00, 0x00, 0x5E);
    else if(color == "Dark Blue")			return RGB(0x00, 0x00, 0x8B);
    else if(color == "Indigo")				return RGB(0x4B, 0x00, 0x82);
    else if(color == "Dark grey")			return RGB(0x28, 0x28, 0x28);

    else if(color == "Dark Red")			return RGB(0x8B, 0x00, 0x00);
    else if(color == "Orange")				return RGB(0xFF, 0x68, 0x20);
    else if(color == "Dark yellow")			return RGB(0x8B, 0x8B, 0x00);
    else if(color == "Green")				return RGB(0x00, 0x93, 0x00);
    else if(color == "Teal")				return RGB(0x38, 0x8E, 0x8E);
    else if(color == "Blue")				return RGB(0x00, 0x00, 0xFF);
    else if(color == "Blue-Grey")			return RGB(0x7B, 0x7B, 0xC0);
    else if(color == "Grey-40")				return RGB(0x66, 0x66, 0x66);

    else if(color == "Red")					return RGB(0xFF, 0x00, 0x00);
    else if(color == "Light Orange")		return RGB(0xFF, 0xAD, 0x5B);
    else if(color == "Lime")				return RGB(0x32, 0xCD, 0x32);
    else if(color == "Sea Green")			return RGB(0x3C, 0xB3, 0x71);
    else if(color == "Aqua")				return RGB(0x7F, 0xFF, 0xD4);
    else if(color == "Light Blue")			return RGB(0x7D, 0x9E, 0xC0);
    else if(color == "Violet")				return RGB(0x80, 0x00, 0x80);
    else if(color == "Grey-50")				return RGB(0x7F, 0x7F, 0x7F);

    else if(color == "Pink")				return RGB(0xFF, 0xC0, 0xCB);
    else if(color == "Gold")				return RGB(0xFF, 0xD7, 0x00);
    else if(color == "Yellow")				return RGB(0xFF, 0xFF, 0x00);
    else if(color == "Bright Green")		return RGB(0x00, 0xFF, 0x00);
    else if(color == "Turquoise")			return RGB(0x40, 0xE0, 0xD0);
    else if(color == "Skyblue")				return RGB(0xC0, 0xFF, 0xFF);
    else if(color == "Plum")				return RGB(0x48, 0x00, 0x48);
    else if(color == "Light Grey")			return RGB(0xC0, 0xC0, 0xC0);

    else if(color == "Rose")				return RGB(0xFF, 0xE4, 0xE1);
    else if(color == "Tan")					return RGB(0xD2, 0xB4, 0x8C);
    else if(color == "Light Yellow")		return RGB(0xFF, 0xFF, 0xE0);
    else if(color == "Pale Green ")			return RGB(0x98, 0xFB, 0x98);
    else if(color == "Pale Turquoise")		return RGB(0xAF, 0xEE, 0xEE);
    else if(color == "Pale Blue")			return RGB(0x68, 0x83, 0x8B);
    else if(color == "Lavender")			return RGB(0xE6, 0xE6, 0xFA);
    else if(color == "White")				return RGB(0xFF, 0xFF, 0xFF);

	return RGB(0,0,0);
}


void CGraphView::PaintNow()
{
	OnPaint();
}

void CGraphView::RePaintNow()
{
	m_Redraw = true;
	OnPaint();
}

void CGraphView::SaveBitmap(CString file)
{
	CClientCapture CapturedImage;

	////////
	m_GraphDestination = BMP;
	CBitmap bmp;

	DrawGraph(&bmp);
	
	CDC *pDC = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&bmp);

	DrawTrace(&MemDC);
	DrawDistance(&MemDC);
	DrawText(&MemDC);
	
	MemDC.SelectObject(pOldBitmap);

	m_GraphDestination = SCRN;	
	//////////////

	CapturedImage.WriteBitmapToDIB(GetDC(), bmp);
	CapturedImage.WriteDIB(file);
	CapturedImage.Release();		
	//Invalidate(TRUE);
}

BOOL CGraphView::OnSetActive() 
{
	#ifdef AUTO_PARAMETRIC
	m_Mode = PARAMETRIC; // TEMPORARY CODE FOR TESTING PARAMETRIC
	#endif

	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	Assert(pDlg);
	
	pDlg->SetMenu(&m_Menu2DGraph);

	m_fSaveSettings = true;

	pDlg->PostMessage(WM_SETFULLWINDOW, 1, 0);

	GraphInfoBar(UpdateInfoBar(true));
	GraphInfoBar(UpdateInfoBarCtrls(true));

	GraphInfoBar(ShowInfoBar(m_fInfoBar));
	//GraphInfoBar(PositionInfoBar());
	
	if(m_fNSliderOn)
		m_pSliderDlg->ShowWindow(SW_SHOW);	
	
	return CPropertyPage::OnSetActive();
}

BOOL CGraphView::OnKillActive() 
{
	if(m_fNSliderOn)
		m_pSliderDlg->ShowWindow(SW_HIDE);	
	
	return CPropertyPage::OnKillActive();
}

void CGraphView::OnSaveAsBitmap()
{
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Windows Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL );

	if(FileDialog.DoModal() == IDOK){
		BeginWaitCursor();
		SaveBitmap(FileDialog.GetPathName());
		EndWaitCursor();
	}
}


UINT CGraphView::OnGetDlgCode( ){

	return(DLGC_WANTALLKEYS);
}

void CGraphView::CenterGraph(long double x, long double y)
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			long double half_x_range = (m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin)/2.0;
			long double half_y_range = (m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin)/2.0;
			
			StoreCurrentRange();
			
			// center graph on point
			m_EuclideanGraph.m_EuclideanRange.Xmax = x + half_x_range;
			m_EuclideanGraph.m_EuclideanRange.Xmin = m_EuclideanGraph.m_EuclideanRange.Xmax - (half_x_range * 2.0);
			m_EuclideanGraph.m_EuclideanRange.Ymax = y + half_y_range;
			m_EuclideanGraph.m_EuclideanRange.Ymin = m_EuclideanGraph.m_EuclideanRange.Ymax - (half_y_range * 2.0);
			break;
		}
	case POLAR:
		{
			long double half_x_range = (m_PolarGraph.m_PolarRange.Xmax-m_PolarGraph.m_PolarRange.Xmin)/2.0;
			long double half_y_range = (m_PolarGraph.m_PolarRange.Ymax-m_PolarGraph.m_PolarRange.Ymin)/2.0;
			
			StoreCurrentRange();
			
			// center graph on point
			m_PolarGraph.m_PolarRange.Xmax = x + half_x_range;
			m_PolarGraph.m_PolarRange.Xmin = m_PolarGraph.m_PolarRange.Xmax - (half_x_range * 2.0);
			m_PolarGraph.m_PolarRange.Ymax = y + half_y_range;
			m_PolarGraph.m_PolarRange.Ymin = m_PolarGraph.m_PolarRange.Ymax - (half_y_range * 2.0);
			break;
		}
	}

	m_Redraw = true;
	OnPaint();
}


void CGraphView::ExpandEquationsValidate()
{
	Assert(m_Mode != PARAMETRIC);
	
	for(int i=0; i < 10; ++i)
		{
		if(!ExpandEq(i, m_Equations[i].eq))
			m_Equations[i].disp = false;
		else
			if(!g_Calculator->IsValid(m_Equations[i].eq))
				m_Equations[i].disp = false;
		}
}

void CGraphView::ExpandEquations()
{
	for(int i=0; i < 10; ++i)
		if(!ExpandEq(i, m_Equations[i].eq))
			m_Equations[i].disp = false;
}

// eq is the index of the eq
bool CGraphView::ExpandEq(int eq, CString &expnEq)
{
	expnEq = m_astrEquationsRaw[eq];
	
	int i=0;
	for(i=0; i < 10; ++i)
		{
		CString eqs;
		if(m_Mode == EUCLIDEAN) eqs.Format("y%d", i+1);
		else eqs.Format("r%d", i+1);
		
		if(0 <= expnEq.Find("("+eqs+")"))
			{
			if(i == eq)
				return false;
			
			CString subExpnEq;
			if(ExpandEq(i, subExpnEq, "" + char('0' + eq)))
				expnEq.Replace(eqs, "("+subExpnEq+")");
			else
				{
				MessageBox("Equation self dependancy detected!","Self Dependancy", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				return false; // error, infinite loop fo eq referrers
				}
			}
		}
	return true;
}

bool CGraphView::ExpandEq(int eq, CString &expnEq, CString strEqStack)
{
	expnEq = m_astrEquationsRaw[eq];
	
	int i=0;

	for(i=0; i < 10; ++i)
		{
		CString eqs;
		if(m_Mode == EUCLIDEAN) eqs.Format("y%d", i+1);
		else eqs.Format("r%d", i+1);
		
		if(0 <= expnEq.Find("("+eqs+")"))
			{
			if(0 <= strEqStack.Find(char('0' + i)))
				return false;
			
			CString subExpnEq;
			if(ExpandEq(i, subExpnEq, strEqStack + char('0' + eq)))
				expnEq.Replace(eqs, "("+subExpnEq+")");
			else
				return false; // error, infinite loop fo eq referrers
			}
		}
	return true;
}

BOOL CGraphView::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CMenu PopUp2DGraph, PopUpView;
	PopUp2DGraph.LoadMenu(IDR_2DGRAPH);
	PopUpView.LoadMenu(IDR_2DGRAPH_VIEW);
	m_Menu2DGraph.LoadMenu(IDR_MENU);

	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->AddScriptLibraryMenu(m_Menu2DGraph, 3);
	
	m_Menu2DGraph.InsertMenu(3, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)PopUp2DGraph.m_hMenu, "2D Graph");
	m_Menu2DGraph.InsertMenu(6, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)PopUpView.m_hMenu, "View");

	PopUp2DGraph.Detach();
	PopUpView.Detach();

	InitToolbar();
	
	ShowInfoBar(m_fInfoBar);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGraphView::InitToolbar() 
{
		// Create the Toolbar and attach the resource
	if(!m_wndToolBar.Create(this) 
	|| !m_wndToolBar.LoadToolBar(IDR_2DGRAPH))
	{
	 TRACE0("Failed to Create Dialog Toolbar\n");
	 EndDialog(IDCANCEL);
	}
	
	m_wndToolBar.SetBarStyle(CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | 
						CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_TOOLTIPS);
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);

	PositionToolbar();
}

void CGraphView::PositionToolbar() 
{
	CRect	rcClientOld; // Old Client Rect
	CRect	rcClientNew; // New Client Rect with Tollbar Added
	GetClientRect(rcClientOld); // Retrive the Old Client WindowSize

	// Called to reposition and resize control bars in the client 
	// area of a window. The reposQuery FLAG does not really draw the 
	// Toolbar.  It only does the calculations. And puts the new 
	// ClientRect values in rcClientNew so we can do the rest of the 
	// Math.
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,
	 AFX_IDW_CONTROLBAR_LAST,0,reposQuery,rcClientNew, false);

	// All of the Child Windows (Controls) now need to be moved so 
	// the Tollbar does not cover them up. Offest to move all child 
	// controls after adding Tollbar
	CPoint ptOffset(rcClientNew.left-rcClientOld.left,
	 rcClientNew.top-rcClientOld.top);

	CRect	rcChild;

	// Handle to the Dialog Controls
	/*CWnd*	pwndChild = GetWindow(GW_CHILD);  
	while(pwndChild) // Cycle through all child controls
	{
	 pwndChild->GetWindowRect(rcChild); // Get the child control RECT
	 ScreenToClient(rcChild); 

	// Changes the Child Rect by the values of the calculated offset
	 rcChild.OffsetRect(ptOffset); 
	  pwndChild->MoveWindow(rcChild,FALSE); // Move the Child Control
	  pwndChild = pwndChild->GetNextWindow();
	}*/

	/*CRect	rcWindow;
	GetWindowRect(rcWindow); // Get the RECT of the Dialog

	// Increase width to new Client Width
	rcWindow.right += rcClientOld.Width() - rcClientNew.Width(); 

	// Increase height to new Client Height
	rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height(); 
	*/
	//MoveWindow(rcWindow,FALSE); // Redraw Window

	// Now we REALLY Redraw the Toolbar
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,
	 AFX_IDW_CONTROLBAR_LAST,0);

	if(m_wndToolBar.m_hWnd)
		m_wndToolBar.ShowWindow(m_fToolbarOn);
}

void CGraphView::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CPropertyPage::OnCaptureChanged(pWnd);
}

LRESULT CGraphView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	#ifdef GRAPH2D_INFOBAR
		if(!m_fInfoBar)
			{
			switch(message)
				{
				case WM_ERASEBKGND: 
					return (LRESULT)1;
				}
			}
	#endif
	
	return CPropertyPage::DefWindowProc(message, wParam, lParam);
}

LRESULT CGraphView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	#ifndef GRAPH2D_INFOBAR
		if(message == WM_ERASEBKGND && !m_fInfoBar)
			return (LRESULT)1; // Say we handled it.
	#endif

	return CPropertyPage::WindowProc(message, wParam, lParam);
}

BOOL CGraphView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CGraphView::OnAnalysisNslider()
{
	if(!m_fNSliderOn)
		{
		m_pSliderDlg= new C2DNSliderDlg(this);
		m_pSliderDlg->Create(IDD_2DGRAPH_N);
		m_pSliderDlg->ShowWindow(SW_SHOW);	
		m_fNSliderOn = true;
		}
	else
		{
		Assert(m_pSliderDlg);
		m_pSliderDlg->SendMessage(WM_CLOSE);
		m_fNSliderOn = false;
		}
}

void CGraphView::On2DNSliderClosing(WPARAM wParam, LPARAM lParam)
{
	m_fNSliderOn = false;
}

int CGraphView::ToolbarHeight()
{
	if(IsWindow(m_wndToolBar.m_hWnd))
		{
		CRect toolbar;
		m_wndToolBar.GetWindowRect(toolbar);
		return toolbar.Height() + 4;
		}
	else
		return 36;
}

void CGraphView::OnToolbar()
{	
	HaltRedraw();
	m_fToolbarOn = !m_fToolbarOn;
	
	m_wndToolBar.ShowWindow(m_fToolbarOn);

	GraphInfoBar(PositionInfoBar());
		
	if(m_fToolbarOn)
		m_graph_height -= ToolbarHeight();
	else
		m_graph_height += ToolbarHeight();

	RePaintNow();
	InvalidateRedraw()

	CRect client;
	GetClientRect(client);	

	InvalidateRect(CRect(client.right-BUTTON_PALLETE_WIDTH, 0, client.right, client.bottom), true);

	if(m_fToolbarOn)
		{
		InvalidateRect(CRect(0, 0, client.right, 2), true); // some 2 pixel strip on top isn't getting cleared
		InvalidateRect(CRect(0,0, client.right, ToolbarHeight()+10), true); // some 2 pixel strip on top isn't getting cleared
		}
		
	m_wndToolBar.Invalidate();

}


inline double CGraphView::GetXPixelIncrement()
{
	switch(m_Mode)
		{
		case EUCLIDEAN: return (m_EuclideanGraph.m_EuclideanRange.Xmax - m_EuclideanGraph.m_EuclideanRange.Xmin) / double(m_graph_width);
		case POLAR:		return (m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin) / double(m_graph_width);
		case PARAMETRIC:		return (m_ParametricGraph.m_Xmax - m_ParametricGraph.m_Xmin) / double(m_graph_width);
		}
	return 0;
}

inline double CGraphView::GetYPixelIncrement()
{
	switch(m_Mode)
		{
		case EUCLIDEAN: return (m_EuclideanGraph.m_EuclideanRange.Ymax - m_EuclideanGraph.m_EuclideanRange.Ymin) / double(m_graph_height);
		case POLAR:		return (m_PolarGraph.m_PolarRange.Ymax - m_PolarGraph.m_PolarRange.Ymin) / double(m_graph_height);
		case PARAMETRIC:		return (m_ParametricGraph.m_Ymax - m_ParametricGraph.m_Ymin) / double(m_graph_height);
		}
	return 0;
}

void CGraphView::OnCreateAnimationScript()
{
	if(m_Mode == PARAMETRIC)
		{
		MessageBox("not yet implemented");
		return;
		}

	C2DCreateAnimationScriptDlg dlgType;

	if(IDOK != dlgType.DoModal())
		return;

	static char BASED_CODE szFilter[] = "GraphCalc Script (*.gcs)|*.gcs||";
	CFileDialog *fileDlg = new CFileDialog(false, 
										"gcs",
										NULL,
										OFN_ENABLESIZING 
										| OFN_CREATEPROMPT 
										| OFN_HIDEREADONLY 
										| OFN_OVERWRITEPROMPT,
										szFilter,
										this);

	if(fileDlg->DoModal() != IDOK)
		{
		delete fileDlg;
		return;
		}


	switch(dlgType.m_nType)
		{
		case ANIMATION_TYPE_REALTIME:
			CreateAnimationRealTimeScript(fileDlg->GetPathName(), 
									   m_pSliderDlg->GetFieldValue(IDC_N_MIN), 
									   m_pSliderDlg->GetFieldValue(IDC_N_STEP), 
									   m_pSliderDlg->GetFieldValue(IDC_N_MAX),
									   dlgType.m_nRangeOption,
									   (dlgType.m_nXTimes == ANIMATION_RANGE_LOOP_X) ? dlgType.m_nTimesThrough : -1);
			break;
		case ANIMATION_TYPE_FRAMES:
			CreateAnimationFramesScript(fileDlg->GetPathName(), 
									   m_pSliderDlg->GetFieldValue(IDC_N_MIN), 
									   m_pSliderDlg->GetFieldValue(IDC_N_STEP), 
									   m_pSliderDlg->GetFieldValue(IDC_N_MAX),
									   dlgType.m_nRangeOption,
									   dlgType.m_nTimesThrough);
			break;
		}

	if(dlgType.m_fRun)
		{
		CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
		pDlg->RunScript(fileDlg->GetPathName());
		}

	delete fileDlg;
}

#define PrintLineRaw(strToPrint) \
	{							\
	str = strToPrint; 			\
	outfile.write(str.GetBuffer(str.GetLength()), str.GetLength()); \
	}

#define NewLine() PrintLineRaw("\n")

#define PrintLine(strToPrint) \
	{						\
	PrintLineRaw(strToPrint); \
	NewLine();				\
	}

void CGraphView::CreateAnimationRealTimeScript(CString strFile, double nMin, double nStep, double nMax, UINT nLoopType, int nTimesThrough)
{
	CString str, strEq, strBmp, strMin, strMax, strStep, strN;
	int i;
	::ofstream outfile;

	Assert((nStep > 0) && (nMin < nMax));
	if((nStep < 0) || (nMin >= nMax))
		return;
	
	outfile.open(strFile);

	strMin.Format("%f", nMin);
	CleanupAnswer(strMin);
	strStep.Format("%f", nStep);
	CleanupAnswer(strStep);
	strMax.Format("%f", nMax);
	CleanupAnswer(strMax);

	PrintLine("#" + strFile);
	PrintLine("# This script was automaticaly generated by GraphCalc");
	//NewLine();
	//PrintLine("# This script animates the drawn equations by changing the variable n from " + strMin + " to " + strMax + " at an interval of " + strStep);
	NewLine();
	PrintLine("[OutputWindow=off]");

	NewLine();

	// spit out all specific equation info and settings
	PrintLine("[2DEqAllOn=off]");

	switch(m_Mode)
		{
		case EUCLIDEAN:	PrintLine("[2DGraphMode=euclidean]"); break;
		case POLAR:		PrintLine("[2DGraphMode=polar]"); break;
		}

	for(i=0; i < MAX_EQUATIONS; ++i)
		{
		if(!strEq.IsEmpty())
			{
			strEq.Format("%d", i+1);
			PrintLine("[2DEq=" + strEq + ":" + m_Equations[i].eq + "]");
			}
		}

	for(i=0; i < MAX_EQUATIONS; ++i)
		{
		if(m_Equations[i].disp)
			{
			strEq.Format("%d", i+1);
			PrintLine("[2DEqOn=" + strEq + ":on]");
			}
		}


	PrintLine("nMin=" + strMin);
	PrintLine("nStep=" + strStep);
	PrintLine("nMax=" + strMax);

	// now actualy do the looping for the animation
	if(nLoopType == ANIMATION_RANGE_LOOP) 
		{
		// our main loop for number of times through	
		if(nTimesThrough == -1)
			{
			PrintLine("While(1)"); // infinitely loop
			}
		else
			{
			CString temp;
			temp.Format("timesthrough=%d", nTimesThrough);
			PrintLine(temp);
			PrintLine("timesthroughcounter=1");
			PrintLine("While(timesthroughcounter <= timesthrough)"); // loop only so many times
			}
		}
	
	// go forward
	PrintLine("\tn = nMin");
	PrintLine("\tWhile(n <= nMax)");
	strBmp.Format("\t\t[2DRecomputeAll]");
	PrintLine(strBmp);
	PrintLine("\t\tn=n+" + strStep);
	PrintLine("\tEndWhile");

	NewLine();

	if(nLoopType == ANIMATION_RANGE_LOOP) 
		{
		// loop back to start nows
		PrintLine("\tn=n-1");
		PrintLine("\tWhile(n >= nMin)");
		strBmp.Format("\t\t[2DRecomputeAll]");
		PrintLine(strBmp);
		PrintLine("\t\tn=n-" + strStep);
		PrintLine("\tEndWhile");

		if(nTimesThrough != -1)
			PrintLine("\ttimesthroughcounter = timesthroughcounter + 1");
		
		PrintLine("EndWhile"); // outer main loop for times through
		}

	
	MessageBox("Animation script generation complete");

	outfile.close();
}

// pre: strFilename must be an integer in string format!
// post: 0's are padded onto the front of strInteger
CString FixedNumberDigits(int cDigits, CString strInteger)
{
	Assert(strInteger.GetLength() <= cDigits);
	
	while(strInteger.GetLength() < cDigits)
		strInteger = "0" + strInteger;

	return strInteger;
}

void CGraphView::CreateAnimationFramesScript(CString strFile, double nMin, double nStep, double nMax, UINT nLoopType, int nTimesThrough)
{
	CString str, strEq, strBmp, strMin, strMax, strStep, strN, strFileCounter, strFileName, strFrameCount;
	double n;
	int i, nFileCounter=0;
	::ofstream outfile;

	Assert(nTimesThrough > 0);
	Assert((nStep > 0) && (nMin < nMax));
	if((nStep < 0) || (nMin >= nMax))
		return;

	strFrameCount.Format("%d", int(((nMax - nMin) / nStep) + 1));
	
	outfile.open(strFile);

	strFile = strFile.Right((strFile.GetLength() - strFile.ReverseFind('\\')) - 1); // gives us the *.gcs file name	
	strFileName = strFile.Left(strFile.ReverseFind('.')); // gives us just the name of the file without the extension
	
	strMin.Format("%f", nMin);
	CleanupAnswer(strMin);
	strStep.Format("%f", nStep);
	CleanupAnswer(strStep);
	strMax.Format("%f", nMax);
	CleanupAnswer(strMax);

	PrintLine("# " + strFile);
	PrintLine("# This script was automaticaly generated by GraphCalc");
	NewLine();
	//PrintLine("# This script generates consecutive images from " + strMin + " to " + strMax + " at an interval of " + strStep);
	NewLine();
	PrintLine("[OutputWindow=off]");

	NewLine();

	// spit out all specific equation info and settings
	PrintLine("[2DEqAllOn=off]");
	
	switch(m_Mode)
		{
		case EUCLIDEAN:	PrintLine("[2DGraphMode=euclidean]"); break;
		case POLAR:		PrintLine("[2DGraphMode=polar]"); break;
		}

	for(i=0; i < MAX_EQUATIONS; ++i)
		{
		if(!strEq.IsEmpty())
			{
			strEq.Format("%d", i+1);
			PrintLine("[2DEq=" + strEq + ":" + m_Equations[i].eq + "]");
			}
		}

	for(i=0; i < MAX_EQUATIONS; ++i)
		{
		if(m_Equations[i].disp)
			{
			strEq.Format("%d", i+1);
			PrintLine("[2DEqOn=" + strEq + ":on]");
			}
		}

	if(nLoopType == ANIMATION_RANGE_ONEWAY)
		nTimesThrough = 1;

	for(i=0; i < nTimesThrough; ++i)
		{
		if(i == 0)
			n = nMin;
		else
			n = nMin + 1; // so on the loop we don't do the min twice
		
		while(n <= nMax)
			{
			strN.Format("%f", n);
			CleanupAnswer(strN);
			PrintLine("n=" + strN);
			strFileCounter.Format("%d", ++nFileCounter);			
			strBmp.Format("[2DSaveBitmap=\"" + strFile.Left(strFile.ReverseFind('.')) + FixedNumberDigits(strFrameCount.GetLength(), strFileCounter) + ".bmp\"]");
			PrintLine(strBmp);
			n += nStep;
			}

		if(nLoopType == ANIMATION_RANGE_LOOP)
			{
			n = nMax-1;
			while(n >= nMin)
				{
				strN.Format("%f", n);
				CleanupAnswer(strN);
				PrintLine("n=" + strN);
				strFileCounter.Format("%d", ++nFileCounter);			
				strBmp.Format("[2DSaveBitmap=\"" + strFile.Left(strFile.ReverseFind('.')) + FixedNumberDigits(strFrameCount.GetLength(), strFileCounter) + ".bmp\"]");
				PrintLine(strBmp);
				n -= nStep;
				}
			}
		}

	PrintLine("[Message=\"Animation Complete\"]");
	
	MessageBox("Animation script generation complete");

	outfile.close();
}

BOOL CGraphView::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

	// allow top level routing frame to handle the message
	if (GetRoutingFrame() != NULL)
		return FALSE;

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	TCHAR szFullText[256];
	CString cstTipText;
	CString cstStatusText;

	UINT nID = pNMHDR->idFrom;
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
		nID = ((UINT)(WORD)::GetDlgCtrlID((HWND)nID));
	}

	if (nID != 0) // will be zero on a separator
	{
		AfxLoadString(nID, szFullText);
			// this is the command id, not the button index
		AfxExtractSubString(cstTipText, szFullText, 0, '\n');
		//AfxExtractSubString(cstStatusText, szFullText, 0, '\n');
	}

	// Non-UNICODE Strings only are shown in the tooltip window...
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, cstTipText,
            (sizeof(pTTTA->szText)/sizeof(pTTTA->szText[0])));
	else
		_mbstowcsz(pTTTW->szText, cstTipText,
            (sizeof(pTTTW->szText)/sizeof(pTTTW->szText[0])));
	*pResult = 0;

	// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);


	return TRUE;    // message was handled
}



#include "2DInfoBar.h"
#include "Zoom.h"
#include "DrawGraph.h"
