// GrphCalcDlg.cpp : implementation file
//
/*********************************************************/
// 
// Pre:
// Post:
// Return Value:
// Intent:
/*********************************************************/

#include "stdafx.h"
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include "GrphCalc.h"
#include "GrphCalcDlg.h"
#include "GraphOptions.h"
#include "Mode.h"
#include "GraphTabNameDlg.h"
#include "CatalogDlg.h"
#include "Color.h"
#include "CommandDlg.h"
#include "EquationSolverDlg.h"
#include "globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <afxtempl.h>
#include <fstream.h>

// needed for accelerator keys
extern HWND    ghDlg;          // Handle to main dialog box
extern HACCEL  ghAccelTable;   // Handle to accelerator table
//////////////////////////////

extern VariableT GetVariable(CString var, long double num);


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink m_WebButtonGC, m_WebSupport;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_WEBGC, m_WebButtonGC);
	DDX_Control(pDX, IDC_SUPPORT, m_WebSupport);
	//}}AFX_DATA_MAP
}

/*********************************************************/
// CAboutDlg::OnInitDialog() 
// Pre: none
// Post: dialog and data are initialized
// Return Value: handled by parent
// Intent: to initialize the dialog and data members
/*********************************************************/
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// INIT FIELDS
	/*m_MailButtonFields.SetURL(_T("mailto:fields@graphcalc.com"));

	m_MailButtonFields.SetColours(m_MailButtonFields.GetLinkColour(),m_MailButtonFields.GetLinkColour());
	m_MailButtonFields.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	// INIT ARRISON
	m_MailButtonArrison.SetURL(_T("mailto:arrison@graphcalc.com"));

	m_MailButtonArrison.SetColours(m_MailButtonArrison.GetLinkColour(),m_MailButtonArrison.GetLinkColour());
	m_MailButtonArrison.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	*/
	// INIT WEB BUTTON
	m_WebButtonGC.SetURL(_T("http://www.graphcalc.com"));

	m_WebButtonGC.SetColours(m_WebButtonGC.GetLinkColour(),m_WebButtonGC.GetLinkColour());
	m_WebButtonGC.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	// INIT WEB BUTTON
	m_WebSupport.SetURL(_T("http://www.graphcalc.com/support.shtml"));

	m_WebSupport.SetColours(m_WebSupport.GetLinkColour(),m_WebSupport.GetLinkColour());
	m_WebSupport.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrphCalcDlg dialog
#include <afxpriv.h>

/*********************************************************/
// Constructor
// Pre: none
// Post: none
// Return Value: none
// Intent: to initialize data members in the dialog
/*********************************************************/
CGrphCalcDlg::CGrphCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGrphCalcDlg::IDD, pParent), m_view("")
{
	//{{AFX_DATA_INIT(CGrphCalcDlg)
	m_Formula = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	g_strApplicationDirectory = GetCurrentDirectory();
	m_fShowScriptLibrary = false;
	
	m_fShowScriptProgressDlg = true;
	g_fQuitScript = false;
	m_fEndProg = false;
	
	m_fNotShutdown = true;
	m_fSaveFont = false;
	
	m_AlwaysOnTop = false;
	m_iScriptLevel = -1;
	m_bShowCommandErrors = true;

	// Load Menu Bitmaps
	m_OpenBmp.bmp.LoadBitmap(IDB_OPEN);
	m_OpenBmp.loaded = false;
	m_SaveBmp.bmp.LoadBitmap(IDB_SAVE);
	m_SaveBmp.loaded = false;
	m_CutBmp.bmp.LoadBitmap(IDB_CUT);
	m_CutBmp.loaded = false;
	m_CopyBmp.bmp.LoadBitmap(IDB_COPY);
	m_CopyBmp.loaded = false;
	m_PasteBmp.bmp.LoadBitmap(IDB_PASTE);
	m_PasteBmp.loaded = false;
	///////////////////////////
	
	m_button_down = false;
	m_SndEffects = true;
	m_FullScreen = false;
	m_Trace = false;
	m_StartProg = false;
	m_button_start = CPoint(391, 235);
	m_alt_button_start = CPoint(391, 184);
	m_TotalGraphViews = 0;
	m_CurrentPalete = NONE;
	m_SaveSettings = true;

	m_ToolTips.Create(this);
	m_ToolTips.On(true);
	m_ToolTips.SetOffset(4, 20);

	m_bSaveExprHistory = false;
	m_bSaveOutputHistory = false;
	m_bStartupScript = false;
	m_sScriptFile.Empty();

	for(int i = 0; i < MAXTABS; ++i){
		m_GraphViewList[i].InitVariables(&m_Calculator, &m_OutputV);
		m_ActiveGraphView[i] = false;
	}

#ifndef GRAPHCALC_LIGHT
	m_3DGraphView = new C3DGraph;
	m_3DGraphView->InitVariables(&m_Calculator);
#endif

	CreateConstantMenus();
	CreateConvertMenus();
	
	// set up fonts for output
	m_OutputV.m_LFAnswerFont.lfHeight=10;
	m_OutputV.m_LFAnswerFont.lfWidth=2;
	m_OutputV.m_LFAnswerFont.lfEscapement=0;
	m_OutputV.m_LFAnswerFont.lfOrientation=0;
	m_OutputV.m_LFAnswerFont.lfWeight=400;
	m_OutputV.m_LFAnswerFont.lfItalic=0;
	m_OutputV.m_LFAnswerFont.lfUnderline=0;
	m_OutputV.m_LFAnswerFont.lfStrikeOut=0;
	m_OutputV.m_LFAnswerFont.lfCharSet=1;
	m_OutputV.m_LFAnswerFont.lfOutPrecision=0;
	m_OutputV.m_LFAnswerFont.lfClipPrecision=0;
	m_OutputV.m_LFAnswerFont.lfQuality=2;
	m_OutputV.m_LFAnswerFont.lfPitchAndFamily=48;
	strcpy(m_OutputV.m_LFAnswerFont.lfFaceName, "Arial");
	m_OutputV.m_LFAnswerFont.lfFaceName[5] = 0x00;
	
	m_OutputV.m_LFExpressionFont.lfHeight=10;
	m_OutputV.m_LFExpressionFont.lfWidth=2;
	m_OutputV.m_LFExpressionFont.lfEscapement=0;
	m_OutputV.m_LFExpressionFont.lfOrientation=0;
	m_OutputV.m_LFExpressionFont.lfWeight=400;
	m_OutputV.m_LFExpressionFont.lfItalic=0;
	m_OutputV.m_LFExpressionFont.lfUnderline=0;
	m_OutputV.m_LFExpressionFont.lfStrikeOut=0;
	m_OutputV.m_LFExpressionFont.lfCharSet=1;
	m_OutputV.m_LFExpressionFont.lfOutPrecision=0;
	m_OutputV.m_LFExpressionFont.lfClipPrecision=0;
	m_OutputV.m_LFExpressionFont.lfQuality=2;
	m_OutputV.m_LFExpressionFont.lfPitchAndFamily=48;
	strcpy(m_OutputV.m_LFExpressionFont.lfFaceName, "Arial");
	m_OutputV.m_LFExpressionFont.lfFaceName[5] = 0x00;

	m_OutputV.m_LFLongOutputFont.lfHeight=8;
	m_OutputV.m_LFLongOutputFont.lfWidth=2;
	m_OutputV.m_LFLongOutputFont.lfEscapement=0;
	m_OutputV.m_LFLongOutputFont.lfOrientation=0;
	m_OutputV.m_LFLongOutputFont.lfWeight=400;
	m_OutputV.m_LFLongOutputFont.lfItalic=0;
	m_OutputV.m_LFLongOutputFont.lfUnderline=0;
	m_OutputV.m_LFLongOutputFont.lfStrikeOut=0;
	m_OutputV.m_LFLongOutputFont.lfCharSet=1;
	m_OutputV.m_LFLongOutputFont.lfOutPrecision=0;
	m_OutputV.m_LFLongOutputFont.lfClipPrecision=0;
	m_OutputV.m_LFLongOutputFont.lfQuality=2;
	m_OutputV.m_LFLongOutputFont.lfPitchAndFamily=48;
	strcpy(m_OutputV.m_LFLongOutputFont.lfFaceName, "Arial");
	m_OutputV.m_LFLongOutputFont.lfFaceName[5] = 0x00;
	
	m_OutputV.m_LFBaseFont.lfHeight=7;
	m_OutputV.m_LFBaseFont.lfWidth=2;
	m_OutputV.m_LFBaseFont.lfEscapement=0;
	m_OutputV.m_LFBaseFont.lfOrientation=0;
	m_OutputV.m_LFBaseFont.lfWeight=400;
	m_OutputV.m_LFBaseFont.lfItalic=0;
	m_OutputV.m_LFBaseFont.lfUnderline=0;
	m_OutputV.m_LFBaseFont.lfStrikeOut=0;
	m_OutputV.m_LFBaseFont.lfCharSet=1;
	m_OutputV.m_LFBaseFont.lfOutPrecision=0;
	m_OutputV.m_LFBaseFont.lfClipPrecision=0;
	m_OutputV.m_LFBaseFont.lfQuality=2;
	m_OutputV.m_LFBaseFont.lfPitchAndFamily=48;
	strcpy(m_OutputV.m_LFBaseFont.lfFaceName, "Arial");
	m_OutputV.m_LFBaseFont.lfFaceName[5] = 0x00;
		
	LoadSettings();
	InitButtons();

	m_UpdateDataOnEnter = true;

	g_Calculator = &m_Calculator;

#ifndef GRAPHCALC_LIGHT
	LoadScriptLibrary();
#endif
}

CGrphCalcDlg::~CGrphCalcDlg(){
	
#ifndef GRAPHCALC_LIGHT
	delete m_3DGraphView;
#endif

}

void CGrphCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrphCalcDlg)
	DDX_Control(pDX, IDC_FORMULA, m_FormulaCtrl);
	DDX_Text(pDX, IDC_FORMULA, m_Formula);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGrphCalcDlg, CDialog)
	ON_MESSAGE(WM_USER_CHANGE_OBJECT_PROPERTIES, OnGraphOptionsChanged)
	ON_MESSAGE(WM_3DOPTIONS_CHANGE, On3DGraphOptionsChanged)
	ON_MESSAGE(WM_2DGRAPH_CENTER,On2DCenterGraph)
	ON_MESSAGE(WM_2DGRAPH_N_SLIDER_UPDATE,On2DNSliderUpdate)
	//{{AFX_MSG_MAP(CGrphCalcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_INITMENUPOPUP()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_COMMAND(ID_OPTIONS_MODE, OnOptionsMode)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_GRAPH_ADDGRAPHTAB, OnGraphAddGraphTab)
	ON_COMMAND(ID_GRAPH_REMOVEGRAPHTAB, OnGraphRemovegraphtab)
	ON_COMMAND(ID_GRAPH_ZOOM_IN_XY, OnGraphZoomInXY)
	ON_COMMAND(ID_GRAPH_ZOOM_OUT_XY, OnGraphZoomOutXY)
	ON_COMMAND(ID_GRAPH_ZOOM_IN_X, OnGraphZoomInX)
	ON_COMMAND(ID_GRAPH_ZOOM_IN_Y, OnGraphZoomInY)
	ON_COMMAND(ID_GRAPH_ZOOM_DECIMAL, OnGraphZoomDecimal)
	ON_COMMAND(ID_GRAPH_ZOOM_STANDARD, OnGraphZoomStandard)
	ON_COMMAND(ID_GRAPH_ZOOM_TRIG, OnGraphZoomTrig)
	ON_COMMAND(ID_GRAPH_ZOOM_OUT_X, OnGraphZoomOutX)
	ON_COMMAND(ID_GRAPH_ZOOM_OUT_Y, OnGraphZoomOutY)
	ON_COMMAND(ID_GRAPH_ZOOM_INTEGER, OnGraphZoomInteger)
	ON_COMMAND(ID_GRAPH_ZOOM_FIT, OnGraphZoomFit)
	ON_COMMAND(ID_GRAPH_GRAPHTRACE, OnGraphGraphtrace)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_GRAPH_FINDAREA, OnGraphFindArea)
	ON_COMMAND(ID_GRAPH_RENAMETAB, OnGraphRenametab)
	ON_COMMAND(ID_OPTIONS_SOUND_EFFECTS, OnOptionsSoundEffects)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_FILE_CATALOG, OnFileCatalog)
	ON_WM_ACTIVATE()
	ON_COMMAND(ID_FILE_OPTIONS_TOOLTIPS, OnFileOptionsTooltips)
	ON_COMMAND(ID_FILE_OPTIONS_EXPRESSIONFONT, OnFileOptionsExpression)
	ON_COMMAND(ID_FILE_OPTIONS_ANSWERFONT, OnFileOptionsAnswer)
	ON_COMMAND(ID_GRAPH_ZOOM_PREVIOUSRANGE, OnGraphZoomPreviousRange)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_FILE_OPTIONS_SAVESETTINGSNOW, OnFileOptionsSavesettingsnow)
	ON_COMMAND(ID_FILE_OPTIONS_SAVESETTINGSONEXIT, OnFileOptionsSavesettingsonexit)
	ON_COMMAND(ID_FILE_LOADSETTINGSFILE, OnFileLoadsettingsfile)
	ON_COMMAND(ID_FILE_SAVESETTINGSAS, OnFileSavesettingsas)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_FILE_OPTIONS_DISAPLAYDETAILEDOUTPUT, OnFileOptionsDisaplaydetailedoutput)
	ON_COMMAND(ID_GRAPH_EVALUATE, OnGraphEvaluate)
	ON_COMMAND(ID_GRAPH_TANGENTLINE, OnGraphTangentline)
	ON_COMMAND(ID_GRAPH_DISTANCE, OnGraphDistance)
	ON_COMMAND(ID_GRAPH_COPYGRAPH, OnGraphCopygraph)
	ON_COMMAND(ID_GRAPH_CLEARTANGENTLINES, OnGraphCleartangentlines)
	ON_COMMAND(ID_OPTIONS_ALWAYSONTOP, OnOptionsAlwaysontop)
	ON_CBN_EDITCHANGE(IDC_FORMULA, OnEditchangeFormula)
	ON_COMMAND(ID_GRAPH_PRINT, OnGraphPrint)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_RUNSCRIPT, OnFileRunscript)
	ON_COMMAND(ID_INSERT_COMMAND, OnInsertCommand)
	ON_COMMAND(ID_OPTIONS_PROGRAMOPTIONS, OnOptionsProgramoptions)
	ON_COMMAND(ID_FILE_SAVESCRIPT, OnFileSaveScript)
	ON_COMMAND(ID_CTRLG, OnCtrlG)	
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SOUND_EFFECTS, OnUpdateOptionsSoundEffects)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_FINDAREA, OnUpdateGraphFindarea)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPTIONS_TOOLTIPS, OnUpdateFileOptionsTooltips)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPTIONS_SAVESETTINGSONEXIT, OnUpdateFileOptionsSavesettingsonexit)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPTIONS_DISAPLAYDETAILEDOUTPUT, OnUpdateFileOptionsDisaplaydetailedoutput)
	ON_UPDATE_COMMAND_UI(ID_FILE_LOADSETTINGSFILE, OnUpdateFileLoadsettingsfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPTIONS_SAVESETTINGSNOW, OnUpdateFileOptionsSavesettingsnow)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_DISTANCE, OnUpdateGraphDistance)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALWAYSONTOP, OnUpdateOptionsAlwaysontop)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GRAPH_SAVEASBITMAP, OnGraphSaveAsBitmap)
	ON_COMMAND(ID_FILE_EQUATIONSOLVER, OnFileEquationSolver)
	ON_COMMAND(ID_2DGRAPH_ANALYSIS_INTERSECTIONOF2EQUATIONS, On2DGraphAnalysisIntersectionof2equations)
	ON_COMMAND(ID_2DGRAPH_ANALYSIS_INTERCEPTS, On2DGraphAnalysisIntercepts)
	ON_UPDATE_COMMAND_UI(ID_2DGRAPH_ANALYSIS_INTERCEPTS, OnUpdate2dgraphAnalysisIntercepts)
	ON_UPDATE_COMMAND_UI(ID_2DGRAPH_ANALYSIS_INTERSECTIONOF2EQUATIONS, OnUpdate2dgraphAnalysisIntersectionof2equations)
	ON_COMMAND(ID_ANALYSIS_EQ_MINMAX, OnAnalysisEqMinmax)
	ON_UPDATE_COMMAND_UI(ID_ANALYSIS_EQ_MINMAX, OnUpdateAnalysisEqMinmax)
	ON_COMMAND(ID_FILE_SAVEOUTPUT, OnFileSaveOutput)
	ON_COMMAND(ID_OPTIONS_OUTPUTFONTSETTINGS_BASE, OnOptionsOutputfontsettingsBase)
	ON_COMMAND(ID_OPTIONS_OUTPUTFONTSETTINGS_DETAILEDOUTPUT, OnOptionsOutputfontsettingsDetailedoutput)
	ON_COMMAND(ID_QUIT_SCRIPT, OnQuitScript)
	ON_WM_CHAR()
	ON_COMMAND(ID_2DGRAPH_ANALYSIS_TABLE, On2DGraphAnalysisTable)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_COPYGRAPH, OnUpdate2DGraphCopy)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SAVEASBITMAP, OnUpdate2DGraphSaveAsBitmap)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_PRINT, OnUpdate2DGraphPrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_EQUATIONSOLVER, OnUpdateFileEquationsolver)
	ON_UPDATE_COMMAND_UI(ID_FILE_RUNSCRIPT, OnUpdateFileRunscript)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVESCRIPT, OnUpdateFileSavescript)
	ON_COMMAND(ID_ANALYSIS_NSLIDER, On2DGraphAnalysisNslider)
	ON_COMMAND(ID_VIEW_2D_INFOBAR, On2DGraphInfobar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_2D_INFOBAR, OnUpdate2DGraphIInfobar)
	ON_COMMAND(ID_VIEW_2D_TOOLBAR, On2DGraphToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_2D_TOOLBAR, OnUpdate2DGraphToolbar)
	ON_COMMAND(ID_ANIMATION_SCRIPT, On2DGraphAnimationScript)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_SCRIPT, OnUpdate2DGraphAnimationScript)
	ON_UPDATE_COMMAND_UI(ID_ANALYSIS_NSLIDER, OnUpdate2DGraphNSlider)
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_SETFULLWINDOW, OnSetFullWindow)
	ON_UPDATE_COMMAND_UI(ID_2DGRAPH_ANALYSIS_TABLE, OnUpdate2dgraphAnalysisTable)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_POWER_1, ID_POWER_9, Power)
	ON_COMMAND_RANGE(ID_LN_1, ID_LN_2, NaturalLN)
	ON_COMMAND_RANGE(ID_EE_1, ID_EE_2, EE)
	ON_COMMAND_RANGE(ID_SIN_1, ID_SIN_4, Sin)
	ON_COMMAND_RANGE(ID_COS_1, ID_COS_4, Cos)
	ON_COMMAND_RANGE(ID_TAN_1, ID_TAN_4, Tan)
	ON_COMMAND_RANGE(ID_CLEAR_1, ID_CLEAR_ALL, Clear)
	ON_COMMAND_RANGE(ID_VAR_X, ID_VAR_R, Var)
	ON_COMMAND_RANGE(ID_LOG_1, ID_LOG_3, Log)
	ON_COMMAND_RANGE(ID_R_1, ID_R_8, RootsMenu)
	ON_COMMAND_RANGE(conv_start, conv_end, OnConvertMenu)
	ON_COMMAND_RANGE(cons_start, cons_end, OnConstantMenu)
	ON_COMMAND_RANGE(ID_BASE_2, ID_BASE_HELP, Base)
	ON_COMMAND_RANGE(ID_PALETES_STATS, ID_PALETES_LETTERS, OnAltMenu)
	ON_COMMAND_RANGE(ID_CONVER_BASE_2, ID_CONVER_BASE_36, OnConvertBaseMenu)
	ON_COMMAND_RANGE(ID_GRAPH_EQUATIONS, ID_OPTIONS_GRAPH, OnOptionsGraph)

	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullscreen)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_GRAPHTRACE, OnUpdateGraphGraphtrace)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PALETES_STATS, ID_PALETES_LETTERS, OnUpdateAltMenu)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BASE_2, ID_BASE_36, OnUpdateBaseMenu)

	ON_COMMAND(ID_3DGRAPH_COPYGRAPH, OnGraphCopygraph)
	ON_COMMAND_RANGE(ID_3DGRAPH_SAVEASBITMAP, ID_3DGRAPH_AUTOROTATE_DECREASESPEED, On3DCommand)
	ON_UPDATE_COMMAND_UI_RANGE(ID_3DGRAPH_AUTOROTATE_ALLAXIS, ID_3DGRAPH_AUTOROTATE_DECREASESPEED, OnUpdate3DAutoRotate)

	ON_COMMAND_RANGE(script_start, script_end, OnScriptLibraryMenu)
	ON_COMMAND_RANGE(ans_history_start, ans_history_end, OnAnswerHistoryMenu)
	
	//ON_UPDATE_COMMAND_UI_RANGE(ID_3DGRAPH_COPYGRAPH, ID_3DGRAPH_EXPORTTODFX, OnUpdate3D)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGrphCalcDlg message handlers
/*********************************************************/
// CGrphCalcDlg::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, 
//							     BOOL bSysMenu)
// Pre: none
// Post: none
// Return Value: none
// Intent: to update menus before they are displayed
/*********************************************************/
void CGrphCalcDlg::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu) 
{
	UpdateMenu(pMenu);
}


/*********************************************************/
// CGrphCalcDlg::OnInitDialog()
// Pre: none
// Post: dialog and data are initialized
// Return Value: handled by parent
// Intent: to initialize the dialog and data members
/*********************************************************/
BOOL CGrphCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_view.AddPage(&m_OutputV);
	
	AddGraphTabs();

#ifndef GRAPHCALC_LIGHT
	m_view.AddPage(m_3DGraphView);
#endif
	
	m_view.EnableStackedTabs(false);
	m_view.Create(this, WS_CHILD | WS_VISIBLE, 0);
	//m_view.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
	m_view.ModifyStyle(0, WS_TABSTOP);
	
	CRect rect(TAB_MARGIN_LEFT, 
			   TAB_MARGIN_TOP, 
			   TAB_MARGIN_LEFT + DEFAULT_TAB_WIDTH, 
			   TAB_MARGIN_TOP + DEFAULT_TAB_HEIGHT);

	m_view.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), 
		SWP_NOZORDER | SWP_NOACTIVATE);

	m_view.SetActivePage(&m_OutputV);

	m_FormulaCtrl.LimitText(0);

	ghDlg = m_hWnd; // needed for accelerator keys
	
	if(m_AlwaysOnTop){
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else{
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	//#ifdef TEST_MODE
	//TestFile();
	//#endif
	
	if(m_bSaveOutputHistory)
		m_OutputV.LoadOutput();
	if(m_bSaveExprHistory)
		LoadExpressionHistory();

	#ifndef GRAPHCALC_LIGHT
	if(m_bStartupScript)
		RunScript(m_sScriptFile);
	#endif

	LoadAnswerHistory();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*********************************************************/
// CGrphCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles system messages
/*********************************************************/
void CGrphCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
/*********************************************************/
// CGrphCalcDlg::OnDestroy()
// Pre: none
// Post: none
// Return Value: none
// Intent: to destroy the dialog box
/*********************************************************/
void CGrphCalcDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

#define RIGHT_BITMAP_INDENT	8
#define RIGHT_BITMAP_WIDTH (RIGHT_BITMAP_INDENT + (BUTTON_PALLETE_WIDTH-3))

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
/*********************************************************/
// CGrphCalcDlg::OnPaint()
// Pre: none
// Post: dialog is drawn
// Return Value: none
// Intent: to draw the dialog box
/*********************************************************/
void CGrphCalcDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);
		
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		if(!m_FullScreen){
			CClientDC DC(this);
			CBitmap rightBmp;
			CDC MemDC;
			
			MemDC.CreateCompatibleDC(&DC);

			rightBmp.CreateCompatibleBitmap(&DC, RIGHT_BITMAP_WIDTH, rect.Height());
			CBitmap *pOldBitmap = MemDC.SelectObject(&rightBmp);

			// draw background
			CBrush brush(GetSysColor(COLOR_3DFACE)), *pOldBrush;
			pOldBrush = MemDC.SelectObject(&brush);
			CPen pen;
			pen.CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE));
			CPen* pOldPen = MemDC.SelectObject(&pen);
			
			MemDC.Rectangle(0, 0, RIGHT_BITMAP_WIDTH, rect.Height());
			MemDC.SelectObject(pOldBrush);
			MemDC.SelectObject(pOldPen);
			pOldBrush = 0;
			delete pOldBrush;
					    
			DrawButtons(&MemDC);
			
			int rows;

			switch(m_CurrentPalete){
			case PROB:
				rows = m_ProbButtons.GetSize() / 5;

				if((double(m_ProbButtons.GetSize()) / 5.0) == 1.0)
					--rows;

				break;
			case MATH:
				rows = m_MathButtons.GetSize() / 5;

				if((double(m_MathButtons.GetSize()) / 5.0) == 1.0)
					--rows;

				break;
			case TEST:
				rows = m_TestButtons.GetSize() / 5;

				if((double(m_TestButtons.GetSize()) / 5.0) == 1.0)
					--rows;

				break;
			case LETTERS:
				rows = m_LetterButtons.GetSize() / 5;

				if((double(m_LetterButtons.GetSize()) / 5.0) == 1.0)
					--rows;

				break;
			default:
				rows = 0;
				break;
			}

			if(m_CurrentPalete != NONE)
				DrawPaleteButtons(&MemDC);

			int y;

			if(rows != 0)
				y = m_alt_button_start.y - ((2+(rows/5)) * button_height) - ((1+rows/5) * button_spacing);
			else
				y = m_alt_button_start.y - ((rows/5) * button_height) - ((rows/5) * button_spacing);
			
			if((m_CurrentPalete == NONE && y >= 160) || (y >= 190))
				{	
				// draw logo
				CBitmap logo;
				logo.LoadBitmap(IDB_LOGO);
				CDC dcMemory;
				dcMemory.CreateCompatibleDC(&DC);
				CBitmap *pOldBitmap = dcMemory.SelectObject(&logo);
				
				MemDC.BitBlt(RIGHT_BITMAP_INDENT, 25, 235, 160, &dcMemory, 0, 0, SRCCOPY);
				
				dcMemory.SelectObject(pOldBitmap);
				DeleteDC(dcMemory);
				}

			// blast it all to the screen
			DC.BitBlt(m_button_start.x - RIGHT_BITMAP_INDENT, 0, 
						RIGHT_BITMAP_WIDTH, rect.Height(), 
						&MemDC, 0, 0, SRCCOPY);
			
			MemDC.SelectObject(pOldBitmap);
			DeleteDC(MemDC);


			CWnd* pWnd;
			pWnd = GetDlgItem(IDC_FORMULA);
			pWnd->Invalidate();
		}
	}
}
/*********************************************************/
// CGrphCalcDlg::PreTranslateMessage(MSG* pMsg) 
// Pre: none
// Post: messages are handled
// Return Value: parent controls this
// Intent: to grab special messages before being directed
//		   through normal messaging process
/*********************************************************/
BOOL CGrphCalcDlg::PreTranslateMessage(MSG* pMsg) 
{
	UpdateDialogControls(this, false);
	// user has hit the minimize button, set focus to the expression box
	if(pMsg->message == 161)
		m_FormulaCtrl.SetFocus();
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		{
		g_fQuitScript = true;
		return true;
		}

	return CDialog::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////////
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGrphCalcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CGrphCalcDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;		
	return 0;
}

/*********************************************************/
// CGrphCalcDlg::OnAppAbout()
// Pre: none
// Post: none
// Return Value: none
// Intent: displays the about dialog box
/*********************************************************/
void CGrphCalcDlg::OnAppAbout() 
{
	CAboutDlg about;
	about.DoModal();	
}

/*********************************************************/
// CGrphCalcDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
// Pre: none
// Post: none
// Return Value: none
// Intent: gets the minimum and maximum window size
//		   information so we can adjust it
/*********************************************************/
void CGrphCalcDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 375;
	lpMMI->ptMinTrackSize.y = 350;
}

/*********************************************************/
// CGrphCalcDlg::FullTab(int i, int &free_pos)
// Pre: none
// Post: none
// Return Value: true if tab is not full
// Intent: to see if graph tab i has 10 equatiosn entered 
//		   in it
/*********************************************************/
bool CGrphCalcDlg::FullTab(int i, int &free_pos)
{
	for(free_pos = 0; free_pos < 10; ++free_pos){
		if(m_GraphViewList[i].m_Equations[free_pos].eq.IsEmpty())
			return false;
	}

	if(free_pos == 10){
		free_pos = -1;
		return true;
	}
	return true;
}

/*********************************************************/
// IsEquation()
// Pre: none
// Post: none
// Return Value: true if we have an equation
// Intent: this function looks in the equation entered and
//		   tries to find an x, if it finds one it looks at
//		   the neighboring characters to determine if the
//		   x is acting as a variable, in which case this
//		   equation is to be graphed.
/*********************************************************/
bool IsEquation(CString equation, char variable)
{
	int pos = equation.Find(variable);
	
	if(pos != -1)
	{
		if(equation.GetLength() == 1)
			return true;
		else if(pos == 0){
			if(((equation[1] >= 'a') && (equation[1] <= 'z')) ||
			   ((equation[1] >= 'A') && (equation[1] <= 'Z')))
			return false;
		}
		else if(pos == (equation.GetLength() - 1)){
			if(((equation[pos - 1] >= 'a') && (equation[pos - 1] <= 'z')) ||
		       ((equation[pos - 1] >= 'A') && (equation[pos - 1] <= 'Z')))
			return false;
		}
		else if(((equation[pos - 1] >= 'a') && (equation[pos - 1] <= 'z')) ||
		   ((equation[pos - 1] >= 'A') && (equation[pos - 1] <= 'Z')) || 
		   ((equation[pos + 1] >= 'a') && (equation[pos + 1] <= 'z')) ||
		   ((equation[pos + 1] >= 'A') && (equation[pos + 1] <= 'Z')))
			 return false;
	}
	else
		return false;
	return true;
}

/*********************************************************/
// CGrphCalcDlg::OnEnter()
// Pre: none
// Post: none
// Return Value: none
// Intent: this function handles when the user presses the 
//		    enter key on the keyboard or in the program
//		    the equation entered is looked at and handled
//		    appropriately
/*********************************************************/
void CGrphCalcDlg::OnEnter() 
{
	if(m_UpdateDataOnEnter)
		UpdateData(true);

	EvaluateFormula(true);
	
	if(m_UpdateDataOnEnter)
		UpdateData(false);

	CWnd* pWnd = GetDlgItem(IDC_FORMULA);
	pWnd->SetFocus();
}

void CGrphCalcDlg::EvaluateFormula(bool auto_change_tabs)
{	
#ifndef GRAPHCALC_LIGHT
	if(!m_Formula.IsEmpty() && m_Formula[0] == '[' && m_Formula[m_Formula.GetLength()-1] == ']')
	{		
		CGCCommand cmd;
		cmd.SetControls(&m_Calculator);
		
		if(!cmd.ExecuteCommand(m_Formula) && m_bShowCommandErrors){
			cmd.HandleError(this->m_hWnd);
			return;
		}
		
		// ADD FORMULA TO FORMULA DROPDOWN LIST
		if(m_FormulaCtrl.FindStringExact(-1, m_Formula) == CB_ERR){
			CArray<CString, CString> list;
			
			list.Add(m_Formula);
			
			for(int i(0); i < m_FormulaCtrl.GetCount(); ++i){
				CString temp;
				m_FormulaCtrl.GetLBText(i, temp);
				list.Add(temp);	
			}
			
			m_FormulaCtrl.ResetContent();
			
			for(int j(0); j < list.GetSize(); ++j)
				m_FormulaCtrl.AddString(list[j]);
		}
		///////////////////////////////////////

		m_Formula.Empty();
	}
	else if(IsEquation(m_Formula, 'x') || IsEquation(m_Formula, 't')){ 
#else
	if(IsEquation(m_Formula, 'x') || IsEquation(m_Formula, 't')){ 
#endif
		
		bool done = false;
		bool full_tab[10];
		int free_pos(-1);

		for(int k = 0; k < 10; ++k)
			full_tab[k] = false;

		while(!done){
			
			if(!m_Calculator.IsValid(m_Formula, this->m_hWnd)){
				UpdateData(false);
				CWnd* pWnd = GetDlgItem(IDC_FORMULA);
				pWnd->SetFocus();
				return;
			}
			
			int i;

			for(i = 0; i < MAXTABS; ++i){
				if((m_view.GetActivePage() == &m_GraphViewList[i]) && !FullTab(i, free_pos))
					break;
			}
			if(i == MAXTABS){
				for(i = 0; i < MAXTABS; ++i){
					if(m_ActiveGraphView[i] && !FullTab(i, free_pos))
						break;
				}
			}
		
			if(i == MAXTABS){
				OnGraphAddGraphTab();
				if(m_TotalGraphViews == MAXTABS)
					return;
			}
			else{
				done = true;
				m_GraphViewList[i].SetEquation(free_pos,m_Formula);
				m_GraphViewList[i].m_Equations[free_pos].disp = true;
				m_GraphViewList[i].m_Redraw = true;

				if(auto_change_tabs)
				{// only change tabs if auto is turned on
					m_view.SetActivePage(&m_GraphViewList[i]);
					m_GraphViewList[i].RePaintNow();				
				}
			}
		}

		m_Formula.Empty();
	}
	else{
		if((m_view.GetActivePage() != &m_OutputV) && auto_change_tabs)  // only change tabs if auto is turned on
			m_view.SetActivePage(&m_OutputV);
		
		if(m_Calculator.IsValid(m_Formula, this->m_hWnd)){
			m_OutputV.OnEnter(m_Formula, m_Calculator, &m_FormulaCtrl);
			m_Formula.Empty();
		}
	}
}

/*********************************************************/
// CGrphCalcDlg::ResizeTabs()
// Pre: none
// Post: tabs are resized
// Return Value: none
// Intent: to resize te tabs and controls when the window 
//		   is resized
/*********************************************************/
void CGrphCalcDlg::ResizeTabs(CSize new_size)
{
	if(m_fEndProg)
		return;
	
	RECT rc;
	
	// RESIZE THE SHEET
	m_view.GetWindowRect (&rc);
	m_view.ScreenToClient (&rc);
	rc.right = new_size.cx - 250;
	rc.bottom = new_size.cy - 6;
	
	if(m_FullScreen)
		rc.right += BUTTON_PALLETE_WIDTH;

	//m_view.SetRedraw(false);
	m_view.MoveWindow (&rc);
	//m_view.SetRedraw();
	//m_view.Invalidate();
	
	// RESIZE THE CTABCTRL
	CTabCtrl* pTab = m_view.GetTabControl();
	ASSERT (pTab);
	pTab->GetWindowRect (&rc);
	ScreenToClient (&rc);

	rc.right = new_size.cx - 250;
	rc.bottom = new_size.cy - 6;
	
	if(m_FullScreen)
		rc.right += BUTTON_PALLETE_WIDTH;

	//pTab->SetRedraw(false);
	pTab->MoveWindow (&rc);
	//pTab->SetRedraw();
	//pTab->Invalidate();
	
	// RESIZE THE PAGE
	CPropertyPage* pPage = m_view.GetActivePage();
	ASSERT (pPage);
	pPage->GetWindowRect(&m_view.m_PageRect);
	ScreenToClient(&m_view.m_PageRect);

	m_view.m_PageRect.left = 7 + 8; //  default + margin
	m_view.m_PageRect.top = 25 + 8; //  default + margin

	m_view.m_PageRect.right = new_size.cx - 261;
	m_view.m_PageRect.bottom = new_size.cy - 16;
	
	if(m_FullScreen)
		m_view.m_PageRect.right += BUTTON_PALLETE_WIDTH;
	
	//pPage->SetRedraw(false);
	pPage->MoveWindow (&m_view.m_PageRect);
	//pPage->SetRedraw();
	//pPage->Invalidate();

	// NEW SIZE FOR ITEMS IN THE TABS
	double tab_w = (new_size.cx - 261) - (m_view.m_PageRect.left + h_space);
	double tab_h = (new_size.cy - 16) - (m_view.m_PageRect.top + v_space);

	if(m_FullScreen)
		tab_w += BUTTON_PALLETE_WIDTH;

	// RESIZE THE GRAPH
	for(int i(0); i < MAXTABS; ++i){
		#ifdef GRAPH2D_INFOBAR
			if(m_GraphViewList[i].m_fInfoBar)
				m_GraphViewList[i].m_graph_width = tab_w - BUTTON_PALLETE_WIDTH;
			else
				m_GraphViewList[i].m_graph_width = tab_w;
		#else
			m_GraphViewList[i].m_graph_width = tab_w;
		#endif
		m_GraphViewList[i].m_graph_height = tab_h - (m_GraphViewList[i].m_fToolbarOn ? m_GraphViewList[i].ToolbarHeight():0);
		m_GraphViewList[i].m_Redraw = true;
	}
	
	// POSITION BUTTONS
	m_button_start.x = new_size.cx - 242;
	m_button_start.y = new_size.cy - 194;
	m_alt_button_start.x = new_size.cx - 242;
	m_alt_button_start.y = new_size.cy - 245;
	// END POSITION BUTTONS

	// MOVE FORMUNLA BOX
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_FORMULA);
    pWnd->GetWindowRect(&rc);     
	ScreenToClient(&rc);

	int h = rc.bottom - rc.top;
	int w = rc.right - rc.left;

	rc.bottom = new_size.cy - 198;     
	rc.top = rc.bottom - h;    
	rc.left = new_size.cx - 240;
	rc.right = rc.left + 236;

	pWnd->SetRedraw(false);
	pWnd->MoveWindow(&rc, true);
	pWnd->SetRedraw();
	pWnd->Invalidate();
	// END MOVE FORMULA BOX

	// tell graph to redraw if it is selected
	int graph_index;
	i = graph_index = GetActiveGraphTabIndex();
	if(graph_index != -1)
		{
		#ifdef GRAPH2D_INFOBAR
			if(m_GraphViewList[graph_index].m_fInfoBar)
				m_GraphViewList[graph_index].InvalidateRect(CRect(tab_w-BUTTON_PALLETE_WIDTH, 
															(m_GraphViewList[graph_index].m_fToolbarOn ? m_GraphViewList[graph_index].ToolbarHeight():0), 
															tab_w, 
															tab_h), true);
			else
				m_GraphViewList[graph_index].Invalidate(false);
		#else
			m_GraphViewList[graph_index].Invalidate(false);
		#endif
		}

#ifndef GRAPHCALC_LIGHT
	if(Is3DGraphActive())
		m_3DGraphView->Invalidate();
#endif
	
	// invalidate region around buttons and logo
	if(!m_FullScreen)
		InvalidateRect(CRect(m_button_start.x-8, 0, new_size.cx, m_button_start.y) , false);
}

void CGrphCalcDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if(m_StartProg){
		ResizeTabs(CSize(cx,cy));
	}
	else{		
		CString dir;
		dir =  g_strApplicationDirectory + "\\graphcalc.ini";
		CWinApp* pApp = AfxGetApp();
		pApp->m_pszProfileName = dir;
		
		CRect winrect;
		winrect.left	= pApp->GetProfileInt("WindowRect", "left", -1);
		winrect.right	= pApp->GetProfileInt("WindowRect", "right", -1);
		winrect.top		= pApp->GetProfileInt("WindowRect", "top", -1);
		winrect.bottom	= pApp->GetProfileInt("WindowRect", "bottom", -1);
		
		if(winrect.Width() > 0)
			MoveWindow(winrect, true);

		m_StartProg = true;
	}
}

/*********************************************************/
// CGrphCalcDlg::FormulaInsertion(CString value)
// Pre: none
// Post: m_FormulaCtrl is updated
// Return Value:  none
// Intent: to insert value into m_Formula wher ethe cursor
//		   is at
/*********************************************************/
void CGrphCalcDlg::FormulaInsertion(CString value)
{
	UpdateData(true);

	int pos_start, pos_end;
	DWORD span = m_FormulaCtrl.GetEditSel();
	pos_start = span & 0xFF;
	pos_end = (span>>16);

	// delete selected text
	if(pos_start != pos_end)
		m_Formula = m_Formula.Left(pos_start) + m_Formula.Right(m_Formula.GetLength() - pos_end);

	// insert new text
	m_Formula = m_Formula.Left(pos_start) + value + m_Formula.Right(m_Formula.GetLength() - pos_start);

	UpdateData(false);

	// for formulas
	if(value.Find("(a:b:c:d)") != -1){
		int s;
		s = m_Formula.Find("(a:b:c:d)",pos_start);
		m_FormulaCtrl.SetEditSel(s+1, s+8);
	}
	else if(value.Find("(a:b)") != -1){
		int s;
		s = m_Formula.Find("(a:b)",pos_start);
		m_FormulaCtrl.SetEditSel(s+1, s+4);
	}
	else if(value.Find("(a)") != -1){
		int s;
		s = m_Formula.Find("(a)",pos_start);
		m_FormulaCtrl.SetEditSel(s+1, s+2);
	}
	// for commands
	else if(value.Find("=a:b:c:d]") != -1){
		int s;
		s = m_Formula.Find("=a:b:c:d]",pos_start);
		m_FormulaCtrl.SetEditSel(s+1, s+8);
	}
	else if(value.Find("=a:b]") != -1){
		int s;
		s = m_Formula.Find("=a:b]",pos_start);
		m_FormulaCtrl.SetEditSel(s+1, s+4);
	}
	else if(value.Find("=a]") != -1){
		int s;
		s = m_Formula.Find("=a]",pos_start);
		m_FormulaCtrl.SetEditSel(s+1, s+2);
	}
	else
		m_FormulaCtrl.SetEditSel(pos_start + value.GetLength(), pos_start + value.GetLength());
}

/*********************************************************/
// 
// Pre:
// Post:
// Return Value:
// Intent:
/*********************************************************/
/*void CGrphCalcDlg::OnOptionsInsertConstant() 
{
	CInsertConstantDlg cons;
	cons.m_Calculator = &m_Calculator;

	if(cons.DoModal() == IDOK){
		::fstream file("constants.dat", ios::in, filebuf::sh_none);
		::fstream tfile("temp", ios::out, filebuf::sh_none);
		CString sline;
		char *cline = new char[50];
		char nl('\n');

		file.getline(cline, 50, '\n');
		sline = cline;
		tfile.write(sline, sline.GetLength());
		tfile.write(&nl, 1);

		while(sline != cons.m_Category && !file.eof()){
			file.getline(cline, 50, '\n');
			sline = cline;
			tfile.write(sline, sline.GetLength());
			tfile.write(&nl, 1);
		}

		if(file.eof()){
			tfile.write("****GROUP****\n", 14);
			tfile.write(cons.m_Category.GetBuffer(cons.m_Category.GetLength()), cons.m_Category.GetLength());
			tfile.write(&nl, 1);
		}

		tfile.write(cons.m_Name.GetBuffer(cons.m_Name.GetLength()), cons.m_Name.GetLength());
		tfile.write(&nl, 1);
		tfile.write(cons.m_Value.GetBuffer(cons.m_Value.GetLength()), cons.m_Value.GetLength());
		tfile.write(&nl, 1);

		while(!file.eof()){
			file.getline(cline, 50, '\n');
			sline = cline;
			tfile.write(sline, sline.GetLength());
			tfile.write(&nl, 1);
		}

		// close the files
		file.close();
		tfile.close();

		TRY{    
			CFile::Remove("constants.dat");
		}
		CATCH( CFileException, e ){
		#ifdef _DEBUG
				afxDump << "File temp not found, cause = "
						<< e->m_cause << "\n";    
		#endif
		}END_CATCH

		TRY{    
			CFile::Rename("temp", "constants.dat");
		}
		CATCH( CFileException, e ){
		#ifdef _DEBUG
				afxDump << "File temp not found, cause = "
						<< e->m_cause << "\n";    
		#endif
		}END_CATCH
			
	}
}*/
/*********************************************************/
// 
// Pre:
// Post:
// Return Value:
// Intent:
/*********************************************************/
/*void CGrphCalcDlg::OnInsertUnit() 
{
	CInsertUnitDlg unit;
	unit.m_Calculator = &m_Calculator;

	if(unit.DoModal() == IDOK){
		::fstream file("units.dat", ios::in, filebuf::sh_none);
		::fstream tfile("temp", ios::out, filebuf::sh_none);
		CString sline;
		char *cline = new char[50];
		char nl('\n');

		file.getline(cline, 50, '\n');
		sline = cline;
		tfile.write(sline, sline.GetLength());
		tfile.write(&nl, 1);

		while(sline != unit.m_Category && !file.eof()){
			file.getline(cline, 50, '\n');
			sline = cline;
			tfile.write(sline, sline.GetLength());
			tfile.write(&nl, 1);
			sline.TrimLeft();
		}

		if(file.eof()){
			tfile.write("****STANDARD****", 16);
			tfile.write(&nl, 1);
			tfile.write(unit.m_Category.GetBuffer(unit.m_Category.GetLength()), unit.m_Category.GetLength());
			tfile.write(&nl, 1);
			tfile.write(unit.m_NewCategoryDlg.m_TypeOne.GetBuffer(unit.m_NewCategoryDlg.m_TypeOne.GetLength()), 
						unit.m_NewCategoryDlg.m_TypeOne.GetLength());
			tfile.write(&nl, 1);
			tfile.write(unit.m_NewCategoryDlg.m_BaseOne.GetBuffer(unit.m_NewCategoryDlg.m_BaseOne.GetLength()), 
						unit.m_NewCategoryDlg.m_BaseOne.GetLength());
			tfile.write(&nl, 1);
			tfile.write(unit.m_NewCategoryDlg.m_TypeTwo.GetBuffer(unit.m_NewCategoryDlg.m_TypeTwo.GetLength()), 
						unit.m_NewCategoryDlg.m_TypeTwo.GetLength());
			tfile.write(&nl, 1);
			tfile.write(unit.m_NewCategoryDlg.m_BaseTwo.GetBuffer(unit.m_NewCategoryDlg.m_BaseTwo.GetLength()), 
						unit.m_NewCategoryDlg.m_BaseTwo.GetLength());
			tfile.write(&nl, 1);
			tfile.write(unit.m_NewCategoryDlg.m_Conversion.GetBuffer(unit.m_NewCategoryDlg.m_Conversion.GetLength()), 
						unit.m_NewCategoryDlg.m_Conversion.GetLength());
			tfile.write(&nl, 1);
		}
		else{
			for(int j = 0; j < 5; ++j){
				file.getline(cline, 50, '\n');
				sline = cline;
				tfile.write(sline, sline.GetLength());
				tfile.write(&nl, 1);
			}
		}

		tfile.write(unit.m_Name.GetBuffer(unit.m_Name.GetLength()), unit.m_Name.GetLength());
		tfile.write(&nl, 1);
		tfile.write(unit.m_Type.GetBuffer(unit.m_Type.GetLength()), unit.m_Type.GetLength());
		tfile.write(&nl, 1);
		tfile.write(unit.m_Value.GetBuffer(unit.m_Value.GetLength()), unit.m_Value.GetLength());
		tfile.write(&nl, 1);

		while(!file.eof()){
			file.getline(cline, 50, '\n');
			sline = cline;
			tfile.write(sline, sline.GetLength());
			tfile.write(&nl, 1);
		}

		// close the files
		file.close();
		tfile.close();

		TRY{    
			CFile::Remove("units.dat");
		}
		CATCH( CFileException, e ){
		#ifdef _DEBUG
				afxDump << "File temp not found, cause = "
						<< e->m_cause << "\n";    
		#endif
		}END_CATCH

		TRY{    
			CFile::Rename("temp", "units.dat");
		}
		CATCH( CFileException, e ){
		#ifdef _DEBUG
				afxDump << "File temp not found, cause = "
						<< e->m_cause << "\n";    
		#endif
		}END_CATCH
			
	}	
}*/

/*********************************************************/
// CGrphCalcDlg::OnHelp()
// Pre: none
// Post: none
// Return Value: none
// Intent: opens up the help files
/*********************************************************/
void CGrphCalcDlg::OnHelp() 
{
	HtmlHelp(NULL, g_strApplicationDirectory + "\\grphcalc.chm", HH_DISPLAY_TOPIC, 0);
}

/*********************************************************/
// CGrphCalcDlg::OnActivate(UINT nState, CWnd* pWndOther, 
//							BOOL bMinimized)
// Pre: none
// Post: none
// Return Value: none
// Intent: to set the focus of the control to the formula
//		   box when the window is activated
/*********************************************************/
void CGrphCalcDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	m_FormulaCtrl.SetFocus();
}
/*********************************************************/
// CGrphCalcDlg::DestroyWindow()
// Pre: window has been created
// Post: none
// Return Value: handled by parent
// Intent: to remove all graph tabs and destroy the window
/*********************************************************/
BOOL CGrphCalcDlg::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

/*********************************************************/
// CGrphCalcDlg::OnGraphOptionsChanged(WPARAM wParam, LPARAM lParam)
// Pre: none
// Post: none
// Return Value: 0
// Intent: called when the graph options have changed.
//		   this invalidates the graph so it redraws with
//		   new settings
/*********************************************************/
LRESULT CGrphCalcDlg::OnGraphOptionsChanged(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].DataExchange();
			m_GraphViewList[i].RePaintNow();
			break;
		}

	return 0;
}

LRESULT CGrphCalcDlg::On3DGraphOptionsChanged(WPARAM wParam, LPARAM lParam)
{
#ifndef GRAPHCALC_LIGHT
	m_3DGraphView->ApplyOptions();	
#endif
	return 0;
}

LRESULT CGrphCalcDlg::On2DCenterGraph(WPARAM wParam, LPARAM lParam)
{
	int i = GetActiveGraphTabIndex();
	if(i < 0) return 0;

	long double *x = (long double*)wParam;
	long double *y = (long double*)lParam;	

	m_GraphViewList[i].CenterGraph(*x, *y);
	return 0;
}

LRESULT CGrphCalcDlg::On2DNSliderUpdate(WPARAM wParam, LPARAM lParam)
{
	int i = GetActiveGraphTabIndex();
	if(i < 0) return 0;
	m_GraphViewList[i].RePaintNow();
	return 0;
}

/*********************************************************/
// CGrphCalcDlg::OnShowWindow(BOOL bShow, UINT nStatus)
// Pre: none
// Post: none
// Return Value: none
// Intent: to set control focus to m_FormulaCtrl when the
//		   window gains or loses focus
/*********************************************************/
void CGrphCalcDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	CRect client_r;
	GetClientRect(&client_r);
	ResizeTabs(CSize(client_r.right, client_r.bottom));
	m_FormulaCtrl.SetFocus();	
}

/*********************************************************/
// CGrphCalcDlg::ReadSettings()
// Pre: none
// Post: all data is initialized form file
// Return Value: none
// Intent: to read in the program settings from file
/*********************************************************/
void CGrphCalcDlg::ReadSettings(CString file)
{		
	CWinApp* pApp = AfxGetApp();
	pApp->m_pszProfileName = file;

	CSettingsIO io(&m_Calculator);
	int base;
	base = m_Calculator.m_base;
	m_Calculator.m_base = 10;

	m_CurrentPalete =			(PaleteE)io.ReadSettingInt("Program", "pallete", 0);
	m_SndEffects =				io.ReadSettingBool("Program", "sound", 1);
	m_ToolTips.On(io.ReadSettingBool("Program", "tooltips", 1));
	m_OutputV.m_LongOutput =	io.ReadSettingBool("Program", "longoutput", 0);
	m_AlwaysOnTop =				io.ReadSettingBool("Program", "alwaysontop", 0);

	m_bSaveExprHistory =	io.ReadSettingBool("Program", "saveexprhistory", 0);
	m_bSaveOutputHistory =	io.ReadSettingBool("Program", "saveoutputhistory", 0);
	m_bStartupScript =		io.ReadSettingBool("Program", "startupscript", 0);
	m_sScriptFile =			io.ReadSettingString("Program", "scriptfile", "");
	m_bShowCommandErrors =  io.ReadSettingBool("Program", "command_errors", 1);
	m_fShowScriptProgressDlg = io.ReadSettingBool("Program", "command_progress", 1);
	
	if(m_hWnd != NULL){
		if(m_AlwaysOnTop){
			SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		else{
			SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
	}
	
	base = io.ReadSettingInt("Calculator", "base", 10);
	m_Calculator.m_DecimalPlaces =	io.ReadSettingInt("Calculator", "base", 10);
	m_Calculator.m_Float = io.ReadSettingBool("Calculator", "float", 1);
	m_Calculator.m_trig_state = (TrigE)io.ReadSettingInt("Calculator", "trigstate", 0);
	m_Calculator.m_Normal = io.ReadSettingBool("Calculator", "scientific", 0);
	m_Calculator.m_IntlMode = (InternationalModeE)io.ReadSettingInt("Calculator", "international_mode", 0);
	
	m_Calculator.m_NumberSeperator = io.ReadSettingBool("Calculator", "number_seperator", 1);
	m_Calculator.m_NumberSeperatorAmount = io.ReadSettingInt("Calculator", "number_seperator_amount", 3);
	m_Calculator.m_nAnswerHistoryCount = io.ReadSettingInt("Calculator", "history_count", ANSWER_HISTORY);

	CString tmp;
	tmp = io.ReadSettingString("Calculator", "number_space_seperator", ",");
	if(!tmp.IsEmpty())
		m_Calculator.m_NumberSpaceSeperator = tmp[0];
	else
		m_Calculator.m_NumberSpaceSeperator = ' ';
	m_Calculator.m_DecimalSeperator = io.ReadSettingBool("Calculator", "decimal_seperator", 0);
	m_Calculator.m_DecimalSeperatorAmount = io.ReadSettingInt("Calculator", "decimal_seperator_amount", 3);

	tmp = io.ReadSettingString("Calculator", "decimal_space_seperator", " ");
	if(!tmp.IsEmpty())
		m_Calculator.m_DecimalSpaceSeperator = tmp[0];
	else
		m_Calculator.m_DecimalSpaceSeperator = ' ';

	// read output fonts
	m_OutputV.m_LFAnswerFont 		= io.ReadLogFont("OutputFonts", "Answer", m_OutputV.m_LFAnswerFont);	
	m_OutputV.m_LFExpressionFont	= io.ReadLogFont("OutputFonts", "Expression", m_OutputV.m_LFExpressionFont);
	m_OutputV.m_LFLongOutputFont	= io.ReadLogFont("OutputFonts", "LongOutput", m_OutputV.m_LFLongOutputFont);
	m_OutputV.m_LFBaseFont			= io.ReadLogFont("OutputFonts", "Base", m_OutputV.m_LFBaseFont);

	m_OutputV.m_AnswerFont 		= io.ReadCharFormat("OutputFonts", "Answer", m_OutputV.m_AnswerFont);
	m_OutputV.m_ExpressionFont 	= io.ReadCharFormat("OutputFonts", "Expression", m_OutputV.m_ExpressionFont);
	m_OutputV.m_LongOutputFont 	= io.ReadCharFormat("OutputFonts", "LongOutput", m_OutputV.m_LongOutputFont);
	m_OutputV.m_BaseFont 		= io.ReadCharFormat("OutputFonts", "Base", m_OutputV.m_BaseFont);

	ClearGraphTabsToAdd();
	///// read 2d graph stuff
	for(int i = 0; i < MAXTABS; ++i){
		CString item("on");
		item = item + char('0' + i);
		
		bool on;
		if(i == 0)
			on = true;
		else
			on = io.ReadSettingBool("GraphTabs", item, 0);

		if(on){
			m_bGraphTabsToAdd[i] = true;
			
			CString section("Graph");
			if(i != 0)
				section = section + char('0' + i);	

			Read2DGraphSettings(section , i, &io);	
		}
	}

#ifndef GRAPHCALC_LIGHT
	m_3DGraphView->SetBGColor(io.ReadSettingColorT("3DGraph", "bg_color", GetRGBString("0", "0", "0")));
	m_3DGraphView->SetWireResolution(io.ReadSettingInt("3DGraph", "wire_resolution", 2));
	m_3DGraphView->SetGridlineWidth(io.ReadSettingInt("3DGraph", "gridline_width", 1));
	m_3DGraphView->SetAxesOn(io.ReadSettingBool("3DGraph", "axes", 1));
	m_3DGraphView->SetAxesLabelsOn(io.ReadSettingBool("3DGraph", "axes_labels", 1));
	m_3DGraphView->SetAxesWidth(io.ReadSettingInt("3DGraph", "axes_width", 2));
	m_3DGraphView->SetAxesLengthMult(io.ReadSettingLDouble("3DGraph", "axes_length_multiplier", "1.1"));
	m_3DGraphView->SetXColor(io.ReadSettingColorT("3DGraph", "x_color", GetRGBString("0", "0", "0.7")));
	m_3DGraphView->SetYColor(io.ReadSettingColorT("3DGraph", "y_color", GetRGBString("0", "0.7", "0")));
	m_3DGraphView->SetZColor(io.ReadSettingColorT("3DGraph", "z_color", GetRGBString("0.7", "0", "0")));
	m_3DGraphView->SetOriginX(io.ReadSettingLDouble("3DGraph", "origin_x", "0"));
	m_3DGraphView->SetOriginY(io.ReadSettingLDouble("3DGraph", "origin_y", "0"));
	m_3DGraphView->SetOriginZ(io.ReadSettingLDouble("3DGraph", "origin_z", "0"));
	m_3DGraphView->SetThetaStep(io.ReadSettingLDouble("3DGraph", "theta_step", "0.5235987755983"));

	m_3DGraphView->SetXInterval(io.ReadSettingInt("3DGraph", "x_interval", 50));
	m_3DGraphView->SetYInterval(io.ReadSettingInt("3DGraph", "y_interval", 50));
	m_3DGraphView->SetXmin(io.ReadSettingLDouble("3DGraph", "x_min", "-5"));
	m_3DGraphView->SetXmax(io.ReadSettingLDouble("3DGraph", "x_max", "5"));
	m_3DGraphView->SetYmin(io.ReadSettingLDouble("3DGraph", "y_min", "-5"));
	m_3DGraphView->SetYmax(io.ReadSettingLDouble("3DGraph", "y_max", "5"));
	m_3DGraphView->SetZoomSpeed(io.ReadSettingLDouble("3DGraph", "ZoomSpeed", "2"));

	m_3DGraphView->SetGraphModePolar(io.ReadSettingBool("3DGraph", "mode", 0));

	
	m_3DGraphView->SetEquation(1, io.ReadSettingS3DEquation("3DGraph", "equation1",GetRGBString("0", "0.2", "0"),
																				   GetRGBString("1", "1", "0"),
																				   GetRGBString("0.8", "0", "0"),
																				   GetRGBString("0", "0", "0.5")));

	m_3DGraphView->SetEquation(2, io.ReadSettingS3DEquation("3DGraph", "equation2",GetRGBString("0", "0.2", "0"),
																				   GetRGBString("1", "1", "0"),
																				   GetRGBString("0.8", "0", "0"),
																				   GetRGBString("0", "0", "0.5")));

	m_3DGraphView->SetEquation(3, io.ReadSettingS3DEquation("3DGraph", "equation3",GetRGBString("0", "0.2", "0"),
																				   GetRGBString("1", "1", "0"),
																				   GetRGBString("0.8", "0", "0"),
																				   GetRGBString("0", "0", "0.5")));

	m_3DGraphView->SetEquation(4, io.ReadSettingS3DEquation("3DGraph", "equation4",GetRGBString("0", "0.2", "0"),
																				   GetRGBString("1", "1", "0"),
																				   GetRGBString("0.8", "0", "0"),
																				   GetRGBString("0", "0", "0.5")));

	m_3DGraphView->SetEquation(5, io.ReadSettingS3DEquation("3DGraph", "equation5",GetRGBString("0", "0.2", "0"),
																				   GetRGBString("1", "1", "0"),
																				   GetRGBString("0.8", "0", "0"),
																				   GetRGBString("0", "0", "0.5")));

	m_3DGraphView->SetEquation(6, io.ReadSettingS3DEquation("3DGraph", "equation6",GetRGBString("0", "0.2", "0"),
																			   GetRGBString("1", "1", "0"),
																			   GetRGBString("0.8", "0", "0"),
																			   GetRGBString("0", "0", "0.5")));

	m_3DGraphView->ExpandEquations();
	

	m_3DGraphView->SetXScale(io.ReadSettingLDouble("3DGraph", "xscale", "1.0"));
	m_3DGraphView->SetYScale(io.ReadSettingLDouble("3DGraph", "yscale", "1.0"));
	m_3DGraphView->SetZScale(io.ReadSettingLDouble("3DGraph", "zscale", "1.0"));
	m_3DGraphView->SetXRotate(io.ReadSettingLDouble("3DGraph", "xrotate", "-30.0"));
	m_3DGraphView->SetYRotate(io.ReadSettingLDouble("3DGraph", "yrotate", "0"));
	m_3DGraphView->SetZRotate(io.ReadSettingLDouble("3DGraph", "zrotate", "0"));
	m_3DGraphView->SetXTranslate(io.ReadSettingLDouble("3DGraph", "xtranslate", "0"));
	m_3DGraphView->SetYTranslate(io.ReadSettingLDouble("3DGraph", "ytranslate", "0"));
	m_3DGraphView->SetZTranslate(io.ReadSettingLDouble("3DGraph", "ztranslate", "-20"));

	m_3DGraphView->SetTicksOn(io.ReadSettingBool("3DGraphTicks", "tick_marks", 1));
	m_3DGraphView->SetTickCustomColor(io.ReadSettingBool("3DGraphTicks", "custom_colors", 1));
	m_3DGraphView->SetTickXInterval(io.ReadSettingLDouble("3DGraphTicks", "x_interval", "2.0"));
	m_3DGraphView->SetTickYInterval(io.ReadSettingLDouble("3DGraphTicks", "y_interval", "2.0"));
	m_3DGraphView->SetTickZInterval(io.ReadSettingLDouble("3DGraphTicks", "z_interval", "2.0"));
	m_3DGraphView->SetTickXColor(io.ReadSettingColorT("3DGraphTicks", "x_color", GetRGBString("0", "0", "0.7")));
	m_3DGraphView->SetTickYColor(io.ReadSettingColorT("3DGraphTicks", "y_color", GetRGBString("0", "0.7", "0.0")));
	m_3DGraphView->SetTickZColor(io.ReadSettingColorT("3DGraphTicks", "z_color", GetRGBString("0.7", "0", "0.0")));
	m_3DGraphView->SetTickWidth(io.ReadSettingLDouble("3DGraphTicks", "width", "1.5"));
	m_3DGraphView->SetTickLength(io.ReadSettingLDouble("3DGraphTicks", "length", "0.5"));
#endif

	/// Error checking ///
	if(base < 2 || base > 36)
		base = 10;

	if(m_Calculator.m_DecimalPlaces < 0 || m_Calculator.m_DecimalPlaces > 15)
		m_Calculator.m_DecimalPlaces = 10;
	
	m_Calculator.m_base = base;
}

void CGrphCalcDlg::Read2DGraphSettings(const CString section, int graph, CSettingsIO *io){
	m_GraphViewList[graph].m_Mode = (EGraphMode)io->ReadSettingInt(section, "mode", 0);

	m_GraphViewList[graph].m_astrEquationsRaw[0] = io->ReadSettingString(section, "y1", "sin(x)");
	m_GraphViewList[graph].m_astrEquationsRaw[1] = io->ReadSettingString(section, "y2", "cos(x)");
	m_GraphViewList[graph].m_astrEquationsRaw[2] = io->ReadSettingString(section, "y3", "");
	m_GraphViewList[graph].m_astrEquationsRaw[3] = io->ReadSettingString(section, "y4", "");
	m_GraphViewList[graph].m_astrEquationsRaw[4] = io->ReadSettingString(section, "y5", "");
	m_GraphViewList[graph].m_astrEquationsRaw[5] = io->ReadSettingString(section, "y6", "");
	m_GraphViewList[graph].m_astrEquationsRaw[6] = io->ReadSettingString(section, "y7", "");
	m_GraphViewList[graph].m_astrEquationsRaw[7] = io->ReadSettingString(section, "y8", "");
	m_GraphViewList[graph].m_astrEquationsRaw[8] = io->ReadSettingString(section, "y9", "");
	m_GraphViewList[graph].m_astrEquationsRaw[9] = io->ReadSettingString(section, "y10", "");
	m_GraphViewList[graph].ExpandEquations();
		
	m_GraphViewList[graph].m_Equations[0].disp = io->ReadSettingBool(section, "y1disp", 0);
	m_GraphViewList[graph].m_Equations[1].disp = io->ReadSettingBool(section, "y2disp", 0);
	m_GraphViewList[graph].m_Equations[2].disp = io->ReadSettingBool(section, "y3disp", 0);
	m_GraphViewList[graph].m_Equations[3].disp = io->ReadSettingBool(section, "y4disp", 0);
	m_GraphViewList[graph].m_Equations[4].disp = io->ReadSettingBool(section, "y5disp", 0);
	m_GraphViewList[graph].m_Equations[5].disp = io->ReadSettingBool(section, "y6disp", 0);
	m_GraphViewList[graph].m_Equations[6].disp = io->ReadSettingBool(section, "y7disp", 0);
	m_GraphViewList[graph].m_Equations[7].disp = io->ReadSettingBool(section, "y8disp", 0);
	m_GraphViewList[graph].m_Equations[8].disp = io->ReadSettingBool(section, "y9disp", 0);
	m_GraphViewList[graph].m_Equations[9].disp = io->ReadSettingBool(section, "y10disp", 0);
	m_GraphViewList[graph].m_Equations[0].color = io->ReadSettingCOLORREF(section, "y1color", "128,0,0");
	m_GraphViewList[graph].m_Equations[1].color = io->ReadSettingCOLORREF(section, "y2color", "0,128,0");
	m_GraphViewList[graph].m_Equations[2].color = io->ReadSettingCOLORREF(section, "y3color", "0,0,128");
	m_GraphViewList[graph].m_Equations[3].color = io->ReadSettingCOLORREF(section, "y4color", "128,128,0");
	m_GraphViewList[graph].m_Equations[4].color = io->ReadSettingCOLORREF(section, "y5color", "0,128,128");
	m_GraphViewList[graph].m_Equations[5].color = io->ReadSettingCOLORREF(section, "y6color", "128,0,128");
	m_GraphViewList[graph].m_Equations[6].color = io->ReadSettingCOLORREF(section, "y7color", "64,0,0");
	m_GraphViewList[graph].m_Equations[7].color = io->ReadSettingCOLORREF(section, "y8color", "0,64,0");
	m_GraphViewList[graph].m_Equations[8].color = io->ReadSettingCOLORREF(section, "y9color", "0,0,64");
	m_GraphViewList[graph].m_Equations[9].color = io->ReadSettingCOLORREF(section, "y10color", "64,64,0");

	m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Xmin = io->ReadSettingLDouble(section, "xmin", "-10");
	m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Xmax = io->ReadSettingLDouble(section, "xmax", "10");
	m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Xscl = io->ReadSettingLDouble(section, "xscl", "1");
	m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Ymin = io->ReadSettingLDouble(section, "ymin", "-10");
	m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Ymax = io->ReadSettingLDouble(section, "ymax", "10");
	m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Yscl = io->ReadSettingLDouble(section, "yscl", "1");

	m_GraphViewList[graph].m_FixedGrid = io->ReadSettingBool(section, "fixed_grid", 1);

	m_GraphViewList[graph].m_Coords = io->ReadSettingBool(section, "coordinates", 1);
	m_GraphViewList[graph].m_Style.line = (ELineStyle)io->ReadSettingInt(section, "graph_style", 0);
	m_GraphViewList[graph].m_Grid = io->ReadSettingBool(section, "grid", 0);
	m_GraphViewList[graph].m_Axis = io->ReadSettingBool(section, "axis", 1);
	m_GraphViewList[graph].m_Labels = io->ReadSettingBool(section, "labels", 0);
	m_GraphViewList[graph].SetCursorPositionState(io->ReadSettingBool(section, "cursorpos", 1));
	m_GraphViewList[graph].m_Style.size = io->ReadSettingInt(section, "width", 1);
	m_GraphViewList[graph].m_AxisStyle.size = io->ReadSettingInt(section, "axis_size", 2);
	m_GraphViewList[graph].m_GridStyle.size = io->ReadSettingInt(section, "grid_size", 1);
	m_GraphViewList[graph].m_nGridLabelInterval = io->ReadSettingInt(section, "grid_label_interval", 2);

	m_GraphViewList[graph].m_ZoomDecPrec = io->ReadSettingLDouble(section, "zoomprec", "0.05");
	m_GraphViewList[graph].m_EuclideanGraph.SetLinePrec(io->ReadSettingInt(section, "resolution", 100));
	m_GraphViewList[graph].m_ZoomPerc = io->ReadSettingInt(section, "zoom", 200);
	m_GraphViewList[graph].m_BackgroundClr = io->ReadSettingCOLORREF(section, "backgroundclr", "255,255,255");
	m_GraphViewList[graph].m_AxisStyle.color = io->ReadSettingCOLORREF(section, "axisclr", "90,90,90");
	m_GraphViewList[graph].m_GridStyle.color = io->ReadSettingCOLORREF(section, "gridclr", "215,215,215");
	m_GraphViewList[graph].m_CoordsClr = io->ReadSettingCOLORREF(section, "coordsclr", "128,128,128");
	m_GraphViewList[graph].m_TextClr = io->ReadSettingCOLORREF(section, "textclr", "192,128,128");
	m_GraphViewList[graph].m_AreaClr = io->ReadSettingCOLORREF(section, "areaclr", "192,192,230");

	m_GraphViewList[graph].m_ActiveDrawFontSize.y = m_GraphViewList[graph].m_DrawFontSize.y = (int)io->ReadSettingLDouble(section, "textsize", "14");

	m_GraphViewList[graph].m_fToolbarOn = io->ReadSettingBool(section, "toolbar", 1);
	m_GraphViewList[graph].m_fInfoBar = io->ReadSettingBool(section, "infobar", 1);
	
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Theta_min = io->ReadSettingLDouble("Polar" + section, "polar_thetamin", "0");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Theta_max = io->ReadSettingLDouble("Polar" + section, "polar_thetamax", "6.28318530717959");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Theta_step = io->ReadSettingLDouble("Polar" + section, "polar_thetastep", "0.01");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.GridAngle = io->ReadSettingLDouble("Polar" + section, "polar_gridangle", "1.570796326794897");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.GridRadius = io->ReadSettingLDouble("Polar" + section, "polar_gridradius", "1");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Xmin = io->ReadSettingLDouble("Polar" + section, "polar_xmin", "-5");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Xmax = io->ReadSettingLDouble("Polar" + section, "polar_xmax", "5");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Ymin = io->ReadSettingLDouble("Polar" + section, "polar_ymin", "-5");
	m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Ymax = io->ReadSettingLDouble("Polar" + section, "polar_ymax", "5");

	if(m_GraphViewList[graph].m_Style.size < 1 || m_GraphViewList[graph].m_Style.size > 50)
		m_GraphViewList[graph].m_Style.size = 1;

	if(m_GraphViewList[graph].m_EuclideanGraph.GetLinePrec() <= 0 || m_GraphViewList[graph].m_EuclideanGraph.GetLinePrec() > 100)
		m_GraphViewList[graph].m_EuclideanGraph.SetLinePrec(100);

	if(m_GraphViewList[graph].m_ZoomPerc < 100)
		m_GraphViewList[graph].m_ZoomPerc = 200;

	
	// write parametric settings
	m_GraphViewList[graph].m_ParametricGraph.m_Tmin = io->ReadSettingLDouble("Parametric" + section, "parametric_tmin", "0");
	m_GraphViewList[graph].m_ParametricGraph.m_Tmax = io->ReadSettingLDouble("Parametric" + section, "parametric_tmax", "10");
	m_GraphViewList[graph].m_ParametricGraph.m_Tstep = io->ReadSettingLDouble("Parametric" + section, "parametric_tstep", "0.05");
	m_GraphViewList[graph].m_ParametricGraph.m_Xmin = io->ReadSettingLDouble("Parametric" + section, "parametric_xmin", "-10");
	m_GraphViewList[graph].m_ParametricGraph.m_Xmax = io->ReadSettingLDouble("Parametric" + section, "parametric_xmax", "10");
	m_GraphViewList[graph].m_ParametricGraph.m_Xscl = io->ReadSettingLDouble("Parametric" + section, "parametric_xscl", "1");
	m_GraphViewList[graph].m_ParametricGraph.m_Ymin = io->ReadSettingLDouble("Parametric" + section, "parametric_ymin", "-10");
	m_GraphViewList[graph].m_ParametricGraph.m_Ymax = io->ReadSettingLDouble("Parametric" + section, "parametric_ymax", "10");
	m_GraphViewList[graph].m_ParametricGraph.m_Yscl = io->ReadSettingLDouble("Parametric" + section, "parametric_yscl", "1");

	for(int i=0; i < MAX_2D_PARAMETRIC_EQS; ++i)
		{
		CString strEqNumber;
		strEqNumber.Format("%d", i+1);
		
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].xt = io->ReadSettingString("Parametric" + section, "xt" + strEqNumber, "");
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].yt = io->ReadSettingString("Parametric" + section, "yt" + strEqNumber, "");
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].disp = io->ReadSettingBool("Parametric" + section, strEqNumber + "disp", 0);
		}
	
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[0].color = io->ReadSettingCOLORREF("Parametric" + section, "1color", "128,0,0");
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[1].color = io->ReadSettingCOLORREF("Parametric" + section, "2color", "0,128,0");
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[2].color = io->ReadSettingCOLORREF("Parametric" + section, "3color", "0,0,128");
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[3].color = io->ReadSettingCOLORREF("Parametric" + section, "4color", "128,128,0");
		m_GraphViewList[graph].m_ParametricGraph.m_Equations[4].color = io->ReadSettingCOLORREF("Parametric" + section, "5color", "0,128,128");


	m_GraphViewList[graph].m_Redraw = true;
}

SRGBString CGrphCalcDlg::GetRGBString(CString r, CString g, CString b)
{
	SRGBString t;
	t.r = r;
	t.g = g;
	t.b = b;
	return t;
}

CString CGrphCalcDlg::GetLine(::ifstream *infile)
{
	CString CSline;
	char *cline = new char[200];
	infile->getline(cline, 200, '\n');
	CSline = (LPCTSTR)cline;
	CSline.TrimLeft();
	CSline.TrimRight();
	
	delete cline;
	return CSline;
}

void CGrphCalcDlg::WriteSettings(CString file)
{
	CWinApp* pApp = AfxGetApp();
	pApp->m_pszProfileName = file;

	CSettingsIO io(&m_Calculator);

	CString line;
	int base = m_Calculator.m_base;
	m_Calculator.m_base = 10;
	
	io.WriteSetting("Program", "pallete", m_CurrentPalete);
	io.WriteSetting("Program", "sound", m_SndEffects);
	io.WriteSetting("Program", "tooltips", m_ToolTips.IsOn());
	io.WriteSetting("Program", "longoutput", m_OutputV.m_LongOutput);
	io.WriteSetting("Program", "alwaysontop", m_AlwaysOnTop);

	io.WriteSetting("Program", "saveexprhistory", m_bSaveExprHistory);
	io.WriteSetting("Program", "saveoutputhistory", m_bSaveOutputHistory);
	io.WriteSetting("Program", "startupscript", m_bStartupScript);
	io.WriteSetting("Program", "scriptfile", m_sScriptFile);
	io.WriteSetting("Program", "command_errors", m_bShowCommandErrors);
	io.WriteSetting("Program", "command_progress", m_fShowScriptProgressDlg);

	io.WriteSetting("Calculator", "base", base);
	io.WriteSetting("Calculator", "decimalplaces", m_Calculator.m_DecimalPlaces);
	io.WriteSetting("Calculator", "float", m_Calculator.m_Float);
	io.WriteSetting("Calculator", "trigstate", m_Calculator.m_trig_state);
	io.WriteSetting("Calculator", "scientific", m_Calculator.m_Normal);
	io.WriteSetting("Calculator", "international_mode", m_Calculator.m_IntlMode);
	io.WriteSetting("Calculator", "number_seperator", m_Calculator.m_NumberSeperator);
	io.WriteSetting("Calculator", "number_seperator_amount", m_Calculator.m_NumberSeperatorAmount);
	io.WriteSetting("Calculator", "number_space_seperator", CString(m_Calculator.m_NumberSpaceSeperator));
	io.WriteSetting("Calculator", "decimal_seperator", m_Calculator.m_DecimalSeperator);
	io.WriteSetting("Calculator", "decimal_seperator_amount", m_Calculator.m_DecimalSeperatorAmount);
	io.WriteSetting("Calculator", "decimal_space_seperator", CString(m_Calculator.m_DecimalSpaceSeperator));
	io.WriteSetting("Calculator", "history_count", m_Calculator.m_nAnswerHistoryCount);	

	if(m_fSaveFont || m_fNotShutdown)
		{
		io.WriteLogFont("OutputFonts", "Answer", m_OutputV.m_LFAnswerFont);	
		io.WriteLogFont("OutputFonts", "LongOutput", m_OutputV.m_LFLongOutputFont);	
		io.WriteLogFont("OutputFonts", "Expression", m_OutputV.m_LFExpressionFont);	
		io.WriteLogFont("OutputFonts", "Base", m_OutputV.m_LFBaseFont);

		io.WriteCharFormat("OutputFonts", "Answer", m_OutputV.m_AnswerFont);
		io.WriteCharFormat("OutputFonts", "Expression", m_OutputV.m_ExpressionFont);
		io.WriteCharFormat("OutputFonts", "LongOutput", m_OutputV.m_LongOutputFont);
		io.WriteCharFormat("OutputFonts", "Base", m_OutputV.m_BaseFont);
		}
	
	bool first(true);
	for(int i = 0; i < MAXTABS; ++i){
		if(m_ActiveGraphView[i] && (m_GraphViewList[i].m_fSaveSettings || m_fNotShutdown)){
			
			if(!first){
				CString section("Graph");
				CString item("on");
				section = section + char('0' + i);
				item = item + char('0' + i);

				io.WriteSetting("GraphTabs", item , 1);
				Write2DGraphSettings(section , i, &io);	
			}
			else{
				first = false;
				CString item("on");
				item = item + char('0' + i);
				io.WriteSetting("GraphTabs", item, 0);
				io.WriteSetting("GraphTabs", "on0", 1);

				Write2DGraphSettings("Graph", i, &io);	
			}
		}
		else{
			CString item("on");
			item = item + char('0' + i);
			io.WriteSetting("GraphTabs", item, 0);
		}
	}


#ifndef GRAPHCALC_LIGHT
	//////////////////////////////////////////////
	// Write 3D Graph Settings
	if(m_3DGraphView->m_fSaveSettings || m_fNotShutdown)
		{
		io.WriteSetting("3DGraph", "mode", (int)m_3DGraphView->GetGraphModePolar());

		io.WriteSettingColorT("3DGraph", "bg_color",	m_3DGraphView->GetBGColor());
		io.WriteSetting("3DGraph", "wire_resolution",	m_3DGraphView->GetWireResolution());
		io.WriteSetting("3DGraph", "gridline_width",	m_3DGraphView->GetGridlineWidth());
		io.WriteSetting("3DGraph", "axes",				m_3DGraphView->GetAxesOn());
		io.WriteSetting("3DGraph", "axes_labels",		m_3DGraphView->GetAxesLabelsOn());

		io.WriteSetting("3DGraph", "axes_width",		m_3DGraphView->GetAxesWidth());
		io.WriteSetting("3DGraph", "axes_length_multiplier",	m_3DGraphView->GetAxesLengthMult());
		io.WriteSettingColorT("3DGraph", "x_color",	m_3DGraphView->GetXColor());
		io.WriteSettingColorT("3DGraph", "y_color",	m_3DGraphView->GetYColor());
		io.WriteSettingColorT("3DGraph", "z_color",	m_3DGraphView->GetZColor());
		io.WriteSetting("3DGraph", "origin_x",			m_3DGraphView->GetOriginX());
		io.WriteSetting("3DGraph", "origin_y",			m_3DGraphView->GetOriginY());
		io.WriteSetting("3DGraph", "origin_z",			m_3DGraphView->GetOriginZ());
		io.WriteSetting("3DGraph", "theta_step",		m_3DGraphView->GetThetaStep());
		io.WriteSetting("3DGraph", "x_interval",		m_3DGraphView->GetXInterval());
		io.WriteSetting("3DGraph", "y_interval",		m_3DGraphView->GetYInterval());
		io.WriteSetting("3DGraph", "x_min",			m_3DGraphView->GetXmin());
		io.WriteSetting("3DGraph", "x_max",			m_3DGraphView->GetXmax());
		io.WriteSetting("3DGraph", "y_min",			m_3DGraphView->GetYmin());
		io.WriteSetting("3DGraph", "y_max",			m_3DGraphView->GetYmax());
		io.WriteSetting("3DGraph", "ZoomSpeed",		m_3DGraphView->GetZoomSpeed());
		
		io.WriteSettingS3DEquation("3DGraph", "equation1", m_3DGraphView->GetEquation(1), m_3DGraphView->GetEquationRaw(1));
		io.WriteSettingS3DEquation("3DGraph", "equation2", m_3DGraphView->GetEquation(2), m_3DGraphView->GetEquationRaw(2));
		io.WriteSettingS3DEquation("3DGraph", "equation3", m_3DGraphView->GetEquation(3), m_3DGraphView->GetEquationRaw(3));
		io.WriteSettingS3DEquation("3DGraph", "equation4", m_3DGraphView->GetEquation(4), m_3DGraphView->GetEquationRaw(4));
		io.WriteSettingS3DEquation("3DGraph", "equation5", m_3DGraphView->GetEquation(5), m_3DGraphView->GetEquationRaw(5));
		io.WriteSettingS3DEquation("3DGraph", "equation6", m_3DGraphView->GetEquation(6), m_3DGraphView->GetEquationRaw(6));

		io.WriteSetting("3DGraph", "xscale",			long double(m_3DGraphView->GetXScale()));
		io.WriteSetting("3DGraph", "yscale",			long double(m_3DGraphView->GetYScale()));
		io.WriteSetting("3DGraph", "zscale",			long double(m_3DGraphView->GetZScale()));
		io.WriteSetting("3DGraph", "xrotate",			long double(m_3DGraphView->GetXRotate()));
		io.WriteSetting("3DGraph", "yrotate",			long double(m_3DGraphView->GetYRotate()));
		io.WriteSetting("3DGraph", "zrotate",			long double(m_3DGraphView->GetZRotate()));
		io.WriteSetting("3DGraph", "xtranslate",		long double(m_3DGraphView->GetXTranslate()));
		io.WriteSetting("3DGraph", "ytranslate",		long double(m_3DGraphView->GetYTranslate()));
		io.WriteSetting("3DGraph", "ztranslate",		long double(m_3DGraphView->GetZTranslate()));

		io.WriteSetting("3DGraphTicks", "tick_marks", m_3DGraphView->GetTicksOn());
		io.WriteSetting("3DGraphTicks", "custom_colors", m_3DGraphView->GetTickCustomColor());
		io.WriteSetting("3DGraphTicks", "x_interval", m_3DGraphView->GetTickXInterval());
		io.WriteSetting("3DGraphTicks", "y_interval", m_3DGraphView->GetTickYInterval());
		io.WriteSetting("3DGraphTicks", "z_interval", m_3DGraphView->GetTickZInterval());
		io.WriteSettingColorT("3DGraphTicks", "x_color", m_3DGraphView->GetTickXColor());
		io.WriteSettingColorT("3DGraphTicks", "y_color", m_3DGraphView->GetTickYColor());
		io.WriteSettingColorT("3DGraphTicks", "z_color", m_3DGraphView->GetTickZColor());
		io.WriteSetting("3DGraphTicks", "width", m_3DGraphView->GetTickWidth());
		io.WriteSetting("3DGraphTicks", "length", m_3DGraphView->GetTickLength());
		}
#endif

	m_Calculator.m_base = base;
}

void CGrphCalcDlg::Write2DGraphSettings(const CString section, int graph, CSettingsIO *io){
	io->WriteSetting(section, "mode", (int)m_GraphViewList[graph].m_Mode);

	io->WriteSetting(section, "y1", m_GraphViewList[graph].m_astrEquationsRaw[0]);
	io->WriteSetting(section, "y2", m_GraphViewList[graph].m_astrEquationsRaw[1]);
	io->WriteSetting(section, "y3", m_GraphViewList[graph].m_astrEquationsRaw[2]);
	io->WriteSetting(section, "y4", m_GraphViewList[graph].m_astrEquationsRaw[3]);
	io->WriteSetting(section, "y5", m_GraphViewList[graph].m_astrEquationsRaw[4]);
	io->WriteSetting(section, "y6", m_GraphViewList[graph].m_astrEquationsRaw[5]);
	io->WriteSetting(section, "y7", m_GraphViewList[graph].m_astrEquationsRaw[6]);
	io->WriteSetting(section, "y8", m_GraphViewList[graph].m_astrEquationsRaw[7]);
	io->WriteSetting(section, "y9", m_GraphViewList[graph].m_astrEquationsRaw[8]);
	io->WriteSetting(section, "y10", m_GraphViewList[graph].m_astrEquationsRaw[9]);
	io->WriteColorSetting(section, "y1color", m_GraphViewList[graph].m_Equations[0].color);
	io->WriteColorSetting(section, "y2color", m_GraphViewList[graph].m_Equations[1].color);
	io->WriteColorSetting(section, "y3color", m_GraphViewList[graph].m_Equations[2].color);
	io->WriteColorSetting(section, "y4color", m_GraphViewList[graph].m_Equations[3].color);
	io->WriteColorSetting(section, "y5color", m_GraphViewList[graph].m_Equations[4].color);
	io->WriteColorSetting(section, "y6color", m_GraphViewList[graph].m_Equations[5].color);
	io->WriteColorSetting(section, "y7color", m_GraphViewList[graph].m_Equations[6].color);
	io->WriteColorSetting(section, "y8color", m_GraphViewList[graph].m_Equations[7].color);
	io->WriteColorSetting(section, "y9color", m_GraphViewList[graph].m_Equations[8].color);
	io->WriteColorSetting(section, "y10color", m_GraphViewList[graph].m_Equations[9].color);
	io->WriteSetting(section, "y1disp", m_GraphViewList[graph].m_Equations[0].disp);
	io->WriteSetting(section, "y2disp", m_GraphViewList[graph].m_Equations[1].disp);
	io->WriteSetting(section, "y3disp", m_GraphViewList[graph].m_Equations[2].disp);
	io->WriteSetting(section, "y4disp", m_GraphViewList[graph].m_Equations[3].disp);
	io->WriteSetting(section, "y5disp", m_GraphViewList[graph].m_Equations[4].disp);
	io->WriteSetting(section, "y6disp", m_GraphViewList[graph].m_Equations[5].disp);
	io->WriteSetting(section, "y7disp", m_GraphViewList[graph].m_Equations[6].disp);
	io->WriteSetting(section, "y8disp", m_GraphViewList[graph].m_Equations[7].disp);
	io->WriteSetting(section, "y9disp", m_GraphViewList[graph].m_Equations[8].disp);
	io->WriteSetting(section, "y10disp", m_GraphViewList[graph].m_Equations[9].disp);
	io->WriteSetting(section, "xmax", m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Xmax);
	io->WriteSetting(section, "xmin", m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Xmin);
	io->WriteSetting(section, "xscl", m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Xscl);
	io->WriteSetting(section, "ymax", m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Ymax);
	io->WriteSetting(section, "ymin", m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Ymin);
	io->WriteSetting(section, "yscl", m_GraphViewList[graph].m_EuclideanGraph.m_EuclideanRange.Yscl);
	io->WriteSetting(section, "fixed_grid", m_GraphViewList[graph].m_FixedGrid);

	io->WriteSetting(section, "coordinates", m_GraphViewList[graph].m_Coords);
	io->WriteSetting(section, "graph_style", m_GraphViewList[graph].m_Style.line);
	io->WriteSetting(section, "grid", m_GraphViewList[graph].m_Grid);
	io->WriteSetting(section, "axis", m_GraphViewList[graph].m_Axis);
	io->WriteSetting(section, "labels", m_GraphViewList[graph].m_Labels);
	io->WriteSetting(section, "cursorpos", m_GraphViewList[graph].m_CursorPos);
	io->WriteSetting(section, "width", m_GraphViewList[graph].m_Style.size);
	io->WriteSetting(section, "zoomprec", m_GraphViewList[graph].m_ZoomDecPrec);
	io->WriteSetting(section, "resolution", m_GraphViewList[graph].m_EuclideanGraph.GetLinePrec());
	io->WriteSetting(section, "zoom", m_GraphViewList[graph].m_ZoomPerc);
	io->WriteSetting(section, "axis_size", m_GraphViewList[graph].m_AxisStyle.size);
	io->WriteSetting(section, "grid_size", m_GraphViewList[graph].m_GridStyle.size);
	io->WriteSetting(section, "grid_label_interval", m_GraphViewList[graph].m_nGridLabelInterval);

	io->WriteColorSetting(section, "backgroundclr", m_GraphViewList[graph].m_BackgroundClr);
	io->WriteColorSetting(section, "axisclr", m_GraphViewList[graph].m_AxisStyle.color);
	io->WriteColorSetting(section, "gridclr", m_GraphViewList[graph].m_GridStyle.color);
	io->WriteColorSetting(section, "coordsclr", m_GraphViewList[graph].m_CoordsClr);
	io->WriteColorSetting(section, "textclr", m_GraphViewList[graph].m_TextClr);
	io->WriteColorSetting(section, "areaclr", m_GraphViewList[graph].m_AreaClr);
	
	io->WriteSetting(section, "textsize", (int)m_GraphViewList[graph].m_DrawFontSize.y);

	
	io->WriteSetting(section, "toolbar", (int)m_GraphViewList[graph].m_fToolbarOn);
	io->WriteSetting(section, "infobar", (int)m_GraphViewList[graph].m_fInfoBar);

	// write polar settings
	io->WriteSetting("Polar" + section, "polar_thetamin", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Theta_min);
	io->WriteSetting("Polar" + section, "polar_thetamax", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Theta_max);
	io->WriteSetting("Polar" + section, "polar_thetastep", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Theta_step);
	io->WriteSetting("Polar" + section, "polar_gridangle", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.GridAngle);
	io->WriteSetting("Polar" + section, "polar_gridradius", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.GridRadius);
	io->WriteSetting("Polar" + section, "polar_xmin", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Xmin);
	io->WriteSetting("Polar" + section, "polar_xmax", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Xmax);
	io->WriteSetting("Polar" + section, "polar_ymin", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Ymin);
	io->WriteSetting("Polar" + section, "polar_ymax", m_GraphViewList[graph].m_PolarGraph.m_PolarRange.Ymax);

	// write parametric settings
	io->WriteSetting("Parametric" + section, "parametric_tmin", m_GraphViewList[graph].m_ParametricGraph.m_Tmin);
	io->WriteSetting("Parametric" + section, "parametric_tmax", m_GraphViewList[graph].m_ParametricGraph.m_Tmax);
	io->WriteSetting("Parametric" + section, "parametric_tstep", m_GraphViewList[graph].m_ParametricGraph.m_Tstep);
	io->WriteSetting("Parametric" + section, "parametric_xmin", m_GraphViewList[graph].m_ParametricGraph.m_Xmin);
	io->WriteSetting("Parametric" + section, "parametric_xmax", m_GraphViewList[graph].m_ParametricGraph.m_Xmax);
	io->WriteSetting("Parametric" + section, "parametric_xscl", m_GraphViewList[graph].m_ParametricGraph.m_Xscl);
	io->WriteSetting("Parametric" + section, "parametric_ymin", m_GraphViewList[graph].m_ParametricGraph.m_Ymin);
	io->WriteSetting("Parametric" + section, "parametric_ymax", m_GraphViewList[graph].m_ParametricGraph.m_Ymax);
	io->WriteSetting("Parametric" + section, "parametric_yscl", m_GraphViewList[graph].m_ParametricGraph.m_Yscl);

	for(int i=0; i < MAX_2D_PARAMETRIC_EQS; ++i)
		{
		CString strEqNumber;
		strEqNumber.Format("%d", i+1);
		
		io->WriteSetting("Parametric" + section, "xt" + strEqNumber, m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].xt);
		io->WriteSetting("Parametric" + section, "yt" + strEqNumber, m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].yt);
		io->WriteColorSetting("Parametric" + section, strEqNumber + "color", m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].color);
		io->WriteSetting("Parametric" + section, strEqNumber + "disp", m_GraphViewList[graph].m_ParametricGraph.m_Equations[i].disp);
		}
}

void CGrphCalcDlg::OnFileLoadsettingsfile() 
{
	static char BASED_CODE szFilter[] = "GraphCalc Files (*.gcl)|*.gcl||";	

	CFileDialog *fileDlg = new CFileDialog(true, 
										   "gcl",
										    NULL,
											OFN_ENABLESIZING 
											| OFN_FILEMUSTEXIST 
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT 
											| OFN_READONLY,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK){
		ReadSettings(fileDlg->GetPathName());
	}

	delete fileDlg;
	AddGraphTabs();

	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].RePaintNow();
			break;
		}
}

void CGrphCalcDlg::OnFileSavesettingsas() 
{
	static char BASED_CODE szFilter[] = "GraphCalc Files (*.gcl)|*.gcl||";	

	CFileDialog *fileDlg = new CFileDialog(false, 
										   "gcl",
										    NULL,
											OFN_ENABLESIZING 
											| OFN_CREATEPROMPT
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK){
		WriteSettings(fileDlg->GetPathName());
	}

	delete fileDlg;	
}

void CGrphCalcDlg::LoadSettings()
{
	CString dir;
	/* 
	for upgrade purposes check to see if they have an ini file
	in c:\
	*/
	bool old_exists(true);
	::ifstream infile;
	infile.open("C:\\graphcalc.ini", ios::nocreate);
	if(infile.rdstate() == ios::failbit){
		old_exists = false;
		dir =  g_strApplicationDirectory + "\\graphcalc.ini"; // file not found, get default dir file
	}
	else
		dir = "c:\\graphcalc.ini";

	infile.close();
	// end upgrade ini file


	CWinApp* pApp = AfxGetApp();
	pApp->m_pszProfileName = dir;

	m_SettingsFile = pApp->GetProfileString("Settings", "file", g_strApplicationDirectory + "\\default.gcl");

	m_SaveSettings = (pApp->GetProfileInt("Settings", "savesettings", 1) == 1);

	// remove old ini file
	if(old_exists){
		TRY{    
			CFile::Remove("c:\\graphcalc.ini");
		}
		CATCH( CFileException, e ){
		#ifdef _DEBUG
				afxDump << "File temp not found, cause = "
						<< e->m_cause << "\n";    
		#endif
		}END_CATCH
	}
	// end remove old ini file

	if(m_SettingsFile.IsEmpty())
		m_SettingsFile = g_strApplicationDirectory + "\\default.gcl";

	ReadSettings(m_SettingsFile);

	m_SettingsFile.MakeLower();

	if(old_exists && m_SettingsFile == "c:\\default.gcl"){
		TRY{    
			CFile::Remove("c:\\default.gcl");
		}
		CATCH( CFileException, e ){
		#ifdef _DEBUG
				afxDump << "File temp not found, cause = "
						<< e->m_cause << "\n";    
		#endif
		}END_CATCH

		m_SettingsFile = g_strApplicationDirectory + "\\default.gcl";

	}
}

void CGrphCalcDlg::TestFile()
{
	::ofstream ofile;
	ofile.open("C:\\GC Test Results.txt", ios::trunc, filebuf::openprot);
	ofile.close();

	::ifstream infile;
	CString CSline;
	int cons(0);
	
	char *cline = new char[100];
	infile.open("C:\\GCtester.txt");
	
	while(!infile.eof()){
		
		infile.getline(cline, 100, '\n');
		CSline = (LPCTSTR)cline;
		CSline.TrimLeft();
		CSline.TrimRight();
		
		m_OutputV.OnEnter(CSline, m_Calculator, &m_FormulaCtrl);
	}
	
	delete cline;
	infile.close();
}

void CGrphCalcDlg::OnOptionsAlwaysontop() 
{
	if(!m_AlwaysOnTop){
		m_AlwaysOnTop = true;
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else{
		m_AlwaysOnTop = false;
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}
void CGrphCalcDlg::OnEditchangeFormula() 
{
	CString old = m_Formula;
	UpdateData(true);
	int pos_start, pos_end;
	if(m_Formula == "+"
		|| m_Formula == "+"
		|| m_Formula == "-"
		|| m_Formula == "*"
		|| m_Formula == "/"
		|| m_Formula == "^"
		|| m_Formula == "!"){
		
		DWORD span = m_FormulaCtrl.GetEditSel();
		pos_start = span & 0xFF;
		pos_end = (span>>16);
		
		m_Formula = "ans" + m_Formula;
		UpdateData(false);

		m_FormulaCtrl.SetEditSel(m_Formula.GetLength(), m_Formula.GetLength());
	}

	UpdateData(false);
}


void CGrphCalcDlg::SetSndEffects(bool val){ m_SndEffects = val; }
void CGrphCalcDlg::SetSaveSettings(bool val){ m_SaveSettings = val; }
void CGrphCalcDlg::SetDetailedOutput(bool val){ m_OutputV.m_LongOutput = val; }
void CGrphCalcDlg::SetTooltips(bool val){ m_ToolTips.On(val); }
void CGrphCalcDlg::SetFullScreen(bool val){ 
	m_FullScreen = val; 

	if(m_FullScreen)
		m_FormulaCtrl.ShowWindow(SW_HIDE);
	else
		m_FormulaCtrl.ShowWindow(SW_SHOW);

	CRect client_r;
	GetClientRect(&client_r);
	ResizeTabs(CSize(client_r.right, client_r.bottom));	
	Invalidate();
}
void CGrphCalcDlg::SetAlwaysOnTop(bool val){ 
	m_AlwaysOnTop = val; 
	if(m_AlwaysOnTop)
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	else
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void CGrphCalcDlg::SetTab(CString val){ 

	CString lower_val(val);
	lower_val.MakeLower();

	if(lower_val == "output")
		m_view.SetActivePage(&m_OutputV);
#ifndef GRAPHCALC_LIGHT
	else if(lower_val == "3dgraph")
		m_view.SetActivePage(m_3DGraphView);
#endif
	else{
		bool first(true);
		int index(-1);

		for(int i = 0; i < MAXTABS; ++i){	
			if(m_ActiveGraphView[i]){
				if(first){
					first = false;
					index = i;
				}

				CTabCtrl* pTab = m_view.GetTabControl();
				TC_ITEM tcItem;				
				tcItem.mask = TCIF_TEXT;
				char *name = new char[15];
				tcItem.pszText = name;
				tcItem.cchTextMax = 15;
				if(pTab->GetItem(m_view.GetPageIndex(&m_GraphViewList[i]) , &tcItem ))				
					if(tcItem.pszText == val){
						m_view.SetActivePage(&m_GraphViewList[i]);
						break;
					}
				delete name;
			}
		}
		
		if(i == MAXTABS && lower_val == "graph")
			m_view.SetActivePage(&m_GraphViewList[index]);	
	}
}


void CGrphCalcDlg::SetEquation(int eq, CString val)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].SetEquation(eq, val);
			m_GraphViewList[i].RePaintNow();
			break;
		}
}

void CGrphCalcDlg::SetEquationState(int eq, bool val)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].SetEquationState(eq, val);
			m_GraphViewList[i].RePaintNow();
			break;
		}
}

void CGrphCalcDlg::SetEquationColor(int eq, CString val)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			m_GraphViewList[i].SetEquationColor(eq, val);
			m_GraphViewList[i].RePaintNow();
			break;
		}
}

void CGrphCalcDlg::SetGraphNumber(CString param, long double val)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){

			if(param == "2DXmin")				m_GraphViewList[i].m_EuclideanGraph.m_EuclideanRange.Xmin = val;
			else if(param == "2DXmax")		m_GraphViewList[i].m_EuclideanGraph.m_EuclideanRange.Xmax = val;
			else if(param == "2DXscl")		m_GraphViewList[i].m_EuclideanGraph.m_EuclideanRange.Xscl = val;
			else if(param == "2DYmin")		m_GraphViewList[i].m_EuclideanGraph.m_EuclideanRange.Ymin = val;
			else if(param == "2DYmax")		m_GraphViewList[i].m_EuclideanGraph.m_EuclideanRange.Ymax = val;
			else if(param == "2DYscl")		m_GraphViewList[i].m_EuclideanGraph.m_EuclideanRange.Yscl = val;
			else if(param == "2DAreaPrecision")		m_GraphViewList[i].m_AreaDeltaX = pow(10,(-1*val));
	
			else if(param == "2DAxisSize")	m_GraphViewList[i].m_AxisStyle.size = val;
			else if(param == "2DGridSize")	m_GraphViewList[i].m_GridStyle.size = val;
			else if(param == "2DLineSize")	m_GraphViewList[i].m_Style.size = val;
			else if(param == "2DZoomDecimalPrec")		m_GraphViewList[i].m_ZoomDecPrec = val;
			else if(param == "2DLineResolution")		m_GraphViewList[i].m_EuclideanGraph.SetLinePrec(val);
			else if(param == "2DZoomFactor")	m_GraphViewList[i].m_ZoomPerc = val;
			
			else if(param == "2DPolarXmax")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Xmax = val;
			else if(param == "2DPolarXmin")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Xmin = val;
			else if(param == "2DPolarYmin")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Ymin = val;
			else if(param == "2DPolarYmax")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Ymax = val;
			else if(param == "2DPolarThetaMin")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Theta_min = val;
			else if(param == "2DPolarThetaMax")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Theta_max = val;
			else if(param == "2DPolarThetaStep")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.Theta_step = val;
			else if(param == "2DPolarGridAngle")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.GridAngle = val;
			else if(param == "2DPolarGridSpace")		m_GraphViewList[i].m_PolarGraph.m_PolarRange.GridRadius = val;

			else if(param == "2DFontSize")
				m_GraphViewList[i].m_DrawFontSize.y = m_GraphViewList[i].m_ActiveDrawFontSize.y = val;

			m_GraphViewList[i].m_Redraw = true;
			break;
		}
}

void CGrphCalcDlg::SetGraphString(CString param, CString val)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
						
			if(param == "2DBackgroundColor")	m_GraphViewList[i].SetBackgroundColor(val);
			else if(param == "2DAxisColor")	m_GraphViewList[i].SetAxisColor(val);
			else if(param == "2DGridColor")	m_GraphViewList[i].SetGridColor(val);
			else if(param == "2DCoordinatesColor")	m_GraphViewList[i].SetCoordinatesColor(val);
			else if(param == "2DOtherText")	m_GraphViewList[i].SetOtherTextColor(val);
			else if(param == "2DAreaColor")	m_GraphViewList[i].SetAreaColor(val);
			else if(param == "2DPlotStyle"){
				if(val == "dot")
					m_GraphViewList[i].m_Style.line = GRAPH_STYLE_POINT;
				else if(val == "line")
					m_GraphViewList[i].m_Style.line = GRAPH_STYLE_LINE;
			}
			/*else if(param == "2DGraphMode"){
				if(val == "euclidean" || val == "Euclidean" || val == "EUCLIDEAN") m_GraphViewList[i].m_Mode = EUCLIDEAN;
				else if(val == "polar" || val == "Polar" || val == "POLAR") m_GraphViewList[i].m_Mode = POLAR;
			}*/

			m_GraphViewList[i].m_Redraw = true;
			//m_GraphViewList[i].PaintNow();
			break;
		}
}

void CGrphCalcDlg::SetGraphBool(CString param, bool val)
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
				
			if(param == "2DFixedGrid")	m_GraphViewList[i].m_FixedGrid = val;
			else if(param == "2DLabels") m_GraphViewList[i].m_Labels = val;
			else if(param == "2DAxis")	m_GraphViewList[i].m_Axis = val;
			else if(param == "2DGrid")	m_GraphViewList[i].m_Grid = val;
			else if(param == "2DCoordinatesPos") m_GraphViewList[i].m_Coords = val;
			
			m_GraphViewList[i].m_Redraw = true;
			//m_GraphViewList[i].PaintNow();
			break;
		}
}


void CGrphCalcDlg::RemoveGraphTab(CString tab)
{
	bool first(true);
	int index(-1);
	
	if(tab.IsEmpty())
		OnGraphRemovegraphtab();
	else{
		for(int i = 0; i < MAXTABS; ++i){	
			if(m_ActiveGraphView[i]){
				if(first){
					first = false;
					index = i;
				}
				
				CTabCtrl* pTab = m_view.GetTabControl();
				TC_ITEM tcItem;				
				tcItem.mask = TCIF_TEXT;
				char *name = new char[15];
				tcItem.pszText = name;
				tcItem.cchTextMax = 15;
				if(pTab->GetItem(m_view.GetPageIndex(&m_GraphViewList[i]) , &tcItem ))				
					if(tcItem.pszText == tab){
						m_view.SetActivePage(&m_GraphViewList[i]);
						OnGraphRemovegraphtab();
						break;
					}
					delete name;
			}
		}
		
		if(i == MAXTABS && tab == "graph"){
			m_view.SetActivePage(&m_GraphViewList[index]);	
			OnGraphRemovegraphtab();
		}
	}
}

void CGrphCalcDlg::RenameGraphTab(CString val)
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i])
			break;
	}
	
	if(i == MAXTABS)
		return;
	
	CGraphTabNameDlg name_dlg;
	
	CTabCtrl* pTab = m_view.GetTabControl();
	TC_ITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = val.GetBuffer(0);
	pTab->SetItem(m_view.GetPageIndex(&m_GraphViewList[i]) , &tcItem );
}

void CGrphCalcDlg::FindGraphArea(bool fAbsolute, long double eq1, long double eq2, long double Xmin, long double Xmax)
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i])
			m_GraphViewList[i].FindArea(eq1, eq2, Xmin, Xmax, fAbsolute);
			break;
	}
}

void CGrphCalcDlg::FindGraphDistance(long double eq1, long double eq2, long double Xmin, long double Xmax)
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i])
			m_GraphViewList[i].FindDistance(eq1, eq2, Xmin, Xmax);
			break;
	}
}

void CGrphCalcDlg::GraphTangentLine(long double eq, long double x)
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i])
			m_GraphViewList[i].TangentLine(eq, x);
			break;
	}
}

void CGrphCalcDlg::Evaluate2DEquation(long double eq, long double x)
{
	int i(0);

	for(i = 0; i < MAXTABS; ++i){
		if(m_view.GetActivePage() == &m_GraphViewList[i])
			break;
	}

	if(i == MAXTABS)
		return;

	long double ans;

	int base = m_Calculator.m_base;
	m_Calculator.m_base = 10;

	CArray<VariableT, VariableT> mmvariables; 
	mmvariables.Add(GetVariable(((m_GraphViewList[i].m_Mode == POLAR) ? "t" : "x") , x));

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(m_Calculator.Compute(m_GraphViewList[i].m_Equations[int(eq)-1].eq, &mmvariables, ans, this->m_hWnd) == SUCCESSFULL){
		CString sX, sA;
		m_Calculator.DecimalToString(sX, x);
		m_Calculator.DecimalToString(sA, ans);
		
		CString head, answer;
		head = "f(" + sX + ") = " + m_GraphViewList[i].m_astrEquationsRaw[int(eq)-1];
		answer = sA;
		m_OutputV.AddEntry(head, answer);
	}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	m_Calculator.m_base = base;
}

#ifndef GRAPHCALC_LIGHT
void CGrphCalcDlg::Evaluate3DEquation(long double eq, long double x, long double y)
{
	if(!Is3DGraphActive())
		return;

	long double ans;
	int base = m_Calculator.m_base;
	m_Calculator.m_base = 10;

	CArray<VariableT, VariableT> mmvariables; 
	mmvariables.Add(GetVariable(((m_3DGraphView->GetGraphModePolar()) ? "t" : "x") , x));
	mmvariables.Add(GetVariable(((m_3DGraphView->GetGraphModePolar()) ? "r" : "y") , y));

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(m_3DGraphView->GetEquation(int(eq)).eq, &mmvariables, ans, this->m_hWnd) == SUCCESSFULL){
		CString sX, sA, sY;
		g_Calculator->DecimalToString(sX, x);
		g_Calculator->DecimalToString(sY, y);
		g_Calculator->DecimalToString(sA, ans);
		
		CString head, answer;
		head = "f(" + sX + "," + sY + ") = " + m_3DGraphView->GetEquation(int(eq)).eq;
		answer = sA;
		m_OutputV.AddEntry(head, answer);
	}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	m_Calculator.m_base = base;
}
#endif

void CGrphCalcDlg::OnFileRunscript() 
{
	static char BASED_CODE szFilter[] = "GraphCalc Script (*.gcs)|*.gcs||";	

	CFileDialog *fileDlg = new CFileDialog(true, 
										   "gcs",
										    NULL,
											OFN_ENABLESIZING 
											| OFN_FILEMUSTEXIST 
											| OFN_HIDEREADONLY 
											| OFN_OVERWRITEPROMPT 
											| OFN_READONLY,
											szFilter,
											this);

	if(fileDlg->DoModal() == IDOK)
		RunScript(fileDlg->GetPathName());

	delete fileDlg;	
}

void CGrphCalcDlg::OnQuitScript()
{
	g_fQuitScript = true;
}

// returns true if valid script, false otherwise
bool CGrphCalcDlg::ParseScript(CString filenameS, CArray<CString, CString> *commands)
{

	::ifstream infile;	
	infile.open(filenameS, ios::nocreate);
	
	if(infile.rdstate() == ios::failbit){
		AfxMessageBox("Error opening script: " + filenameS, MB_OK | MB_ICONEXCLAMATION, 0);
		return false;
	}

	int			line=0;
	int 		nIfCount=0;
	int 		nWhileCount=0;	
	CString 	strError;
	CList<int,int> fElseLevel; // keep track of Else's we have found
	
	// read in all commands
	while(!infile.eof()){		
		char *cline = new char[2048];
		infile.getline(cline, 2048, '\n');
		++line;
		
		if(infile.rdstate() == ios::failbit){
			AfxMessageBox("Error reading script: " + filenameS + ".  The file either does not exist, is locked, or may be damaged", MB_OK | MB_ICONEXCLAMATION, 0);
			delete cline;
			return false;
		}

		CString temp = (LPCTSTR)cline;	
		delete cline;

		temp.TrimRight();
		temp.TrimLeft();
		
		if(!temp.IsEmpty() && temp[0] != '#')
			{
			commands->Add(temp);

			// keep track of if's and while's
			if(IsIfCommand(temp, true))
				++nIfCount;
			else if(IsWhileCommand(temp, true))
				++nWhileCount;
			else if(IsElseIfCommand(temp, true))
				{
				if(!nIfCount)
					{
					strError = "ElseIf without matching If.";
					goto Error;
					}
				else if(fElseLevel.GetCount() && (fElseLevel.GetHead() == nIfCount))
					{
					strError = "ElseIf not allowed after Else.";
					goto Error;
					}
				}
			else if(temp == "Else")
				if(!nIfCount)
					{
					strError = "Else without matching If.";
					goto Error;
					}
				else if(fElseLevel.GetCount() && (fElseLevel.GetHead() == nIfCount))
					{
					strError = "Only 1 Else is allowed per If statement.";
					goto Error;
					}
				else
					fElseLevel.AddHead(nIfCount);
			else if(temp == "EndIf")
				{
				if(fElseLevel.GetCount() && (fElseLevel.GetHead() == nIfCount))
					fElseLevel.RemoveHead();
				--nIfCount;
				}
			else if(temp == "EndWhile")
				--nWhileCount;

			if(nIfCount < 0)
				{
				strError = "EndIf without matching If.";
				goto Error;
				}
			else if(nWhileCount < 0)
				{
				strError = "EndWhile without matching While.";
				goto Error;
				}
			
			}		
	}
	infile.close();

	// make sure we have matching if's and while's, otherwise error out
	if(nIfCount > 0)
		{
		strError = "Missing EndIf.";
		goto Error;
		}
	else if(nIfCount < 0)
		{
		strError = "EndIf without matching If.";
		goto Error;
		}
	else if(nWhileCount > 0)
		{
		strError = "Missing EndWhile.";
		goto Error;
		}
	else if(nWhileCount < 0)
		{
		strError = "EndWhile without matching While.";
		goto Error;
		}

	return true;

	Error:
		CString er;
		er.Format("Line %d: " + strError + "  The script will not be run!", line);
		MessageBox(er,"Script Error", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return false;
}

void CGrphCalcDlg::RunScript(CString filenameS)
{
	if(filenameS.IsEmpty()){
		AfxMessageBox("Script filename is empty.  Unable to run script", MB_OK | MB_ICONEXCLAMATION, 0);
		return;
	}

	m_UpdateDataOnEnter = false;
	CArray<CString, CString> commands;

	// set the current working directory
	CString str_old_dir = GetCurrentDirectory();
	int nPos = filenameS.ReverseFind('\\');
	if(nPos > 0 && filenameS[1] == ':')
		chdir(filenameS.Left(nPos));
	
	if(!ParseScript(filenameS, &commands))
		{
		chdir(str_old_dir);
		return;
		}
	
	// initialize cursor
	if(m_iScriptLevel < 0)
		{
		BeginWaitCursor();
		g_fQuitScript = false;
		}

	// INIT PROGRESS BAR
	bool progress_bar_on(false);

	if(m_fShowScriptProgressDlg && m_iScriptLevel < 0){
		if(m_ScriptProgressBar.Create()){
			//success
			progress_bar_on = true;
		}
	}
	else if(m_ScriptProgressBar.m_hWnd != NULL)
		progress_bar_on = true;
	// END INIT PGOGRESS BAR

	
	double 		count(0.0);
	double 		step(100.0 / double(commands.GetSize()));
	CString 	filename;
	int 		pos;
	int 		nIfCount=0;
	CList<int,int> nWhileStart;	// keep track of the start of the while loops
	CList<bool,bool> bnIfDone;	// keep track if we succeeded in one of the If statements
	
	pos = filenameS.ReverseFind('\\');
	filename = filenameS.Right(filenameS.GetLength() - pos - 1);
	m_ScriptProgressBar.ResetCancel();
	++m_iScriptLevel;

	
	// EXECUTE COMMANDS
	for(int i(0); i < commands.GetSize(); ++i)
		{
		if(commands[i] == "EndIf")
			{
			bnIfDone.RemoveHead();
			--nIfCount;
			continue;
			}
		else if((commands[i] == "Else") && bnIfDone.GetCount() && !bnIfDone.GetHead())
			continue;
		else if(commands[i] == "EndWhile") // jump to begining of While
			i = nWhileStart.RemoveHead();

		ProcessMessages();
		
		if(g_fQuitScript)	// check for cancel
			goto Cancel;
		if(progress_bar_on)	// update progress bar
			{
			if(m_ScriptProgressBar.CheckCancelButton()) // chech for cancel on progress dialog
				{
				m_ScriptProgressBar.SetCancel();
				goto Cancel;
				}

			m_ScriptProgressBar.SetStatus(filename + " : " + commands[i]);
			m_ScriptProgressBar.SetPos(int(count));
			}

		bool 	fIf=false,
			 	fElseIf=false;
		if((fIf = IsIfCommand(commands[i])) || (fElseIf = IsElseIfCommand(commands[i])))
			{
			// handle If
			long double 	answer = 0;
			int 			nTempIfCount=1;
			ErrorT 			etError;

			if(fIf)
				{
				bnIfDone.AddHead(false);
				etError = g_Calculator->Compute(GetIfCondition(commands[i]), answer, this->m_hWnd);
				}
			else if(fElseIf && !bnIfDone.GetHead())
				etError = g_Calculator->Compute(GetElseIfCondition(commands[i]), answer, this->m_hWnd);
			
			if(etError == SUCCESSFULL && answer && !bnIfDone.GetHead())
				{
				++nIfCount;
				bnIfDone.RemoveHead(); // remove the false head and add a true one (ther is no set head so this was easiest)
				bnIfDone.AddHead(true); // we know we are done now, so don't go into any more ElseIf's
				}
			else
				{
				// if it failed or answer < 0 then If fails and we jump past the If
				nTempIfCount = 1;
				for(++i; i < commands.GetSize() && nTempIfCount; ++i)
					{
					if(commands[i] == "EndIf") 
						--nTempIfCount;
					else if(IsIfCommand(commands[i])) 
						++nTempIfCount;
					else if(nTempIfCount == 1 && !bnIfDone.GetHead()
						&& (IsElseIfCommand(commands[i]) || commands[i] == "Else"))
						break;
					}
				--i; // because we have gone to the next item, but the outer for loop
					 // is going to increment i too so we would skip right past it
				}
			}
		else if(IsWhileCommand(commands[i]))
			{
			// handle While
			long double 	answer;
			int 			nTempWhileCount=1;
			if(g_Calculator->Compute(GetWhileCondition(commands[i]), answer, this->m_hWnd) == SUCCESSFULL && answer)
				nWhileStart.AddHead(i);
			else
				{
				// if it failed or answer < 0 then While fails and we jump past the While
				nTempWhileCount = 1;
				for(++i; i < commands.GetSize() && nTempWhileCount; ++i)
					{
					if(commands[i] == "EndWhile") 
						--nTempWhileCount;
					else if(IsWhileCommand(commands[i])) 
						++nTempWhileCount;
					}
				--i; // because we have gone to the next item, but the outer for loop
					 // is going to increment i too so we would skip right past it
				}
			}
		else
			{
			m_Formula = commands[i];
			EvaluateFormula(false);
			}

		count += step;
	}
	// END EXECUTE COMMANDS

Cancel:
	if(progress_bar_on && m_iScriptLevel == 0)
		m_ScriptProgressBar.DestroyWindow();

	if(m_iScriptLevel == 0)
		{
		m_OutputV.m_fOutputWindow = true;
		EndWaitCursor();
		m_UpdateDataOnEnter = true;
		g_fQuitScript = false;
		}

	commands.RemoveAll();
	--m_iScriptLevel;
	chdir(str_old_dir);	
}

int CGrphCalcDlg::GetActiveGraphTabIndex()
{
	for(int i = 0; i < MAXTABS; ++i)
		if(m_view.GetActivePage() == &m_GraphViewList[i]){
			return i;
		}

	return -1;
}

bool CGrphCalcDlg::Is3DGraphActive()
{
#ifndef GRAPHCALC_LIGHT
	if(m_3DGraphView == NULL)
		return false;

	if(m_view.GetActivePage() == m_3DGraphView)
		return true;
#endif

	return false;
}

void CGrphCalcDlg::SaveExpressionHistory()
{
	::ofstream outfile;
	CString CSline;

	chdir(g_strApplicationDirectory);
	outfile.open("expression_history.gcs");
	
	for(int i(0); i < m_FormulaCtrl.GetCount(); ++i){
		CString temp;
		m_FormulaCtrl.GetLBText(i, temp);
		outfile.write(temp.GetBuffer(temp.GetLength()), temp.GetLength());

		char nl('\n');
		outfile.write(&nl, 1);
	}
	
	outfile.close();
}

void CGrphCalcDlg::LoadExpressionHistory()
{
	::ifstream infile;
	CArray<CString, CString> list;
	CString expr;

	chdir(g_strApplicationDirectory);
	infile.open("expression_history.gcs", ios::nocreate);
	
	if(infile.rdstate() == ios::failbit){
		AfxMessageBox("Error opening expression_history.gcs", MB_OK | MB_ICONEXCLAMATION, 0);
		return;
	}
	
	char *line = new char[1000];

	while(!infile.eof()){
		infile.getline(line, 1000, '\n');
		expr = (LPCTSTR)line;
		expr.TrimLeft();
		expr.TrimRight();
		
		if(!expr.IsEmpty())
			list.Add(expr);
	}

	delete line;
	infile.close();

	for(int j(0); j < list.GetSize(); ++j)
		m_FormulaCtrl.AddString(list[j]);
}

void CGrphCalcDlg::SaveAnswerHistory()
{
	::ofstream outfile;
	CString CSline;

	chdir(g_strApplicationDirectory);
	outfile.open("answer_history.gcs");
	
	while(g_Calculator->m_lststrAnswerHistory.GetCount())
	{
		CString temp;
		temp = g_Calculator->m_lststrAnswerHistory.RemoveTail();
		outfile.write(temp.GetBuffer(temp.GetLength()), temp.GetLength());

		char nl('\n');
		outfile.write(&nl, 1);
	}
	
	outfile.close();
}

void CGrphCalcDlg::LoadAnswerHistory()
{
	::ifstream infile;
	CArray<CString, CString> list;
	CString expr;

	chdir(g_strApplicationDirectory);
	infile.open("answer_history.gcs", ios::nocreate);
	
	if(infile.rdstate() == ios::failbit){
		//AfxMessageBox("Error opening answer_history.gcs", MB_OK | MB_ICONEXCLAMATION, 0);
		return;
	}
	
	char *line = new char[1000];

	while(!infile.eof()){
		infile.getline(line, 1000, '\n');
		expr = (LPCTSTR)line;
		expr.TrimLeft();
		expr.TrimRight();
		
		if(!expr.IsEmpty())
			list.Add(expr);
	}

	delete line;
	infile.close();

	for(int j(0); j < list.GetSize(); ++j)
		g_Calculator->AddAnsToHistory(list[j]);
}


bool CGrphCalcDlg::IsActive2DGraph(int i)
{
	return m_ActiveGraphView[i];
}

#include "GrphCalcInclude.h"

void CGrphCalcDlg::OnAppExit() 
{
	SendMessage(WM_CLOSE,0,0);
	m_fEndProg = true;
}
void CGrphCalcDlg::OnClose() 
{
	g_fQuitScript = true;
	m_fEndProg = true;
	
	m_fNotShutdown = false;
	SaveAllSettings();

	if(m_ScriptProgressBar.m_hWnd != NULL)
		m_ScriptProgressBar.DestroyWindow();

	while(m_view.GetPageCount() > 0)
		m_view.RemovePage(0);
	
	CDialog::OnClose();
}

void CGrphCalcDlg::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == VK_ESCAPE)
		return;
	OnKeyDown(nChar, nRepCnt, nFlags) ;
}
void CGrphCalcDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if(nChar == VK_ESCAPE)
		return;
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
	
}

void CGrphCalcDlg::ClearGraphTabsToAdd()
{
	for(int i(0); i < MAXTABS; ++i)
		m_bGraphTabsToAdd[i] = false;
}

/*
Adds the tabs specified by
m_bGraphTabsToAdd to the view
*/
void CGrphCalcDlg::AddGraphTabs()
{
	for(int i = 0; i < MAXTABS; ++i){
		if(m_bGraphTabsToAdd[i]){
			AddGraphTab(i);
			m_bGraphTabsToAdd[i] = false;
		}
	}
}

void CGrphCalcDlg::SaveAllSettings()
{
	BeginWaitCursor();

#ifndef GRAPHCALC_LIGHT
	m_3DGraphView->m_bCalculateEquations = false;
#endif

	if(m_SaveSettings)
		WriteSettings(m_SettingsFile);

	if(m_bSaveExprHistory)
		SaveExpressionHistory();
	if(m_bSaveOutputHistory)
		m_OutputV.SaveOutput();

	SaveAnswerHistory();

	CString dir;
	dir =  g_strApplicationDirectory + "\\graphcalc.ini";
	CWinApp* pApp = AfxGetApp();
	pApp->m_pszProfileName = dir;

	pApp->WriteProfileString("Settings", "file", m_SettingsFile);
	pApp->WriteProfileInt("Settings", "savesettings", m_SaveSettings);

	WINDOWPLACEMENT wnd;
	GetWindowPlacement(&wnd);
	pApp->WriteProfileInt("WindowRect", "left", wnd.rcNormalPosition.left);
	pApp->WriteProfileInt("WindowRect", "right", wnd.rcNormalPosition.right);
	pApp->WriteProfileInt("WindowRect", "top", wnd.rcNormalPosition.top);
	pApp->WriteProfileInt("WindowRect", "bottom", wnd.rcNormalPosition.bottom);

	EndWaitCursor();
}

CString CGrphCalcDlg::GetCurrentDirectory()
{
	char* pth = new char[300];
	DWORD count = 300;
	::GetCurrentDirectory(count, pth);
	CString path;
	path = (LPCTSTR)pth;
	pth = 0;
	return path;
}

void CGrphCalcDlg::Solve(CString expression, long double guess, CString var /*"x"*/)
{
	long double ldAnswer;
	CString strAnswer = "", strEntry;
	strEntry = "'" + expression + "' solved for '" + var + "'";

	// solve
	switch(g_Calculator->EqSolver(expression, var, guess, ldAnswer, strAnswer))
	{
	case UNDEFINED_VALUE:  strAnswer = "error: undefined value";	break;
 	case ZERO_SLOPE: 		strAnswer = "error: zero slope"; 		break;
	case INFINITE_VALUE:	strAnswer = "error: infinite value";	break;
	case NO_ROOTS:			strAnswer = "error: no roots found";	break;
	case SUCCESSFULL:
		{
		g_Calculator->SetPrevAnswerStr(strAnswer);
		g_Calculator->FormatString(strAnswer);

		strAnswer = var + " = " + strAnswer;
		break;
		}
	case INVALID_EQ:		strAnswer = "error: invalid equation";	break;
	case UNKNOWNERR:
	default:				strAnswer = "error: unknown error";
	}

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	m_OutputV.AddEntry(strEntry, strAnswer);
}
	
void CGrphCalcDlg::Graph2DEqIntersection(int eq1, int eq2, long double guess)
	{
	int i = GetActiveGraphTabIndex();

	if(i == -1)
		return;
	
	if(m_GraphViewList[i].m_Mode == POLAR)
		return;
	
	long double ldX, ldY;
	CString strX, strY;
	CString strAnswer = "unknown error", strEntry;

	strEntry = m_GraphViewList[i].m_astrEquationsRaw[eq1] + " = " + m_GraphViewList[i].m_astrEquationsRaw[eq2];
	
	// solve
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	switch(g_Calculator->EqSolver(m_GraphViewList[i].m_Equations[eq1].eq + " = " + m_GraphViewList[i].m_Equations[eq2].eq, "x", guess, ldX, strX))
	{	
	case SUCCESSFULL:
		{
		g_Calculator->SetPrevAnswerStr(strX);
		g_Calculator->FormatString(strX);
		// calculate y
		if(g_Calculator->Compute(m_GraphViewList[i].m_Equations[eq1].eq, "x", ldX, ldY, this->m_hWnd) != SUCCESSFULL)
			break;

		g_Calculator->DecimalToStringSci(strY, ldY);
		g_Calculator->FormatString(strY);

		strAnswer = "x = " + strX + ", y = " + strY;		
		break;
		}
	case UNDEFINED_VALUE: 	strAnswer = "error: undefined value";	break;
	case ZERO_SLOPE: 		strAnswer = "error: zero slope";		break;	
	case INFINITE_VALUE:	strAnswer = "error: infinite value";	break;
	case INVALID_EQ:		strAnswer = "error: invalid equation";	break;		
	case NO_ROOTS:
	case UNKNOWNERR:
	default:				strAnswer = "error: no intersection found";
	}

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	m_OutputV.AddEntry(strEntry, strAnswer);
	}

void CGrphCalcDlg::Graph2DXIntercept(int eq, long double guess)
	{
	int i = GetActiveGraphTabIndex();

	if(i == -1)
		return;
	
	if(m_GraphViewList[i].m_Mode == POLAR)
		return;
	
	long double ldAnswer;
	CString strAnswer = "unknown error", strEntry;
	strEntry = "f(x) = " + m_GraphViewList[i].m_astrEquationsRaw[eq];

	// solve
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	switch(g_Calculator->EqSolver(m_GraphViewList[i].m_Equations[eq].eq, "x", guess, ldAnswer, strAnswer))
	{
	case UNDEFINED_VALUE:	strAnswer = "error: undefined value";	break;
	case ZERO_SLOPE:		strAnswer = "error: zero slope";		break;	
	case INFINITE_VALUE:	strAnswer = "error: infinite value";	break;
	case NO_ROOTS:			strAnswer = "error: no roots found";	break;			
	case SUCCESSFULL:
		{
		g_Calculator->SetPrevAnswerStr(strAnswer);
		g_Calculator->FormatString(strAnswer);
		strAnswer = "root found at: x = " + strAnswer;
		break;
		}
	case INVALID_EQ:		strAnswer = "error: invalid equation";	break;		
	case UNKNOWNERR:
	default:				strAnswer = "error: unknown error";
	}

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	m_OutputV.AddEntry(strEntry, strAnswer);
	}
void CGrphCalcDlg::Graph2DYIntercept(int eq)
	{
	int i = GetActiveGraphTabIndex();

	if(i == -1)
		return;
	
	if(m_GraphViewList[i].m_Mode == POLAR)
		return;
	
	long double ldAnswer;
	CString strAnswer = "unknown error", strEntry;
	strEntry = "f(x)=" + m_GraphViewList[i].m_astrEquationsRaw[eq];

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(m_GraphViewList[i].m_Equations[eq].eq, "x", 0, ldAnswer, this->m_hWnd) != SUCCESSFULL)
		{
		m_OutputV.AddEntry(strEntry, "error: invalid equation");
		return;
		}

	g_Calculator->DecimalToStringSci(strAnswer, ldAnswer);
	if(strAnswer != "overflow")
		{
		g_Calculator->SetPrevAnswerStr(strAnswer);
		g_Calculator->FormatString(strAnswer);
		strAnswer = " intersection found at: y = " + strAnswer;
		}
	else
		strAnswer = "no intersection with y-axis";

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	m_OutputV.AddEntry(strEntry, strAnswer);
	}

void CGrphCalcDlg::Graph2DStationaryPoint(int eq, long double lbound, long double ubound)
	{
	int i = GetActiveGraphTabIndex();
	if(i == -1)
		return;
	
	if(m_GraphViewList[i].m_Mode == POLAR)
		return;

	int minmax;
	long double ldAnswer;
	CString strAnswer, strX, strEntry, strLBound, strUBound;
	
	g_Calculator->DecimalToStringSci(strLBound, lbound);
	g_Calculator->FormatString(strLBound);
	g_Calculator->DecimalToStringSci(strUBound, ubound);
	g_Calculator->FormatString(strUBound);
	
	strEntry = "f(x) = " + m_GraphViewList[i].m_astrEquationsRaw[eq] + " lower bound=" + strLBound + " upper bound=" + strUBound;

	// solve
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	switch(g_Calculator->MinMaxSolverBisection(m_GraphViewList[i].m_Equations[eq].eq, "x", lbound, ubound, ldAnswer, strX, minmax))
	{
	case UNDEFINED_VALUE:	strAnswer = "error: undefined value";	break;
	case INFINITE_VALUE:	strAnswer = "error: infinite value";	break;	
	case NO_ROOTS:			strAnswer = "no stationary points found";     break;		
	case SUCCESSFULL:
		{
		g_Calculator->SetPrevAnswerStr(strX);
		g_Calculator->FormatString(strX);

		long double ans;
		CString strY;
		
		g_Calculator->Compute(m_GraphViewList[i].m_Equations[eq].eq, "x", ldAnswer, ans, this->m_hWnd);
		g_Calculator->DecimalToStringSci(strY, ans);
		g_Calculator->FormatString(strY);

		if(minmax != 0)
			{
			if(minmax > 0)
				strAnswer = "maximum found at: ";
			else if(minmax < 0)
				strAnswer = "minimum found at: ";

			strAnswer = strAnswer + "x = " + strX + ", y = " + strY;
			}
		else
			strAnswer =  "error determining minimum or maximum";			
			
		break;
		}
	case INVALID_EQ:	strAnswer =  "error: invalid equation";	break;		
	case UNKNOWNERR:
	default:			strAnswer =  "error: unknown error";
	}

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	m_OutputV.AddEntry(strEntry, strAnswer);	
}

void CGrphCalcDlg::Graph2DDyDx(int eq, long double x)
{
	int i = GetActiveGraphTabIndex();
	if(i == -1)
		return;
	
	if(m_GraphViewList[i].m_Mode == POLAR)
		return;

	CString strAnswer = m_GraphViewList[i].m_EuclideanGraph.GetDyDxStr(m_GraphViewList[i].m_Equations[eq].eq, x);
	CString strEntry;
	strEntry.Format("D(" + m_GraphViewList[i].m_Equations[eq].eq + ")/Dx   at x=%f", x);
	m_OutputV.AddEntry(strEntry, strAnswer);
}


void CGrphCalcDlg::LoadScriptLibrary()
{
	m_aScripts.name = g_strApplicationDirectory + "\\scripts";
	ReadScriptDIR(m_aScripts, g_strApplicationDirectory + "\\scripts");

	if(m_fShowScriptLibrary)
		{
		m_MenuScripts.CreateMenu();
		int pos = script_start;
		CreateScriptMenu(pos, m_MenuScripts, m_aScripts);
		}
}

void CGrphCalcDlg::ReadScriptDIR(ScriptsT &scripts, CString dir)
{
	CFileFind finder;

	if(0 > _chdir(dir))
		return; // directory doesn't exist
	
	// find scripts in current directory
	BOOL bWorking = finder.FindFile("*.gcs");
	while (bWorking)
    {
      bWorking = finder.FindNextFile();
      scripts.entries.Add(finder.GetFileName());
      m_fShowScriptLibrary = true;
    }
	finder.Close();

	// search for subdirectories and get scripts in there
	int subs=0;
	
	bWorking = finder.FindFile("*");
	while (bWorking)
    {
      bWorking = finder.FindNextFile();
	  if(finder.IsDirectory() && !finder.IsDots())
	  	{
	      scripts.sub_menu.SetSize(subs+1,1);
	      scripts.sub_menu[subs].name = dir+"\\"+finder.GetFileName();
	      ReadScriptDIR(scripts.sub_menu[subs], scripts.sub_menu[subs].name);
    	  ++subs;
	  	}
    }
	finder.Close();	
}

void CGrphCalcDlg::CreateScriptMenu(int &pos, CMenu &menu, ScriptsT &scripts)
{
	int num_entries(0);
	bool sub_menu(false);
	CMenu pSub;
	pSub.CreatePopupMenu();

	// check for sub menus
	for(int i = 0; i < scripts.sub_menu.GetSize(); ++i)
		{
		sub_menu = true;
		CreateScriptMenu(pos, pSub, scripts.sub_menu[i]);
		}
		
	// check for scripts in this level
	num_entries = scripts.entries.GetSize();
	CGCCommand cmd;
	cmd.SetControls(&m_Calculator);
		
	for(int j = 0; j < num_entries; ++j){
		// get name of script
		CString script_name;
		::ifstream infile;
		CString CSline;
		
		infile.open(scripts.name+"\\"+scripts.entries[j], ios::nocreate);
			
		char *cline = new char[100];
		infile.getline(cline, 1000, '\n');
		CSline = (LPCTSTR)cline;
		CSline.TrimLeft();

		if(!CSline.IsEmpty() && CSline[0] == '#')
			script_name = CSline.Right(CSline.GetLength() - 1);
		else if(!cmd.GetComment(CSline, script_name))
			script_name = scripts.entries[j];
					
		infile.close();
		delete cline;
		
		// set menu item
		pSub.AppendMenu(MF_STRING, pos, script_name);
		++pos;
	}
	
	if(num_entries > 0 || sub_menu){
		CString pop_name;
		pop_name = scripts.name.Right(scripts.name.GetLength() - scripts.name.ReverseFind('\\') - 1);
		
		menu.AppendMenu(MF_STRING | MF_POPUP | MF_ENABLED, (UINT)pSub.m_hMenu, pop_name);
		pSub.Detach();
	}
}

void CGrphCalcDlg::AddScriptLibraryMenu(CMenu &menu, int tools_position)
{
	if(!m_fShowScriptLibrary)
		return;
	
	CMenu *tools=menu.GetSubMenu(tools_position);
	tools->InsertMenu(1, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)m_MenuScripts.GetSubMenu(0)->m_hMenu, "Script Library");
	tools->Detach();
}

void CGrphCalcDlg::EvaluateFormula(CString formula, bool auto_change_tabs/*true*/)
{
	m_Formula = formula;
	EvaluateFormula(auto_change_tabs);
}

void CGrphCalcDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}


LRESULT CGrphCalcDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	return CDialog::DefWindowProc(message, wParam, lParam);
}

#ifdef STRESS_TEST
void CGrphCalcDlg::StressTestCalculator()
{
	//ErrorT et;
	CString str = "53498758.987895098", strAns;
	long double answer;
	for(int i=0; i < 5000; ++i)
		{
		//g_Calculator->ClearEqHistory();

		//g_Calculator->IsValid("x^2+3*x/4+5-x", this->m_hWnd);

		//g_Calculator->Compute("x^2+3*x/4+5-x", "x", i, answer, this->m_hWnd);
		//g_Calculator->Compute("897^2+3*54/4+5-213", answer, this->m_hWnd);
		//g_Calculator->Compute("3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3", answer, this->m_hWnd);
		//g_Calculator->Compute("3+3+3+3+3+3+3+3+3", answer, this->m_hWnd);
		//g_Calculator->DecimalToString(str, answer);

		//g_Calculator->EqSolver("4=sqrt(x^2+y^2)", "y", 1, answer, strAns);
		
		}
}
#endif

